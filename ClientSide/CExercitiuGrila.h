#ifndef CEXERCITIUGRILA_H
#define CEXERCITIUGRILA_H
#include "AExercitiu.h"

class CExercitiuGrila : public AExercitiu
{
private:
    std::vector<std::string> varRaspuns;
    std::string raspunsCorect;
public:
    CExercitiuGrila(std::string cerinta, std::vector<std::string> varRaspuns, std::string raspunsCorect);
    void printEx() { ; }
    bool checkAns() { return true; }
};

#endif // CEXERCITIUGRILA_H
