#include "CChatManager.h"
#include "Constraints.h"
#include "CWordSeparator.h"

CChatManager::CChatManager()
{

}

CChatManager::~CChatManager()
{
}

ServerMessageContainer CChatManager::getMessages(const std::string& username)
{
	if (this->chat.find(username) == this->chat.end())
		return ServerMessageContainer(GET_NEW_MESSAGES_CODE, "");
	std::string toSend = CWordSeparator::encapsulateWords(this->chat[username], PAYLOAD_DELIM);
	this->chat[username].clear();
	this->chat.erase(username);
	return ServerMessageContainer(GET_NEW_MESSAGES_CODE, toSend);
}

void CChatManager::addMessage(const std::string& username, const std::string& message)
{
	this->chat[username].push_back(message);
}
