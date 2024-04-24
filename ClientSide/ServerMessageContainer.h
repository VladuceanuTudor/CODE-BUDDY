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
    ServerMessageContainer(char type, std::string Message);
    std::string toSend();
    int getSize();
    std::string getMess();
    ServerMessageContainer(char *buff);
    void cutFront(int i);
};
