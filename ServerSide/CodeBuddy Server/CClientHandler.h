#pragma once
#include "CUserHandler.h"
#include "Constraints.h"
#include "CLessonManager.h"
#include <map>

class CClientHandler
{
private:
	CUserHandler* userHandler{nullptr};
	std::map<std::string, CLessonManager*> lessons;	//[LIMBAJ] = LessonManager
public:
	~CClientHandler();
	std::string handleRequest(char request[MAX_BUFFER_LEN]);

	void setLessonTileDone(int LessonsDone, std::vector<std::string> lessonTitles, const std::string& language);

	CUserHandler& getUserHandler() const;
	CLessonManager& getLanguage(const std::string& language);
	bool existsLesson(const std::string& language);
	bool existsContent();
};

