#include "BitcoinExchange.hpp"


/* ----------------------------Implementación de los metodos de la clase Filedata ----------------------------*/

Filedata::Filedata(std::string filePath){
    this->_filePath = filePath;
    this->readInputFile();
}

Filedata::~Filedata(){}

Filedata &Filedata::operator=(Filedata& src){
    this->_filePath = src._filePath;
    this->_inputFileData =src._inputFileData;
    return *this;
}

Filedata::Filedata(Filedata& copy){
    *this = copy;
}


//lectura y carga del archivo input.txt
void Filedata::readInputFile(){
    std::string line;
    std::string firsLine;
    std::ifstream file(this->_filePath.c_str());

    //verifica si se puede leer el archivo de entrada
    this->openInputFile(file);
    
    //verifica la cabecera del archivo input
    std::getline(file, firsLine);
    if (firsLine.compare("date | value")){
        std::cerr << "Error: file header" << std::endl;
        return ;
    } 
    std::cout << firsLine << std::endl;

    //se lee linea a linea para realizar el analisis
    while (std::getline(file, line)){
        if(!line.empty())
            this->loadDate(line);            
    }
}

void Filedata::openInputFile(const std::ifstream& file){
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

//crea el objeto date por cada linea del documento
void Filedata::loadDate(std::string line){
    Date date;
    std::string linedate;
    int npos = 0;
    int npos_aux;

    if (!line.empty()){
       
        this->eraseSpaces(line);
        
        date.line = line;
        npos_aux = line.find(' ');
        npos = line.find('|');
        while(npos_aux < npos){
            if(!std::isspace(line[npos_aux++])){
                npos = 0;
                break;
            }
        }
        if(npos > 0){
            linedate = line.substr(0,npos);
            std::stringstream ss(linedate);
            std::getline(ss, date.year, '-');  
            std::getline(ss, date.month, '-');
            std::getline(ss, date.day, ' ');
            while(line[++npos] == ' '){}
            date.value = line.substr(npos, line.length());
            validateStruct(date);
        }
        else
            date.err =  "Error: bad input";
    }
    this->_inputFileData.push_back(date);
} 

int Filedata::validateStruct(Date& date){
    if(validateDataLen(date.year, 4) || !isNumeric(date.year, 1) || validateDataLen(date.month, 2) ||
    std::atoi(date.month.c_str()) > 12 || !isNumeric(date.month, 1) || validateDataLen(date.day, 2) ||
    std::atoi(date.day.c_str()) > 31 || !isNumeric(date.day, 1) ){
        date.err = "Error: bad input";
        return false;
    }
    else  if(date.month == "02"){
        if(leap_year(date.year)){
            if(std::atoi(date.day.c_str()) > 29){
                date.err = "Error: bad input";
                return false;
            }
        }
        else{
            if(std::atoi(date.day.c_str()) > 28){
                date.err = "Error: bad input";
                return false;
            }
        }
    }
    else if(!validateValue(date)){
        return false;
    }
    return true;
}

bool Filedata::validateValue(Date& date){
    if(*date.value.begin() == '-'){
        date.err = "Error: not a positive number.";
        return false;
    }
    else if(std::atof(date.value.c_str()) > 1000){
        date.err = "Error: too large a number.";
        return false;
    }
    else if(!isNumeric(date.value, 0) || !isfloat(date.value) || date.value.empty()){
        date.err = "Error: bad input";
        return false;
    }
    return true;
}

bool Filedata::isfloat(std::string str){
    std::string dotstring;
    int pos = 0;
    pos = str.find('.');
    if(pos > 0){
        dotstring = str.substr(++pos, str.length());
        return isNumeric(dotstring,1);
    }
    return isNumeric(str,1);    
}

bool Filedata::isNumeric(const std::string& cadena, int onlynum=0) {
    if(onlynum == 0)
        return cadena.find_first_not_of(".0123456789") == std::string::npos;
    return cadena.find_first_not_of("0123456789") == std::string::npos;
}

bool Filedata::leap_year(std::string year){
    return std::atoi(year.c_str()) % 4 == 0 && (std::atoi(year.c_str()) % 100 != 0 || std::atoi(year.c_str()) % 400 == 0);
}

bool Filedata::validateDataLen(std::string str, size_t len){
    return str.length() != len;
}

void Filedata::eraseSpaces(std::string& line){
    int pos = 0;
    while(line[pos] == ' '){pos++;}
    if(pos > 0){
        line.erase(0,pos);
    }
}

Date Filedata::getInputData(size_t it){
    return this->_inputFileData[it];
}

size_t Filedata::getInputDataSize(){
    return this->_inputFileData.size();
}



/* ----------------------------Implementación de los metodos de la clase BitcoinExchange ----------------------------*/

BitcoinExchange::BitcoinExchange(){
    this->_filePath = "../cpp_09/data.csv";
    this->readInputFile();
    this->chargePairdb();
}

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange& src){
    this->_filePath = src._filePath;
    this->DataBase = src.DataBase;
    this->pairDateValue = src.pairDateValue;
    return *this;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange& copy){
    *this = copy;
}

