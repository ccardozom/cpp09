#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
#include <list>
#include <map>


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
        void mergeInsertionSort(std::map<std::string,int> &array);
        void mergeInsertionSort(std::list<int> &array);
    private:
};

#endif