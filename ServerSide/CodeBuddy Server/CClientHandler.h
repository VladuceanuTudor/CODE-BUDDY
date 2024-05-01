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
public:
	CClientHandler(SOCKET sock) : userSocket(sock) {}
	~CClientHandler();
	std::string handleRequest(char request[MAX_BUFFER_LEN]);

	void setLessonTileDone(int LessonsDone, std::vector<std::string> lessonTitles, const std::string& language);

	ServerMessageContainer sendExercices(std::string request);

	CUserHandler& getUserHandler() const;
	CLessonManager& getLanguage(const std::string& language);
	bool existsLesson(const std::string& language);

	void sendExercices();
};

