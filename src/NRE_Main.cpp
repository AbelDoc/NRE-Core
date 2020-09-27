
    /**
     * @file NRE_Main.cpp
     * @brief Test of Core's API
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */
    
    #include <iostream>
    
    #include "Header/NRE_Core.hpp"

    using namespace NRE;
    
    int main(int, char**) {
        std::allocator<char> aChar;
        std::allocator<int> aInt;
        std::allocator<long long int> aLongLongInt;
        std::allocator<long double> aLongDouble;
        
        std::cout << Memory::AllocatorTraits<decltype(aChar)>::getMaxSize(aChar) << std::endl;
        std::cout << Memory::AllocatorTraits<decltype(aInt)>::getMaxSize(aInt) << std::endl;
        std::cout << Memory::AllocatorTraits<decltype(aLongLongInt)>::getMaxSize(aLongLongInt) << std::endl;
        std::cout << Memory::AllocatorTraits<decltype(aLongDouble)>::getMaxSize(aLongDouble) << std::endl;
        
        return 0;
    }
