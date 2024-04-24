#ifndef SERVERMESSAGECONTAINER_H
#define SERVERMESSAGECONTAINER_H

#include <sec_api/string_s.h>
#include <string>
#endif // SERVERMESSAGECONTAINER_H


class ServerMessageContainer{
private:
    char _type;
    std::string _Message;
public:
    ServerMessageContainer(){;}
    ServerMessageContainer(char type, std::string Message){
        _type = type;
        _Message = Message;
    }
    std::string toSend(){
        std::string readyMess;
        readyMess += _type;
        readyMess += _Message.size();
        readyMess+= _Message;
        return readyMess;
    }
    int getSize(){
        return _Message.size()+2;
    }
    std::string getMess(){
        return this->_Message;
    }
    ServerMessageContainer(char *buff){
        _type = buff[0];
        int length= buff[1];

        buff[length+2] = '\0';
        _Message = buff+2;
    }
    void cutFront(int i){
        this->_Message = this->_Message.substr(2);
    }
};
