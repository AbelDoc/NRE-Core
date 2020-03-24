    
    /**
     * @file NRE_UnorderedMap.hpp
     * @brief Declaration of Utility's API's Container : UnorderedMap
     * @author Louis ABEL
     * @date 15/05/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <Memory/Allocator/NRE_Allocator.hpp>
    #include "../Detail/UnorderedMap/NRE_UnorderedMap.hpp"
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Utility
         * @brief Utility's API
         */
        namespace Utility {
            
            template <class Key, class T, class Allocator = Memory::Allocator<T>, bool StoreHash = false, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
            using UnorderedMap = Detail::UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>;
        }
    }
    
