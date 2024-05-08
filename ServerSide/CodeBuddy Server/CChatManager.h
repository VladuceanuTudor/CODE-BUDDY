#pragma once
#include <string>
#include <map>
#include <vector>
#include "ServerMessageContainer.h"

class CChatManager
{
private:
	std::map<std::pair<std::string, std::string>, std::vector<std::string>> chat;	//Username = std::vector<Messages>

public:
	CChatManager();
	~CChatManager();
	ServerMessageContainer getMessages(const std::string& userSending, const std::string& userRecieving);
	void addMessage(const std::string& userSending, const std::string& userRecieving, const std::string& message);

};

