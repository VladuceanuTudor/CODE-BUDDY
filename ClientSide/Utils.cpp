#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "Utils.h"
#include <regex>

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

int registerCorectnessCheck(std::string email, std::string username, std::string passw1, std::string passw2){
    if(passw1!=passw2)return 1;
    std::regex patternEmail(R"([A-Za-z0-9\._]+@[A-Za-z]+\.[A-Za-z]+)");
    if(!std::regex_match(email, patternEmail)) return 2;
    std::regex patternUser(R"([A-Za-z0-9_]+)");
    if(!std::regex_match(username, patternUser)) return 3;
    std::regex patternPassw(R"([A-Za-z0-9]+)");
    if(!std::regex_match(passw1, patternPassw)) return 4;
    return 0;
}

int loginCorectnessCheck(std::string email, std::string passw){
    std::regex patternEmail(R"([A-Za-z0-9\._]+@[A-Za-z]+\.[A-Za-z]+)");
    if(!std::regex_match(email, patternEmail)) return 1;
    std::regex patternPassw(R"([A-Za-z0-9]+)");
    if(!std::regex_match(passw, patternPassw)) return 2;
    return 0;
}

std::vector<std::string> SeparateWords(std::string source, char delim)
{
    std::istringstream ss(source);
    std::vector<std::string> output;
    std::string token{};
    while (std::getline(ss, token, delim))
    {
        output.push_back(token);
    }

    return output;
}
