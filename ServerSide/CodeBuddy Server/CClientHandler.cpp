#include "CClientHandler.h"
#include "ServerMessageContainer.h"
#include "SDataBase.h"

std::string CClientHandler::handleRequest(char request[MAX_BUFFER_LEN])
{
    ServerMessageContainer procRequest(request);
    ServerMessageContainer sendBuffer('E', "FailHandle");   //In cazul in care sendBuffer nu se modifica, inseamnca ca a aparut o problema
    switch (procRequest.getType())
    {
    case 'l':
    {
        bool logged = SDataBase::getInstance().processLoginRequest(procRequest.getMess());
        if (logged)
        {
            this->userHandler = SDataBase::getInstance().getUserInfo(procRequest.getMess());
            sendBuffer = this->userHandler->getSendResponseForLogin();
        }
        else
        {
            sendBuffer = ServerMessageContainer('l', "fail");
        }
    }
        break;
    case 'r':
        sendBuffer = SDataBase::getInstance().processRegisterRequest(procRequest.getMess());
        break;
    case 'b':
        sendBuffer = SDataBase::getInstance().processGetLessonsTitleRequest(procRequest.getMess(), this);
        break;
    case 'L':
        sendBuffer = SDataBase::getInstance().processGetLessonContent(procRequest.getMess(), this);
        break;
    case 'e':
        sendBuffer = ServerMessageContainer('e', "To be done...");
        break;
    default:
        ServerMessageContainer errorBuffer('E', "Invalid Option given.");
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
