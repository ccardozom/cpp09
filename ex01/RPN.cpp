#include "RPN.hpp"

RPN::RPN(){
    std::cout << "Se necesita un argumento para crear un objeto valido." << std::endl;
}

RPN::RPN(std::string str){
    this->str = str;
}

RPN::~RPN(){}

RPN::RPN(RPN& copy){
    this->str = copy.str;
    this->s = copy.s;
}

RPN &RPN::operator=(const RPN& rhs){
    if(this != &rhs){
        this->str = rhs.str;
        this->s = rhs.s;
    }
    return *this;
}

void RPN::makeOperation(){
    std::stringstream ss(str);
    std::string elem;

    while (std::getline(ss, elem, ' ')) { // Se obtiene cada elemento de la cadena separado por espacios
        std::cout << "Size s: " << elem[0] << std::endl;
        if (isdigit(elem[0])) { // Si el elemento es un dígito, se valida que sea un número entero del 0 al 9
            int num = atoi(elem.c_str());
            if (num > 9) { // Si el número no está en el rango correcto, se lanza una excepción
                std::cerr << "Error: el número no puede ser mayor a 9." << std::endl;
                exit(EXIT_FAILURE);
            }
            s.push(num);
        }
        else if(this->s.size() == 2){
            if (elem == "+"){ // Si el elemento es una suma, sacamos los dos elementos superiores de la pila y los sumamos
                int b = s.top(); s.pop();
                int a = s.top(); s.pop();
                s.push(a + b);
            }
            else if (elem == "-"){ // Si el elemento es una resta, realizamos la operación similarmente
                int b = s.top(); s.pop();
                int a = s.top(); s.pop();
                s.push(a - b);
            }
            else if (elem == "*"){ // Si el elemento es una multiplicación, realizamos la operación similarmente
                int b = s.top(); s.pop();
                int a = s.top(); s.pop();
                s.push(a * b);
            }
            else if (elem == "/") { // Si el elemento es una división, realizamos la operación similarmente
                int b = s.top(); s.pop();
                int a = s.top(); s.pop();
                if(b <= 0){
                    std::cerr << "El número no puede ser menor o igual a 0." << std::endl;
                    exit(EXIT_FAILURE);
                }
                s.push(a / b);
            }
        }
        /*else{
            std::cerr << "Faltan números para realizar la operación." << std::endl;
            exit(EXIT_FAILURE);
        }*/
        else { // Si el elemento no es un dígito ni una operación válida, se ignora
            continue;
        }
        std::cout << s.top() << std::endl; // Imprimimos el resultado final de la operación
    }
}