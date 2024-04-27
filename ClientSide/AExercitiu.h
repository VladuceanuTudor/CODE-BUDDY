#ifndef AEXERCITIU_H
#define AEXERCITIU_H
#include "iexercitiu.h"

class AExercitiu : public IExercitiu
{
protected:
    std::string _cerinta;
    bool rezolvat;

public:
    AExercitiu(std::string cerinta) : _cerinta{ cerinta }, rezolvat{false}{ ; }
    std::string getCerinta();
    void setRezolvat();
    bool getRezolvat();
};

#endif // AEXERCITIU_H
