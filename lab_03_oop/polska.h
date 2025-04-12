#ifndef POLSKA_H
#define POLSKA_H

#include <stack>
#include <unordered_map>
#include <string>

#include <queue>
#include <sstream>
#include <vector>
#include <limits>

#include <math.h>
#include <stdexcept>


using namespace std;

class Polska
{
private:
    string postfixExp;
public:
    bool isOperator(char c);
    int getPrecedence(char op);
    void toReversePolska(string infixExp);
    double findAnswer();
};

#endif // POLSKA_H
