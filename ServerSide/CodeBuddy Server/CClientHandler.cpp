#include "CClientHandler.h"
#include "ServerMessageContainer.h"
#include "SDataBase.h"
#include "CWordSeparator.h"
#include "CTCPServer.h"

ServerMessageContainer CClientHandler::sendExercices(std::string request)
{
    std::vector<std::string> words = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);
    //words[0] = LessonName
    //words[1] = Language
    for (const auto& it : this->getLanguage(words[1]).getLesson(words[0]).getExercices())
    {
        CTCPServer::sendData(it->getSendData(), this->userSocket);
        Sleep(100);
    }
    
    return ServerMessageContainer(GET_EXERCICE_CODE, "Done");
}

ServerMessageContainer CClientHandler::updateLessonDone(const std::string& request)
{
    //request = LIMBAJ TITLU_LECTIE
    std::vector<std::string> inputs = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);
    if (this->lessons[inputs[0]]->getLesson(this->lessons[inputs[0]]->getLessonsDone() - 1).getTitle() == inputs[1])
    {
        this->lessons[inputs[0]]->addLessonDone();
        SDataBase::getInstance().updateLessonsDone(this, inputs[0]);
    }

    this->userHandler->addXP(this->lessons[inputs[0]]->getLesson(inputs[1]).getXp());
    SDataBase::getInstance().updateUserXp(this->userHandler->getUsername(), this->userHandler->getXp());

    return ServerMessageContainer(LESSON_DONE_CODE, "ok");
}

ServerMessageContainer CClientHandler::successLogin()
{
    std::vector<std::string> sendData = { "accepted", this->userHandler->getUsername() };
    return ServerMessageContainer(GET_LOGIN_CODE, CWordSeparator::encapsulateWords(sendData, PAYLOAD_DELIM));
}

std::vector<std::string> getColumn(std::vector<std::vector<std::string>> mat, int i)
{
    std::vector<std::string> column;
    for (const auto& row : mat) {
        if (!row.empty()) {
            column.push_back(row[i]);
        }
    }
    return column;
}

ServerMessageContainer CClientHandler::processGetLessonsTitleRequest(std::string request)
{
    SDataBase& DB = SDataBase::getInstance();
    if (!this->existsLesson(request))
    {

        std::vector<std::string> selects; selects.push_back("LessonTitle");
        std::vector<std::vector<std::string>> cols = DB.selectFromDatabase(selects, "Lessons", "Language = \'" + request + "\'", "LessonNumber");

        std::string buffer = "LessonsDone" + request;
        selects.clear();
        selects.push_back(buffer);
        std::string lessonsDone = DB.selectFromDatabase(selects, "Users", "Username = \'" + this->getUserHandler().getUsername() + "\'")[0][0];

        this->setLessonTileDone(std::stoi(lessonsDone), getColumn(cols, 0), request);
    }

    return this->getLanguage(request).getSendMessageTitles();
}

ServerMessageContainer CClientHandler::processGetLessonContent(std::string request)
{
    SDataBase& DB = SDataBase::getInstance();
    std::vector<std::string> words = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);

    if (this->getLanguage(words[1]).getLesson(words[0]).getFilename().empty())
    {
        std::vector<std::string> selects = { "Language", "Filename", "XpGiven" };
        std::vector<std::vector<std::string>> cols = DB.selectFromDatabase(selects, "Lessons", "LessonTitle = \'" + words[0] + "\'");
        for (const auto& it : cols)
        {
            if (it[0] == words[1])  //Punem Lectia cu care vrem sa lucram pe prima pozitie
            {
                cols[0] = it;
                break;
            }
        }

        this->getLanguage(words[1]).getLesson(words[0]).setFilename(cols[0][1]);
        this->getLanguage(words[1]).getLesson(words[0]).extractExercices();
        this->getLanguage(words[1]).getLesson(words[0]).setXp(std::stoi(cols[0][2]));
    }

    return this->getLanguage(words[1]).getLesson(words[0]).getSendMessage();
}

ServerMessageContainer CClientHandler::handleLives(const std::string& request)
{
    if (this->userHandler->isPremium())
    {
        return ServerMessageContainer(GET_LIVES_CODE, std::to_string(MAX_LIVES + 1));
    }

    SDataBase& DB = SDataBase::getInstance();
    std::vector<std::string> selects = { "Lives", "DATEDIFF(MINUTE, LivesTimeLost, GETDATE()) AS Minutes" };
    std::vector<std::vector<std::string>> cols = DB.selectFromDatabase(selects, "Users", "Username = \'"
        + this->userHandler->getUsername() + "\'");

    int minutes = std::stoi(cols[0][1]);

    ServerMessageContainer message{};
    while (this->userHandler->getLives() < MAX_LIVES &&
        minutes >= LIVES_REGEN_INTERVAL)
    {
        this->userHandler->addLives(1);
        minutes -= LIVES_REGEN_INTERVAL;
    }

    if (request == "0")
    {
        message = ServerMessageContainer(GET_LIVES_CODE, std::to_string(this->userHandler->getLives()));
    }
    else if (request == "1")
    {
        if (this->userHandler->getLives() == MAX_LIVES)
        {
            DB.updateIntoDatabase("Users", "LivesTimeLost", "GETDATE()", "Username = \'" + this->userHandler->getUsername() + "\'", true);
        }
        this->userHandler->subtractLives();

        message = ServerMessageContainer(GET_LIVES_CODE, std::to_string(this->userHandler->getLives()));
    }
    DB.updateIntoDatabase("Users", "Lives", std::to_string(this->userHandler->getLives()),
        "Username = \'" + this->userHandler->getUsername() + "\'");

    return message;
}

