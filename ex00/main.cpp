#include "BitcoinExchange.hpp"

//imprime en pantalla la linea con o sin errores
 void printLine(Date data, std::string value=""){
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

std::string int_to_string(int n){
    std::ostringstream stm ;
    if(n < 10)
        stm << 0 << n ;
    else
        stm << n;
    return stm.str() ;
} 

//buscando el valor de btc en la base de datos
float getValue(const Date inputData, std::vector<std::pair<std::string, double> > vPairdb){
    float value;
    std::string yearMonthDay;
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
            yearMonthDay = int_to_string(year) + "-" + int_to_string(month) + "-" + int_to_string(day);
            while(it != vPairdb.end()){
                if (it->first == yearMonthDay){
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
    if(cont != 2){
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    else{
        BitcoinExchange dataBase;
        // BitcoinExchange dataBase2(dataBase);
        Filedata inputFile(argv[1]);
        size_t it = 0, size;
        size = inputFile.getInputDataSize();
        std::ostringstream value;
        while(it < size){
            value << getValue(inputFile.getInputData(it), dataBase.getPairdb());
            printLine(inputFile.getInputData(it), value.str());
            value.str("");
            it++;
        } 
    }
    return 0;
}