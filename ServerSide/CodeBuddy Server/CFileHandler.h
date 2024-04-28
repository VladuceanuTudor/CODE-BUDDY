#pragma once
#include <string>
#include "CExercice.h"

class CFileHandler
{

public:
	static std::string getContent(const std::string & filename);
	static std::list<CExercice*> getExercises(const std::string& filename);
};