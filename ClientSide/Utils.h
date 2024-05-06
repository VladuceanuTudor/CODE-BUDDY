#ifndef UTILS_H
#define UTILS_H


#pragma once
#include <string>
#include <vector>
#include <QTextEdit>

int sock_init();
int registerCorectnessCheck(std::string email, std::string username, std::string passw1, std::string passw2);
int loginCorectnessCheck(std::string email, std::string passw);
std::vector<std::string> SeparateWords(std::string source, char delim);

void appendLeftAlignedText(QTextEdit *textEdit, const QString &text);

void appendRightAlignedText(QTextEdit *textEdit, const QString &text);

#endif // UTILS_H
