#define _CRT_SECURE_NO_WARNINGS
#include "SDataBase.h"
#include "CWordSeparator.h"
#include "CClientHandler.h"
#include "CTCPServer.h"
#include "Utils.h"
#include <sstream>
#include <iostream>
#include <fstream>

SDataBase* SDataBase::instance = nullptr;
SQLHANDLE SDataBase::sqlConnHandle = nullptr;
SQLHANDLE SDataBase::sqlEnvHandle = nullptr;
SQLHANDLE SDataBase::sqlStmtHandle = nullptr;


int SDataBase::init()
{
    // Allocate environment handle
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &this->sqlEnvHandle) != SQL_SUCCESS)
    {
        std::cerr << "Error allocating environment handle" << std::endl;
        return -1;
    }

    // Set the ODBC version environment attribute
    if (SQLSetEnvAttr(this->sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) != SQL_SUCCESS)
    {
        std::cerr << "Error setting the ODBC version environment attribute" << std::endl;
        SQLFreeHandle(SQL_HANDLE_ENV, this->sqlEnvHandle);
        return -1;
    }

    // Allocate connection handle
    if (SQLAllocHandle(SQL_HANDLE_DBC, this->sqlEnvHandle, &this->sqlConnHandle) != SQL_SUCCESS)
    {
        std::cerr << "Error allocating connection handle" << std::endl;
        SQLFreeHandle(SQL_HANDLE_ENV, this->sqlEnvHandle);
        return -1;
    }

    // Connection string
    SQLWCHAR connectionStr[] = L"DRIVER={SQL SERVER};SERVER=localhost,1433;DATABASE=CodeBuddy;UID=Doru;PWD=;Trusted_Connection=Yes;";
    // Connect to SQL Server
    std::cout << "Connecting to DataBase...\n";

    switch (SQLDriverConnect(this->sqlConnHandle, NULL, connectionStr, SQL_NTS, this->retconstring, SQL_RETURN_CODE_LEN, NULL, SQL_DRIVER_NOPROMPT))
    {
    case SQL_SUCCESS_WITH_INFO:
        break;
    case SQL_INVALID_HANDLE:
    case SQL_ERROR:
        std::cerr << "Error connecting to SQL Server" << std::endl;
        SQLFreeHandle(SQL_HANDLE_DBC, this->sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_ENV, this->sqlEnvHandle);
        return -1;
    }
    std::cout << "Connected to DataBase..\n";


    return 0;
}

SDataBase::SDataBase()
{
    if (this->init() != 0)
    {
        std::cerr << "Closing server...\n";
        exit(-1);
    }
}

SDataBase::~SDataBase()
{
    // Free statement handle
    SQLFreeHandle(SQL_HANDLE_STMT, this->sqlStmtHandle);

    // Disconnect from SQL Server
    SQLDisconnect(this->sqlConnHandle);

    // Free connection handle
    SQLFreeHandle(SQL_HANDLE_DBC, this->sqlConnHandle);

    // Free environment handle
    SQLFreeHandle(SQL_HANDLE_ENV, this->sqlEnvHandle);
}

void SDataBase::AllocPrepare(SQLWCHAR* query)
{
    // Allocate statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, SDataBase::sqlConnHandle, &SDataBase::sqlStmtHandle) != SQL_SUCCESS)
        throw std::exception("Error allocating statement handle");
    // Prepare the SQL statement
    if (SQLPrepare(SDataBase::sqlStmtHandle, query, SQL_NTS) != SQL_SUCCESS)
        throw std::exception("Error preparing SQL statement\n");

}

