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
    std::vector<IExercitiu*> getEx() {return this->exercitii;}
    std::string getText() { return this->curs; }
};

#endif // CLECTIE_H
