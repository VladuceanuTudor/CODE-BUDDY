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

bool SDataBase::processLoginRequest(std::string request)
{
    // SQL query
    SQLWCHAR* selectQuery = (SQLWCHAR*)L"SELECT Password, Email FROM Users";

    SDataBase::AllocPrepare(selectQuery);

    // Execute the SQL statement
    if (SQLExecute(SDataBase::sqlStmtHandle) != SQL_SUCCESS) {
        throw std::exception("Error executing SQL statement\n");
    }

    // Bind columns to fetch the results
    SQLCHAR col1[SQL_RESULT_LEN]{};         //DE MODIFICAT SQL_RESULT_LEN {LA FEL SI MAI JOS}
    SQLCHAR col2[SQL_RESULT_LEN]{};

    // Bind column 1 (Password)
    if (SQLBindCol(SDataBase::sqlStmtHandle, 1, SQL_C_CHAR, col1, SQL_RESULT_LEN, nullptr) != SQL_SUCCESS)
        throw std::exception("Error binding column 1\n");
    // Bind column 2 (Email)
    if (SQLBindCol(SDataBase::sqlStmtHandle, 2, SQL_C_CHAR, col2, SQL_RESULT_LEN, nullptr) != SQL_SUCCESS)
        throw std::exception("Error binding column 2\n");

    bool found{ false };
    std::vector<std::string> inputs;
    inputs = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);

    // Fetch and display results
    while (SQLFetch(SDataBase::sqlStmtHandle) == SQL_SUCCESS)
    {
        if (inputs[0] == std::string(reinterpret_cast<char*>(col2)) && inputs[1] == std::string(reinterpret_cast<char*>(col1)))
        {
            found = true;
        }
    }

    // Eliberarea resurselor asociate statement-ului SQL
    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);

    if (found)
        return true;
    return false;
    
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

ServerMessageContainer SDataBase::processGetLessonsTitleRequest(std::string request)
{
    // SQL query
    std::string selectString = "SELECT LessonTitle FROM Lessons WHERE Language = \'";//cpp\' ORDER BY LessonNumber";
    selectString += request;
    selectString += "\' ORDER BY LessonNumber";

    std::wstring selectWstring(selectString.begin(), selectString.end());

    SQLWCHAR* selectQuery = new SQLWCHAR[selectString.size() + 1];
    wcscpy(selectQuery, selectWstring.c_str());

    this->AllocPrepare(selectQuery);

    // Execute the SQL statement
    if (SQLExecute(SDataBase::sqlStmtHandle) != SQL_SUCCESS) {
        throw std::exception("Error executing SQL statement\n");
    }

    // Bind columns to fetch the results
    SQLCHAR col1[SQL_RESULT_LEN]{};         //DE MODIFICAT SQL_RESULT_LEN 

    if (SQLBindCol(SDataBase::sqlStmtHandle, 1, SQL_C_CHAR, col1, SQL_RESULT_LEN, nullptr) != SQL_SUCCESS)
        throw std::exception("Error binding column 1\n");

    std::string lessons{};
    char a = 2;
    lessons = a;
    lessons += "#";//DE MODIFICAT AICI SA IA PRIMUL OCTET DIN BAZA DE DATE ASTFEL INCAT SA IA EXACT LECTIA LA CARE SE AFLA USERUL

    // Fetch and display results
    while (SQLFetch(SDataBase::sqlStmtHandle) == SQL_SUCCESS)
    {
        lessons += (char*)col1;
        lessons += PAYLOAD_DELIM;
    }

    // Eliberarea resurselor asociate statement-ului SQL
    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);

    delete[] selectQuery;

    return ServerMessageContainer('b', lessons);
}

CUserHandler SDataBase::getUserInfo(std::string request)
{
    std::vector<std::string> inputs;

    inputs = CWordSeparator::SeparateWords(request, PAYLOAD_DELIM);

    // SQL query
    std::string selectString = "SELECT Password, Email FROM Users WHERE Email = " + inputs[0];

    std::wstring selectWstring(selectString.begin(), selectString.end());

    SQLWCHAR* selectQuery = new SQLWCHAR[selectString.size() + 1];
    wcscpy(selectQuery, selectWstring.c_str());

    SDataBase::AllocPrepare(selectQuery);
    // Execute the SQL statement
    if (SQLExecute(SDataBase::sqlStmtHandle) != SQL_SUCCESS) {
        throw std::exception("Error executing SQL statement\n");
    }

    // Bind columns to fetch the results
    SQLCHAR col1[SQL_RESULT_LEN]{};         //DE MODIFICAT SQL_RESULT_LEN {LA FEL SI MAI JOS}
    SQLCHAR col2[SQL_RESULT_LEN]{};

    // Bind column 1 (Password)
    if (SQLBindCol(SDataBase::sqlStmtHandle, 1, SQL_C_CHAR, col1, SQL_RESULT_LEN, nullptr) != SQL_SUCCESS)
        throw std::exception("Error binding column 1\n");
    // Bind column 2 (Email)
    if (SQLBindCol(SDataBase::sqlStmtHandle, 2, SQL_C_CHAR, col2, SQL_RESULT_LEN, nullptr) != SQL_SUCCESS)
        throw std::exception("Error binding column 2\n");

    // Eliberarea resurselor asociate statement-ului SQL
    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);

    delete[] selectQuery;

    return CUserHandler();
}
