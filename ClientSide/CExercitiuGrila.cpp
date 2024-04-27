#include "CExercitiuGrila.h"

CExercitiuGrila::CExercitiuGrila(std::string cerinta,
                                 std::vector<std::string> varRaspuns,
                                 std::string raspunsCorect) : AExercitiu(cerinta), varRaspuns{ varRaspuns }, raspunsCorect{ raspunsCorect } {
    ;
}

std::vector<std::string> CExercitiuGrila::getListaRasp(){
    return this->varRaspuns;
}

char CExercitiuGrila::getType(){
    return 'G';
}
std::string CExercitiuGrila::getRaspCorect(){
    return this->raspunsCorect;
}
