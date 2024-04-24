#include "TCPClient.h"

TCPClient::TCPClient()
{
    int iResult;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


}

void TCPClient::connect(const char * ip_dest, short port_dest)
{
    int iResult;
    char port_str[6];
    _itoa_s(port_dest, port_str, 10);

    iResult = getaddrinfo(ip_dest, port_str, &hints, &ptr);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        exit(-1);
    }

    sock = socket(ptr->ai_family, ptr->ai_socktype,
                  ptr->ai_protocol);

    if (sock == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        exit(-1);
    }

    iResult = ::connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(sock);
        sock = INVALID_SOCKET;
        throw "Unable to connect to Server!";
    }


}

int TCPClient::send(const char * send_buff, const int size) const
{
    int send_bytes = ::send(sock, send_buff, size, 0);
    return send_bytes;
}

int TCPClient::recv(char* recv_buff, const int size) const
{
    int recv_bytes = ::recv(sock, recv_buff, size, 0);
    return recv_bytes;
}
