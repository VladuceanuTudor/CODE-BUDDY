#include "CClientHandler.h"
#include "ServerMessageContainer.h"
#include "SDataBase.h"

std::string CClientHandler::handleRequest(char request[MAX_BUFFER_LEN])
{
    ServerMessageContainer procRequest(request);
    ServerMessageContainer sendBuffer;
    switch (procRequest.getType())
    {
    case 'l':
        sendBuffer = SDataBase::processLoginRequest(procRequest.getMess());
        this->userHandler = SDataBase::getUserInfo(procRequest.getMess());
        break;
    case 'r':
        sendBuffer = SDataBase::processRegisterRequest(procRequest.getMess());
        break;
    case 'b':
        sendBuffer = SDataBase::processGetLessonsRequest(procRequest.getMess());
        break;

    default:
        ServerMessageContainer errorBuffer('E', "Invalid Option given.");
        return errorBuffer.getWholeString();
    }
    return sendBuffer.getWholeString();
}
