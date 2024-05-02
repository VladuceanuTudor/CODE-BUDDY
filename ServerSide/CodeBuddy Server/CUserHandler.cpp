#include "CUserHandler.h"

void CUserHandler::subtractLives()
{
	this->lives--;
}

void CUserHandler::addLives(int i)
{
	this->lives +=i ;
}

void CUserHandler::addXP(int xp)
{
	this->xp += xp;
}

void CUserHandler::makePremium()
{
	this->premiumUser = true;
}

bool CUserHandler::isPremium() const
{
	return this->premiumUser;
}
