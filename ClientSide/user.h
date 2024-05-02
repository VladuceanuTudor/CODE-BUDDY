#ifndef USER_H
#define USER_H
#include <string>

class User
{
private:
    std::string _userName;
    int _xp;
public:
    User(std::string userName, int xp);
    std::string getUsername();
    int getXp();
};

#endif // USER_H
