#include "usermessage.h"

userMessage::userMessage(std::string emitator, std::string continut){
    this->emitator = emitator;
    this->continut = continut;
}
std::string userMessage::getEmitator(){
    return this->emitator;
}
std::string userMessage::getContinut(){
    return this->continut;
}