ServerMessageContainer CClientHandler::handlePremiumPayment(const std::string& request)
{
    SDataBase& DB = SDataBase::getInstance();
    switch (DB.processPremiumPayment(request, this->userHandler->getUsername()))
    {
    case 0:
        this->userHandler->makePremium();
        return ServerMessageContainer(GET_PAYMENT_CODE, "success");
    case 1:
        return ServerMessageContainer(GET_PAYMENT_CODE, "Insufficient Funds");
    case 2:
        return ServerMessageContainer(GET_PAYMENT_CODE, "Incorrect Data");
    }
}

ServerMessageContainer CClientHandler::processLoginRequest(const std::string& request)
{
    //request = EMAIL PASSWORD
    SDataBase& DB = SDataBase::getInstance();

    std::vector<std::string> inputs;
    inputs = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);

    if (CTCPServer::getInstance().existsMail(inputs[0]))//Verificam daca exista deja utilizatorul conectat
    {
        return ServerMessageContainer(GET_LOGIN_CODE, "User Already Connected");
    }

    CTCPServer::getInstance().addMail(this->userSocket, inputs[0]);

    std::vector<std::string> selects = { "Email", "Password" };
    std::vector<std::vector<std::string>> cols = DB.selectFromDatabase(selects, "Users", "Email = \'" + inputs[0] + "\'");

    if (cols[0][0] != inputs[0] || cols[0][1] != inputs[1])
    {
        return ServerMessageContainer(GET_LOGIN_CODE, "Invalid Credentials");
    }
    this->userHandler = SDataBase::getInstance().getUserInfo(inputs[0]);
    this->processDailyLogin();
    return this->successLogin();
}

std::string CClientHandler::handleRequest(char request[MAX_BUFFER_LEN])
{
    ServerMessageContainer procRequest(request);
    ServerMessageContainer sendBuffer(ERROR_CODE, "FailHandle");   //In cazul in care sendBuffer nu se modifica, inseamna ca a aparut o problema
    switch (procRequest.getType())
    {
    case GET_LOGIN_CODE:
        sendBuffer = this->processLoginRequest(procRequest.getMess());
        break;
    case REGISTER_CODE:
        sendBuffer = SDataBase::getInstance().processRegisterRequest(procRequest.getMess());
        break;
    case GET_LESSON_TITLES_CODE:
        //sendBuffer = SDataBase::getInstance().processGetLessonsTitleRequest(procRequest.getMess(), this);
        sendBuffer = this->processGetLessonsTitleRequest(procRequest.getMess());
        break;
    case GET_LESSON_CONTENT:
        //sendBuffer = SDataBase::getInstance().processGetLessonContent(procRequest.getMess(), this);
        sendBuffer = this->processGetLessonContent(procRequest.getMess());
        break;
    case GET_EXERCICE_CODE:
        sendBuffer = this->sendExercices(procRequest.getMess());
        break;
    case LESSON_DONE_CODE:
        sendBuffer = this->updateLessonDone(procRequest.getMess());
        break;
    case GET_LEADERBOARD_CODE:
        sendBuffer = SDataBase::getInstance().processLeadearboardRequest(procRequest.getMess(), this->userHandler->getUsername(), this->userHandler->getXp());
        break;
    case GET_LIVES_CODE:
        //sendBuffer = SDataBase::getInstance().handleLives(procRequest.getMess(), this);
        sendBuffer = this->handleLives(procRequest.getMess());
        break;
    case GET_PAYMENT_CODE:
        sendBuffer = this->handlePremiumPayment(procRequest.getMess());
        break;
    default:
        ServerMessageContainer errorBuffer(ERROR_CODE, "Invalid Option given.");
        return errorBuffer.getWholeString();
    }
    return sendBuffer.getWholeString();
}

CClientHandler::~CClientHandler()
{
    if (this->userHandler)
        delete this->userHandler;
    for (const auto& it : this->lessons)
        if(it.second)
            delete it.second;
}

CUserHandler& CClientHandler::getUserHandler() const
{
    if (!this->userHandler)
    {
        exit(-1);
    }
    return *this->userHandler;
}

CLessonManager& CClientHandler::getLanguage(const std::string& language)
{
    return *this->lessons[language];
}

bool CClientHandler::existsLesson(const std::string& language)
{
    return this->lessons.find(language) != this->lessons.end();
}

void CClientHandler::setLessonTileDone(int LessonsDone, std::vector<std::string> lessonTitles, const std::string& language)
{
    this->lessons[language] = new CLessonManager(LessonsDone, lessonTitles);
}

void CClientHandler::processDailyLogin()
{
    int lastDaysLogin = SDataBase::getInstance().getLastDayLogin(this->userHandler->getUsername());

    if (lastDaysLogin > 0)
    {
        this->userHandler->addXP(DAILY_XP_GIVEN);
        SDataBase::getInstance().updateUserXp(this->userHandler->getUsername(), this->userHandler->getXp());
    }
}