void BitcoinExchange::openInputFile(const std::ifstream& file){
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void BitcoinExchange::readInputFile(){
    std::string line;
    std::string firsLine;
    std::ifstream file(this->_filePath.c_str());

    
    this->openInputFile(file);
    
    std::getline(file, firsLine);
    
    while (std::getline(file, line)){
       
        if(!line.empty())
            this->loadDate(line);
                 
    }
}

void BitcoinExchange::loadDate(std::string line){
    Date date; 
    std::string str_extract;
    int npos = 0;

    npos = line.find(',');
    if(npos > 0){
        this->eraseSpaces(line);
        str_extract = line.substr(0, npos);
        std::stringstream ss(str_extract);
        std::getline(ss, date.year, '-');  
        std::getline(ss, date.month, '-');
        std::getline(ss, date.day, ',');
        while(line[++npos] == ' '){}
        date.value = line.substr(npos, line.length());
        // this->validateStruct(date);
    }
    else
        date.err = "Error: bad database line";
    this->DataBase.push_back(date);
}


void BitcoinExchange::eraseSpaces(std::string& line){
    int pos = 0;
    while(line[pos] == ' '){pos++;}
    if(pos > 0){
        line.erase(0,pos);
    }
}

/* Metodos para trabajar con DataBase */
size_t BitcoinExchange::getDataBaseSize(){
    return this->DataBase.size();
}

std::string BitcoinExchange::getYear(size_t it){
    return this->DataBase[it].year;
}

std::string BitcoinExchange::getMonth(size_t it){
    return this->DataBase[it].month;
}

std::string BitcoinExchange::getDay(size_t it){
    return this->DataBase[it].day;
}

void BitcoinExchange::chargePairdb(){
    size_t it = 0, size;
    std::string date;

    size = this->getDataBaseSize();
    while(it < size){
        date = this->getYear(it) + "-" + this->getMonth(it) + "-" + this->getDay(it);
        this->pairDateValue.push_back(std::make_pair(date,atof(this->DataBase[it].value.c_str())));
        it++;
    }
}

std::vector<std::pair<std::string, double> > BitcoinExchange::getPairdb(){
    return this->pairDateValue;
}


// esto despues de hacerlo me han dicho que no hacia falta :-(
int BitcoinExchange::validateStruct(Date& date){
    if(validateDataLen(date.year, 4) || !isNumeric(date.year, 1) || validateDataLen(date.month, 2) ||
    std::atoi(date.month.c_str()) > 12 || !isNumeric(date.month, 1) || validateDataLen(date.day, 2) ||
    std::atoi(date.day.c_str()) > 31 || !isNumeric(date.day, 1) ){
        date.err = "Error: bad input";
        return false;
    }
    else  if(date.month == "02"){
        if(leap_year(date.year)){
            if(std::atoi(date.day.c_str()) > 29){
                date.err = "Error: bad input";
                return false;
            }
        }
        else{
            if(std::atoi(date.day.c_str()) > 28){
                date.err = "Error: bad input";
                return false;
            }
        }
    }
    else if(!validateValue(date)){
        return false;
    }
    return true;
}

bool BitcoinExchange::validateDataLen(std::string str, size_t len){
    return str.length() != len;
}

bool BitcoinExchange::isNumeric(const std::string& cadena, int onlynum=0) {
    if(onlynum == 0)
        return cadena.find_first_not_of(".0123456789") == std::string::npos;
    return cadena.find_first_not_of("0123456789") == std::string::npos;
}

bool BitcoinExchange::leap_year(std::string year){
    return std::atoi(year.c_str()) % 4 == 0 && (std::atoi(year.c_str()) % 100 != 0 || std::atoi(year.c_str()) % 400 == 0);
}

bool BitcoinExchange::validateValue(Date& date){
    if(*date.value.begin() == '-'){
        date.err = "Error: not a positive number.";
        return false;
    }
    else if(!isNumeric(date.value) || !isfloat(date.value) || date.value.empty()){
        date.err = "Error: bad input";
        return false;
    }
    return true;
}

bool BitcoinExchange::isfloat(std::string str){
    std::string dotstring;
    int pos = 0;
    pos = str.find('.');
    if(pos > 0){
        dotstring = str.substr(++pos, str.length());
        return isNumeric(dotstring,1);
    }
    return isNumeric(str);    
}

void BitcoinExchange::printPairdb(){
    size_t it = 0, size;

    size = this->getDataBaseSize();
    while(it < size){
        std::cout << "Date: " << this->pairDateValue[it].first << " Value: " << this->pairDateValue[it].second << std::endl;
        it++;
    }
}


/*------- Implementación de los metodos de la clase Date --------*/
Date::Date(){
    this->year = "";
    this->month = "";
    this->day = "";
    this->err = "";
    this->value = "";
    this->line = "";
}

Date::~Date(){}

Date &Date::operator=(const Date& src){
    this->year = src.year;
    this->month = src.month;
    this->day = src.day;
    this->err = src.err;
    this->value = src.value;
    this->line = src.line;
    return *this;
}

Date::Date(const Date& src){
    *this = src;
}
