#pragma once
#include <vector>
#include <map>
#include "ServerMessageContainer.h"
#include "CLessonHandler.h"

class CLessonManager
{
private:
	std::vector<CLessonHandler*> lessons;
	int lessonsDone;
public:
	CLessonManager(char lessonsDone, std::vector<std::string> titles);

	CLessonHandler& getLesson(const std::string& lessonName) const;
	CLessonHandler& getLesson(int index) const;
	int getLessonsDone() const;
	int getLessonsNumber() const;

	ServerMessageContainer getSendMessageTitles();

	void addLessonDone();

	~CLessonManager();
};

