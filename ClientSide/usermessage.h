#ifndef USERMESSAGE_H
#define USERMESSAGE_H
#include <string>

class userMessage
{
    std::string emitator;
    std::string continut;
public:
    userMessage(std::string emitator, std::string continut);
    std::string getEmitator();
    std::string getContinut();
};

#endif // USERMESSAGE_H
