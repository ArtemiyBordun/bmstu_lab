#include "polska.h"

bool Polska::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int Polska::getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '^')
        return 3;
    return 0;
}

void Polska::toReversePolska(string infixExp)
{
    stack<char> operators;

    for (char c : infixExp)
    {
        if (isalnum(c) || c == '.')
        {
            postfixExp += c;
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfixExp += operators.top();
                operators.pop();
            }
            operators.pop(); // Удаляем открывающую скобку
        } else if (isOperator(c)) {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(c)) {
                postfixExp += operators.top();
                operators.pop();
            }
            operators.push(c);
            postfixExp += ' ';
        }
    }

    while (!operators.empty()) {
        postfixExp += operators.top();
        operators.pop();
    }
}

double parse(string str)
{
    double result = stod(str); //Преобразуем строку в число
    return result;
}

double Polska::findAnswer()
{
    double result = 0; //Результат
    stack<double> temp; //Временный стек для решения

    for (int i = 0; i < postfixExp.length(); i++) //Для каждого символа в строке
    {
        //Если символ - цифра, то читаем все число и записываем на вершину стека
        if (isdigit(postfixExp[i]))
        {
            string a;

            while (postfixExp[i] != ' ' && !isOperator(postfixExp[i])) //Пока не разделитель
            {
                a += postfixExp[i]; //Добавляем
                i++;
                if (i == postfixExp.length())
                    break;
            }
            temp.push(parse(a)); //Записываем в стек
            i--;
        }
        else if (isOperator(postfixExp[i])) //Если символ - оператор
        {
            //Берем два последних значения из стека
            double a = temp.top();
            temp.pop();
            if (temp.empty())
                throw runtime_error("Incorrect entry");
            double b = temp.top();
            temp.pop();

            switch (postfixExp[i]) //И производим над ними действие, согласно оператору
            {
                case '+':
                    result = b + a;
                    break;
                case '-':
                    result = b - a;
                    break;
                case '*':
                    result = b * a;
                    break;
                case '/':
                    if (!a)
                        throw runtime_error("Division by zero is not allowed");
                    else
                        result = b / a;
                    break;
                case '^':
                    result = pow(b, a);
                    break;
            }
            temp.push(result); //Результат вычисления записываем обратно в стек
        }
    }
    return temp.top(); //Забираем результат всех вычислений из стека и возвращаем его
}
