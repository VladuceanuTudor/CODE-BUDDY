#include "leaderboard.h"

void LeaderBoard::showGlobalLeaderboard(QVBoxLayout *verticalLayout, std::string myUserName){
    std::list<User*> _globalLeaderBoard;
    Connection::_req_GlobalLeaderB(_globalLeaderBoard);

    if (verticalLayout) {
        // Clear all layout items:
        while (QLayoutItem* item = verticalLayout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                // Check if the widget is a QLabel
                if (qobject_cast<QLabel*>(widget)) {
                    delete widget; // Delete the QLabel
                }
            }
            delete item;  // Delete the layout item
        }
    }


    verticalLayout->setAlignment(Qt::AlignCenter);

    int position = 1; // Initialize position counter

    for (User* user : _globalLeaderBoard) {

        QLabel* label = new QLabel(QString::fromStdString(std::to_string(position++) + ". " + user->getUsername() + " - XP: " + std::to_string(user->getXp())));

        // Apply styling to the QLabel
        if(user->getUsername() == myUserName)
            label->setStyleSheet("font-size: 18px; color: #FA8334; background-color: #808080; border: 1px solid grey; border-radius: 10px;");
        else
            label->setStyleSheet("font-size: 18px; color: #271033; background-color: #808080; border: 1px solid grey; border-radius: 10px;");
        label->setMinimumSize(400, 40); // Set minimum width and height
        label->setMaximumSize(400, 40);

        // Add the QLabel to the vertical layout
        verticalLayout->addWidget(label);
    }
}

void LeaderBoard::showLocalLeaderboard(QVBoxLayout *verticalLayout, std::string myUserName){
    std::list<User*> _localLeaderBoard;
    int myPos = 0;
    Connection::_req_LocalLeaderB(_localLeaderBoard, myPos);

    if (verticalLayout) {
        // Clear all layout items:
        while (QLayoutItem* item = verticalLayout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                // Check if the widget is a QLabel
                if (qobject_cast<QLabel*>(widget)) {
                    delete widget; // Delete the QLabel
                }
            }
            delete item;  // Delete the layout item
        }
    }

    verticalLayout->setAlignment(Qt::AlignCenter);

    int position = myPos; // Initialize position counter

    for (User* user : _localLeaderBoard) {

        QLabel* label = new QLabel(QString::fromStdString(std::to_string(position++) + ". " + user->getUsername() + " - XP: " + std::to_string(user->getXp())));

        // Apply styling to the QLabel
        if(user->getUsername() == myUserName)
            label->setStyleSheet("font-size: 18px; color: #CDDB50; background-color: #2A1E5C; border: 1px solid grey; border-radius: 10px;");
        else
            label->setStyleSheet("font-size: 18px; color: #EE4266; background-color: #2A1E5C; border: 1px solid grey; border-radius: 10px;");
        label->setMinimumSize(400, 40); // Set minimum width and height
        label->setMaximumSize(400, 40);

        // Add the QLabel to the vertical layout
        verticalLayout->addWidget(label);
    }
}
