#pragma once
#include "CUserHandler.h"
#include "Constraints.h"
#include "CLessonManager.h"
#include <WinSock2.h>
#include <map>

class CClientHandler
{
private:
	SOCKET userSocket;
	CUserHandler* userHandler{nullptr};
	std::map<std::string, CLessonManager*> lessons;	//[LIMBAJ] = LessonManager

	ServerMessageContainer updateLessonDone(const std::string& request);

	void processDailyLogin();
	ServerMessageContainer successLogin();
	ServerMessageContainer processGetLessonsTitleRequest(std::string request);
	ServerMessageContainer processGetLessonContent(std::string request);
	ServerMessageContainer handleLives(const std::string& request);
	ServerMessageContainer handlePremiumPayment(const std::string& request);
	ServerMessageContainer processLoginRequest(const std::string& request);
	ServerMessageContainer processChatSendMessage(const std::string& request);
	ServerMessageContainer processGetChatWithUser(const std::string& request);
public:
	CClientHandler(SOCKET sock) : userSocket(sock) {}
	~CClientHandler();
	ServerMessageContainer handleRequest(char request[MAX_BUFFER_LEN]);

	void setLessonTileDone(int LessonsDone, std::vector<std::string> lessonTitles, const std::string& language);

	ServerMessageContainer sendExercices(std::string request);

	CUserHandler& getUserHandler() const;
	CLessonManager& getLanguage(const std::string& language);
	bool existsLesson(const std::string& language);
};

