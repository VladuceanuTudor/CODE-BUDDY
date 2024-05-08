#include "CChatManager.h"
#include "Constraints.h"
#include "CWordSeparator.h"

CChatManager::CChatManager()
{

}

CChatManager::~CChatManager()
{
}

ServerMessageContainer CChatManager::getMessages(const std::string& userSending, const std::string& userRecieving)
{
	std::pair<std::string, std::string> pairChat = std::make_pair(userSending, userRecieving);
	if (this->chat.find(pairChat) == this->chat.end())
		return ServerMessageContainer(GET_NEW_MESSAGES_CODE, "");
	std::string toSend = CWordSeparator::encapsulateWords(this->chat[pairChat], PAYLOAD_DELIM);
	this->chat[pairChat].clear();
	this->chat.erase(pairChat);
	return ServerMessageContainer(GET_NEW_MESSAGES_CODE, toSend);
}

void CChatManager::addMessage(const std::string& userSending, const std::string& userRecieving, const std::string& message)
{
	this->chat[std::make_pair(userSending, userRecieving)].push_back(message);
}
