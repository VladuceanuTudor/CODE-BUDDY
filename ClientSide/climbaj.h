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
    int _completed;
public:
    CLimbaj(std::string nume) : _numeLimbaj { nume } { ; }
    void addLectie(ILectie* l);
    void addNumeLectii(std::string nume);

    std::vector<std::string> getNumeLectii() const;

    std::string getName();

    void setCompleted(int completed);

    int getCompleted();

    int getLessonNrByName(std::string name);
};

#endif // CLIMBAJ_H
