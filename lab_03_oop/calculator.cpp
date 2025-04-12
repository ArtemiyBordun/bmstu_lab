#include "calculator.h"

Calculator::Calculator(string exp, string operation) : exp(exp), operation(operation) {}

void Calculator::findAnswer()
{
    replaceMathCommand(exp);
    exp = solutionExp(exp);
}

string Calculator::solutionExp(string exp)
{
    p.toReversePolska(exp);
    double result = p.findAnswer();
    exp = deleteNull(result);
    return exp;
}

void Calculator::replaceMathCommand(string exp)
{
    string opers[] = {"sqrt", "sin", "cos", "tg", "ctg"};
    for (const string& oper : opers)
    {
        exp = findOper(oper);
    }
}

string Calculator::findOper(string oper)
{
    while (true)
    {
        size_t pos = exp.find(oper);
        if (pos == string::npos)
            break;
        else
            exp = solutionOper(pos, oper);

    }
    return exp;
}

string Calculator::solutionOper(size_t pos, string oper)
{
    exp.erase(pos, oper.length() + 1);
    int i = pos;
    for (i; exp[i] != ')'; i++) {}
    exp.erase(i, 1);

    string numStr = exp.substr(pos);
    int lenght = numStr.length();

    numStr = solutionExp(numStr);

    double num;
    if (oper == "sqrt")
        num = solutionSqrt(numStr);
    else if (oper == "sin")
        num = solutionSin(numStr);
    else if (oper == "cos")
        num = solutionCos(numStr);
    else if (oper == "tg")
        num = solutionTg(numStr);
    else if (oper == "ctg")
        num = solutionCtg(numStr);

    numStr = deleteNull(num);
    exp.replace(pos, lenght, numStr);
    return exp;
}

void Calculator::findNum()
{
    int i = exp.length();

    for (i; i >= 0 && !p.isOperator(exp[i]); i--) {}

    string numStr = exp.substr(i + 1);
    double num;

    if (operation == "1/x")
        num = solutionPropor(numStr);
    else if (operation == "%")
        num = solutionPercent(numStr);
    else
        return;

    numStr = deleteNull(num);
    exp.replace(i + 1, numStr.length(), numStr);
}

void Calculator::addMathCommand()
{
    int i = exp.length();
    if (p.isOperator(exp[i - 1]))
        exp += operation + "(";
    else
    {
        for (i; i >= 0 && !p.isOperator(exp[i]); i--) {}
        string command = operation + "(";

        exp.insert(i + 1, command);
    }
}

double Calculator::solutionPropor(string numStr)
{
    if (!stod(numStr))
        throw runtime_error("This function is not applicable to zero");
    double num = 1 / stod(numStr);
    return num;
}

double Calculator::solutionPercent(string numStr)
{
    double num = stod(numStr) / 100;
    return num;
}

double Calculator::solutionSqrt(string numStr)
{
    if (stod(numStr) < 0)
        throw runtime_error("The number must be positive");
    double num = sqrt(stod(numStr));
    return num;
}

double Calculator::solutionSin(string numStr)
{
    double num = sin(stod(numStr));
    return num;
}

double Calculator::solutionCos(string numStr)
{
    double num = cos(stod(numStr));
    return num;
}

double Calculator::solutionTg(string numStr)
{
    double num = tan(stod(numStr));
    return num;
}

double Calculator::solutionCtg(string numStr)
{
    double num = 1 / tan(stod(numStr));
    return num;
}

string Calculator::getExp()
{
    return exp;
}

string Calculator::deleteNull(double num)
{
    stringstream stream;
    stream << num;          //убираем нули
    return stream.str();
}
