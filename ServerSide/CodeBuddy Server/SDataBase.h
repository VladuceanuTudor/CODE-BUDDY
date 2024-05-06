#pragma once
#include <string>
#include <winsock2.h>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include "Constraints.h"
#include "ServerMessageContainer.h"
#include "CClientHandler.h"



/*
		Coduri specifice:
Register    r -> r UNAME MAIL PASSWORD
Login       l -> l MAIL PASSWORD
Get lessons	b -> b LIMBAJ
Lesson		L -> L LIMBAJ LESSON_TITLE
Add Xp		x -> x XP
Vieti		i -> i 0/1
leaderboard a -> a g/l	(g -> global, l -> local)
Chat        c -> c UNAME1 UNAME2
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

	ServerMessageContainer processGlobalRequest();
	ServerMessageContainer processLocalRequest(const std::string& username, int xp);

public:
	static SDataBase& getInstance();
	static void destroyInstance();

	std::vector<std::vector<std::string>> selectFromDatabase(
		const std::vector<std::string>& selectColumns,
		const std::string& table,
		const std::string& whereCondition = "",
		const std::string& orderColumn = "",
		bool orderDesc = false);

	void insertIntoDatabase(
		const std::vector<std::string>& insertIntoColumn,
		const std::string& table,
		const std::vector<std::string>& values);

	void updateIntoDatabase(
		const std::string& table,
		const std::string& updateColumn,
		const std::string& updateValue,
		const std::string& whereCondition,
		bool command = false);

	ServerMessageContainer processRegisterRequest(std::string request);
	ServerMessageContainer processLeadearboardRequest(std::string request, const std::string& username, int xp);
	ServerMessageContainer processGetFriendsRequest(const std::string& username);
	int processPremiumPayment(const std::string& request, const std::string& username);
	int getLastDayLogin(const std::string& username);

	void updateLessonsDone(CClientHandler* ch, std::string language);

	CUserHandler* getUserInfo(std::string email);


	void updateUserXp(std::string username, int newXp);
	void addUserLessonDone(std::string username, int index);

};