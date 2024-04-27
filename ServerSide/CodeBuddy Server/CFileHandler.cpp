#include "CFileHandler.h"
#include <fstream>
#include <sstream>

std::list<CExercice*> CFileHandler::getExercises(const std::string& filename)
{
	std::ifstream f(filename);
	if (!f.is_open())
		exit(-1);

	std::string line;
	std::getline(f, line);
	int exercises = std::stoi(line);
	std::string question;
	char type;
	std::string realAnswer;
	std::list<std::string> answers;

	std::list<CExercice*> exercices;

	for (int i = 0; i < exercises; i++)
	{
		std::getline(f, line);
		type = line[0];
		std::getline(f, question);
		for (int j = 0; j < 4; j++)
		{
			std::getline(f, line);
			answers.push_back(line);
		}
		std::getline(f, realAnswer);
		exercices.push_back(new CExercice(type, question, answers, realAnswer));

	}

	f.close();

	return exercices;
}

std::string CFileHandler::getContent(const std::string& filename)
{
	std::ifstream f(filename);
	std::stringstream ss;
	ss << f.rdbuf();
	f.close();

	std::string str = ss.str();

	return str;
}