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
public:
    CLectie(std::string curs, int xp) : curs{ curs }, _xp{xp} { ; }
    void addExercitiu(IExercitiu* ex);
    int getXp() { return _xp; }
    void print() { ; }
};

#endif // CLECTIE_H
