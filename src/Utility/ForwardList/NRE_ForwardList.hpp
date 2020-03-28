    
    /**
     * @file NRE_ForwardList.hpp
     * @brief Declaration of Utility's API's Container : ForwardList
     * @author Louis ABEL
     * @date 15/05/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <Memory/Allocator/NRE_Allocator.hpp>
    #include "../Detail/ForwardList/NRE_ForwardList.hpp"
    
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
            
            template <class T, class Allocator = Memory::Allocator<T>>
            using ForwardList = Detail::ForwardList<T, Allocator>;
        }
    }
    
