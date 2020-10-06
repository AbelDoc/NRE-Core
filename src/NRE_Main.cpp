
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
        SizeType nb = 10;
        Vector<int> vec1(nb, 0);
        Vector<int> vec2(nb * 2, 2);
        
        std::cout << vec1 << std::endl;
    
        Core::fill(vec1.begin(), vec1.end(), 1);
        
        std::cout << vec1 << std::endl;
        std::cout << vec2 << std::endl;
        
        Core::copy(vec1.begin(), vec1.end(), vec2.begin());
        std::cout << vec2 << std::endl;
        Core::copy(vec2.begin() + 10, vec2.end(), vec2.begin());
        std::cout << vec2 << std::endl;
        
        return 0;
    }
