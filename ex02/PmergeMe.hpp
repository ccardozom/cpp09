#include <iostream>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque> // Cambiamos a std::deque
#include <list>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &rhs);
    ~PmergeMe();

    PmergeMe &operator=(const PmergeMe &rhs);

    bool isDuplicate(int number, int *array, int size);
    bool isNumber(char *arg);
    bool isValid(int argc, char **argv);

    // Modificamos las funciones para usar std::deque en lugar de std::vector
    void mergeInsertionSort(std::deque<int> &array);
    void mergeInsertionSort(std::list<int> &array);
};