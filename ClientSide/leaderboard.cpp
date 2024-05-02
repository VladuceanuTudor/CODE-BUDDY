#include "leaderboard.h"

void LeaderBoard::showGlobalLeaderboard(QVBoxLayout *verticalLayout){
    std::list<User*> _globalLeaderBoard;
    Connection::_req_GlobalLeaderB(_globalLeaderBoard);

}

void LeaderBoard::showLocalLeaderboard(QVBoxLayout *verticalLayout){
    std::list<User*> _localLeaderBoard;
    Connection::_req_LocalLeaderB(_localLeaderBoard);
}
