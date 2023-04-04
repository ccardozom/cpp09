#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <vector>
#include <typeinfo>

struct t_data{
    std::string line;
    std::string year;
    std::string month;
    std::string day;
    std::string value;
    bool neg;
    std::string err;
};

struct t_db{
    std::string year;
    std::string month;
    std::string day;
    std::string value;
    std::string err;
    std::string line;
};

template<typename T>
void initData(T data){
    data.line = "";
    data.year = "";
    data.month = "";
    data.day = "";
    data.value = "";
    data.err = "";
}

template<>
void initData(t_db data){
    data.year = "";
    data.month = "";
    data.day = "";
    data.value = "";
    data.err = "";
    data.line = "";
}

//imprime una linea
void printLine(t_data& data, std::string value=""){
    if (data.err != ""){
        if (data.err == "Error: bad input")
            std::cout << data.err + " => " + data.line << std::endl;
        else
            std::cout << data.err << std::endl;
    }
    else{
        data.line = data.year + "-" + data.month + "-" + data.day + " => " + data.value + " = " + value;
        std::cout << data.line << std::endl;
    }
}

//verifica si se puede abrir el archivo
void openInputFile(const std::ifstream& file){
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool isNumeric(const std::string& cadena, int onlynum=0) {
    if(onlynum == 0)
        return cadena.find_first_not_of(".0123456789") == std::string::npos;
    return cadena.find_first_not_of("0123456789") == std::string::npos;
}

bool validateDataLen(std::string str, size_t len){
    return str.length() != len;
}

bool isfloat(std::string str){
    std::string dotstring;
    int pos = 0;
    pos = str.find('.');
    if(pos > 0){
        dotstring = str.substr(++pos, str.length());
        return isNumeric(dotstring,1);
    }
    return isNumeric(str);    
    }
template<typename T>
bool validateValue(T& data){
    if(*data.value.begin() == '-'){
        data.err = "Error: not a positive number.";
        return false;
    }
    if(std::atof(data.value.c_str()) > 1000){
        data.err = "Error: too large a number.";
        return false;
    }
    else if(!isNumeric(data.value) || !isfloat(data.value) || data.value.empty()){
        data.err = "Error: bad input";
        return false;
    }
    return true;
}

bool leap_year(std::string year){
    return std::atoi(year.c_str()) % 4 == 0 && (std::atoi(year.c_str()) % 100 != 0 || std::atoi(year.c_str()) % 400 == 0);
}

//verifica el formato de los datos almacenados en la estructura t_data
template<typename T>
int validateStruct(T& data){
    if(validateDataLen(data.year, 4) || !isNumeric(data.year) || validateDataLen(data.month, 2) ||
    std::atoi(data.month.c_str()) > 12 || !isNumeric(data.month) || validateDataLen(data.day, 2) ||
    std::atoi(data.day.c_str()) > 31 || !isNumeric(data.day) ){
        data.err = "Error: bad input";
        return false;
    }
    else  if(data.month == "02"){
        if(leap_year(data.year)){
            if(std::atoi(data.day.c_str()) > 29){
                data.err = "Error: bad input";
                return false;
            }
        }
        else{
            if(std::atoi(data.day.c_str()) > 28){
                data.err = "Error: bad input";
                return false;
            }
        }
    }
    else if(!validateValue<T>(data)){
        return false;
    }
    return true;
}

void eraseSpaces(std::string& line){
    int pos = 0;
    while(line[pos] == ' '){pos++;}
        if(pos > 0){
            line.erase(0,pos);
        }
}


//carga los datos de la linea en un vector
template<typename T>
void loadDate(std::vector<T>& vData, std::string line){  //ver si podemos hacer que sirva para dos archivos
    T sdata;
    std::string str_extract;
    int npos = 0;

    initData(sdata);
    if (!line.empty()){
        eraseSpaces(line);
       // std::cout << "line: " << line << std::endl;
        sdata.line = line;
        npos = line.find('|');
        if(npos > 0){
            str_extract = line.substr(0,npos);
            std::stringstream ss(str_extract);
            std::getline(ss, sdata.year, '-');  
            std::getline(ss, sdata.month, '-');
            std::getline(ss, sdata.day, ' ');
            while(line[++npos] == ' '){}
            sdata.value = line.substr(npos, line.length());
            validateStruct<t_data>(sdata);
            sdata.line = sdata.year + "-" + sdata.month + "-"  + sdata.day + " | " + sdata.value;
        }
        else
            sdata.err =  "Error: bad input";
    }
    vData.push_back(sdata);
}

template<>
void loadDate(std::vector<t_db>& vData, std::string line){
    t_db sdata;
    std::string str_extract;
    int npos = 0;

    initData(sdata);
    npos = line.find(',');
    if(npos > 0){
        str_extract = line.substr(0, npos);
        std::stringstream ss(str_extract);
        std::getline(ss, sdata.year, '-');  
        std::getline(ss, sdata.month, '-');
        std::getline(ss, sdata.day, ',');
        while(line[++npos] == ' '){}
        sdata.value = line.substr(npos, line.length());
        validateStruct<t_db>(sdata);
    }
    else
        sdata.err = "Error: bad database line";
    vData.push_back(sdata);
}

template<typename data>
void readInputFile(std::vector<data>& Data, std::string filename){
    std::string line;
    std::string firsLine;
    std::ifstream file(filename.c_str());

    //verifica si se puede leer el archivo de entrada
    openInputFile(file);
    
    std::getline(file, firsLine);
    //std::cout << firsLine << std::endl;

    while (std::getline(file, line)){
        if(!line.empty())
            loadDate(Data, line);            
    }
}

template <typename T> 
std::string to_string(const T& n){
    std::ostringstream stm ;
    if(n < 10)
        stm << 0 << n ;
    else
        stm << n;
    return stm.str() ;
}

//buscando el valor de btc en la base de datos
float getValue(const t_data inputData, std::vector<std::pair<std::string, double> > vPairdb){
    float value;
    std::string date;
    std::vector<std::pair<std::string, double> >::iterator it;
    if(inputData.err == ""){
        int day = atoi(inputData.day.c_str());
        int month = atoi(inputData.month.c_str());
        int year = atoi(inputData.year.c_str());
        while(true && year > 2008){
            it = vPairdb.begin();
            if(day == 0){
                day = 31;
                month -= 1;
            }
            if(month == 0){
                month = 12;
                year -= 1;
            }
            date = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
            while(it != vPairdb.end()){
                if (it->first == date){
                    return it->second * atof(inputData.value.c_str());
                }
                it++;
            }
            day -= 1;   
        }
    }
    value = 0.0;
    return value;
}


int main(int cont, char **argv){
    std::string inputFile = "";
    std::string dbFile = "../cpp_09/data.csv";
    std::string dbline;
    std::vector<t_data> inputData;
    std::vector<t_db> dataBase;
    std::vector<std::pair<std::string, double> > vPairdb;
    std::size_t size;
    size_t it = 0;
    
    if(cont != 2){
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    else{
        //lectura, analisis y almacenamiento de la base de datos data.csv
        readInputFile<t_db>(dataBase, dbFile);
        it = 0;
        size = dataBase.size();
        std::string date;
        while(it < size){
            date = dataBase[it].year + "-" + dataBase[it].month + "-" + dataBase[it].day;
            vPairdb.push_back(std::make_pair(date,atof(dataBase[it].value.c_str())));
            it++;
        }
        
        //lectura, analisis y almacenamiento de los datos del archivo input.txt
        it = 0;
        inputFile = argv[1];
        readInputFile<t_data>(inputData, inputFile);
        size = inputData.size();
        std::ostringstream value;
        while(it < size){
            value << getValue(inputData[it], vPairdb);
            printLine(inputData[it], value.str());
            value.str("");
            it++;
        }
    }
    return 0;
}