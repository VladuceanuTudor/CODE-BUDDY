#ifndef UTILS_H
#define UTILS_H


#pragma once
#include <string>

int sock_init();
int registerCorectnessCheck(std::string email, std::string username, std::string passw1, std::string passw2);
int loginCorectnessCheck(std::string email, std::string passw);
#endif // UTILS_H
