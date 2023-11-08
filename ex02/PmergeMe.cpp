#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe &rhs) {
    (void)rhs;
}

PmergeMe::~PmergeMe() {
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
    if (this == &rhs)
        return *this;
    return *this;
}

bool PmergeMe::isDuplicate(int number, int *array, int size) {
    for (int i = 0; i < size; ++i)
        if (number == array[i])
            return true;
    return false;
}

bool PmergeMe::isNumber(char *arg) {
    for (size_t i = 0; i < std::strlen(arg); ++i)
        if (!isdigit(arg[i]))
            return true;
    return false;
}

bool PmergeMe::isValid(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [number1, number2,...]" << std::endl;
        return true;
    }
    int numbers[argc - 1];
    int size = 0;
    for (int i = 1; i < argc; ++i) {
        char *argument = argv[i];
        if (isNumber(argument)) {
            std::cout << "Error: Cannot process characters" << std::endl;
            return true;
        }
        long number = std::atol(argument);
        if (number > INT_MAX || number <= 0) {
            std::cout << "Error: Only positive integers can be process" << std::endl;
            return true;
        }
        if (isDuplicate(number, numbers, size)) {
            std::cout << "Error: Cannot process duplicate numbers" << std::endl;
            return true;
        }
        numbers[i - 1] = static_cast<int>(number);
        ++size;
    }
    return false;
}

void PmergeMe::mergeInsertionSort(std::deque<int> &array) { 
    size_t n = array.size();
    if (n <= 1)
        return;
    std::deque<int> larger, smaller;
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            larger.push_back(std::max(array[i], array[i + 1]));
            smaller.push_back(std::min(array[i], array[i + 1]));
        } else
            larger.push_back(array[i]);
    }
    mergeInsertionSort(larger);
    int smallestLarger = larger[0];
    int correspondingSmaller = -1;
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            if (array[i] == smallestLarger || array[i + 1] == smallestLarger) {
                correspondingSmaller = std::min(array[i], array[i + 1]);
                break;
            }
        }
    }
    array.clear();
    array = larger;
    if (correspondingSmaller != -1)
        array.push_front(correspondingSmaller);
    
    for (size_t i = 0; i < smaller.size(); ++i) {
        if (smaller[i] != correspondingSmaller) {
            std::deque<int>::iterator it = std::lower_bound(array.begin(), array.end(), smaller[i]);
            array.insert(it, smaller[i]);
        }
    }
}


void PmergeMe::mergeInsertionSort(std::list<int> &array)
{
    size_t n =array.size();
    if (n <= 1)
        return;
    std::list<int> larger, smaller;

    std::list<int>::iterator it = array.begin();
    for (size_t i = 0; i < n; i += 2)
    {
        if (i + 1 < n)
        {
            int first = *it++;
            int second = *it++;
            larger.push_back(std::max(first, second));
            smaller.push_back(std::min(first, second));
        }
        else
            larger.push_back(*it++);
    }
 
    mergeInsertionSort(larger);

    int smallestLarger = larger.front();
    int correspondingSmaller = -1;
    it = array.begin();
    for (size_t i = 0; i < n; i += 2)
    {
        if (i + 1 < n)
        {
            int first = *it++;
            int second = *it++;
            if (first == smallestLarger || second == smallestLarger)
            {
                correspondingSmaller = std::min(first, second);
                break;
            }
        }
    }
    array.clear();
    array = larger;
    if (correspondingSmaller != -1)
        array.push_front(correspondingSmaller);
    for (std::list<int>::iterator it = smaller.begin(); it != smaller.end(); ++it)
    {
        if (*it != correspondingSmaller)
        {
            std::list<int>::iterator pos = std::lower_bound(array.begin(), array.end(), *it);
            array.insert(pos, *it);
        }
    }
}