#define _CRT_SECURE_NO_WARNINGS
#include "SDataBase.h"
#include "CWordSeparator.h"
#include <iostream>

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
    SQLWCHAR connectionStr[] = L"DRIVER={SQL SERVER};SERVER=DESKTOP-ROOGGU8;DATABASE=CodeBuddy;UID=Doru;PWD=;Trusted_Connection=Yes;";
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

bool SDataBase::checkIfInDatabase(std::string table, std::string columnName, std::string value)
{
    std::string selectString = "SELECT ";
    selectString += columnName + " FROM " +  table + " WHERE " + columnName + " = \'" + value + "\'";

    std::wstring selectWstring(selectString.begin(), selectString.end());

    SQLWCHAR* selectQuery = new SQLWCHAR[selectString.size() + 1];
    wcscpy(selectQuery, selectWstring.c_str());

    this->AllocPrepare(selectQuery);

    // Execute the SQL statement
    if (SQLExecute(SDataBase::sqlStmtHandle) != SQL_SUCCESS) {
        throw std::exception("Error executing SQL statement\n");
    }

    int returnVal = SQLFetch(SDataBase::sqlStmtHandle);
        // Eliberarea resurselor asociate statement-ului SQL
    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);

    return returnVal == SQL_SUCCESS;
}

std::vector<std::vector<std::string>> SDataBase::selectFromDatabase(
    const std::vector<std::string>& selectColumns,
    const std::string& table,
    const std::string& whereColumn = "",
    const std::string& whereValue = "",
    const std::string& orderColumn = "",
    bool orderDesc = false)
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

    if (!whereColumn.empty()) {
        selectString += " WHERE " + whereColumn + " = '" + whereValue + "'";
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
    for (size_t i = 0; i < selectColumns.size(); ++i) {
        colBindings[i] = new SQLCHAR[SQL_RESULT_LEN]{}; // Adjust SQL_RESULT_LEN as needed
        if (SQLBindCol(SDataBase::sqlStmtHandle, i + 1, SQL_C_CHAR, colBindings[i], SQL_RESULT_LEN, nullptr) != SQL_SUCCESS) {
            throw std::exception("Error binding column\n");
        }
    }

    // Fetch and process the results
    std::vector<std::vector<std::string>> result;
    while (SQLFetch(SDataBase::sqlStmtHandle) == SQL_SUCCESS) {
        std::vector<std::string> row;
        for (size_t i = 0; i < selectColumns.size(); ++i) {
            row.emplace_back(reinterpret_cast<char*>(colBindings[i]));
        }
        result.push_back(row);
    }

    // Clean up resources
    for (size_t i = 0; i < colBindings.size(); ++i) {
        delete[] colBindings[i];
    }
    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);
    delete[] selectQuery;

    return result;
}



bool SDataBase::processLoginRequest(std::string request)
{
    bool found{ false };
    std::vector<std::string> inputs;
    inputs = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);

    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);

    std::vector<std::string> selects; selects.push_back("Email"); selects.push_back("Password");
    std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "Users");

    for (const auto& it : cols)
    {
        if (it[0] == inputs[0] && it[1] == inputs[1])
        {
            found = true;
            break;
        }
    }

    return found;
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
        return ServerMessageContainer('r', "user");

    if (this->checkIfInDatabase("Users", "Email", inputs[1]))
        return ServerMessageContainer('r', "email");

    // Bind parameter values to the prepared statement
    SQLWCHAR* sqlQuery = (SQLWCHAR*)L"INSERT INTO Users (Username, Email, Password) VALUES (?, ?, ?)";

    this->AllocPrepare(sqlQuery);

    // Bind parameter values to the prepared statement
    if (SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, inputs[0].length(), 0, (SQLPOINTER)inputs[0].c_str(), 0, NULL) != SQL_SUCCESS ||
        SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, inputs[1].length(), 0, (SQLPOINTER)inputs[1].c_str(), 0, NULL) != SQL_SUCCESS ||
        SQLBindParameter(sqlStmtHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, inputs[2].length(), 0, (SQLPOINTER)inputs[2].c_str(), 0, NULL) != SQL_SUCCESS)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        throw std::exception("Error binding parameter values");
    }

    if (SQLExecDirect(sqlStmtHandle, sqlQuery, SQL_NTS) != SQL_SUCCESS)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        throw std::exception("Error executing SQL query");
    }

    return ServerMessageContainer('r', "accepted");
}

ServerMessageContainer SDataBase::processGetLessonsTitleRequest(std::string request, std::string username)
{
    std::string lessons{};
    
    std::vector<std::string> selects; selects.push_back("LessonTitle");
    std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "Lessons", "Language", request);

    std::string buffer = "LessonsDone" + request;
    selects.clear();
    selects.push_back(buffer);
    std::string lessonsDone = this->selectFromDatabase(selects, "Users", "Username", username)[0][0];
    
    lessons += std::stoi(lessonsDone);
    lessons += PAYLOAD_DELIM;
    lessons += CWordSeparator::encapsulateWords(cols, 0, PAYLOAD_DELIM);

    return ServerMessageContainer('b', lessons);
}

CUserHandler SDataBase::getUserInfo(std::string request)
{
    CUserHandler ch;

    std::vector<std::string> inputs;

    inputs = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);

    // SQL query
    std::string selectString = "SELECT Username, Xp, Lives, LessonsDoneCpp, LessonsDoneCsh, LessonsDoneJava FROM Users WHERE Email = \'"
        + inputs[0] + "\'";

    std::wstring selectWstring(selectString.begin(), selectString.end());

    SQLWCHAR* selectQuery = new SQLWCHAR[selectString.size() + 1];
    wcscpy(selectQuery, selectWstring.c_str());

    SDataBase::AllocPrepare(selectQuery);

    // Execute the SQL statement
    if (SQLExecute(SDataBase::sqlStmtHandle) != SQL_SUCCESS) 
        throw std::exception("Error executing SQL statement\n");

    SQLCHAR strData[SQL_RESULT_LEN]{};
    SQLINTEGER intData[5]{};

    // Bind column 1 (Password)
    if (SQLBindCol(SDataBase::sqlStmtHandle, 1, SQL_C_CHAR, strData, SQL_RESULT_LEN, nullptr) != SQL_SUCCESS)
        throw std::exception("Error binding column 1\n");
    
    // Bind columns 2 to 6 (IntColumn0 to IntColumn5)
    for (int i = 0; i < 5; ++i) 
    {
        if (SQLBindCol(SDataBase::sqlStmtHandle, 2 + i, SQL_C_LONG, &intData[i], 0, nullptr) != SQL_SUCCESS)
            throw std::exception("Error binding integer column\n");
    }

    // Fetch and process the results
    if (SQLFetch(SDataBase::sqlStmtHandle) == SQL_SUCCESS) 
    {
        std::vector<int> vec;
        vec.push_back(intData[2]); vec.push_back(intData[3]); vec.push_back(intData[4]);
        ch = CUserHandler(reinterpret_cast<char*>(strData), intData[0], vec, intData[1]);
    }
    else
    {
        throw std::exception("Error fetching results\n");
    }

    // Eliberarea resurselor asociate statement-ului SQL
    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);

    delete[] selectQuery;

    return ch;
}
