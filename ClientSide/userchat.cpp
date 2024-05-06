#include "userchat.h"

userChat::userChat(std::string numeUser){
    this->numeUser = numeUser;
}
std::string userChat::getUser(){
    return this->numeUser;
}
void userChat::addMesaj(std::string nume, std::string continut){
    this->corespondenta.push_back(new userMessage(nume, continut));
}
std::list<userMessage* > userChat::getConversatie(){
    return this->corespondenta;
}
