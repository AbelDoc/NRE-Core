
    /**
     * @file NRE_Main.cpp
     * @brief Test of Utility's API
     * @author Louis ABEL
     * @date 13/05/2019
     * @copyright CC-BY-NC-SA
     */

    #include <unordered_map>
    #include <iostream>
    #include <chrono>

    #include "Header/NRE_Utility.hpp"
    #include "Header/NRE_Exception.hpp"

    int main(int, char**) {
        std::size_t sumSTD = 0, sumNRE = 0;
        std::size_t worstSTD = 0, worstNRE = 0;
        std::size_t bestSTD = std::numeric_limits<std::size_t>::max(), bestNRE = std::numeric_limits<std::size_t>::max();

        std::size_t firstLoopSize = 100;
        std::size_t constexpr containerSize = 10'000;
        std::size_t secondLoopSize = containerSize;

        std::cout << "Benchmark : NRE::Utility::UnorderedMap vs std::unordered_map" << std::endl;
        std::cout << "Stress test [Constructor + Insert + LookUp] : x" << firstLoopSize << std::endl;
        std::cout << "\tDeclaration size : " << containerSize << std::endl;
        std::cout << "\tContainer type : std::size_t" << std::endl;
        std::cout << "\tIterator loop size : " << secondLoopSize << std::endl << std::endl;


        std::cout << "Current target : std::unordered_map" << std::endl;
        std::cout << "Size of target : " << sizeof(std::unordered_map<std::size_t, std::size_t>) << std::endl;
        std::cout << "Size of target iterator : " << sizeof(std::unordered_map<std::size_t, std::size_t>::iterator) << std::endl;

        std::size_t res = 0;
        std::size_t capacity = 0;
        for (std::size_t i = 0; i < firstLoopSize; i++) {
            auto start = std::chrono::steady_clock::now();
            std::unordered_map<std::size_t, std::size_t> map(secondLoopSize);
            for (std::size_t j = 0; j < secondLoopSize; j++) {
                map.insert({j, j});
            }
            for (auto& it : map) {
                res += it.second;
            }
            capacity = map.bucket_count();
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
        std::cout << "Final used memory : " << capacity * sizeof(std::pair<std::size_t, std::size_t>) + firstLoopSize * sizeof(std::unordered_map<std::size_t, std::size_t>) << " o" << std::endl;

        std::cout << "\tAverage : " << sumSTD / firstLoopSize << " ns" << std::endl;
        std::cout << "\tWorst   : " << worstSTD << " ns" << std::endl;
        std::cout << "\tBest    : " << bestSTD  << " ns" << std::endl;

        std::cout << "Current target : NRE::Utility::UnorderedMap" << std::endl;
        std::cout << "Size of target : " << sizeof(NRE::Utility::UnorderedMap<std::size_t, std::size_t>) << std::endl;
        std::cout << "Size of target iterator : " << sizeof(NRE::Utility::UnorderedMap<std::size_t, std::size_t>::Iterator) << std::endl;

        res = 0;
        capacity = 0;
        for (std::size_t i = 0; i < firstLoopSize; i++) {
            auto start = std::chrono::steady_clock::now();
            NRE::Utility::UnorderedMap<std::size_t, std::size_t> map(secondLoopSize);
            for (std::size_t j = 0; j < secondLoopSize; j++) {
                map.insert({j, j});
            }
            for (auto& it : map) {
                res += it.second;
            }
            capacity = map.getBucketCount();;
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
        std::cout << "Final used memory : " << capacity * sizeof(NRE::Utility::Pair<std::size_t, std::size_t>) + firstLoopSize * sizeof(NRE::Utility::UnorderedMap<std::size_t, std::size_t>) << " o" << std::endl;

        std::cout << "\tAverage : " << sumNRE / firstLoopSize << " ns" << std::endl;
        std::cout << "\tWorst   : " << worstNRE << " ns" << std::endl;
        std::cout << "\tBest    : " << bestNRE  << " ns" << std::endl;

        return 0;
    }
