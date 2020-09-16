    
    /**
     * @file NRE_TypeTraits.hpp
     * @brief Declaration of Utility's API's Traits
     * @author Louis ABEL
     * @date 13/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../../Concept/NRE_TypeConcept.hpp"
    
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
            
            /** Define an abstract unsigned size type */
            using SizeType = std::size_t;
            /** Define an abstract signed size type */
            using DifferenceType = std::ptrdiff_t;
            /** Define a null pointer type from the nullptr litteral */
            using NullPointer = decltype(nullptr);

            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wpedantic"
                #if __SIZEOF_INT128__
                    /** Define the maximum signed type */
                    using MaxDifferenceType = __int128;
                    /** Define the maximum unsigned type */
                    using MaxSizeType       = unsigned __int128;
                #else
                    /** Define the maximum signed type */
                    using MaxDifferenceType = long long;
                    /** Define the maximum unsigned type */
                    using MaxSizeType       = unsigned long long;
                #endif
            #pragma GCC diagnostic pop
            
            /**
             * @struct Constant
             * @brief Wrap a constant for metaprogramming/concept use
             */
            template <class T, T v>
            struct Constant {
                /** The internal constant value */
                static constexpr T value = v;
                /** The internal constant type */
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
            
            /** Helper to access IsSameAs value */
            template <class T, class U>
            inline constexpr bool IsSameAsV = IsSameAs<T, U>::value;
    
            /** Allow to add a reference to a type for metaprogramming/concept use */
            template <class T>
            using WithReference = T&;
            
            /**
             * @struct RemoveConst
             * @brief Allow to remove any const modifier on a given type
             */
            template <class T>
            struct RemoveConst {
                using Type = T;
            };
            
            template <class T>
            struct RemoveConst<const T> {
                using Type = T;
            };
            
            /** Helper to access RemoveConst type */
            template <class T>
            using RemoveConstT = typename RemoveConst<T>::Type;
    
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
    
            /** Helper to access RemoveVolatile type */
            template <class T>
            using RemoveVolatileT = typename RemoveVolatile<T>::Type;
    
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
    
            /** Helper to access RemoveCV type */
            template <class T>
            using RemoveCVT = typename RemoveCV<T>::Type;
            
    
            /**
             * @struct RemoveReference
             * @brief Allow to remove any reference on a given type
             */
            template <class T>
            struct RemoveReference {
                using Type = T;
            };
            
            template <class T>
            struct RemoveReference<T&> {
                using Type = T;
            };
            
            template <class T>
            struct RemoveReference<T&&> {
                using Type = T;
            };
    
            /** Helper to access RemoveReference type */
            template <class T>
            using RemoveReferenceT = typename RemoveReference<T>::Type;
            
            /**
             * @struct RemoveCVReference
             * @brief Allow to remove any reference and const/volatile modifier on a given type
             */
            template <class T>
            struct RemoveCVReference {
                using Type = RemoveCVT<RemoveReferenceT<T>>;
            };
    
            /** Helper to access RemoveCVReference type */
            template <class T>
            using RemoveCVReferenceT = typename RemoveCVReference<T>::Type;
            
            /**
             * @struct RemoveExtent
             * @brief Allow to remove one dimension from an array type
             */
            template <class T>
            struct RemoveExtent {
                using Type = T;
            };
            
            template <class T>
            struct RemoveExtent<T[]> {
                using Type = T;
            };
            
            template <class T, SizeType N>
            struct RemoveExtent<T[N]> {
                using Type = T;
            };
            
            /** Helper to access RemoveExtent type */
            template <class T>
            using RemoveExtentT = typename RemoveExtent<T>::Type;
    
    
            namespace Detail {
                /**
                 * @struct IsPointer
                 * @brief Helper to allow to check if a type is a pointer
                 */
                template <class T>
                struct IsPointer : FalseType {
                };
    
                template <class T>
                struct IsPointer<T*> : TrueType {
                };
            }
    
            /**
             * @struct IsPointer
             * @brief Allow to check if a type is a pointer
             */
            template <class T>
            struct IsPointer : Detail::IsPointer<typename RemoveCV<T>::Type> {
            };
    
            /** Helper to access IsPointer value */
            template <class T>
            inline constexpr bool IsPointerV = IsPointer<T>::value;
            
            namespace Detail {
                /**
                 * @struct IsMemberPointer
                 * @brief Helper to allow to check if a type is a pointer to a non-static member
                 */
                template <class T>
                struct IsMemberPointer : FalseType {
                };
    
                template <class T, class U>
                struct IsMemberPointer<T U::*> : TrueType {
                };
            }
    
            /**
             * @struct IsMemberPointer
             * @brief Allow to check if a type is a pointer to a non-static member
             */
            template <class T>
            struct IsMemberPointer : Detail::IsMemberPointer<typename RemoveCV<T>::Type> {
            };
    
            /** Helper to access IsMemberPointer value */
            template <class T>
            inline constexpr bool IsMemberPointerV = IsMemberPointer<T>::value;
            
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
    
            /** Helper to access IsArray value */
            template <class T>
            inline constexpr bool IsArrayV = IsArray<T>::value;
            
            /**
             * @struct CommonReference
             * @brief Allow to find a reference that's convertible to any of the given types
             */
            template <class ... T>
            struct CommonReference {
                using Type = typename std::common_reference<T...>::type;
            };
            
            /** Helper to access CommonReference type */
            template <class ... T>
            using CommonReferenceT = typename CommonReference<T...>::Type;
            
            
            /**
             * @struct AddPointer
             * @brief Allow to get a pointer type on a given type
             */
            template <class T>
            struct AddPointer {
                using Type = typename std::add_pointer<T>::type;
            };
            
            /** Helper to access AddPointer type */
            template <class T>
            using AddPointerT = typename AddPointer<T>::Type;
            
            /**
             * @struct IsbaseOf
             * @brief Allow to check if a type is a base of a derived one
             */
            template <class B, class D>
            struct IsBaseOf {
                static constexpr bool value = std::is_base_of_v<B, D>;
            };
            
            /** Helper to access IsBaseOf value */
            template <class B, class D>
            inline constexpr bool IsBaseOfV = IsBaseOf<B, D>::value;
            
            /**
             * @struct IsLValueReference
             * @brief Allow to check if a type is a l-value reference
             */
            template <class T>
            struct IsLValueReference : FalseType {
            };
            
            template <class T>
            struct IsLValueReference<T&> : TrueType {
            };
            
            /** Helper to access IsLValueReference value */
            template <class T>
            inline constexpr bool IsLValueReferenceV = IsLValueReference<T>::value;
            
            /**
             * @struct MakeSigned
             * @brief Provide a signed type from the given type
             */
            template <class T>
            struct MakeSigned {
                using Type = std::make_signed_t<T>;
            };
            
            /** Helper to access MakeSigned type */
            template <class T>
            using MakeSignedT = typename MakeSigned<T>::Type;
            
            /**
             * @struct IsSigned
             * @brief Allow to check if a type is signed or not
             */
            template <class T>
            struct IsSigned : FalseType {
            };
    
            template <Concept::Arithmetic T>
            struct IsSigned<T> : Constant<bool, T(-1) < T(0)> {
            };
            
            /** Helper to access IsSigned value */
            template <class T>
            inline constexpr bool IsSignedV = IsSigned<T>::value;
            
            /**
             * @struct IsVolatile
             * @brief ALlow to check if a type is volatile or not
             */
            template <class T>
            struct IsVolatile : FalseType {
            };
            
            template <class T>
            struct IsVolatile<volatile T> : TrueType {
            };
            
            /** Helper to access IsVolatile value */
            template <class T>
            inline constexpr bool IsVolatileV = IsVolatile<T>::value;
        }
    }