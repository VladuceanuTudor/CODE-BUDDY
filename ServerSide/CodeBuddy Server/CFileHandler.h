#pragma once
#include <string>
#include "CExercice.h"

class CFileHandler
{

public:
	static std::string getContent(const std::string & filename);
	static std::list<CExercice*> getExercises(const std::string& filename);
	static bool fileExists(const std::string& filename);
	static void createFile(const std::string& filename);
	static ServerMessageContainer getMessages(const std::string& filename);
	static void addMessage(const std::string& user1, const std::string& user2, const std::string& message);
};