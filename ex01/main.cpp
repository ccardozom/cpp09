#include <iostream>
#include "RPN.hpp"

using namespace std;

int main(int argc, char **argv){
    if(argc != 2){
        std::cout << "Se necesita un argumento válido." << std::endl;
        return -1;
    }
    else{
        RPN pila(argv[1]);

        pila.makeOperation();

    }
    
 /*  while (getline(ss, elem, ' ')) { // Se obtiene cada elemento de la cadena separado por espacios
    if (isdigit(elem[0])) { // Si el elemento es un dígito, se valida que sea un número entero del 0 al 9
      int num = stoi(elem);
      if (num < 0 || num > 9) { // Si el número no está en el rango correcto, se lanza una excepción
        throw invalid_argument("El número " + elem + " no es un dígito válido.");
      }
      s.push(num);
    } else if (elem == "+") { // Si el elemento es una suma, sacamos los dos elementos superiores de la pila y los sumamos
      int b = s.top(); s.pop();
      int a = s.top(); s.pop();
      s.push(a + b);
    } else if (elem == "-") { // Si el elemento es una resta, realizamos la operación similarmente
      int b = s.top(); s.pop();
      int a = s.top(); s.pop();
      s.push(a - b);
    } else if (elem == "*") { // Si el elemento es una multiplicación, realizamos la operación similarmente
      int b = s.top(); s.pop();
      int a = s.top(); s.pop();
      s.push(a * b);
    } else if (elem == "/") { // Si el elemento es una división, realizamos la operación similarmente
      int b = s.top(); s.pop();
      int a = s.top(); s.pop();
      s.push(a / b);
    } else { // Si el elemento no es un dígito ni una operación válida, se ignora
      continue;
    }
  }

  cout << s.top() << endl; */ // Imprimimos el resultado final de la operación
    return 0;
}
