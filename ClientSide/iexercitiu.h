#ifndef IEXERCITIU_H
#define IEXERCITIU_H
#include <string>
#include <vector>

class IExercitiu
{
public:
    virtual std::string getCerinta() = 0;
    virtual char getType() =0;
    virtual std::vector<std::string> getListaRasp() = 0;
    virtual std::string getRaspCorect() = 0;
    virtual void setRezolvat() = 0;
    virtual bool getRezolvat() = 0;
};

#endif // IEXERCITIU_H
