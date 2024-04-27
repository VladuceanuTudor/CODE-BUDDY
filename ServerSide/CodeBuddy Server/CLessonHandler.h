#pragma once
#include <string>
#include <list>
#include "CExercice.h"

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

	CLessonHandler(const std::string& title);
	~CLessonHandler();

	void setFilename(const std::string& filename);
	void setXp(int xp);

	void extractExercices();

};