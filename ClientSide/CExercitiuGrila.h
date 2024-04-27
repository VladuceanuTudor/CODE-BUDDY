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
    char getType();
    std::vector<std::string> getListaRasp();
    std::string getRaspCorect();
};

#endif // CEXERCITIUGRILA_H
