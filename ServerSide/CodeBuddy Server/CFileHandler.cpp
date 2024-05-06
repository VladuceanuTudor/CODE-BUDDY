#include "CFileHandler.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "Constraints.h"
#include "CWordSeparator.h"
#include <iostream>

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
		answers.clear();
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

bool CFileHandler::fileExists(const std::string& filename)
{
	std::ifstream file(filename);
	bool exists = file.good();
	file.close();
	return exists;
}

void CFileHandler::createFile(const std::string& filename)
{
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to create file " << filename <<std::endl;
	}
	else {
		file.close();
	}
}

ServerMessageContainer CFileHandler::getMessages(const std::string& filename)
{
	std::vector<std::string> buffer{};

	std::ifstream f(filename);
	if (!f.is_open()) {
		std::cerr << "Error: Unable to open file " << filename << std::endl;
		return ServerMessageContainer('E', "Unable to open file" + filename);
	}

	std::string line;
	while (std::getline(f, line)) {
		std::istringstream iss(line);
		std::string user, message;

		if (std::getline(iss, user, ':') && std::getline(iss, message)) {
			buffer.push_back(user);
			buffer.push_back(message);
		}
	}

	f.close();

	return ServerMessageContainer(GET_CHAT_CODE, CWordSeparator::encapsulateWords(buffer, PAYLOAD_DELIM));

}