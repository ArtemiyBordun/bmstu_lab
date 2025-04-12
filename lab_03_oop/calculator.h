#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include "polska.h"

using namespace std;

class Calculator
{
private:
    string exp;
    Polska p;
    string operation;
public:
    Calculator(string exp, string operation);
    ~Calculator() = default;

    void findAnswer();
    string solutionExp(string exp);
    void findNum();
    void addMathCommand();
    void replaceMathCommand(string exp);
    string findOper(string oper);
    string solutionOper(size_t pos, string oper);

    double solutionPropor(string numStr);
    double solutionPercent(string numStr);

    string solutionMathCommand(string numStr, string operation);
    double solutionSqrt(string numStr);

    double solutionSin(string numStr);
    double solutionCos(string numStr);
    double solutionTg(string numStr);
    double solutionCtg(string numStr);

    string deleteNull(double num);

    string getExp();
};

#endif // CALCULATOR_H
