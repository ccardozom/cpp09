#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>


template<typename data>
void readInputFile(std::vector<data>& Data, std::string filename);

/* template<typename T>
void initData(T data); */

class Date{
    public:
        Date();
        ~Date();

        /* std::string getLine();
        std::string getYear();
        std::string getMonth();
        std::string getDay();
        std::string getValue();
        std::string getErr();

        void setLine(std::string line);
        void setYear(std::string year);
        void setMonth(std::string month);
        void setDay(std::string day);
        void setValue(std::string value);
        void setErr(std::string err); */
    //private:
        std::string _line;
        std::string _year;
        std::string _month;
        std::string _day;
        std::string _value;
        std::string _err;
};

class Filedata{
    public:
        Filedata();
    private:
        
};


class BitcoinExchange{
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        //falta una sobrecarga de operador

        void openInputFile(const std::ifstream& file);
        void readInputFile();
        void loadDate(std::string line);
        int validateStruct(Date& date);
        bool validateDataLen(std::string str, size_t len);
        bool isNumeric(const std::string& cadena, int onlynum);
        bool leap_year(std::string year);
        bool validateValue(Date& data);
        bool isfloat(std::string str);
        void eraseSpaces(std::string& line);

        //metodos para trabajar con _vDataBase
        size_t getDataBaseSize();
        std::string getYear(size_t it);
        std::string getMonth(size_t it);
        std::string getDay(size_t it);

        //cargar el vector vPairdb con cada pareja de string + valor
        void chargePairdb();

        //imprimir elementos del vector vPairdb
        void printPairdb();
        
    private:
        std::string _filePath;
        std::vector<Date> _vDataBase;
        std::vector<std::pair<std::string, double> > _vPairdb;

        
};

#endif


/*

para la clase Bitcoinexchange necesito
crear un objeto de tipo bitcoinexchange con atributos privados
    un vector dbData que va a tener objetos de tipo date donde cada objeto
        tendrá los atributos necesarios
    un vector pair para almacenar la fecha y valor obtenida de cada objeto del vector
        dbData
*/

/*
para la clase Date necesito
variables privadas _year, _month, _day, _value, _err, _line, _FilePath
metodos get y set para todos los atributos
*/