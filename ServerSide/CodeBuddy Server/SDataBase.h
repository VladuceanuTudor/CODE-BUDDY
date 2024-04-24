#pragma once
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include "Constraints.h"



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

	std::string processLoginRequest(char request[MAX_BUFFER_LEN]);
	std::string processRegisterRequest(char request[MAX_BUFFER_LEN]);
	std::string processGetLessonsRequest(char request[MAX_BUFFER_LEN]);
public:
	static SDataBase& getInstance();
	static void destroyInstance();
	std::string processRequest(char request[MAX_BUFFER_LEN]);
};