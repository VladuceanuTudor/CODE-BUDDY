#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "qboxlayout.h"
#include "user.h"
#include <list>
#include "ServerConnection.h"

class LeaderBoard
{
public:
    static void showGlobalLeaderboard(QVBoxLayout *verticalLayout, std::string myUserName);
    static void showLocalLeaderboard(QVBoxLayout *verticalLayout, std::string myUserName);
};

#endif // LEADERBOARD_H
