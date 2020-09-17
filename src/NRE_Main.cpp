
    /**
     * @file NRE_Main.cpp
     * @brief Test of Core's API
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */
    
    #include <iostream>
    #include <forward_list>
    #include <list>
    #include <deque>
    #include <vector>
    
    #include "Header/NRE_Core.hpp"

    using namespace NRE;
    
    int main(int, char**) {
        std::cout << "Input/Output Iterator test : " << std::endl;
        std::cout << "int* -> " << Concept::InputOrOutputIterator<int*> << std::endl;
    
        std::cout << "\nInput Iterator test : " << std::endl;
        std::cout << "istream_iterator<char> -> " << Concept::InputIterator<std::istream_iterator<char>> << std::endl;
        std::cout << "int* -> " << Concept::InputIterator<int*> << std::endl;
    
        std::cout << "\nOutput Iterator test : " << std::endl;
        std::cout << "ostream_iterator<char> -> " << Concept::OutputIterator<std::ostream_iterator<char>, char> << std::endl;
        std::cout << "int* -> " << Concept::OutputIterator<int*, int> << std::endl;
    
        std::cout << "\nForward Iterator test : " << std::endl;
        std::cout << "forward_list<int>::iterator -> " << Concept::ForwardIterator<std::forward_list<int>::iterator> << std::endl;
        std::cout << "int* -> " << Concept::ForwardIterator<int*> << std::endl;
    
        std::cout << "\nBidirectional Iterator test : " << std::endl;
        std::cout << "list<int>::iterator -> " << Concept::BidirectionalIterator<std::list<int>::iterator> << std::endl;
        std::cout << "int* -> " << Concept::BidirectionalIterator<int*> << std::endl;
    
        std::cout << "\nRandom Access Iterator test : " << std::endl;
        std::cout << "deque<int>::iterator -> " << Concept::RandomAccessIterator<std::deque<int>::iterator> << std::endl;
        std::cout << "int* -> " << Concept::RandomAccessIterator<int*> << std::endl;
    
        std::cout << "\nContiguous Iterator test : " << std::endl;
        std::cout << "vector<int>::iterator -> " << Concept::ContiguousIterator<std::vector<int>::iterator> << std::endl;
        std::cout << "int* -> " << Concept::ContiguousIterator<int*> << std::endl;
        
        return 0;
    }
