#pragma comment (lib, "Ws2_32.lib")
#include <iostream>
#include <thread>
#include "Utils.h"
#include "SDataBase.h"
#include "CTCPServer.h"

void handleClient(SOCKET sock) {
    char buffer[BUFFER_SEND_RECV_SIZE];
    CClientHandler ch(sock);
    while (true) {
        if (CTCPServer::recvData(buffer, sock) < 0)
            break;
        ServerMessageContainer message{};
        try
        {
            message = ch.handleRequest(buffer);
        }
        catch (const std::exception& e)
        {
            message = ServerMessageContainer(ERROR_CODE, "Error");
            std::cerr << e.what() << std::endl;
        }
        CTCPServer::sendData(message, sock);
    }
    CTCPServer::getInstance().freeSocket(sock);
}

int main() 
{
    SDataBase::getInstance();
    sock_init();

    CTCPServer& server = CTCPServer::getInstance();

    while (true)
    {
        SOCKET sock = server.wait_connection();   // Asteapta conexiune
        std::thread(handleClient, sock).detach();
    }
    SDataBase::destroyInstance();
    return 0;
}