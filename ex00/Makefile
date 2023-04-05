CXX = c++  # Especifica el compilador que deseas utilizar
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror  # Especifica las opciones de compilación

# Especifica el nombre del archivo ejecutable
TARGET = btc

# Especifica los archivos que deseas compilar
SRCS = main.cpp BitcoinExchange.cpp
OBJS = $(SRCS:.cpp=.o)
INCLUDE = .

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)