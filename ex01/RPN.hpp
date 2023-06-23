#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <sstream>
#include <cstdlib>

class RPN{
    public:
        RPN();
        RPN(std::string str);
        ~RPN();
        RPN(RPN& copy);
        RPN &operator=(const RPN& rhs);

        void makeOperation();
    private:
        std::stack<int> s;
        std::string str;
};

#endif