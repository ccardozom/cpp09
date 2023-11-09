#include "PmergeMe.hpp"


void print_deque(std::deque<int> deque, std::string str){
    std::cout << str << ": ";
    for (size_t i = 0; i < deque.size(); ++i)
        std::cout << deque[i] << " ";
    std::cout << std::endl;
}

void print_list(std::list<int> list, std::string str){
    std::cout << str << ": ";
    std::list<int>::iterator it = list.begin();
    for( ; it != list.end() ; it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}



int main(int argc, char **argv) {
    PmergeMe array1;
    
    if (array1.isValid(argc, argv))
        return 1;
    // array2 = array1;

    // --------- desarrollo utilizando el contenedor deque ----------
    std::deque<int> deque; 
    for (int i = 1; i < argc; ++i)
        deque.push_back(std::atoi(argv[i]));

    print_deque(deque, "Before");

    std::clock_t startTime = std::clock();
    array1.mergeInsertionSort(deque);
    std::clock_t endTime = std::clock();
    double dequeElapsedTime = double(endTime - startTime)/ CLOCKS_PER_SEC;

    print_deque(deque, "After");
    std::cout << "Time to process a range of " << deque.size() << " elements with std::deque : " << std::fixed << std::setprecision(6) << dequeElapsedTime << " us" << std::endl;

    // --------- desarrollo utilizando el contenedor list ----------
    std::list<int> list;
    for (int i = 1; i < argc; ++i)
        list.push_back(std::atoi(argv[i]));

    //print_list(list, "Before");

    startTime = std::clock();
    array1.mergeInsertionSort(list);
    endTime = std::clock();
    double listElapsedTime = double(endTime - startTime) / CLOCKS_PER_SEC;

    //print_list(list, "After");
    std::cout << "Time to process a range of " << list.size() << " elements with std::list : " << std::fixed << std::setprecision(6) << listElapsedTime << " us" << std::endl; 


    return 0;    
}