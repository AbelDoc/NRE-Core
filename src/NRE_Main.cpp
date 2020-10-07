
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
        Vector<unsigned char> vec(SizeType(10), 1);
        
        std::cout << vec << std::endl;
        
        Core::fill(vec.begin(), vec.end(), 2);

        std::cout << vec << std::endl;
        
        return 0;
    }
