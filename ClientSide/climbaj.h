#ifndef CLIMBAJ_H
#define CLIMBAJ_H
#include <vector>
#include <string>
#include "ILectie.h"

class CLimbaj {
private:
    std::string _numeLimbaj;
    std::vector<ILectie*> _lectii;
    std::vector<std::string> _numeLectii;
public:
    CLimbaj(std::string nume) : _numeLimbaj { nume } { ; }
    void addLectie(ILectie* l) {
        _lectii.push_back(l);
    }
    void addNumeLectii(std::string nume){
        _numeLectii.push_back(nume);
    }

    std::vector<std::string> getNumeLectii() const{
        return this->_numeLectii;
    }

    std::string getName(){
        return this->_numeLimbaj;
    }
};

#endif // CLIMBAJ_H
