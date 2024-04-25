#pragma once
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include "Constraints.h"
#include "ServerMessageContainer.h"
#include "CUserHandler.h"



/*
		Coduri specifice:
Register    r -> r UNAME MAIL PASSWORD
Login       l -> l MAIL PASSWORD
Get lessons	b -> b LIMBAJ
Lesson		s -> s LIMBAJ LESSON_NUMBER
Chat        c -> c UNAME1 UNAME2
leaderboard b -> b
lb Player   p -> p UNAME
follow      f -> f UNAME1 UNAME2
Certificate t -> t UNAME
Eroare		E
		*/

class SDataBase
{
private:
	static SDataBase* instance;
	int init();
	SDataBase();
	~SDataBase();

	static SQLHANDLE sqlConnHandle;
	static SQLHANDLE sqlStmtHandle;
	static SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

	SDataBase(SDataBase* other) = delete;
	SDataBase(const SDataBase& other) = delete;

	static void AllocPrepare(SQLWCHAR* query);
	
	bool checkIfInDatabase(std::string table, std::string columnName, std::string value);

	std::vector<std::vector<std::string>> selectFromDatabase(
		const std::vector<std::string>& selectColumns,
		const std::string& table,
		const std::string& whereColumn,
		const std::string& whereValue,
		const std::string& orderColumn,
		bool orderDesc);

	void insertIntoDatabase();
public:
	static SDataBase& getInstance();
	static void destroyInstance();

	bool processLoginRequest(std::string request);
	ServerMessageContainer processRegisterRequest(std::string request);
	ServerMessageContainer processGetLessonsTitleRequest(std::string request, std::string username);
	ServerMessageContainer processGetLessonContent(std::string request);

	CUserHandler getUserInfo(std::string request);


	static void updateUserXp(std::string username, int newXp);
	static void addUserLessonDone(std::string username, int index);

};