#define _CRT_SECURE_NO_WARNINGS
#include "SDataBase.h"
#include "CWordSeparator.h"
#include "CClientHandler.h"
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
    SQLWCHAR connectionStr[] = L"DRIVER={SQL SERVER};SERVER=25.16.102.33,1433;DATABASE=CodeBuddy;UID=Doru;PWD=;Trusted_Connection=Yes;";
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
        for (int i = 0; i < selectColumns.size(); ++i) {
            row.emplace_back(reinterpret_cast<char*>(colBindings[i]));
        }
        result.push_back(row);
    }

    // Clean up resources
    for (int i = 0; i < colBindings.size(); ++i) {
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
        throw std::exception("Error executing SQL query");
    }

    //Eliberare Resurse StmtHandle
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
}


bool SDataBase::checkIfInDatabase(std::string table, std::string columnName, std::string value)
{
    std::vector<std::string> selects; selects.push_back(columnName);

    return !this->selectFromDatabase(selects, table, columnName, value).empty();
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

    std::vector<std::string> insertColumns = { "Username", "Email", "Password" };
    this->insertIntoDatabase(insertColumns, "Users", inputs);

    return ServerMessageContainer('r', "accepted");
}

std::vector<std::string> getColumn(std::vector<std::vector<std::string>> mat, int i)
{
    std::vector<std::string> column;
    for (const auto& row : mat) {
        if (!row.empty()) {
            column.push_back(row[i]);
        }
    }
    return column;
}

ServerMessageContainer SDataBase::processGetLessonsTitleRequest(std::string request, CClientHandler* ch)
{
    if (!ch->existsLesson(request))
    {

        std::vector<std::string> selects; selects.push_back("LessonTitle");
        std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "Lessons", "Language", request, "LessonNumber");

        std::string buffer = "LessonsDone" + request;
        selects.clear();
        selects.push_back(buffer);
        std::string lessonsDone = this->selectFromDatabase(selects, "Users", "Username", ch->getUserHandler().getUsername())[0][0];

        ch->setLessonTileDone(std::stoi(lessonsDone), getColumn(cols, 0), request);
    }

    return ch->getLanguage(request).getSendMessageTitles();
}

ServerMessageContainer SDataBase::processGetLessonContent(std::string request, CClientHandler* ch)
{
    std::vector<std::string> words = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);   

    if (ch->getLanguage(words[1]).getLesson(words[0]).getFilename().empty())
    {
        std::vector<std::string> selects = { "Language", "Filename", "XpGiven" };
        std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "Lessons", "LessonTitle", words[0]);
        for (const auto& it : cols)
        {
            if (it[0] == words[1])  //Punem Lectia cu care vrem sa lucram pe prima pozitie
            {
                cols[0] = it;
                break;
            }
        }

        ch->getLanguage(words[1]).getLesson(words[0]).setFilename(cols[0][1]);
        ch->getLanguage(words[1]).getLesson(words[0]).extractExercices();
        ch->getLanguage(words[1]).getLesson(words[0]).setXp(std::stoi(cols[0][2]));
    }

    return ch->getLanguage(words[1]).getLesson(words[0]).getSendMessage();
}

CUserHandler* SDataBase::getUserInfo(std::string request)
{
    CUserHandler* ch{nullptr};

    std::vector<std::string> inputs;

    inputs = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);

    std::vector<std::string> selects = { "Username", "Xp", "Lives"};
    std::vector<std::vector<std::string>> cols = this->selectFromDatabase(selects, "Users", "Email", inputs[0]);

    ch = new CUserHandler(cols[0][0], std::stoi(cols[0][1]), std::stoi(cols[0][2]));

    return ch;
}
