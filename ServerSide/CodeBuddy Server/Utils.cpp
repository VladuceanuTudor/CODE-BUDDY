#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Utils.h"

int sock_init() {
    WSADATA wsaData;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return -1;
    }

    return 0;
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