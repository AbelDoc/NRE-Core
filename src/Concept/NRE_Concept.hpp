    
    /**
     * @file NRE_Concept.hpp
     * @brief Declaration of Utility's API's Concept
     * @author Louis ABEL
     * @date 13/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../Utility/Traits/NRE_Traits.hpp"
    
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
             * @interface SameAs
             * @brief Allow to check if two types are strictly the same
             */
            template <class T, class U>
            concept SameAs = Utility::IsSameAs<T, U>::value && Utility::IsSameAs<U, T>::value;

            /**
             * @interface Referenceable
             * @brief Define a referenceable object
             */
            template <class T>
            concept Referenceable = requires {
                typename Utility::WithReference<T>;
            };

            /**
             * @interface Dereferenceable
             * @brief Define a dereferenceable object
             */
            template <class T>
            concept Dereferenceable = requires(T& t) {
                { *t } -> Referenceable;
            };

            /**
             * @interface Integral
             * @brief Define an integral type
             */
            template <class T>
            concept Integral = std::is_integral<T>::value;
            
            /**
             * @interface FloatingPoint
             * @brief Define a floating point type
             */
            template <class T>
            concept FloatingPoint = std::is_floating_point<T>::value;

            /**
             * @interface Enum
             * @brief Define an enum type
             */
            template <class T>
            concept Enum = std::is_enum<T>::value;
    
            /**
             * @interface Union
             * @brief Define an union type
             */
            template <class T>
            concept Union = std::is_union<T>::value;
    
            /**
             * @interface Class
             * @brief Define a class type
             */
            template <class T>
            concept Class = std::is_class<T>::value;
    
            /**
             * @interface Arithmetic
             * @brief Define a arithmetic type
             */
            template <class T>
            concept Arithmetic = Integral<T> || FloatingPoint<T>;
    
            /**
             * @interface Pointer
             * @brief Define a pointer type
             */
            template <class T>
            concept Pointer = Utility::IsPointer<T>::value;
    
            /**
             * @interface MemberPointer
             * @brief Define a pointer on non-static member type
             */
            template <class T>
            concept MemberPointer = Utility::IsMemberPointer<T>::value;
    
            /**
             * @interface NullPointer
             * @brief Define a null pointer type
             */
            template <class T>
            concept NullPointer = SameAs<Utility::NullPointer, typename Utility::RemoveCV<T>::Type>;
    
            /**
             * @interface Scalar
             * @brief Define a scalar type
             */
            template <class T>
            concept Scalar = Arithmetic<T> || Enum<T> || Pointer<T> || MemberPointer<T> || NullPointer<T>;
    
            /**
             * @interface Array
             * @brief Define an array type
             */
            template <class T>
            concept Array = Utility::IsArray<T>::value;
    
    
            /**
             * @interface Object
             * @brief Define an object type
             */
            template <class T>
            concept Object = Scalar<T> || Array<T> || Union<T> || Class<T>;
    
            /**
             * @interface Copyable
             * @brief Define a copyable type
             */
            template <class T>
            concept Copyable = std::copyable<T>;
            
            /**
             * @struct IteratorTraits
             * @brief Allow an uniform access to several iterator traits
             */
            template <class It>
            struct IteratorTraits {
            };
            
            template <Object T>
            struct IteratorTraits<T*> {
                using DifferenceType = Utility::DifferenceType;
                using SizeType       = Utility::SizeType;
                using ValueType      = T;
                using Pointer        = T*;
                using Reference      = T&;
            };
            
            template <class T>
            struct IteratorTraits<const T> : IteratorTraits<T> {
            };
            
            template <class T> requires requires {
                typename T::DifferenceType;
                typename T::SizeType;
                typename T::ValueType;
                typename T::Pointer;
                typename T::Reference;
            } struct IteratorTraits<T> {
                using DifferenceType = T::DifferenceType;
                using SizeType       = T::SizeType;
                using ValueType      = T::ValueType;
                using Pointer        = T::Pointer;
                using Reference      = T::Reference;
            };
            
            /**
             * @interface Iterator
             * @brief Define a base iterator concept
             */
            template <class It>
            concept Iterator = Copyable<It> && Dereferenceable<It> && requires (It it) {
                { ++it} -> SameAs<It&>;
                typename IteratorTraits<It>::ValueType;
                typename IteratorTraits<It>::DifferenceType;
                typename IteratorTraits<It>::SizeType;
                typename IteratorTraits<It>::Reference;
                typename IteratorTraits<It>::Pointer;
            };
        }
    }