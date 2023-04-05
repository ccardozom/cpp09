#include "BitcoinExchange.hpp"




/* void openInputFile(const std::ifstream& file){
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        exit(EXIT_FAILURE);
    }
} */

/*Implementación de los metodos de la clase BitcoinExchange*/
BitcoinExchange::BitcoinExchange(){
    this->_filePath = "../cpp_09/data.csv";
    this->readInputFile();
    this->chargePairdb();
}

BitcoinExchange::~BitcoinExchange(){}

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

    //verifica si se puede leer el archivo de entrada
    this->openInputFile(file);
    
    std::getline(file, firsLine);

    while (std::getline(file, line)){
        if(!line.empty())
            this->loadDate(line);            
    }
}

void BitcoinExchange::loadDate(std::string line){
    Date date;    //t_db sdata;  <-- esto se sustituye por this->_date
    std::string str_extract;
    int npos = 0;

    //initData(sdata);
    npos = line.find(',');
    if(npos > 0){
        this->eraseSpaces(line);
        str_extract = line.substr(0, npos);
        std::stringstream ss(str_extract);
        std::getline(ss, date._year, '-');  
        std::getline(ss, date._month, '-');
        std::getline(ss, date._day, ',');
        while(line[++npos] == ' '){}
        date._value = line.substr(npos, line.length());
        this->validateStruct(date);
    }
    else
        date._err = "Error: bad database line";
    this->_vDataBase.push_back(date);
}

int BitcoinExchange::validateStruct(Date& date){
    if(validateDataLen(date._year, 4) || !isNumeric(date._year, 1) || validateDataLen(date._month, 2) ||
    std::atoi(date._month.c_str()) > 12 || !isNumeric(date._month, 1) || validateDataLen(date._day, 2) ||
    std::atoi(date._day.c_str()) > 31 || !isNumeric(date._day, 1) ){
        date._err = "Error: bad input";
        return false;
    }
    else  if(date._month == "02"){
        if(leap_year(date._year)){
            if(std::atoi(date._day.c_str()) > 29){
                date._err = "Error: bad input";
                return false;
            }
        }
        else{
            if(std::atoi(date._day.c_str()) > 28){
                date._err = "Error: bad input";
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
    if(*date._value.begin() == '-'){
        date._err = "Error: not a positive number.";
        return false;
    }
    if(std::atof(date._value.c_str()) > 1000){
        date._err = "Error: too large a number.";
        return false;
    }
    else if(!isNumeric(date._value) || !isfloat(date._value) || date._value.empty()){
        date._err = "Error: bad input";
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

    void BitcoinExchange::eraseSpaces(std::string& line){
        int pos = 0;
        while(line[pos] == ' '){pos++;}
        if(pos > 0){
            line.erase(0,pos);
        }
    }

    /* Metodos para trabajar con _vDataBase */
    size_t BitcoinExchange::getDataBaseSize(){
        return this->_vDataBase.size();
    }

    std::string BitcoinExchange::getYear(size_t it){
        return this->_vDataBase[it]._year;
    }

    std::string BitcoinExchange::getMonth(size_t it){
        return this->_vDataBase[it]._month;
    }

    std::string BitcoinExchange::getDay(size_t it){
        return this->_vDataBase[it]._day;
    }

    void BitcoinExchange::chargePairdb(){
        size_t it = 0, size;
        std::string date;

        size = this->getDataBaseSize();
        while(it < size){
            date = this->getYear(it) + "-" + this->getMonth(it) + "-" + this->getDay(it);
            this->_vPairdb.push_back(std::make_pair(date,atof(this->_vDataBase[it]._value.c_str())));
            it++;
        }
    }

    void BitcoinExchange::printPairdb(){
        size_t it = 0, size;

        size = this->getDataBaseSize();
        while(it < size){
            std::cout << "Date: " << this->_vPairdb[it].first << " Value: " << this->_vPairdb[it].second << std::endl;
            it++;
        }
    }

/*------- Implementación de los metodos de la clase Date --------*/
Date::Date(){
    this->_year = "";
    this->_month = "";
    this->_day = "";
    this->_err = "";
    this->_value = "";
    this->_line = "";
}

Date::~Date(){}

/* std::string Date::getLine(){
    return this->_line;
}

std::string Date::getYear(){
    return this->_year;
}

std::string Date::getMonth(){
    return this->_month;
}

std::string Date::getDay(){
    return this->_day;
}

std::string Date::getValue(){
    return this->_value;
}

std::string Date::getErr(){
    return this->_err;
}

void Date::setLine(std::string line){
    this->_line = line;
}

void Date::setYear(std::string year){
    this->_year = year;
}

void Date::setMonth(std::string month){
    this->_month = month;
}

void Date::setDay(std::string day){
    this->_day = day;
}

void Date::setValue(std::string value){
    this->_value = value;
}

void Date::setErr(std::string err){
    this->_err = err;
} */
