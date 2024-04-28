#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <string>

class CTCPServer
{
private:
	struct addrinfo* result = NULL;
	struct addrinfo hints{};
	SOCKET listen_sock = NULL;
	std::list<SOCKET> client_sock{NULL};
	static CTCPServer* instance;

	static int send(const char const* send_buf, const int size, SOCKET sock);
	static int recv(char* recv_buf, const int size, SOCKET sock);

	CTCPServer(short listen_port);
	CTCPServer(const CTCPServer& other) = delete;

	//std::list<std::string> emails{};

public:
	static CTCPServer& getInstance();
	static void destroyInstance();
	void wait_connection();
	SOCKET getLastSocket() const;

	static void sendData(std::string message, SOCKET sock);
	static int recvData(char* buffer, SOCKET sock);
};

