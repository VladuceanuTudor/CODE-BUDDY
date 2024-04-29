#include "ServerConnection.h"
#include "CExercitiuGrila.h"
#include "CExercitiuText.h"
#include "CExercitiuBlocuri.h"
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

    void _initExercitii(std::string numeLectie, std::string numeLimbaj, int nr_ex_lectie, ILectie*& lectie){

        ServerMessageContainer getExReq('e', numeLectie+'#'+numeLimbaj);
        client->send(getExReq.toSend().c_str(), getExReq.getSize());

        for(int i=0; i<nr_ex_lectie; i++){
            IExercitiu* ex;
            char buffer[1024];
            client->recv(buffer, sizeof(buffer));
            ServerMessageContainer getExReq(buffer);
            std::string tip_ex, cerinta, rasp1, rasp2, rasp3, rasp4, rasp_corect;

            std::stringstream ss(getExReq.getMess());
            std::string token;

            std::getline(ss, token, PAYLOAD_DELIM);
             tip_ex = token;
            std::getline(ss, token, PAYLOAD_DELIM);
             cerinta = token;
            std::getline(ss, token, PAYLOAD_DELIM);
             rasp1 = token;
            std::getline(ss, token, PAYLOAD_DELIM);
             rasp2 = token;
            std::getline(ss, token, PAYLOAD_DELIM);
             rasp3 = token;
            std::getline(ss, token, PAYLOAD_DELIM);
             rasp4 = token;
            std::getline(ss, token, PAYLOAD_DELIM);
             rasp_corect = token;

            std::vector<std::string> varRaspuns;
             varRaspuns.push_back(rasp1);
             varRaspuns.push_back(rasp2);
             varRaspuns.push_back(rasp3);
             varRaspuns.push_back(rasp4);

            if(tip_ex == "G")
            {
                ex = new CExercitiuGrila(cerinta, varRaspuns, rasp_corect);
            }
            else if(tip_ex == "T")
            {
                ex = new CExercitiuText(cerinta, rasp_corect);
            }
            else if(tip_ex == "B")
            {
                ex = new CExercitiuBlocuri(cerinta, varRaspuns, rasp_corect);
            }

            lectie->addExercitiu(ex);

        }

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
    }

    void _initLectie(ILectie*& lectie, std::string numeLectie, std::string numeLimbaj){
        //type:  payload:
        // -> L numeLectie
        // <- L content_lectie#xp_lectie#nr_ex_lectie
        // -> e limbaj numeLectie
        // <- e ex1 ... ex2 ... ex3 ...(while)(tip_ex#cerinta#rasp1#rasp2#rasp3#rasp4#rasp_corect#)
        ServerMessageContainer getLectieReq('L', numeLectie+'#'+numeLimbaj);
        client->send(getLectieReq.toSend().c_str(), getLectieReq.getSize());

        //lectie = new CLectie("Acesta este contentul de probaal unui curs \njajdnkjkja afoinva nfafjbje \nnafjbae fkjj af naef a", 30);
        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getLectie(buffer);

        std::stringstream ss(getLectie.getMess());
        std::string token;

        std::getline(ss, token, PAYLOAD_DELIM);
            std::string content_lectie = token;
        std::getline(ss, token, PAYLOAD_DELIM);
            int xp_lectie = std::stoi(token);
        std::getline(ss, token, PAYLOAD_DELIM);
            int nr_ex_lectie = std::stoi(token);

            lectie = new CLectie(content_lectie, xp_lectie);

            _initExercitii(numeLectie, numeLimbaj, nr_ex_lectie, lectie);

    }

    void send_Exercitiu_DONE(std::string numeLectie, std::string numeLimbaj){
        ServerMessageContainer sendLectieDONE('d', numeLimbaj+'#'+numeLectie);
        client->send(sendLectieDONE.toSend().c_str(), sendLectieDONE.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getACK(buffer);
        if(getACK.getMess()!="ok"){
            throw 1;
        }
    }

    void send_Inimi_decrease(){

        ServerMessageContainer sendLectieDONE('i', "");
        client->send(sendLectieDONE.toSend().c_str(), sendLectieDONE.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
    }

}
