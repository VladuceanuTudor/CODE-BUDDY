#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "qboxlayout.h"
#include "user.h"
#include <list>
#include "ServerConnection.h"

class LeaderBoard
{
public:
    static void showGlobalLeaderboard(QVBoxLayout *verticalLayout);
    static void showLocalLeaderboard(QVBoxLayout *verticalLayout);
};

#endif // LEADERBOARD_H
