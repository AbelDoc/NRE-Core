    
    /**
     * @file NRE_TypeTraits.hpp
     * @brief Declaration of Utility's API's Type Traits
     * @author Louis ABEL
     * @date 27/03/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include <type_traits>

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
    
            /**< Shortcut to is_trivially_copyable_v inner value */
            template <class T>
            constexpr bool IsTriviallyCopyableV = std::is_trivially_copyable_v<T>;
            
            /**< Allow to enable a function if the given template parameter is trivially copyable */
            template <class T>
            using UseIfTriviallyCopyable = std::enable_if_t<IsTriviallyCopyableV<T>, int>;
    
            /**< Allow to enable a function if the given template parameter is not trivially copyable */
            template <class T>
            using UseIfNotTriviallyCopyable = std::enable_if_t<!IsTriviallyCopyableV<T>, int>;
        
        }
    }