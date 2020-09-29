
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
    using namespace NRE::Core;
    using namespace NRE::Memory;
    using namespace NRE::Concept;
    
    int main(int, char**) {
        std::vector<int> vec;
        vec.emplace_back(0);
        vec.emplace_back(1);
        vec.emplace_back(2);
        vec.emplace_back(3);
        
        int* p = new int[3];
        
        copyIf(vec.begin(), vec.end(), p, [](int v) {
            return v != 0;
        });
        
        delete[] p;
        
        return 0;
    }
