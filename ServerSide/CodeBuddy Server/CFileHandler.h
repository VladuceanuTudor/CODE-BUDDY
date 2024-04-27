#pragma once
#include <string>
#include "CExercice.h"

class CFileHandler
{

public:
	static std::string getContent(const std::string & filename);
	CExercice* getExercises(const std::string& filename);
};