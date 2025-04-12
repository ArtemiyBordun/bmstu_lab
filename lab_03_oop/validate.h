#ifndef VALIDATE_H
#define VALIDATE_H

#include <string>
#include "polska.h"

using namespace std;

class Validate
{
private:
    string exp;
    Polska p;
    bool noErr;
    bool isPoint;
public:
    Validate(string exp, bool isPoint);
    void validate();
    void verPoint();
    void verBracket();

    bool getErr();
};

#endif // VALIDATE_H
