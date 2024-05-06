#ifndef CHATAPP_H
#define CHATAPP_H
#include "userchat.h"

class ChatApp
{
public:
    static ChatApp& getInstance();
    static void destroyInstance();

    void initConversatie(std::string numeConversatie);
    void initMesajToConversatie(std::string numeConversatie, std::string mesaj, std::string participant="eu");
    void initPrieten(std::string numePrieten);

    std::list<std::string> getListaPrieteni();
    std::list<userMessage* > getChatByPrieten(std::string numePrieten);

private:
    static ChatApp* instance;

    std::list<userChat* > _conversatii;
    std::list<std::string> _prieteni;

    ChatApp(){};
    ChatApp(const ChatApp&) {};
    ~ChatApp(){};
};

#endif // CHATAPP_H
