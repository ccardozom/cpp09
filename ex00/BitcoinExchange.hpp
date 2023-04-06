#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class Date{
    public:
        Date();
        ~Date();

        std::string line;
        std::string year;
        std::string month;
        std::string day;
        std::string value;
        std::string err;
};

class Filedata{
    public:
        Filedata(std::string filePath);
        ~Filedata();
        void readInputFile();
        void openInputFile(const std::ifstream& file);
        void loadDate(std::string line);
        void eraseSpaces(std::string& line);
        int validateStruct(Date& date);
        bool validateDataLen(std::string str, size_t len);
        bool isNumeric(const std::string& cadena, int onlynum);
        bool leap_year(std::string year);
        bool validateValue(Date& data);
        bool isfloat(std::string str);
        Date getInputData(size_t it);

        //metodos para trabajar con _vInputFileData
        size_t getInputDataSize();


    private:
        std::string _filePath;
        std::vector<Date> _vInputFileData;
};

class BitcoinExchange{
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        //falta una sobrecarga de operador

        void readInputFile();
        void openInputFile(const std::ifstream& file);
        void loadDate(std::string line);
        void eraseSpaces(std::string& line);
        int validateStruct(Date& date);
        bool validateDataLen(std::string str, size_t len);
        bool isNumeric(const std::string& cadena, int onlynum);
        bool leap_year(std::string year);
        bool validateValue(Date& data);
        bool isfloat(std::string str);

        //metodos para trabajar con _vDataBase
        size_t getDataBaseSize();
        std::string getYear(size_t it);
        std::string getMonth(size_t it);
        std::string getDay(size_t it);

        //cargar el vector vPairdb con cada pareja de string + valor
        void chargePairdb();

        //imprimir elementos del vector vPairdb
        std::vector<std::pair<std::string, double> > getPairdb();
        void printPairdb();
        
    private:
        std::string _filePath;
        std::vector<Date> _vDataBase;
        std::vector<std::pair<std::string, double> > _vPairdb;        
};

#endif