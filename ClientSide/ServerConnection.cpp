#include "ServerConnection.h"
#include <sstream>

namespace Connection{

    void init_and_start_connection(char const* ip_dest, short port_dest){
        sock_init();

        client = new TCPClient();
        client->connect(ip_dest, port_dest);
    }

    void send_login(std::string username, std::string password, int& Status){
        std::string buffer;
        buffer = username;
        buffer += PAYLOAD_DELIM;
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
        buffer += PAYLOAD_DELIM;
        buffer += email;
        buffer += PAYLOAD_DELIM;
        buffer += password;

        ServerMessageContainer registerReq('r', buffer);
        qDebug() << registerReq.toSend().c_str();
        client->send(registerReq.toSend().c_str(), registerReq.getSize());

        char status[1024];
        client->recv(status, sizeof(status));

        ServerMessageContainer response(status);

        qDebug() << status;

        if(response.getMess() == "accepted")
            Status= 1;
        else if(response.getMess() == "user")
            Status = 2;
        else if(response.getMess() == "email")
            Status = 3;
    }

    void initLimbaj(CLimbaj& limbaj){
        ServerMessageContainer getLessonsReq('b', limbaj.getName());
        client->send(getLessonsReq.toSend().c_str(), getLessonsReq.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getLessons(buffer);

        std::stringstream ss(getLessons.getMess());
        std::string token;
        std::getline(ss, token, PAYLOAD_DELIM);
        limbaj.setCompleted(token[0]);

        while(std::getline(ss, token, PAYLOAD_DELIM))
        {
            limbaj.addNumeLectii(token);
        }
    }

    void _initLectie(ILectie* lectie, std::string numeLectie, std::string numeLimbaj){
        //type:  payload:
        // -> L numeLectie
        // <- L content_lectie#xp_lectie#nr_ex_lectie
        // -> e numeLectie
        // <- e ex1 ... ex2 ... ex3 ...(while)(tip_ex#cerinta#rasp1#rasp2#rasp3#rasp4#rasp_corect#)
        ServerMessageContainer getLectieReq('L', numeLectie+'#'+numeLimbaj);
        client->send(getLectieReq.toSend().c_str(), getLectieReq.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getLectie(buffer);


    }
}
