#pragma comment (lib, "Ws2_32.lib")
#include <iostream>
#include <thread>
#include "Utils.h"
#include "SDataBase.h"
#include "CTCPServer.h"

void handleClient(CTCPServer& server, SOCKET sock) {
    char buffer[BUFFER_SEND_RECV_SIZE];
    CClientHandler ch(sock);
    while (true) {
        if (CTCPServer::recvData(buffer, sock) < 0)
            break;
        std::string message{};
        try
        {
            message = ch.handleRequest(buffer);
        }
        catch (const std::exception& e)
        {
            message = ServerMessageContainer(ERROR_CODE, "Error").getWholeString();
            std::cerr << e.what() << std::endl;
        }
        CTCPServer::sendData(message, sock);
    }
}

int main() 
{
    SDataBase::getInstance();
    sock_init();

    CTCPServer& server = CTCPServer::getInstance();

    while (true)
    {
        server.wait_connection();   // Asteapta conexiune
        std::thread(handleClient, std::ref(server), server.getLastSocket()).detach();
    }
    SDataBase::destroyInstance();
    return 0;
}