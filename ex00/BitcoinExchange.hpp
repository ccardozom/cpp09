#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

class Date{
    public:
        Date();
        ~Date();
        Date(const Date& copy);
        Date& operator=(const Date& src);

        std::string line;
        std::string year;
        std::string month;
        std::string day;
        std::string value;
        std::string err;
};

class Filedata{
    private:
        std::string _filePath;
        std::vector<Date> _inputFileData;
    
    public:
        Filedata(std::string filePath);
        ~Filedata();
        Filedata(Filedata& copy);
        Filedata& operator=(Filedata& src);
         
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

        //metodos para trabajar con _inputFileData
        size_t getInputDataSize();

};

class BitcoinExchange{
    public:
        BitcoinExchange();
        ~BitcoinExchange();
        BitcoinExchange& operator=(BitcoinExchange& src);
        BitcoinExchange(BitcoinExchange& copy);

        void readInputFile();
        void openInputFile(const std::ifstream& file);
        void loadDate(std::string line);
        void eraseSpaces(std::string& line);

        //metodos para trabajar con DataBase
        size_t getDataBaseSize();
        std::string getYear(size_t it);
        std::string getMonth(size_t it);
        std::string getDay(size_t it);

        //cargar el vector Pairdb con cada pareja de string + valor
        void chargePairdb();

        std::vector<std::pair<std::string, double> > getPairdb();
        
        // imprimir elementos del vector Pairdb
        void printPairdb();
        int validateStruct(Date& date);
        bool validateDataLen(std::string str, size_t len);
        bool isNumeric(const std::string& cadena, int onlynum);
        bool leap_year(std::string year);
        bool validateValue(Date& data);
        bool isfloat(std::string str);
        
    private:
        std::string _filePath;
        std::vector<Date> DataBase;
        std::vector<std::pair<std::string, double> > pairDateValue;        
};

#endif