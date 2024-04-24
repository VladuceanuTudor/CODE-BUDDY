#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>

class CTCPServer
{
private:
	short port;
	struct addrinfo* result = NULL;
	struct addrinfo hints;
	SOCKET listen_sock = NULL;
	std::list<SOCKET> client_sock{NULL};

public:
	CTCPServer(short listen_port);
	void wait_connection();
	int send(const char const* send_buf, const int size, SOCKET sock) const;
	int recv(char* recv_buf, const int size, SOCKET sock) const;
	const short getPort() const;
	SOCKET getLastSocket() const;
	void handleClient(SOCKET sock);
};

