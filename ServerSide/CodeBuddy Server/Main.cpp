#pragma comment (lib, "Ws2_32.lib")
#include <iostream>
#include <thread>
#include "Utils.h"
#include "SDataBase.h"
#include "CTCPServer.h"

void handleClient(CTCPServer& server, SOCKET sock) {
    server.handleClient(sock);
}

int main() {
    SDataBase::getInstance();
    sock_init();

    CTCPServer server(5520); // Port number

    while (true)
    {
        server.wait_connection();   // Asteapta conexiune
        std::thread(handleClient, std::ref(server), server.getLastSocket()).detach();
    }
    SDataBase::destroyInstance();
    return 0;
}