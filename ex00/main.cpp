#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
//#include "BitcoinExchange.hpp"

void checkLinedb(std::string line){
    std::istringstream stringStream(line);

    if (line.find(",") == std::string::npos)
        std::cout << "Error: bad input => " << line << std::endl;
    else{
        std::cout << line << std::endl;
    }
}

void checkLine(std::string line){
    std::istringstream stringStream(line);

    if (line.find("|") == std::string::npos)
        std::cout << "Error: bad input => " << line << std::endl;
    else{
        std::cout << line << std::endl;
    }
}

void checkInputFile(std::ifstream& input){
    if (!input.is_open()) {
        std::cout << "Error al leer el archivo de entrada" << std::endl;
        exit(0);
    }
}

int main(int cont, char **argv){
    std::string inputFile = "";
    std::string line;
    std::string dbline;
    int contador = 0;
    
    if(cont != 2){
        std::cout << "Error: se necesita un argumento para validar al solicitud" << std::endl;
        return 1;
    }
    else{
        inputFile = argv[1];
        std::ifstream filename(inputFile.c_str());
        checkInputFile(filename);
        while (std::getline(filename, line)){
            checkLine(line);
        }
        
        std::ifstream database("../cpp_09/data.csv");
        checkInputFile(database);
        std::getline(database, dbline);
        while(contador < 5){
            std::getline(database, dbline);
            checkLinedb(dbline);
            contador++;
        }
    }
    return 0;
}