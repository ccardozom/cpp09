#include "PmergeMe.hpp"


int main(int argc, char **argv) {
    PmergeMe p;

    if (p.isValid(argc, argv))
        return 1;

    std::deque<int> deque; 
    for (int i = 1; i < argc; ++i)
        deque.push_back(std::atoi(argv[i]));

    std::cout << "Before: ";
    for (size_t i = 0; i < deque.size(); ++i)
        std::cout << deque[i] << " ";
    std::cout << std::endl;

    std::clock_t startTime = std::clock();
    p.mergeInsertionSort(deque);
    std::clock_t endTime = std::clock();
    double elapsedTime = static_cast<double>((endTime - startTime) * 1000000 / CLOCKS_PER_SEC);

    std::cout << "After: ";
    for (size_t i = 0; i < deque.size(); ++i)
        std::cout << deque[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << deque.size() << " elements with std::deque : " << elapsedTime << " microsegundos (us)" << std::endl;

    std::list<int> list;
    for (int i = 1; i < argc; ++i)
        list.push_back(std::atoi(argv[i]));
    startTime = std::clock();
    p.mergeInsertionSort(list);
    endTime = std::clock();
    elapsedTime = static_cast<double>((endTime - startTime) * 1000000 / CLOCKS_PER_SEC);
    
    std::cout << "Time to process a range of " << list.size() << " elements with std::list : " << elapsedTime << " microsegundos (us)" << std::endl; 

    return 0;    
}