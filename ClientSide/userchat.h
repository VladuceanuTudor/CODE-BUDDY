#ifndef USERCHAT_H
#define USERCHAT_H
#include "usermessage.h"
#include <list>

class userChat
{
    std::string numeUser;
    std::list<userMessage* > corespondenta;
public:
    userChat(std::string numeUser);
    std::string getUser();
    void addMesaj(std::string nume, std::string continut);
    std::list<userMessage* > getConversatie();

};

#endif // USERCHAT_H
