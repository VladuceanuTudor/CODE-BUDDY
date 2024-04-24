#pragma once
#include "CUserHandler.h"
#include "Constraints.h"

class CClientHandler
{
private:
	CUserHandler userHandler;
public:
	std::string handleRequest(char request[MAX_BUFFER_LEN]);
};

