#include "CExercitiuBlocuri.h"

CExercitiuBlocuri::CExercitiuBlocuri(std::string cerinta,
                                     std::vector<std::string> varBlocuri,
                                     std::string raspunsCorect) : AExercitiu{ cerinta },
                                     varBlocuri{ varBlocuri },
                                     raspunsCorect{ raspunsCorect } {
    ;
}

std::vector<std::string> CExercitiuBlocuri::getListaRasp(){
    return this->varBlocuri;
}

char CExercitiuBlocuri::getType(){
    return 'B';
}
std::string CExercitiuBlocuri::getRaspCorect(){
    return this->raspunsCorect;
}
