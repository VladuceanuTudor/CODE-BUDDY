#include "ServerMessageContainer.h"

ServerMessageContainer::ServerMessageContainer(char type, std::string Message){
    _type = type;
    _Message = Message;
}
std::string ServerMessageContainer::toSend(){
    std::string readyMess;
    readyMess += _type;
    readyMess += _Message.size();
    readyMess+= _Message;
    return readyMess;
}
int ServerMessageContainer::getSize(){
    return _Message.size()+2;
}
std::string ServerMessageContainer::getMess(){
    return this->_Message;
}
ServerMessageContainer::ServerMessageContainer(char *buff){
    _type = buff[0];
    int length= buff[1];

    buff[length+2] = '\0';
    _Message = buff+2;
}
void ServerMessageContainer::cutFront(int i){
    this->_Message = this->_Message.substr(i);
}
