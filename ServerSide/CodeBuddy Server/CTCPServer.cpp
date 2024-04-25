#include "CTCPServer.h"
#include "SDataBase.h"
#include "CClientHandler.h"
#include <iostream>

CTCPServer::CTCPServer(short listen_port)
{
    int iResult;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    char port_str[6];
    _itoa_s(listen_port, port_str, 10);

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, port_str, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(-1);
    }

    listen_sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listen_sock == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        exit(-1);
    }

    iResult = bind(listen_sock, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        WSACleanup();
        exit(-1);
    }

    iResult = listen(listen_sock, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        WSACleanup();
        exit(-1);
    }
}

void CTCPServer::wait_connection()
{
    SOCKET sock = accept(listen_sock, NULL, NULL);
    if (sock == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        WSACleanup();
        exit(-1);
    }
    this->client_sock.push_back(sock);
    fprintf(stderr, "Connected on socket %llu\n", sock);
}

int CTCPServer::send(const char const* send_buff, const int size, SOCKET sock) const
{
    int send_bytes = ::send(sock, send_buff, size, 0);
    return send_bytes;
}

int CTCPServer::recv(char* recv_buff, const int size, SOCKET sock) const
{
    int recv_bytes = ::recv(sock, recv_buff, size, 0);
    return recv_bytes;
}

const short CTCPServer::getPort() const
{
    return this->port;
}

SOCKET CTCPServer::getLastSocket() const
{
    return this->client_sock.back();
}

void CTCPServer::handleClient(SOCKET sock)
{
    char buffer[1024];
    char responsebuffer[1024]{};
    CClientHandler ch;
    while (true) {
        int recv_bytes = this->recv(buffer, sizeof(buffer), sock);
        if (recv_bytes <= 0) {
            std::cout << "Client disconnected on socket " << sock << std::endl;
            break;
        }
        //Decriptare
        std::cout << "Socket " << sock << ": ";
        fwrite(buffer, 1, recv_bytes, stderr);
        std::cout << std::endl;
        std::string message{};
        try
        {
            message = ch.handleRequest(buffer);
        }
        catch (const std::exception& e)
        {
            message = ServerMessageContainer('E', "Error").getWholeString();
            std::cerr << e.what() << std::endl;
        }
        strcpy_s(responsebuffer, message.c_str());

        std::cout << "Response socket " << sock << ": ";
        std::cout << responsebuffer << std::endl;

        //Criptare
        this->send(responsebuffer, strlen(responsebuffer), sock);
    }
}
