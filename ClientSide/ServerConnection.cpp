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

    void send_login(std::string username, std::string password, int& Status, std::string& aux_username){
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

        std::stringstream ss(response.getMess());
        std::string token;

        std::getline(ss, token, PAYLOAD_DELIM);
        if(token == "accepted")
            Status=1;
        std::getline(ss, token, PAYLOAD_DELIM);
            aux_username = token;
        std::getline(ss, token, PAYLOAD_DELIM);
        if(token == "p")
            Status=2;


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

        ServerMessageContainer sendInimiDEC('i', "1");
        client->send(sendInimiDEC.toSend().c_str(), sendInimiDEC.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
    }

    void _req_Inimi_nr(int& nrInimi, QLabel* label){
        ServerMessageContainer sendInimiREQ('i', "0");
        client->send(sendInimiREQ.toSend().c_str(), sendInimiREQ.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getInimi(buffer);
        nrInimi = std::stoi(getInimi.getMess());
        label->setText(QString::fromStdString(std::to_string(nrInimi)));
    }

    void _req_GlobalLeaderB(std::list<User*>& leaderb){
        ServerMessageContainer sendLBGreq('a', "g");
        client->send(sendLBGreq.toSend().c_str(), sendLBGreq.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getLBG(buffer);

        std::vector<std::string> mesajSpart = SeparateWords(getLBG.getMess(), '#');

        for(int i=0; i < mesajSpart.size(); i+=2){
            User* u = new User(mesajSpart[i], std::stoi(mesajSpart[i+1]));
            leaderb.push_back(u);
        }
    }

    void _req_LocalLeaderB(std::list<User*>& leaderb){
        ServerMessageContainer sendLBLreq('a', "l");
        client->send(sendLBLreq.toSend().c_str(), sendLBLreq.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getLBL(buffer);

        std::vector<std::string> mesajSpart = SeparateWords(getLBL.getMess(), '#');

        for(int i=0; i < mesajSpart.size(); i+=2){
            leaderb.push_back(new User(mesajSpart[i], std::stoi(mesajSpart[i+1])));
        }
    }

    int send_payment(std::string nr_card, std::string nume_prenume, std::string cvv, std::string an, std::string luna){
        //Numar Card(ex: 5123987654321098) Nume de pe Card(ex: Bob Williams) Expiration Date(ex: 2026-03-31) CVV(ex: 795)
        std::string _payload;
        _payload += nr_card;
        _payload += "#";
        _payload += nume_prenume;
        _payload += "#";
        _payload += "20";
        _payload += an;
        _payload += "#";
        _payload += luna;
        _payload += "#";
        _payload += cvv;
        ServerMessageContainer sendpayment('p', _payload);
        client->send(sendpayment.toSend().c_str(), sendpayment.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getPaymentStatus(buffer);
        if(getPaymentStatus.getMess() == "success")
            return 1;
        else return 0;
    }

    void initChat(std::string myUsername){
        ServerMessageContainer sendFriendsReq('f', "");
        client->send(sendFriendsReq.toSend().c_str(), sendFriendsReq.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getFriends(buffer);

        std::vector<std::string> mesajSpart = SeparateWords(getFriends.getMess(), '#');

        for(const auto& numePrieten : mesajSpart){
            ChatApp::getInstance().initPrieten(numePrieten);
            ChatApp::getInstance().initConversatie(numePrieten);
        }

        for(const auto& numePrieten : mesajSpart){
            ServerMessageContainer sendConvosReq('c', numePrieten);
            client->send(sendConvosReq.toSend().c_str(), sendConvosReq.getSize());

            //buffer = "c";
            client->recv(buffer, sizeof(buffer));
            ServerMessageContainer getConvo(buffer);

            std::vector<std::string> mesajSpart2 = SeparateWords(getConvo.getMess(), '#');

            for(int i=0; i < mesajSpart2.size(); i+=2){
                if(mesajSpart2[i] == myUsername)
                        ChatApp::getInstance().initMesajToConversatie(numePrieten, mesajSpart2[i+1]);
                    else
                        ChatApp::getInstance().initMesajToConversatie(numePrieten, mesajSpart2[i+1], mesajSpart2[i]);
            }

        }

        // ChatApp::getInstance().initPrieten("Prieten 1");
        // ChatApp::getInstance().initPrieten("Prieten 2");
        // ChatApp::getInstance().initPrieten("Prieten 3");
        // ChatApp::getInstance().initPrieten("Prieten 4");

        // ChatApp::getInstance().initConversatie("Prieten 1");
        // ChatApp::getInstance().initConversatie("Prieten 2");
        // ChatApp::getInstance().initConversatie("Prieten 3");
        // ChatApp::getInstance().initConversatie("Prieten 4");

        // ChatApp::getInstance().initMesajToConversatie("Prieten 1", "Ce faci?", "Prieten 1");
        // ChatApp::getInstance().initMesajToConversatie("Prieten 1", "Bine, tu?");
        // ChatApp::getInstance().initMesajToConversatie("Prieten 1", "Bine si eu.", "Prieten 1");
        // ChatApp::getInstance().initMesajToConversatie("Prieten 1", "Scriu cod.", "Prieten 1");
        // ChatApp::getInstance().initMesajToConversatie("Prieten 1", "Super");

    }


    void sendNewMessage(std::string message, std::string conv){
        conv+="#";
        conv+=message;
        ServerMessageContainer sendNM('N', conv);
        client->send(sendNM.toSend().c_str(), sendNM.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getAck(buffer);
        if(getAck.getMess() != "Done")
            throw 1;
    }

    void receiveNewMessages(std::string myUsername, std::string numePrieten, QTextEdit *textEdit){
        ServerMessageContainer sendNM('n', numePrieten);
        client->send(sendNM.toSend().c_str(), sendNM.getSize());

        char buffer[1024];
        client->recv(buffer, sizeof(buffer));
        ServerMessageContainer getConvo(buffer);

        std::vector<std::string> mesajSpart = SeparateWords(getConvo.getMess(), '#');

        std::vector<QString> messagesToDisplay; // Store messages in a separate vector

        for(int i=0; i < mesajSpart.size(); i++)
                ChatApp::getInstance().initMesajToConversatie(numePrieten, mesajSpart[i], numePrieten);

        // Update the textEdit in the main thread using a queued connection
        // QObject::connect(qApp, &QApplication::aboutToQuit, qApp, [textEdit, numePrieten]() {
        //         textEdit->clear();
        //         for (userMessage* mesaj : ChatApp::getInstance().getChatByPrieten(numePrieten))
        //             if(mesaj->getEmitator() == "eu")
        //                 appendLeftAlignedText(textEdit, QString::fromStdString("Eu:   " + mesaj->getContinut()));
        //             else
        //                 appendRightAlignedText(textEdit, QString::fromStdString(mesaj->getEmitator() + ":   " + mesaj->getContinut()));

        //     }, Qt::QueuedConnection);

    }
}
