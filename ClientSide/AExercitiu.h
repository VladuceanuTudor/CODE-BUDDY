#ifndef AEXERCITIU_H
#define AEXERCITIU_H
#include "iexercitiu.h"
#include <string>
#include <vector>

class AExercitiu : public IExercitiu
{
protected:
    std::string _cerinta;

public:
    AExercitiu(std::string cerinta) : _cerinta{ cerinta } { ; }
};

#endif // AEXERCITIU_H
