
    /**
     * @file NRE_Main.cpp
     * @brief Test of Utility's API
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */
    
    #include <iostream>
    
    #include "Header/NRE_Utility.hpp"

    using namespace NRE;
    
    int main(int, char**) {
        std::cout << "Input/Output Iterator test : " << std::endl;
        std::cout << "int* -> " << Concept::InputOrOutputIterator<int*> << std::endl;
    
        std::cout << "Input Iterator test : " << std::endl;
        std::cout << "istream_iterator<char> -> " << Concept::InputIterator<std::istream_iterator<char>> << std::endl;
        std::cout << "int* -> " << Concept::InputIterator<int*> << std::endl;
    
        std::cout << "Output Iterator test : " << std::endl;
        std::cout << "ostream_iterator<char> -> " << Concept::OutputIterator<std::ostream_iterator<char>, char> << std::endl;
        std::cout << "int* -> " << Concept::OutputIterator<int*, int> << std::endl;
        
        return 0;
    }
