CXX = c++  # Especifica el compilador que deseas utilizar
CXXFLAGS = -std=c++11  -g -Wall -Wextra -Werror  # Especifica las opciones de compilación

# Especifica el nombre del archivo ejecutable
TARGET = PmergeMe#nombre del ejecutable

# Especifica los archivos que deseas compilar
SRCS = main.cpp PmergeMe.cpp #archivos para compilar
OBJS = $(SRCS:.cpp=.o)
INCLUDE = .

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(OBJS) $(TARGET)

re: fclean all