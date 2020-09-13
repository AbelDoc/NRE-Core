
    /**
     * @file NRE_Main.cpp
     * @brief Test of Utility's API
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */
    
    #define NRE_USE_MEMORY_MANAGER
    
    #include <unordered_map>
    #include <iostream>
    #include <chrono>

    #include "Header/NRE_Utility.hpp"

    using namespace NRE::Utility;
    
    int main(int, char**) {
        /*std::size_t sumNRE2 = 0, sumNRE = 0;
        std::size_t worstNRE2 = 0, worstNRE = 0;
        std::size_t bestNRE2 = std::numeric_limits<std::size_t>::max(), bestNRE = std::numeric_limits<std::size_t>::max();

        std::size_t firstLoopSize = 1000;
        std::size_t constexpr containerSize = 100'000;
        std::size_t secondLoopSize = containerSize;

        std::cout << "Benchmark : std::vector vs NRE::Utility::Vector" << std::endl;
        std::cout << "Stress test [Constructor + Insert + LookUp] : x" << firstLoopSize << std::endl;
        std::cout << "\tDeclaration size : " << containerSize << std::endl;
        std::cout << "\tContainer type : std::size_t" << std::endl;
        std::cout << "\tIterator loop size : " << secondLoopSize << std::endl << std::endl;


        std::cout << "Current target : std::vector" << std::endl;
        std::cout << "Size of target : " << sizeof(std::vector<std::size_t>) << std::endl;
        std::cout << "Size of target iterator : " << sizeof(std::vector<std::size_t>::iterator) << std::endl;

        std::size_t res = 0;
        std::size_t capacity = 0;
        for (std::size_t i = 0; i < firstLoopSize; i++) {
            auto start = std::chrono::steady_clock::now();
            std::vector<std::size_t> o;
            for (std::size_t j = 0; j < secondLoopSize; j++) {
                o.emplace_back(j);
            }
            for (auto& it : o) {
                res += it;
            }
            capacity = o.capacity();
            auto end = std::chrono::steady_clock::now();
            auto diff = static_cast <std::size_t> (std::chrono::duration<double, std::nano>(end - start).count());
            sumNRE2 += diff;
            if (diff > worstNRE2) {
                worstNRE2 = diff;
            }
            if (diff < bestNRE2) {
                bestNRE2 = diff;
            }
        }

        std::cout << "Result : " << res << std::endl;
        std::cout << "Final used memory : " << firstLoopSize * capacity * sizeof(std::size_t) + firstLoopSize * sizeof(std::vector<std::size_t>) << " o" << std::endl;

        std::cout << "\tAverage : " << sumNRE2 / firstLoopSize << " ns" << std::endl;
        std::cout << "\tWorst   : " << worstNRE2 << " ns" << std::endl;
        std::cout << "\tBest    : " << bestNRE2 << " ns" << std::endl;

        std::cout << "Current target : NRE::Utility::Vector" << std::endl;
        std::cout << "Size of target : " << sizeof(Vector<std::size_t>) << std::endl;
        std::cout << "Size of target iterator : " << sizeof(Vector<std::size_t>::Iterator) << std::endl;

        res = 0;
        capacity = 0;
        for (std::size_t i = 0; i < firstLoopSize; i++) {
            auto start = std::chrono::steady_clock::now();
            Vector<std::size_t> o;
            for (std::size_t j = 0; j < secondLoopSize; j++) {
                o.emplaceBack(j);
            }
            for (auto& it : o) {
                res += it;
            }
            capacity = o.getCapacity();;
            auto end = std::chrono::steady_clock::now();
            auto diff = static_cast <std::size_t> (std::chrono::duration<double, std::nano>(end - start).count());
            sumNRE += diff;
            if (diff > worstNRE) {
                worstNRE = diff;
            }
            if (diff < bestNRE) {
                bestNRE = diff;
            }
        }

        std::cout << "Result : " << res << std::endl;
        std::cout << "Final used memory : " << firstLoopSize * capacity * sizeof(std::size_t) + firstLoopSize * sizeof(Vector<std::size_t>) << " o" << std::endl;

        std::cout << "\tAverage : " << sumNRE / firstLoopSize << " ns" << std::endl;
        std::cout << "\tWorst   : " << worstNRE << " ns" << std::endl;
        std::cout << "\tBest    : " << bestNRE  << " ns" << std::endl;*/
        
        Vector<int*> test(10);
        std::cout << *test[0] << std::endl;
        std::cout << *test[1] << std::endl;
        std::cout << *test[2] << std::endl;
        std::cout << *test[3] << std::endl;
        
        return 0;
    }
