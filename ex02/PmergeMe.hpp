#include <iostream>
#include <iomanip>
#include <deque> 
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

    void mergeInsertionSort(std::deque<int> &array);
    void mergeInsertionSort(std::list<int> &array);

};
