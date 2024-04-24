#pragma once
#include <string>
#include <vector>
class CUserHandler
{
private:
	std::string username{};
	int xp{};
	int lives{};
	std::vector<int> lessonsDone{};
public:
	CUserHandler() {}
	CUserHandler(std::string username, int xp, std::vector<int> lessonsDone, int lives)
		: username{username}
		, xp{xp}
		, lives{lives}
		, lessonsDone{lessonsDone}
	{}
	std::string getUsername() const;
	int getXp() const;
	int getLessonDone(int i) const;
};

