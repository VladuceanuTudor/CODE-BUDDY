#include "ServerMessageContainer.h"

ServerMessageContainer::ServerMessageContainer(char type, std::string Message){
    _type = type;
    _Message = Message;
}
std::string ServerMessageContainer::toSend(){
    // std::string readyMess;
    // readyMess += _type;
    // readyMess += _Message.size();
    // readyMess+= _Message;
    // return readyMess;
    std::string buffer{};
    buffer += _type;
    int length = _Message.size();
    buffer.append(reinterpret_cast<char*>(&length), sizeof(int));
    buffer += _Message;
    return buffer;
}
int ServerMessageContainer::getSize(){
    return _Message.size()+5;
}
std::string ServerMessageContainer::getMess(){
    return this->_Message;
}
ServerMessageContainer::ServerMessageContainer(char *buff){
    // _type = buff[0];
    // int length= buff[1];

    // buff[length+2] = '\0';
    // _Message = buff+2;
    _type = buff[0];
    int length;
    memcpy(&length, &buff[1], sizeof(int));
    _Message = std::string(buff + sizeof(int) + sizeof(char), length);
}
void ServerMessageContainer::cutFront(int i){
    this->_Message = this->_Message.substr(i);
}
