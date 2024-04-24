#include "ServerConnection.h"

namespace Connection{

void init_and_start_connection(char const* ip_dest, short port_dest){
    sock_init();

    client = new TCPClient();
    client->connect(ip_dest, port_dest);
}

void send_login(std::string username, std::string password, int& Status){
    std::string buffer;
    buffer = username;
    buffer += " ";
    buffer += password;
    qDebug() << buffer;

    ServerMessageContainer loginReq('l', buffer);
    qDebug() << loginReq.toSend();
    client->send(loginReq.toSend().c_str(), loginReq.getSize());

    char status[1024];
    client->recv(status, sizeof(status));

    ServerMessageContainer response(status);


    qDebug() << status;

    if(response.getMess() == "accepted")
        Status=1;
    else
        Status=0;


}

void send_register(std::string email, std::string username, std::string password, int& Status){
    std::string buffer;
    buffer = username;
    buffer += " ";
    buffer += email;
    buffer += " ";
    buffer += password;

    ServerMessageContainer registerReq('r', buffer);
    qDebug() << registerReq.toSend().c_str();
    client->send(registerReq.toSend().c_str(), registerReq.getSize());

    char status[1024];
    client->recv(status, sizeof(status));

    ServerMessageContainer response(status);

    qDebug() << status;

    if(response.getMess() == "accepted")
        Status=1;
    else
        Status=0;
}

void initLimbaj(CLimbaj& limbaj){
    ServerMessageContainer registerReq('b', limbaj.getName());
    client->send(registerReq.toSend().c_str(), registerReq.getSize());
}

}
