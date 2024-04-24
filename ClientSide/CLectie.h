#ifndef CLECTIE_H
#define CLECTIE_H
#pragma once
#include "ILectie.h"


class CLectie : public ILectie
{
private:
    std::vector<IExercitiu*> exercitii;
    std::string curs;
    int _xp;
    bool completat;
public:
    CLectie(std::string curs) : curs{ curs } { ; }
    void addExercitiu(IExercitiu* ex);
    void setCompleted() { completat = true; }
    int getXp() { return _xp; }
    void print() { ; }
};

#endif // CLECTIE_H
