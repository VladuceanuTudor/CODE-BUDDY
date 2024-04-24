#include "climbaj.h"

void CLimbaj::addLectie(ILectie* l) {
    _lectii.push_back(l);
}
void CLimbaj::addNumeLectii(std::string nume){
    _numeLectii.push_back(nume);
}

std::vector<std::string> CLimbaj::getNumeLectii() const{
    return this->_numeLectii;
}

std::string CLimbaj::getName(){
    return this->_numeLimbaj;
}

void CLimbaj::setCompleted(int completed){
    this->_completed = completed;
}

int CLimbaj::getCompleted() {
    return this->_completed;
}

int CLimbaj::getLessonNrByName(std::string name){
    int i=0;
    for(const auto &lesson : this->_numeLectii){
        i++;
        if(name == lesson)return i;
    }
    return 0;
}
