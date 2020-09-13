    
    /**
     * @file NRE_TypeTraits.hpp
     * @brief Declaration of Utility's API's Traits
     * @author Louis ABEL
     * @date 13/09/2020
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
            
            using SizeType = std::size_t;
            using DifferenceType = std::ptrdiff_t;
    
            /**
             * @struct Constant
             * @brief Wrap a constant for metaprogramming/concept use
             */
            template <class T, T v>
            struct Constant {
                static constexpr T value = v;
                using ValueType = T;
                /**
                 * @return the internal value
                 */
                constexpr operator ValueType() const noexcept {
                    return value;
                }
                /**
                 * @return the internal value
                 */
                constexpr operator()() const noexcept {
                    return value;
                }
            };
    
            /** Wrap a false value for metaprogramming/concept use */
            using FalseType = Constant<bool, false>;
            /** Wrap a true value for metaprogramming/concept use */
            using TrueType  = Constant<bool, true>;
    
            /**
             * @struct IsSameAs
             * @brief Allow to check if two types are strictly the same
             */
            template <class T, class U>
            struct IsSameAs : FalseType {
            };
    
            template <class T>
            struct IsSameAs<T, T> : TrueType {
            };
    
            /** Allow to add a reference to a type for metaprogramming/concept use */
            template <class T>
            using WithReference = T&;
            
            /**
             * @struct RemoveConst
             * @brief Allow to remove any const modifier on a given type
             */
            template <class T>
            struct RemoveConst {
                using type = T;
            };
            
            template <class T>
            struct RemoveConst<const T> {
                using type = T;
            };
    
            /**
             * @struct RemoveVolatile
             * @brief Allow to remove any volatile modifier on a given type
             */
            template <class T>
            struct RemoveVolatile {
                using Type = T;
            };
            
            template <class T>
            struct RemoveVolatile<volatile T> {
                using Type = T;
            };
    
            /**
             * @struct RemoveCV
             * @brief Allow to remove any const/volatile modifier on a given type
             */
            template <class T>
            struct RemoveCV {
                using Type = T;
            };
            
            template <class T>
            struct RemoveCV<const T> {
                using Type = T;
            };
            
            template <class T>
            struct RemoveCV<volatile T> {
                using Type = T;
            };
            
            template <class T>
            struct RemoveCV<const volatile T> {
                using Type = T;
            };
            
            /**
             * @struct IsPointerHelper
             * @brief Helper to allow to check if a type is a pointer
             */
            template <class T>
            struct IsPointerHelper : FalseType {
            };
            
            template <class T>
            struct IsPointerHelper<T*> : TrueType {
            };
    
            /**
             * @struct IsPointer
             * @brief Allow to check if a type is a pointer
             */
            template <class T>
            struct IsPointer : IsPointerHelper<typename RemoveCV<T>::Type> {
            };
    
            /**
             * @struct IsMemberPointerHelper
             * @brief Helper to allow to check if a type is a pointer to a non-static member
             */
            template <class T>
            struct IsMemberPointerHelper : FalseType {
            };
            
            template <class T, class U>
            struct IsMemberPointerHelper<T U::*> : TrueType {
            };
    
            /**
             * @struct IsMemberPointer
             * @brief Allow to check if a type is a pointer to a non-static member
             */
            template <class T>
            struct IsMemberPointer : IsMemberPointerHelper<typename RemoveCV<T>::Type> {
            };
            
            /**
             * @struct IsArray
             * @brief Allow to check if a type is an array
             */
            template <class T>
            struct IsArray : FalseType {
            };
            
            template <class T>
            struct IsArray<T[]> : TrueType {
            };
            
            template <class T, SizeType N>
            struct IsArray<T[N]> : TrueType {
            };
            
            /** Define a null pointer type from the nullptr litteral */
            using NullPointer = decltype(nullptr);
            
        }
    }