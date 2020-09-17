    
    /**
     * @file Core/UnorderedMap/NRE_UnorderedMap.hpp
     * @brief Declaration of Core's API's Container : UnorderedMap
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
         * @namespace Core
         * @brief Core's API
         */
        namespace Core {
    
            /** Hide UnorderedMap detail implementation and provide default allocator */
            template <class Key, class T, class Allocator = Memory::Allocator<Pair<Key, T>>, bool StoreHash = false, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
            using UnorderedMap = Detail::UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>;
        }
    }
    
