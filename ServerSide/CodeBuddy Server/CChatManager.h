#pragma once
#include <string>
#include <map>
#include <vector>
#include "ServerMessageContainer.h"

class CChatManager
{
private:
	std::map<std::string, std::vector<std::string>> chat;	//Username = std::vector<Messages>

public:
	CChatManager();
	~CChatManager();
	ServerMessageContainer getMessages(const std::string& username);
	void addMessage(const std::string& username, const std::string& message);

};

