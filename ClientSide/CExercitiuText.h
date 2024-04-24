#ifndef CEXERCITIUTEXT_H
#define CEXERCITIUTEXT_H
#include "AExercitiu.h"

class CExercitiuText : public AExercitiu
{
private:
    std::string raspunsCorect;
public:
    CExercitiuText(std::string cerinta,
                   std::string raspunsCorect) : AExercitiu{cerinta}, raspunsCorect{raspunsCorect} {;}
    void printEx() { ; }
    bool checkAns() { return true; }
};

#endif // CEXERCITIUTEXT_H
