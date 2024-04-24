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
    void printEx() { ; }
    bool checkAns() { return true; }
};

#endif // CEXERCITIUBLOCURI_H
