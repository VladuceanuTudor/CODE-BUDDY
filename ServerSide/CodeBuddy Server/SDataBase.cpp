#define _CRT_SECURE_NO_WARNINGS
#include "SDataBase.h"
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
    default:
        break;
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

std::string SDataBase::processLoginRequest(char request[MAX_BUFFER_LEN])
{
    // SQL query
    SQLWCHAR* selectQuery = (SQLWCHAR*)L"SELECT Password, Email FROM Users";

    // Allocate statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, this->sqlConnHandle, &this->sqlStmtHandle) != SQL_SUCCESS)
    {
        throw std::exception("Error allocating statement handle");
    }

    // Prepare the SQL statement
    if (SQLPrepare(SDataBase::sqlStmtHandle, selectQuery, SQL_NTS) != SQL_SUCCESS)
    {
        throw std::exception("Error preparing SQL statement\n");
    }
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
    char* password{}, *email{};
    email = strtok(_strdup(request), PAYLOAD_DELIM);
    password = strtok(NULL, PAYLOAD_DELIM);

    // Fetch and display results
    while (SQLFetch(SDataBase::sqlStmtHandle) == SQL_SUCCESS)
    {
        if (strcmp(password, (char*)col1) == 0 && strcmp(email, (char*)col2) == 0)
        {
            found = true;
        }
    }

    // Eliberarea resurselor asociate statement-ului SQL
    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);

    std::string buffer = "l";

    if (found)
    {
        buffer += strlen("accepted");
        buffer += "accepted";
    }
    else
    {
        buffer += strlen("fail");
        buffer += "fail";
    }

    return buffer;
    
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
    SQLDisconnect(SDataBase::sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, SDataBase::sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, SDataBase::sqlEnvHandle);
}

std::string SDataBase::processRegisterRequest(char request[MAX_BUFFER_LEN])
{
    std::string buffer = "r";

    // Allocate statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, SDataBase::sqlConnHandle, &SDataBase::sqlStmtHandle) != SQL_SUCCESS)
    {
        throw std::exception("Error allocating statement handle");
    }

    std::string username = "";
    std::string email = "";
    std::string password = "";

    username = strtok(request, PAYLOAD_DELIM);
    email = strtok(NULL, PAYLOAD_DELIM);
    password = strtok(NULL, PAYLOAD_DELIM);

    // Bind parameter values to the prepared statement
    SQLWCHAR* sqlQuery = (SQLWCHAR*)L"INSERT INTO Users (Username, Email, Password) VALUES (?, ?, ?)";

    if (SQLPrepare(sqlStmtHandle, sqlQuery, SQL_NTS) != SQL_SUCCESS)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        throw std::exception("Error preparing SQL statement");
    }

    // Bind parameter values to the prepared statement
    if (SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, username.length(), 0, (SQLPOINTER)username.c_str(), 0, NULL) != SQL_SUCCESS ||
        SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, email.length(), 0, (SQLPOINTER)email.c_str(), 0, NULL) != SQL_SUCCESS ||
        SQLBindParameter(sqlStmtHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, password.length(), 0, (SQLPOINTER)password.c_str(), 0, NULL) != SQL_SUCCESS)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        throw std::exception("Error binding parameter values");
    }

    if (SQLExecDirect(sqlStmtHandle, sqlQuery, SQL_NTS) != SQL_SUCCESS)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        throw std::exception("Error executing SQL query");
    }

    //
    buffer += strlen("accepted");
    buffer += "accepted";

    return buffer;
}

std::string SDataBase::processGetLessonsRequest(char request[MAX_BUFFER_LEN])
{
    // SQL query
    SQLWCHAR* selectQuery = (SQLWCHAR*)L"SELECT LessonTitle FROM Lessons WHERE Language = \'cpp\' ORDER BY LessonNumber DESC";

    // Allocate statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, this->sqlConnHandle, &this->sqlStmtHandle) != SQL_SUCCESS)
    {
        throw std::exception("Error allocating statement handle");
    }

    // Prepare the SQL statement
    if (SQLPrepare(SDataBase::sqlStmtHandle, selectQuery, SQL_NTS) != SQL_SUCCESS)
    {
        throw std::exception("Error preparing SQL statement\n");
    }
    // Execute the SQL statement
    if (SQLExecute(SDataBase::sqlStmtHandle) != SQL_SUCCESS) {
        throw std::exception("Error executing SQL statement\n");
    }

    // Bind columns to fetch the results
    SQLCHAR col1[SQL_RESULT_LEN]{};         //DE MODIFICAT SQL_RESULT_LEN {LA FEL SI MAI JOS}

    if (SQLBindCol(SDataBase::sqlStmtHandle, 1, SQL_C_CHAR, col1, SQL_RESULT_LEN, nullptr) != SQL_SUCCESS)
        throw std::exception("Error binding column 1\n");

    char* password{}, * email{};
    email = strtok(_strdup(request), PAYLOAD_DELIM);
    password = strtok(NULL, PAYLOAD_DELIM);

    std::string buffer = "b";

    std::string lessons{};

    // Fetch and display results
    while (SQLFetch(SDataBase::sqlStmtHandle) == SQL_SUCCESS)
    {
        lessons += (char*)col1;
        lessons += PAYLOAD_DELIM;
    }

    // Eliberarea resurselor asociate statement-ului SQL
    SQLFreeStmt(SDataBase::sqlStmtHandle, SQL_DROP);
    //SI AICI DE MODIFICAT CU CLASA CMESSAGE
    buffer += lessons.size();
    buffer += lessons;

    return buffer;
}

std::string SDataBase::processRequest(char request[MAX_BUFFER_LEN])
{
    std::string buffer{};
    short endIndex = request[1];
    request[endIndex + 2] = '\0';      //Punem \0 acolo unde este nevoie
    strcpy(request + 1, request + 2); //Stergem caracterul cu lungime
    switch (request[0])
    {
    case 'l':
        buffer = this->processLoginRequest(request + 1);
        break;
    case 'r':
        buffer = this->processRegisterRequest(request + 1);
        break;
    case 'b':
        buffer = this->processGetLessonsRequest(request + 1);
        break;
    
    default:
        buffer = "E" + strlen("Invalid Option given.");
        buffer += "Invalid Option given.(";
        buffer += request;
        buffer += ").";
    }
    return buffer;
}
