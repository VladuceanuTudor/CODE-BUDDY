#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include "CChatManager.h"
#include "ServerMessageContainer.h"

class CTCPServer
{
private:
	struct addrinfo* result = NULL;
	struct addrinfo hints{};
	SOCKET listen_sock = NULL;
	std::map<std::string, SOCKET> socketMail{};
	CChatManager* chatManager{ nullptr };
	static CTCPServer* instance;

	static int send(const char const* send_buf, const int size, SOCKET sock);
	static int recv(char* recv_buf, const int size, SOCKET sock);

	CTCPServer(short listen_port);
	CTCPServer(const CTCPServer& other) = delete;

	~CTCPServer();

public:
	static CTCPServer& getInstance();
	static void destroyInstance();
	void addMail(SOCKET sock, std::string email);
	bool existsMail(std::string email);
	void freeSocket(SOCKET sock);
	SOCKET wait_connection();

	static void sendData(ServerMessageContainer message, SOCKET sock);
	static int recvData(char* buffer, SOCKET sock);

	void addMessage(const std::string& userSenging, const std::string& userReceiving, const std::string& message);
	ServerMessageContainer getNewMessagesFromUser(const std::string& userSenging, const std::string& userReceiving);
};

