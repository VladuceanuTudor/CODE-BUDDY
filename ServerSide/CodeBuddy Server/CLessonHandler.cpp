#include "CLessonHandler.h"
#include "CFileHandler.h"
#include "Constraints.h"
#include "CWordSeparator.h"
#include <vector>

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
	std::string fileEx = this->filename;
	fileEx.erase(fileEx.size() - 4);
	fileEx += "_ex.txt";
	this->exercices = CFileHandler::getExercises(fileEx);
}

void CLessonHandler::setXp(int xp)
{
	this->xp = xp;
}

ServerMessageContainer CLessonHandler::getSendMessage()
{
	std::vector<std::string> buffer;

	buffer.push_back(CFileHandler::getContent(this->filename));
	buffer.push_back(std::to_string(this->xp));
	buffer.push_back(std::to_string(this->exercices.size()));

	return ServerMessageContainer(GET_LESSON_CONTENT, CWordSeparator::encapsulateWords(buffer, PAYLOAD_DELIM));
}

std::list<CExercice*> CLessonHandler::getExercices() const
{
	return this->exercices;
}

int CLessonHandler::getXp() const
{
	return this->xp;
}
