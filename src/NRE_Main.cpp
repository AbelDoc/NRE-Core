
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

        std::cout << Concept::InputOrOutputIterator<int*> << std::endl;
        std::cout << Concept::InputOrOutputIterator<std::istream_iterator<char>> << std::endl;
        
        return 0;
    }
