#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H



// // Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS
#include "TCPClient.h"
#include "Utils.h"
#include "ServerMessageContainer.h"
#include <QDebug>
#include "climbaj.h"

static TCPClient* client;

namespace Connection{

void init_and_start_connection(char const* ip_dest, short port_dest);

void send_login(std::string username, std::string password, int& Status);

void send_register(std::string email, std::string username, std::string password, int& Status);

void initLimbaj(CLimbaj& limbaj);
}

#endif // SERVERCONNECTION_H
