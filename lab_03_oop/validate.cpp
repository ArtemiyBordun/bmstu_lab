#include "validate.h"

Validate::Validate(string exp, bool isPoint) : exp(exp), isPoint(isPoint) { }

void Validate::validate()
{
    noErr = true;
    if (isPoint)
        verPoint();
    verBracket();
}

void Validate::verPoint()
{
    int i = exp.length() - 1;
    if (p.isOperator(exp[i]))
    {
        noErr = false;
        throw runtime_error("First, enter a number");
    }
    for (i; i >= 0 && !p.isOperator(exp[i]); i--)
    {
        if (exp[i] == '.')
        {
            noErr = false;
            throw runtime_error("There can only be one point in the number");
        }
    }
}

void Validate::verBracket()
{
    stack<char> stack;
    for (char c : exp) {
        switch (c) {

            case '(':
                stack.push(')');
                break;

            case ')':
                if (stack.empty() || stack.top() != c)
                {
                    noErr = false;
                    throw runtime_error("Check your brackets in the expression");
                }
                stack.pop();
                break;
            default:
                break;
        }
    }
    if (!stack.empty()) {
        noErr = false;
        throw runtime_error("Check your brackets in the expression");
    }
}

bool Validate::getErr()
{
    return noErr;
}
