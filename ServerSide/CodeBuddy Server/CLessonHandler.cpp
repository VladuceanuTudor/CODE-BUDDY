#include "CLessonHandler.h"
#include "CFileHandler.h"

const std::string& CLessonHandler::getTitle() const
{
	return this->title;
}

CLessonHandler::CLessonHandler(const std::string& title)
{
	this->title = title;
}

CLessonHandler::~CLessonHandler()
{
	for (const auto& it : this->exercices)
		if (it)
			delete it;
}

const std::string& CLessonHandler::getFilename() const
{
	return this->filename;
}

void CLessonHandler::setFilename(const std::string& filename)
{
	this->filename = filename;
}

void CLessonHandler::extractExercices()
{
	this->exercices = CFileHandler::getExercises(this->filename);
}

void CLessonHandler::setXp(int xp)
{
	this->xp = xp;
}