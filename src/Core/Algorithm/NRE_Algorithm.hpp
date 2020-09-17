    
    /**
     * @file NRE_Algorithm.hpp
     * @brief Declaration of Core's API's Algorithm
     * @author Louis ABEL
     * @date 16/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../../Concept/NRE_IteratorConcept.hpp"
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Core
         * @brief Core's API
         */
        namespace Core {
            
            /**
             * Copy a range of data [begin, end) into an uninitialized memory location, destroy copied data in case of exception
             * @param begin the data's range begin
             * @param end   the data's range end
             * @param first the memory location to copy data into
             */
            template <Concept::InputIterator InputIt, Concept::ForwardIterator ForwardIt> requires (!Concept::DerivedFrom<IteratorCategoryT<ForwardIt>, RandomAccessIteratorCategory>)
            ForwardIt unitializedCopy(InputIt begin, InputIt end, ForwardIt first) {
                /*ForwardIt current = first;
                try {
                    for (; begin != end; ++begin, ++current) {
                        Memory::construct(addressOf(*current), *begin);
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }*/
            }
        
        }
    }