#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN &rhs)
{
    *this = rhs;
}

RPN::~RPN()
{}

RPN & RPN::operator=(const RPN &rhs)
{
    this->_pile = rhs._pile;
    return *this;
}

double RPN::calculate(char **argument)
{
    
   
    while (**argument != '\0')
    {
        char token = **argument;
        
        if (token > 48 && token < 58)
        {
            _pile.push(token - 48);
            (*argument)++;
        }
        else if (**argument == 32)
            (*argument)++;
        else if (**argument != 43 && **argument != 45 && **argument != 47 && **argument != 42){
            throw "Error";
        }
        else if (**argument == 43 || **argument == 45 || **argument == 47 || **argument == 42)
        {
            int number1;
            int number2;
            int result;
            if (_pile.size() < 2)
                throw "Error";
            number2 = _pile.top();
            _pile.pop();
            number1 = _pile.top();
            _pile.pop();
            if (**argument == 43)
                result = number1 + number2;
            if (**argument == 45)
                result = number1 - number2;
            if (**argument == 42){
                result = number1 * number2;}
            if (**argument == 47)
            {
                if (number2 == 0)
                    throw "Error";
                result = number1 / number2;
            }
            _pile.push(result);
            (*argument)++;
        }
    }
    if (_pile.size() != 1)
        throw "Error";
    return (_pile.top());
}

void RPN::printstack()
{
    while (!_pile.empty())
    {
        std::cout << _pile.top() << " ";
        _pile.pop();
    }
    std::cout << std::endl;
}