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
        // if (isDuplicate(number, numbers, size)) {
        //     std::cout << "Error: Cannot process duplicate numbers" << std::endl;
        //     return true;
        // }
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
    //carga los valores del array por parejas y los separa en mayor y menor cada pareja
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            larger.push_back(std::max(array[i], array[i + 1]));
            smaller.push_back(std::min(array[i], array[i + 1]));
        } else
            larger.push_back(array[i]);
    }
    
    // se envia el array que tiene los mayores valores de la separación
    mergeInsertionSort(larger);

    int firtstLargerArrayElement = larger[0];
    int smallerNumOfCouple = -1;
    
    // si cumple la condición se busca el mínimo de cada pareja
    for (size_t i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            if (array[i] == firtstLargerArrayElement || array[i + 1] == firtstLargerArrayElement) {
                smallerNumOfCouple = std::min(array[i], array[i + 1]);
                break;
            }
        }
    }


    array.clear();
    array = larger;
    
    if (smallerNumOfCouple != -1)
        array.push_front(smallerNumOfCouple);
        
    for (size_t i = 0; i < smaller.size(); ++i) {
        if (smaller[i] != smallerNumOfCouple) {
            //devuelve un iterador al primer elemento que no es menor a smaller[i]
            std::deque<int>::iterator it = std::lower_bound(array.begin(), array.end(), smaller[i]);
            // inserta el elemento antes de la posicon que apunta el iterador
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

    int firtstLargerlistElement = larger.front();
    int smallerNumOfCouple = -1;
    it = array.begin();
    for (size_t i = 0; i < n; i += 2)
    {
        if (i + 1 < n)
        {
            int first = *it++;
            int second = *it++;
            if (first == firtstLargerlistElement || second == firtstLargerlistElement)
            {
                smallerNumOfCouple = std::min(first, second);
                break;
            }
        }
    }
    array.clear();
    array = larger;
    if (smallerNumOfCouple != -1)
        array.push_front(smallerNumOfCouple);
    for (std::list<int>::iterator it = smaller.begin(); it != smaller.end(); ++it)
    {
        if (*it != smallerNumOfCouple)
        {
            // devuelve un iterador al primer elemento que no es menor a *it
            std::list<int>::iterator pos = std::lower_bound(array.begin(), array.end(), *it);
            /// inserta el elemento antes de la posicon que apunta el iterador
            array.insert(pos, *it);
        }
    }
}