std::vector<std::vector<std::string>> SDataBase::selectFromDatabase(
    const std::vector<std::string>& selectColumns,
    const std::string& table,
    const std::string& whereCondition,
    const std::string& orderColumn,
    bool orderDesc)
{
    // Construct the SELECT query
    std::string selectString = "SELECT ";
    for (int i = 0; i < selectColumns.size(); i++) {
        selectString += selectColumns[i];
        if (i < selectColumns.size() - 1) {
            selectString += ", ";
        }
    }
    selectString += " FROM " + table;

    if (!whereCondition.empty()) {
        selectString += " WHERE " + whereCondition;
    }

    if (!orderColumn.empty()) {
        selectString += " ORDER BY " + orderColumn;
        if (orderDesc) {
            selectString += " DESC";
        }
    }

    // Convert to wstring for SQL API
    std::wstring selectWstring(selectString.begin(), selectString.end());
    SQLWCHAR* selectQuery = new SQLWCHAR[selectString.size() + 1];
    wcscpy(selectQuery, selectWstring.c_str());

    // Prepare the SQL statement
    this->AllocPrepare(selectQuery);

    // Execute the SQL statement
    if (SQLExecute(SDataBase::sqlStmtHandle) != SQL_SUCCESS) {
        throw std::exception("Error executing SQL statement\n");
    }

    // Bind columns
    std::vector<SQLCHAR*> colBindings(selectColumns.size());
    for (int i = 0; i < selectColumns.size(); ++i) {
        colBindings[i] = new SQLCHAR[SQL_RESULT_LEN]{}; // Adjust SQL_RESULT_LEN as needed
        if (SQLBindCol(SDataBase::sqlStmtHandle, i + 1, SQL_C_CHAR, colBindings[i], SQL_RESULT_LEN, nullptr) != SQL_SUCCESS) {
            throw std::exception("Error binding column\n");
        }
    }

    // Fetch and process the results
    std::vector<std::vector<std::string>> result;
    while (SQLFetch(SDataBase::sqlStmtHandle) == SQL_SUCCESS) {
        std::vector<std::string> row;
        for (int i = 0; i < selectColumns.size(); i++) {
            row.emplace_back(reinterpret_cast<char*>(colBindings[i]));
        }
        result.push_back(row);
    }

    // Clean up resources
    for (int i = 0; i < colBindings.size(); i++) {
        delete[] colBindings[i];
    }
    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);
    delete[] selectQuery;

    return result;
}

void SDataBase::insertIntoDatabase(const std::vector<std::string>& insertIntoColumn,
    const std::string& table,
    const std::vector<std::string>& values)
{
    // Construct the SELECT query
    std::string insertString = "INSERT INTO " + table + " (";
    for (int i = 0; i < insertIntoColumn.size(); i++) {
        insertString += insertIntoColumn[i];
        if (i < insertIntoColumn.size() - 1) {
            insertString += ", ";
        }
    }
    insertString += ") VALUES (";

    for (int i = 0; i < values.size(); i++) {
        insertString += "\'";
        insertString += values[i];
        insertString += "\'";
        if (i < values.size() - 1) {
            insertString += ", ";
        }
    }
    insertString += ")";

    std::wstring selectWstring(insertString.begin(), insertString.end());
    SQLWCHAR* insetQuery = new SQLWCHAR[insertString.size() + 1];
    wcscpy(insetQuery, selectWstring.c_str());

    this->AllocPrepare(insetQuery);

    if (SQLExecDirect(sqlStmtHandle, insetQuery, SQL_NTS) != SQL_SUCCESS)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        delete[] insetQuery;
        throw std::exception("Error executing SQL query");
    }

    //Eliberare Resurse StmtHandle
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    delete[] insetQuery;
}


void SDataBase::updateIntoDatabase(
    const std::string& table,
    const std::string& updateColumn,
    const std::string& updateValue,
    const std::string& whereCondition,
    bool command)
{
    std::string updateString;
    if(!command)
        updateString = "UPDATE " + table + " SET " + updateColumn + " = \'" + updateValue + "\' WHERE " + whereCondition;
    else
        updateString = "UPDATE " + table + " SET " + updateColumn + " = " + updateValue + " WHERE " + whereCondition;

    std::wstring updateWstring(updateString.begin(), updateString.end());

    SQLWCHAR* updateQuery = new SQLWCHAR[updateWstring.size() + 1];
    wcscpy(updateQuery, updateWstring.c_str());

    this->AllocPrepare(updateQuery);

    if (SQLExecDirect(sqlStmtHandle, updateQuery, SQL_NTS) != SQL_SUCCESS)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        delete[] updateQuery; 
        throw std::exception("Error executing SQL query");
    }

    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    delete[] updateQuery;
}


