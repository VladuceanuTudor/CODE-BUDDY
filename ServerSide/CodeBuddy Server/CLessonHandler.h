#pragma once
#include <string>
#include <list>
#include "CExercice.h"
#include "ServerMessageContainer.h"

class CLessonHandler
{
private:
	std::string title{};
	std::list<CExercice*> exercices{};
	int xp;
	std::string filename;
public:
	const std::string& getTitle() const;
	const std::string& getFilename() const;
	ServerMessageContainer getSendMessage();
	std::list<CExercice*> getExercices() const;
	int getXp() const;

	CLessonHandler(const std::string& title);
	~CLessonHandler();

	void setFilename(const std::string& filename);
	void setXp(int xp);

	void extractExercices();

};