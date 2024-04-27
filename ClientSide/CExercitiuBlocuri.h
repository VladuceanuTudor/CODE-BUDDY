#ifndef CEXERCITIUBLOCURI_H
#define CEXERCITIUBLOCURI_H
#include "AExercitiu.h"

class CExercitiuBlocuri : public AExercitiu
{
private:
    std::vector<std::string> varBlocuri;
    std::string raspunsCorect;
public:
    CExercitiuBlocuri(std::string cerinta, std::vector<std::string> varBlocuri, std::string raspunsCorect);
    char getType();
    std::vector<std::string> getListaRasp();
    std::string getRaspCorect();
};

#endif // CEXERCITIUBLOCURI_H