bool SDataBase::checkIfInDatabase(std::string table, std::string columnName, std::string value)
{
    std::vector<std::string> selects; selects.push_back(columnName);

    return !this->selectFromDatabase(selects, table, columnName + " = \'" + value + "\'").empty();
}

SDataBase& SDataBase::getInstance()
{
    if (!SDataBase::instance)
        SDataBase::instance = new SDataBase();
    return *SDataBase::instance;
}

void SDataBase::destroyInstance()
{
    if (SDataBase::instance)
        delete SDataBase::instance;
    SDataBase::instance = nullptr;
    std::cerr << "Disconnecting Database" << std::endl;
}

ServerMessageContainer SDataBase::processRegisterRequest(std::string request)
{
    std::vector<std::string> inputs;

    inputs = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);

    if(this->checkIfInDatabase("Users", "Username", inputs[0]))
        return ServerMessageContainer(REGISTER_CODE, "user");

    if (this->checkIfInDatabase("Users", "Email", inputs[1]))
        return ServerMessageContainer(REGISTER_CODE, "email");

    std::vector<std::string> insertColumns = { "Username", "Email", "Password" };
    this->insertIntoDatabase(insertColumns, "Users", inputs);

    return ServerMessageContainer(REGISTER_CODE, "accepted");
}

void SDataBase::updateLessonsDone(CClientHandler* ch, std::string language)
{
    std::string updateColumn = "LessonsDone" + language;

    this->updateIntoDatabase("Users", updateColumn, std::to_string(ch->getLanguage(language).getLessonsDone()),
        "Username = \'" + ch->getUserHandler().getUsername() + "\'");
}

CUserHandler* SDataBase::getUserInfo(std::string email)
{
    //request = EMAIL

    CUserHandler* ch{nullptr};

    std::vector<std::string> selects = { "Username", "Xp", "Lives", "IsPremium"};
    std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "Users", "Email = \'" + email + "\'");

    ch = new CUserHandler(cols[0][0], std::stoi(cols[0][1]), std::stoi(cols[0][2]), std::stoi(cols[0][3]));

    return ch;
}

ServerMessageContainer SDataBase::processGlobalRequest()
{
    std::vector<std::string> selects = {"TOP(10) Xp", "Username"};
    std::vector<std::vector<std::string>> cols = SDataBase::selectFromDatabase(selects, "Users", "", "Xp", true);

    selects.clear();
    for (const auto& it : cols)
    {
        selects.push_back(it[1]);
        selects.push_back(it[0]);
    }
    return ServerMessageContainer(GET_LEADERBOARD_CODE, CWordSeparator::encapsulateWords(selects, PAYLOAD_DELIM));
}

ServerMessageContainer SDataBase::processLocalRequest(const std::string& username, int xp)
{

    std::vector<std::string> selects = { "COUNT(*) + 1" };

    std::vector<std::vector<std::string>> cols = SDataBase::selectFromDatabase(selects, "Users",
        "XP > (SELECT XP FROM Users WHERE UserName = '" + username + "')");

    if (cols[0][0].empty())
        return ServerMessageContainer(ERROR_CODE, "User Local Place not found");

    std::vector<std::string> sendMessage{};

    selects = { "TOP(9) Xp", "Username" };
    std::vector<std::vector<std::string>> othersCols = SDataBase::selectFromDatabase(selects, "Users",
        "Xp <= " + std::to_string(xp) + " AND Username != \'" + username + "\'", 
        "Xp", true);

    sendMessage.push_back(cols[0][0]);
    sendMessage.push_back(username);
    sendMessage.push_back(std::to_string(xp));
    for (const auto& it : othersCols)
    {
        sendMessage.push_back(it[1]);
        sendMessage.push_back(it[0]);
    }
    return ServerMessageContainer(GET_LEADERBOARD_CODE, CWordSeparator::encapsulateWords(sendMessage, PAYLOAD_DELIM));
}

