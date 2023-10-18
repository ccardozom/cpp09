#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <list>

int main (int argc, char **argv)
{
    PmergeMe list_of_numbers;
    int value;
    //int i;

    if (list_of_numbers.isValid(argc, argv))
        return 1;

    std::map<std::string, int> map;

    for (int i = 1; i < argc; ++i){
        value = std::atoi(argv[i]);
        // std::cout << "value: " << value << std::endl;
        std::string key = std::to_string(i);
        map[key] = value;
    }
    // return 0;
    std::cout << "Before: ";
    for (size_t i = 1; i < map.size(); ++i)
        std::cout << map[std::to_string(i)] << " ";
    std::cout << std::endl;

    std::clock_t startTime = std::clock();
    list_of_numbers.mergeInsertionSort(map);
    std::clock_t endTime = std::clock();
    
    double elapsedTime = static_cast<double>((endTime - startTime) * 1000000 / CLOCKS_PER_SEC);
    std::cout << "After: ";
    for (size_t i = 0; i < map.size(); ++i)
        std::cout << map[std::to_string(i)] << " ";
    std::cout << std::endl;
    std::cout << "Time to process a range of " << map.size() << " elements with std::vector : " << elapsedTime << " us" << std::endl;

    std::list<int> list;
    for (int i = 1; i < argc; ++i)
        list.push_back(std::atoi(argv[i]));
    startTime = std::clock();
    list_of_numbers.mergeInsertionSort(list);
    endTime = std::clock();
    elapsedTime = static_cast<double>((endTime - startTime) * 1000000 / CLOCKS_PER_SEC);
    //std::cout << "After: ";
    //for(std::list<int>::iterator it = list.begin(); it != list.end(); it++)
    //    std::cout << *it << " ";
    //std::cout << std::endl;
    std::cout << "Time to process a range of " << list.size() << " elements with std::list : " << elapsedTime << " us" << std::endl; 

    return 0;    
}