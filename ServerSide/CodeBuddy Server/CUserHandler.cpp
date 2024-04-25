#include "CUserHandler.h"

ServerMessageContainer CUserHandler::getSendResponseForLogin()
{
    return ServerMessageContainer('l', "accepted");
}
