#include "chatapp.h"

ChatApp* ChatApp::instance = nullptr;

ChatApp& ChatApp::getInstance()
{
    if (!ChatApp::instance)
        ChatApp::instance = new ChatApp();

    return (*ChatApp::instance);
}

void ChatApp::destroyInstance(){
    if (ChatApp::instance){
        delete ChatApp::instance;
        ChatApp::instance = nullptr;
    }
}

void ChatApp::initConversatie(std::string numeConversatie){
    this->_conversatii.push_back(new userChat(numeConversatie));
}

void ChatApp::initMesajToConversatie(std::string numeConversatie, std::string mesaj, std::string participant){
    for(auto conv : this->_conversatii){
        if(conv->getUser() == numeConversatie)
            conv->addMesaj(participant, mesaj);
    }
}

void ChatApp::initPrieten(std::string numePrieten){
    this->_prieteni.push_back(numePrieten);
}

std::list<std::string> ChatApp::getListaPrieteni(){
    return this->_prieteni;
}

std::list<userMessage* > ChatApp::getChatByPrieten(std::string numePrieten){
    for(auto conv : this->_conversatii){
        if(conv->getUser() == numePrieten)
            return conv->getConversatie();
    }
}
