#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <cstdlib>
#include <sstream>
#include <iostream>

class RPN
{
    public:
        RPN();
        RPN(const RPN &rhs);
        ~RPN();

        RPN &operator=(const RPN &rhs);

        double calculate(char **argument);
        void printstack();

    private:
        std::stack<int> _pile;
};

#endif