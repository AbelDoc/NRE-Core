
    /**
     * @file NRE_Main.cpp
     * @brief Test of Utility's API
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */

    #include <forward_list>
    #include <iostream>
    #include <chrono>

    #include "Header/NRE_Utility.hpp"

    int main(int, char**) {
        std::size_t sumSTD = 0, sumNRE = 0;
        std::size_t worstSTD = 0, worstNRE = 0;
        std::size_t bestSTD = std::numeric_limits<std::size_t>::max(), bestNRE = std::numeric_limits<std::size_t>::max();

        std::size_t firstLoopSize  = 1;
        std::size_t constexpr containerSize  = 1'000;
        std::size_t secondLoopSize = containerSize;

        std::cout << "Benchmark : NRE::Utility::ForwardList vs std::forward_list" << std::endl;
        std::cout << "Stress test [Constructor + PushFront] : x" << firstLoopSize << std::endl;
        std::cout << "\tDeclaration size : " << containerSize << std::endl;
        std::cout << "\tContainer type : std::size_t" << std::endl;
        std::cout << "\tIterator loop size : " << secondLoopSize << std::endl << std::endl;


        std::cout << "Current target : std::forward_list" << std::endl;
        std::cout << "Size of target : " << sizeof(std::forward_list<std::size_t>) << std::endl;
        std::cout << "Size of target iterator : " << sizeof(std::forward_list<std::size_t>::iterator) << std::endl;

        std::size_t res = 0;
        std::size_t capacity = 0;
        for (std::size_t i = 0; i < firstLoopSize; i++) {
            auto start = std::chrono::steady_clock::now();
            std::forward_list<std::size_t> list;
            for (std::size_t j = 0; j < secondLoopSize; j++) {
                list.push_front(j);
            }
            capacity = secondLoopSize;
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
        std::cout << "Final used memory : " << capacity * sizeof(std::size_t) + firstLoopSize * sizeof(std::forward_list<std::size_t>) << " o" << std::endl;

        std::cout << "\tAverage : " << sumSTD / firstLoopSize << " ns" << std::endl;
        std::cout << "\tWorst   : " << worstSTD << " ns" << std::endl;
        std::cout << "\tBest    : " << bestSTD  << " ns" << std::endl;

        std::cout << "Current target : NRE::Utility::ForwardList" << std::endl;
        std::cout << "Size of target : " << sizeof(NRE::Utility::ForwardList<std::size_t>) << std::endl;
        std::cout << "Size of target iterator : " << sizeof(NRE::Utility::ForwardList<std::size_t>::Iterator) << std::endl;

        res = 0;
        capacity = 0;
        for (std::size_t i = 0; i < firstLoopSize; i++) {
            auto start = std::chrono::steady_clock::now();
            NRE::Utility::ForwardList<std::size_t> list;
            for (std::size_t j = 0; j < secondLoopSize; j++) {
                list.pushFront(j);
            }
            capacity = secondLoopSize;
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
        std::cout << "Final used memory : " << capacity * sizeof(std::size_t) + firstLoopSize * sizeof(NRE::Utility::ForwardList<std::size_t>) << " o" << std::endl;

        std::cout << "\tAverage : " << sumNRE / firstLoopSize << " ns" << std::endl;
        std::cout << "\tWorst   : " << worstNRE << " ns" << std::endl;
        std::cout << "\tBest    : " << bestNRE  << " ns" << std::endl;

        return 0;
    }
