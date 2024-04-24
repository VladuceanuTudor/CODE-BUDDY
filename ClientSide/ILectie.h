#ifndef ILECTIE_H
#define ILECTIE_H
#include "IExercitiu.h"
#include <string>
#include <vector>


class ILectie
{
public:
    virtual void addExercitiu(IExercitiu* ex) = 0;
    virtual void print() = 0;
    virtual int getXp() = 0;
};

#endif // ILECTIE_H
