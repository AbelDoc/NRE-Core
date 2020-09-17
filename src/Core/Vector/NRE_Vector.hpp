
    /**
     * @file Core/Vector/NRE_Vector.hpp
     * @brief Declaration of Core's API's Container : Vector
     * @author Louis ABEL
     * @date 15/05/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Memory/Allocator/NRE_Allocator.hpp>
     #include "../Detail/Vector/NRE_Vector.hpp"
    
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
        
            /** Hide Vector detail implementation and provide default allocator */
            template <class T, class Allocator = Memory::Allocator<T>>
            using Vector = Detail::Vector<T, Allocator>;
        }
    }

