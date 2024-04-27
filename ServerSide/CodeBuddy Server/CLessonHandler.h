#pragma once
#include <string>
#include <list>
#include "CExercice.h"

class CLessonHandler
{
private:
	std::string title{};
	std::list<CExercice*> exercices{};
	std::string filename{};
public:
	const std::string& getTitle() const;
	const std::string& getFilename() const;

	CLessonHandler(const std::string& title);
	void setFilename(const std::string& filename);

	~CLessonHandler();
};