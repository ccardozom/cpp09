#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

typedef struct s_date{
    int year;
    int month;
    int day;
}date;

//peek 

class BitcoinExchange{
    public:
        BitcoinExchange();
        ~BitcoinExchange();
    private:
        std::string _line;
        date _date;
        std::string _value;
}

#endif
/* esto hay que ver como implementar y probar si es mejor hacer una clase
string fecha_str = "2013-06-25";
    int year, month, day;
    char delimiter;
    istringstream fecha_stream(fecha_str);
    fecha_stream >> year >> delimiter >> month >> delimiter >> day;
    // Crear la estructura que almacena la fecha
    struct fecha_estructura {
        int year;
        int month;
        int day;
    };
    fecha_estructura fecha = {year, month, day};*/