ServerMessageContainer SDataBase::processLeadearboardRequest(std::string request, const std::string& username, int xp)
{
    if (request == "g")
    {
        return this->processGlobalRequest();
    }
    else if (request == "l")
    {
        return this->processLocalRequest(username, xp);
    }
    return ServerMessageContainer(ERROR_CODE, "Invalid option for leaderboard request");
}

int SDataBase::getLastDayLogin(const std::string& username)
{
    std::vector<std::string> selects = { "DATEDIFF(DAY, LastLoggedIn, GETDATE())" };
    std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "Users", "Username = \'" + username + "\'");
    this->updateIntoDatabase("Users", "LastLoggedIn", "GETDATE()", "Username = \'" + username + "\'", true);

    return std::stoi(cols[0][0]);
}

void SDataBase::updateUserXp(std::string username, int newXp)
{
    this->updateIntoDatabase("Users", "Xp", std::to_string(newXp), "Username = \'" + username + "\'");
}

int SDataBase::processPremiumPayment(const std::string& request, const std::string& username)
{
    // request = NUMBER_CARD NAME YEAR MONTH CVV
    std::vector<std::string> inputs = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);
    std::vector<std::string> selects = { "CardNumber", "CardName", "YEAR(ExpirationDate)", "MONTH(ExpirationDate)", "CVV", "Balance" };
    std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "ClientsCards", "CardNumber = \'" + inputs[0] + "\'");

    if (cols.empty())
        return 2;

    for (int i = 0; i < 5; i++)
        if (inputs[i] != cols[0][i] && inputs[i] != ("0" + cols[0][i]))
            return 2;
    int balance = std::stoi(cols[0][5]);
    if (balance < PREMIUM_PRICE)
        return 1;
    this->updateIntoDatabase("ClientsCards", "Balance", std::to_string(balance - PREMIUM_PRICE), "CardNumber = \'" + inputs[0] + "\'");
    this->updateIntoDatabase("Users", "IsPremium", "1", "Username = \'" + username + "\'");
    return 0;
}

ServerMessageContainer SDataBase::processGetFriendsRequest(const std::string& username)
{
    std::vector<std::string> selects = { "User1", "User2" };
    std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "Friends",
        "User1 = \'" + username + "\' OR User2 = \'" + username + "\'");
    selects.clear();
    
    for (const auto& it : cols)
    {
        if (it[0] == username)
            selects.push_back(it[1]);
        else
            selects.push_back(it[0]);
    }

    return ServerMessageContainer(GET_FRIENDS_CODE, CWordSeparator::encapsulateWords(selects, PAYLOAD_DELIM));
}

ServerMessageContainer SDataBase::addFriendToUser(const std::string& user1, const std::string& user2)
{
    //request = user1 user2 (user1 da cerere lui user2)
    std::vector<std::string> selects = { "Username" };
    std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "Users", "Username = \'" + user2 + "\'");
    
    if (cols.empty())
        return ServerMessageContainer(ADD_FRIEND_CODE, "NotFound");

    selects = { "*" };
    std::string whereCondition = "(User1 = \'" + user1 + "\' AND User2 = \'" + user2 + "\') OR (User1 = \'" + user2 + "\' AND User2 = \'" + user1 + "\')";
    cols = this->selectFromDatabase(selects, "Friends", whereCondition);
    if(!cols.empty())
        return ServerMessageContainer(ADD_FRIEND_CODE, "AlreadyFriends");

    selects = { "User1", "User2" };
    std::vector<std::string>insertValues = { user1, user2 };
    this->insertIntoDatabase(selects, "Friends", insertValues);
    return ServerMessageContainer(ADD_FRIEND_CODE, "Accepted");
}
