
    /**
     * @file NRE_Main.cpp
     * @brief Test of Utility's API
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */
    
    #include <iostream>
    
    #include "Concept/NRE_Concept.hpp"

    using namespace NRE;
    
    template <Concept::Iterator It>
    void f() {
        std::cout << "Type is an iterator" << std::endl;
    }
    
    template <class T>
    void f() {
        std::cout << "Type isn't an iterator" << std::endl;
    }
    
    struct IntegerIt {
        using DifferenceType = Utility::DifferenceType;
        using SizeType = Utility::SizeType;
        using ValueType = int;
        using Pointer = int*;
        using Reference = int&;
        
        Pointer data;
        
        IntegerIt& operator++() {
            data++;
            return *this;
        }
        
        ValueType operator*() {
            return *data;
        }
    };
    
    int main(int, char**) {
        
        f<int*>();
        f<int>();
        f<IntegerIt>();
        
        return 0;
    }
