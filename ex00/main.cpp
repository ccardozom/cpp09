#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

typedef struct s_data{
    std::string line;
    std::string year;
    std::string month;
    std::string day;
    std::string value;
    std::string err;
}t_data;

typedef struct s_db{
    std::string key;
    std::string value;
    std::string err;
}t_db;

//verifica la linea de la base de datos
void checkLinedb(std::string line){
    std::istringstream stringStream(line);

    if (line.find(",") == std::string::npos)
        std::cout << "Error: bad input => " << line << std::endl;
    else{
        std::cout << line << std::endl;
    }
}

//imprime una linea
void printLine(t_data data, std::string value=""){
    if (data.err != ""){
        std::cout << data.err << std::endl;
    }
    else{
        data.line = data.line + value;
        std::cout << data.line << std::endl;
    }
}

//verica si existen en la linea los caracteres que se pasan y contabiliza la cantidad de veces que se repiten
int charCount(std::string str, const char character1,const char character2='\0'){
    int cont = 0;
    std::string::iterator it = str.begin();
    while(it != str.end()){
        if(character2){
            if(*it == character1)
                return cont;
            if(*it == character2)
                cont++;
        }
        else
            if(*it == character1)
                cont++;
        it++;
    }
    return cont;
}

//verifica la linea del archivo input
std::string checkLine(const std::string line){
    std::istringstream stringStream(line);

    if (charCount(line, '|') != 1 || charCount(line, '|', '-') != 2){
        //std::cout << "Error: bad input => " << line << std::endl;
        //return NULL;
    }
    else{
       // printLine(line);
    }
    return line;
}

//verifica si se puede abrir el archivo
void checkInputFile(const std::ifstream& input){
    if (!input.is_open()) {
        std::cerr << "Error al leer el archivo de entrada" << std::endl;
        exit(EXIT_FAILURE);
    }
}
/*
template<typename T>
std::string bindDate(T data){
    std::string str;
    std::stringstream ss;
    ss << 
    return str;
}*/

//verifica el formato de los datos almacenados en la estructura t_data
template<typename T>
int checkstruct(T& data){
    //std::cout << "longitud de year: " <<data.day.length() << std::endl;

    if(data.year.length() != 4 || data.month.length() != 2 || data.day.length() != 2){
        data.err = "Error: bad input => " + data.line;
        return false;
    }
    return true;
}
/*
template<>
int checkstruct<t_db>(t_db database){

}
*/

void initData(t_data data){
    data.year = "";
    data.month = "";
    data.day = "";
    data.value = "";
    data.err = "";
}

//carga los datos de la linea en un vector
void loadDate(std::string line, std::vector<t_data>& Date){
    t_data data;
    std::string str_extract;
    int npos = 0;
    std::vector<std::string> tokens;
    std::string token;
    initData(data);
    data.line = line;
    if (!line.empty()){
        npos = line.find('|');
        if(npos > 0){
            //std::cout << "line: " << line << std::endl;
            //std::cout << "npos: " << npos << std::endl;
            str_extract = line.substr(0,npos);
            std::stringstream ss(str_extract);
            std::getline(ss, data.year, '-');    //por aqui hay un fallo al cargar day esta cargando tres valores
            std::getline(ss, data.month, '-');
            std::getline(ss, data.day, ' ');
            //std::cout << "Fecha completa: " << ss.str() << std::endl;
            //std::cout << "day: " << data.day << std::endl;
            
            data.value = line.substr(npos+2, line.length());
            //std::cout << "value: " << data.value << std::endl;
            //std::cout << "longitud de value: " << data.value.length() << std::endl;
            //std::cout << "longitud de year: " <<date.year.length() << std::endl;
            if (checkstruct<t_data>(data))
            //std::cout << "year: " << date.year << " month: " << date.month << " day: " << date.day << " value: " << date.value << std::endl;
                Date.push_back(data);
        }
        else{
            data.err =  "Error: bad input => " + data.line;
            //std::cout << data.err << std::endl;
        }
    }
    printLine(data);
   // else
     //   std::cout << data.err << std::endl;
    //std::cout << "stringDate: "<< stringDate << std::endl;
}

int main(int cont, char **argv){
    std::string inputFile = "";
    std::string line;
    std::string dbline;
    std::vector<t_data> inputData;
    
    if(cont != 2){
        std::cout << "Error: se necesita un argumento para validar al solicitud" << std::endl;
        return 1;
    }
    else{
        
        inputFile = argv[1];
        std::ifstream filename(inputFile.c_str());
        
        //verifica si se puede leer el archivo de entrada
        checkInputFile(filename);

        //descartamos la primera linea
        std::getline(filename, line);
        //printLine(line);

        //analizamos las lineas del archivo de entrada
        while (std::getline(filename, line)){
            loadDate(line, inputData);
        }

/*
    int contador = 0;
        std::ifstream database("../cpp_09/data.csv");
        
        //verifica si se puede leer la base de datos
        checkInputFile(database);

        //descartamos la cabecera que se encuentra en la primera linea
        std::getline(database, dbline);

        while(contador < 5){
            std::getline(database, dbline);
            checkLinedb(dbline);
            contador++;
        }
  */     
        }
    return 0;
}