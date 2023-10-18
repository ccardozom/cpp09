#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &rhs)
{
    (void)rhs;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe& PmergeMe::operator=(const PmergeMe &rhs)
{
    if (this == &rhs)
        return *this;
    return *this;
}

bool PmergeMe::isDuplicate(int number, int *array, int size)
{
    for (int i = 0; i < size; ++i)
        if (number == array[i])
            return true;
    return false;
}

bool PmergeMe::isNumber(char *arg)
{
    for (size_t i = 1; i < std::strlen(arg); ++i){
        if (!isdigit(arg[i]))
            return true;
        // std::cout << "arg[i]: " << arg[i] << std::endl;
    }
    return false;
}

bool PmergeMe::isValid(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " [number1, number2,...]" << std::endl;
        return true;
    }
    int numbers[argc -1];
    int size = 0;
    for (int i = 1; i < argc; ++i)
    {
        char *argument = argv[i];
        if(isNumber(argument))
        {
            std::cout << "Error: Cannot process characters" << std::endl;
            return true;
        }
        long number = std::atol(argument);
        if (number > INT_MAX || number <= 0)
        {
            std::cout << "Error: Only positive integers can be process" << std::endl;
            return true;
        }
        if (isDuplicate(number, numbers, size))
        {
            std::cout << "Error: Cannot process duplicate numbers" << std::endl;
            return true;
        }
        numbers[i] = static_cast<int>(number);
        ++size;
    }
    return false;
}

void PmergeMe::mergeInsertionSort(std::map<std::string, int>& array) {
    size_t n = array.size();
    if (n <= 1)
        return;
    // std::cout << "n: " << n << std::endl;
    std::map<std::string, int> larger, smaller;

    // Step 1 and 2: Grouping the numbers into pairs and sorting each pair
    std::map<std::string, int>::iterator it = array.begin();

    // for (std::pair<std::string, int> it : array) {  //esto es solo para probar, no se puede usar para c++98 <------------------------ OJO
    //     std::cout << it.first << " = " << it.second << std::endl;
    // }
    std::cout << "begin first: " << it->first << std::endl;
    std::cout << "begin second: " << it->second << std::endl;

    
    for (size_t i = 1; i < n; i += 1) {
        if (std::next(it) != array.end()) {
            std::map<std::string, int>::iterator next = std::next(it);
            // std::cout << "it->second: " << it->second << " " << "next->second: " << next->second << std::endl;
            int maxVal = std::max(it->second, next->second); // 5 9 -> 9
            int minVal = std::min(it->second, next->second); // 5 9 -> 5
            smaller[it->first] = minVal; // smaller[2] -> 5
            larger[next->first] = maxVal; // larger[1] -> 9
        } 
        else {
            smaller[it->first] = it->second; // larger[1] -> 5
        }
        ++it;
    }

    // Step 3: Recursively sort the larger elements
    mergeInsertionSort(larger);

    // Step 4: Find the corresponding smaller element for the smallest larger element
    int smallestLarger = larger.begin()->second;
    int correspondingSmaller = -1;

    for (it = array.begin(); it != array.end(); ++it) {
        if (it->second == smallestLarger) {
            correspondingSmaller = it->second;
            break;
        }
    }

    // Step 5: Clear the original map and rebuild it
    array.clear();

    // Insert the smallestLarger element at the beginning if it exists
    if (correspondingSmaller != -1)
        array[std::to_string(correspondingSmaller)] = correspondingSmaller;

    // Insert the remaining larger elements
    for (std::map<std::string, int>::const_iterator it = larger.begin(); it != larger.end(); ++it) {
    if (it->second != smallestLarger) {
        array[it->first] = it->second;
        }
    }

    // Insert the smaller elements
    for (std::map<std::string, int>::const_iterator it = smaller.begin(); it != smaller.end(); ++it) {
        array[it->first] = it->second;
    }
}

void PmergeMe::mergeInsertionSort(std::list<int> &array)
{
    size_t n =array.size();
    if (n <= 1)
        return;
    std::list<int> larger, smaller;
    //step1 and 2: grouping the numbers into pairs and sorting each pair
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
    //step3: recursively sort the larger elements
    mergeInsertionSort(larger);
    //step4: find the corresponding smaller element for the smallest larger element
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
    //step5: insert the remaining smaller elements
    for (std::list<int>::iterator it = smaller.begin(); it != smaller.end(); ++it)
    {
        if (*it != correspondingSmaller)
        {
            std::list<int>::iterator pos = std::lower_bound(array.begin(), array.end(), *it);
            array.insert(pos, *it);
        }
    }
}