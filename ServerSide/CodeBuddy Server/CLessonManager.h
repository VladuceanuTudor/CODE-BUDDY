#pragma once
#include <vector>
#include <map>
#include "ServerMessageContainer.h"
#include "CLessonHandler.h"

class CLessonManager
{
private:
	std::vector<CLessonHandler*> lessons;
	char lessonsDone;
public:
	CLessonManager(char lessonsDone, std::vector<std::string> titles);

	CLessonHandler& getLesson(const std::string& lessonName) const;

	ServerMessageContainer getSendMessageTitles();

	~CLessonManager();
};

