#include "user.h"

User::User(std::string userName, int xp) {
    this->_xp = xp;
    this->_userName = userName;
}

std::string User::getUsername(){
    return this->_userName;
}
int User::getXp(){
    return this->_xp;
}
