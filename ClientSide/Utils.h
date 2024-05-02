#ifndef UTILS_H
#define UTILS_H


#pragma once
#include <string>
#include <vector>

int sock_init();
int registerCorectnessCheck(std::string email, std::string username, std::string passw1, std::string passw2);
int loginCorectnessCheck(std::string email, std::string passw);
std::vector<std::string> SeparateWords(std::string source, char delim);
#endif // UTILS_H
