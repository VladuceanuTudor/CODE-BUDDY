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
            sendBuffer = this->userHandler.getSendResponseForLogin();
        }
    }
        break;
    case 'r':
        sendBuffer = SDataBase::getInstance().processRegisterRequest(procRequest.getMess());
        break;
    case 'b':
        sendBuffer = SDataBase::getInstance().processGetLessonsTitleRequest(procRequest.getMess());
        break;

    default:
        ServerMessageContainer errorBuffer('E', "Invalid Option given.");
        return errorBuffer.getWholeString();
    }
    return sendBuffer.getWholeString();
}
