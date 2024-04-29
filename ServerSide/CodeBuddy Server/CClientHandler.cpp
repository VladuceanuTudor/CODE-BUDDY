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

    return ServerMessageContainer(LESSON_DONE_CODE, "ok");
}

std::string CClientHandler::handleRequest(char request[MAX_BUFFER_LEN])
{
    ServerMessageContainer procRequest(request);
    ServerMessageContainer sendBuffer(ERROR_CODE, "FailHandle");   //In cazul in care sendBuffer nu se modifica, inseamna ca a aparut o problema
    switch (procRequest.getType())
    {
    case GET_LOGIN_CODE:
    {
        bool logged = SDataBase::getInstance().processLoginRequest(procRequest.getMess());
        if (logged)
        {
            this->userHandler = SDataBase::getInstance().getUserInfo(procRequest.getMess());
            sendBuffer = ServerMessageContainer(GET_LOGIN_CODE, "accepted");
        }
        else
        {
            sendBuffer = ServerMessageContainer(GET_LOGIN_CODE, "fail");
        }
    }
        break;
    case REGISTER_CODE:
        sendBuffer = SDataBase::getInstance().processRegisterRequest(procRequest.getMess());
        break;
    case GET_LESSON_TITLES_CODE:
        sendBuffer = SDataBase::getInstance().processGetLessonsTitleRequest(procRequest.getMess(), this);
        break;
    case GET_LESSON_CONTENT:
        sendBuffer = SDataBase::getInstance().processGetLessonContent(procRequest.getMess(), this);
        break;
    case GET_EXERCICE_CODE:
        sendBuffer = this->sendExercices(procRequest.getMess());
        break;
    case LESSON_DONE_CODE:
        sendBuffer = this->updateLessonDone(procRequest.getMess());
        break;
    case GET_LEADERBOARD_CODE:
        sendBuffer = SDataBase::getInstance().processLeadearboardRequest(procRequest.getMess(), this);
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
