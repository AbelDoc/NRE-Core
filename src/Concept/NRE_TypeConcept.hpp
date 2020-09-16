    
    /**
     * @file NRE_TypeConcept.hpp
     * @brief Declaration of Utility's API's Concept
     * @author Louis ABEL
     * @date 15/09/2020
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
         * @namespace Concept
         * @brief Concept's API
         */
        namespace Concept {
        
            /**
             * @interface Integral
             * @brief Define an integral type
             */
            template <class T>
            concept Integral = std::is_integral_v<T>;
        
            /**
             * @interface FloatingPoint
             * @brief Define a floating point type
             */
            template <class T>
            concept FloatingPoint = std::is_floating_point_v<T>;
        
            /**
             * @interface Enum
             * @brief Define an enum type
             */
            template <class T>
            concept Enum = std::is_enum_v<T>;
        
            /**
             * @interface Union
             * @brief Define an union type
             */
            template <class T>
            concept Union = std::is_union_v<T>;
        
            /**
             * @interface Class
             * @brief Define a class type
             */
            template <class T>
            concept Class = std::is_class_v<T>;
        
            /**
             * @interface Arithmetic
             * @brief Define a arithmetic type
             */
            template <class T>
            concept Arithmetic = Integral<T> || FloatingPoint<T>;
        }
    }