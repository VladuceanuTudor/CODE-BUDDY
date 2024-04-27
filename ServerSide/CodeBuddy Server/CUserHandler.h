#pragma once
#include <string>
#include <vector>
#include "ServerMessageContainer.h"

class CUserHandler
{
private:
	std::string username{};
	int xp{};
	int lives{};
public:
	CUserHandler() {}
	CUserHandler(std::string username, int xp, int lives)
		: username{username}
		, xp{xp}
		, lives{lives}
	{}
	std::string getUsername() const { return this->username; }
	int getXp() const;
	ServerMessageContainer getSendResponseForLogin();
};

