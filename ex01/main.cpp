#include "RPN.hpp"

int main (int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "[Usage]" << argv[0] << " [\"number1, number2, operand...\"]" << std::endl;
        return (1);
    }
    try
    {
        RPN rpn;
        std::cout << rpn.calculate(++argv) << std::endl;
    }
    catch(const char *e)
    {
        std::cout << e << '\n';
        return 1;
    }

    return 0; 
}