#include "CLessonManager.h"
#include "Constraints.h"
#include "CWordSeparator.h"

CLessonManager::CLessonManager(char lessonsDone, std::vector<std::string> titles)
{
	this->lessonsDone = lessonsDone;

	for (int i = 0; i < titles.size(); i++)
	{
		this->lessons.push_back(new CLessonHandler(titles[i]));
	}
}

ServerMessageContainer CLessonManager::getSendMessageTitles()
{
	std::string lessonsDone{};
	lessonsDone += this->lessonsDone;
	std::vector<std::string>toSend = {lessonsDone};
	for (int i = 0; i < this->lessons.size(); i++)
	{
		toSend.push_back(this->lessons[i]->getTitle());
	}

	return ServerMessageContainer(GET_LESSON_TITLES_CODE, CWordSeparator::encapsulateWords(toSend, PAYLOAD_DELIM));
}


CLessonManager::~CLessonManager()
{
	for (const auto& it : this->lessons)
		if (it)
			delete it;

}

CLessonHandler& CLessonManager::getLesson(const std::string& lessonName) const
{
	for (int i = 0; i < this->lessons.size(); i++)
		if (this->lessons[i]->getTitle() == lessonName)
			return *this->lessons[i];
	exit(-1);
}

CLessonHandler& CLessonManager::getLesson(int index) const
{
	return *this->lessons[index];
}

int CLessonManager::getLessonsDone() const
{
	return this->lessonsDone;
}


void CLessonManager::addLessonDone()
{
	this->lessonsDone++;
}

int CLessonManager::getLessonsNumber() const
{
	return this->lessons.size();
}