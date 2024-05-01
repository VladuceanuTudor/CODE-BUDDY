#pragma once
#include <string>


class ServerMessageContainer{
private:
    char _type{};
    std::string _Message{};
public:
    ServerMessageContainer(){;}
    ServerMessageContainer(char type, std::string Message){
        _type = type;
        _Message = Message;
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
    char getType(){
        return this->_type;
    }
    std::string getWholeString()
    {
        std::string buffer{};
        buffer += this->_type;
        buffer += this->_Message.size();
        buffer += this->_Message;
        return buffer;
    }
};
