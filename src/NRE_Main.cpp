
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

    template <Concept::InputIterator It>
    void f() {
        std::cout << "Type is an input iterator" << std::endl;
    }

    template <Concept::ForwardIterator It>
    void f() {
        std::cout << "Type is a forward iterator" << std::endl;
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
    struct IntegerInputIt {
        using DifferenceType = Utility::DifferenceType;
        using SizeType = Utility::SizeType;
        using ValueType = int;
        using Pointer = int*;
        using Reference = int&;
    
        Pointer data;
    
        IntegerInputIt& operator++() {
            data++;
            return *this;
        }
    
        IntegerInputIt operator++(int) {
            IntegerInputIt r = *this;
            data++;
            return r;
        }
    
        ValueType operator*() {
            return *data;
        }
        
        bool operator==(IntegerInputIt const& it) const {
            return data == it.data;
        }
        
        bool operator!=(IntegerInputIt const& it) const {
            return !(*this == it);
        }
    };
    struct IntegerForwardIt {
        using DifferenceType = Utility::DifferenceType;
        using SizeType = Utility::SizeType;
        using ValueType = int;
        using Pointer = int*;
        using Reference = int&;
    
        Pointer data;
    
        IntegerForwardIt& operator++() {
            data++;
            return *this;
        }
    
        IntegerForwardIt operator++(int) {
            IntegerForwardIt r = *this;
            data++;
            return r;
        }
    
        Reference operator*() {
            return *data;
        }
    
        bool operator==(IntegerForwardIt const& it) const {
            return data == it.data;
        }
    
        bool operator!=(IntegerForwardIt const& it) const {
            return !(*this == it);
        }
    };
    
    int main(int, char**) {
        f<int*>();
        f<int>();
        f<IntegerIt>();
        f<IntegerInputIt>();
        f<IntegerForwardIt>();
        
        return 0;
    }
