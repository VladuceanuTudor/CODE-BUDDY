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
	bool premiumUser = false;
public:
	CUserHandler() {}
	CUserHandler(std::string username, int xp, int lives, bool premiumUser)
		: username{username}
		, xp{xp}
		, lives{lives}
		, premiumUser{premiumUser}
	{}
	std::string getUsername() const { return this->username; }
	void subtractLives();
	void makePremium();
	bool isPremium() const;
	void addLives(int i);
	int getLives() const { return this->lives; }
	void addXP(int xp);
	int getXp() const { return this->xp; }
};

