
    /**
     * @file NRE_Main.cpp
     * @brief Test of Core's API
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */
    
    #include <iostream>
    #include <forward_list>

    #include "Header/NRE_Core.hpp"

    using namespace NRE;
    using namespace NRE::Core;
    using namespace NRE::Memory;
    using namespace NRE::Concept;
    
    int main(int, char**) {
        int a[5] = {1, 2, 3, 4, 5};
        int* p = a;
        std::cout << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << std::endl;
        fill(p, next(p, 3), 10);
        std::cout << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << std::endl;
        ReverseIterator<int*> rp(p + 5);
        std::cout << *(0 + rp) << std::endl;
        
//        Vector<unsigned char> vec(SizeType(10), 1);
//
//        std::cout << vec << std::endl;
//
//        Core::fill(vec, 2);
//
//        std::cout << vec << std::endl;
//
//        vec[9] = 99;
//
//        auto it = vec.begin();
//        Core::advance(it, 15, vec.end() - 1);
//        std::cout << static_cast <int> (*it) << std::endl;
//
//        Core::shiftLeft(vec, 1);
//
//        std::cout << vec << std::endl;
//
//        Core::shiftRight(vec, 1);
//
//        std::cout << vec << std::endl;
//
//        Core::transform(vec, vec.begin(), [&](unsigned char c) {
//            return static_cast <unsigned char> (c * 10);
//        });
//
//        std::cout << vec << std::endl;
//
//        Core::transform(vec, vec, vec.begin(), [&](unsigned char c1, unsigned char c2) {
//            return static_cast <unsigned char> (c1 + c2);
//        });
//
//        std::cout << vec << std::endl;
//
//        std::cout << static_cast <int> (*Core::find(vec, 188)) << std::endl;
//
//        std::cout << static_cast <int> (*vec.begin()) << std::endl;
//        std::cout << static_cast <int> (*vec.rbegin()) << std::endl;
//
        return 0;
    }
