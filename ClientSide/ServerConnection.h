#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H



// // Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS
#include "TCPClient.h"
#include "Utils.h"
#include "ServerMessageContainer.h"
#include <QDebug>
#include "climbaj.h"
#include "CLectie.h"
#include <QLabel>
#include "user.h"
#include "chatapp.h"
#include <QApplication>
#include <qthread.h>

#define PAYLOAD_DELIM '#'

static TCPClient* client;

namespace Connection{

void init_and_start_connection(char const* ip_dest, short port_dest);

void send_login(std::string username, std::string password, int& Status, std::string& aux_username);

void send_register(std::string email, std::string username, std::string password, int& Status);

void initLimbaj(CLimbaj& limbaj);

void _initLectie(ILectie*& lectie, std::string numeLectie, std::string numeLimbaj);

void send_Exercitiu_DONE(std::string numeLectie, std::string numeLimbaj);

void send_Inimi_decrease();

void _req_Inimi_nr(int& nrInimi, QLabel* label);

void _req_GlobalLeaderB(std::list<User*>& leaderb);

void _req_LocalLeaderB(std::list<User*>& leaderb, int& myPos);

int send_payment(std::string nr_card, std::string nume_prenume, std::string cvv, std::string an, std::string luna);

void initChat(std::string myUsername);

void sendNewMessage(std::string message, std::string conv);

void receiveNewMessages(std::string myUsername, std::string numePrieten, QTextEdit *textEdit);

void messagesReceived(std::string numePrieten, QTextEdit *textEdit);

void addFriend(std::string nume_prieten);

}


#endif // SERVERCONNECTION_H
