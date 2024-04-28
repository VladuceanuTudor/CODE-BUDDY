#pragma once
#include <string>
#include <list>
#include "ServerMessageContainer.h"

class CExercice
{
private:
	char type;
	std::string question;
	std::list<std::string> answers;
	std::string realAnswer;
public:
	CExercice(char type, std::string question, std::list<std::string> answers, std::string realAnswer)
		: type{type}
		, question{question}
		, answers{answers}
		, realAnswer{realAnswer}
	{}
	std::string getSendData();
};