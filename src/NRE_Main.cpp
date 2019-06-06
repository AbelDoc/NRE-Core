
    /**
     * @file NRE_Main.cpp
     * @brief Test of Utility's API
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */

    #include <string>
    #include <iostream>
    #include <chrono>

    #include "Header/NRE_Utility.hpp"

    int main(int, char**) {
        std::size_t sumSTD = 0, sumNRE = 0;
        std::size_t worstSTD = 0, worstNRE = 0;
        std::size_t bestSTD = std::numeric_limits<std::size_t>::max(), bestNRE = std::numeric_limits<std::size_t>::max();

        std::size_t firstLoopSize  = 1'000'000;
        std::size_t constexpr containerSize  = 216;
        std::size_t secondLoopSize = containerSize;

        std::cout << "Benchmark : NRE::Utility::String vs std::string" << std::endl;
        std::cout << "Stress test [Constructor + End Find] : x" << firstLoopSize << std::endl;
        std::cout << "\tDeclaration size : " << containerSize << std::endl;
        std::cout << "\tContainer type : char" << std::endl;
        std::cout << "\tIterator loop size : " << secondLoopSize << std::endl << std::endl;


        std::cout << "Current target : std::string" << std::endl;
        std::cout << "Size of target : " << sizeof(std::string) << std::endl;
        std::cout << "Size of target iterator : " << sizeof(std::string::iterator) << std::endl;

        std::size_t res = 0;
        std::size_t capacity = 0;
        for (std::size_t i = 0; i < firstLoopSize; i++) {
            auto start = std::chrono::steady_clock::now();
            std::string str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB";
            res = str.rfind("AB");
            capacity = str.capacity();
            auto end = std::chrono::steady_clock::now();
            auto diff = static_cast <std::size_t> (std::chrono::duration<double, std::nano>(end - start).count());
            sumSTD += diff;
            if (diff > worstSTD) {
                worstSTD = diff;
            }
            if (diff < bestSTD) {
                bestSTD = diff;
            }
        }

        std::cout << "Result : " << res << std::endl;
        std::cout << "Final used memory : " << capacity * sizeof(char) + firstLoopSize * sizeof(std::string) << " o" << std::endl;

        std::cout << "\tAverage : " << sumSTD / firstLoopSize << " ns" << std::endl;
        std::cout << "\tWorst   : " << worstSTD << " ns" << std::endl;
        std::cout << "\tBest    : " << bestSTD  << " ns" << std::endl;

        std::cout << "Current target : NRE::Utility::String" << std::endl;
        std::cout << "Size of target : " << sizeof(NRE::Utility::String) << std::endl;
        std::cout << "Size of target iterator : " << sizeof(NRE::Utility::String::Iterator) << std::endl;

        res = 0;
        capacity = 0;
        for (std::size_t i = 0; i < firstLoopSize; i++) {
            auto start = std::chrono::steady_clock::now();
            NRE::Utility::String str = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB";
            res = str.rfind("AB", str.getSize());
            capacity = str.getCapacity();
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
        std::cout << "Final used memory : " << capacity * sizeof(char) + firstLoopSize * sizeof(NRE::Utility::String) << " o" << std::endl;

        std::cout << "\tAverage : " << sumNRE / firstLoopSize << " ns" << std::endl;
        std::cout << "\tWorst   : " << worstNRE << " ns" << std::endl;
        std::cout << "\tBest    : " << bestNRE  << " ns" << std::endl;

        return 0;
    }
