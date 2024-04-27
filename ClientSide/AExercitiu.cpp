#include "AExercitiu.h"

std::string AExercitiu::getCerinta(){
    return this->_cerinta;
}

void AExercitiu::setRezolvat(){
    this->rezolvat = true;
}

bool AExercitiu::getRezolvat(){
    return this->rezolvat;
}
