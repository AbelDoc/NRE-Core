    
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
             * @interface Destructible
             * @brief Define a type that's destructible without the risk of throwing exceptions
             */
            template <class T>
            concept Destructible = std::destructible<T>;
    
            /**
             * @interface ConstructibleFrom
             * @brief Define a type that's constructible from a given set of arguments
             */
            template <class T, class ... Args>
            concept ConstructibleFrom = Destructible<T> && std::is_constructible_v<T, Args...>;
    
            /**
             * @interface ConvertibleTo
             * @brief Define a type that's convertible to another
             */
            template <class T, class U>
            concept ConvertibleTo = std::convertible_to<T, U>;
    
            template <class T>
            concept ConvertibleToBoolean = ConvertibleTo<T, bool>;
    
            /**
             * @interface BooleanTestable
             * @brief Define a type that's convertible to boolean
             */
            template <class T>
            concept BooleanTestable = ConvertibleToBoolean<T> && requires(T&& b) {
                { !std::forward<T>(b) } -> ConvertibleToBoolean;
            };
    
            /**
             * @interface EqualityComparableWith
             * @brief Define a type that's equality comparable with another
             */
            template <class T, class U>
            concept EqualityComparableWith = requires(typename Utility::RemoveReference<T>::Type const& t,
                                                      typename Utility::RemoveReference<U>::Type const& u) {
                { t == u } -> BooleanTestable;
                { t != u } -> BooleanTestable;
                { u == t } -> BooleanTestable;
                { u != t } -> BooleanTestable;
            };
    
            /**
             * @interface EqualityComparable
             * @brief Define a type that's equality comparable with himself
             */
            template <class T>
            concept EqualityComparable = EqualityComparableWith<T, T>;
        }
        /**
         * @namespace Utility
         * @brief Utility's API
         */
        namespace Utility {
    
            /**
             * @struct IteratorTraits
             * @brief Allow an uniform access to several iterator traits
             */
            template <class It>
            struct IteratorTraits {
            };
    
            template <Concept::Object T>
            struct IteratorTraits<T*> {
                using DifferenceType = DifferenceType;
                using SizeType       = SizeType;
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
            }
            struct IteratorTraits<T> {
                using DifferenceType = T::DifferenceType;
                using SizeType       = T::SizeType;
                using ValueType      = T::ValueType;
                using Pointer        = T::Pointer;
                using Reference      = T::Reference;
            };
        }
        /**
         * @namespace Concept
         * @brief Concept's API
         */
        namespace Concept {
            /**
             * @interface Iterator
             * @brief Define a base iterator concept
             */
            template <class It>
            concept Iterator = Copyable<It> && Dereferenceable<It> && requires(It it) {
                { ++it } -> SameAs<It&>;
                typename Utility::IteratorTraits<It>::ValueType;
                typename Utility::IteratorTraits<It>::DifferenceType;
                typename Utility::IteratorTraits<It>::SizeType;
                typename Utility::IteratorTraits<It>::Reference;
                typename Utility::IteratorTraits<It>::Pointer;
            };
    
            /**
             * @interface InputIterator
             * @brief Define an input iterator, capable of reading the pointed element, guarantee validity on single pass
             */
            template <class It>
            concept InputIterator = Iterator<It> && EqualityComparable<It> && requires(It it) {
                typename Utility::CommonReference<typename Utility::IteratorTraits<It>::Reference&&, typename Utility::IteratorTraits<It>::ValueType&>;
                *it++;
                typename Utility::CommonReference<decltype(*it++)&&, typename Utility::IteratorTraits<It>::ValueType&>;
            };
    
            /**
             * @interface ForwardIterator
             * @brief Define a forward iterator, capable of multi-pass iteration, if coupled with OutputIterator it will be mutable
             */
            template <class It>
            concept ForwardIterator = InputIterator<It> && ConstructibleFrom<It> && SameAs<typename Utility::IteratorTraits<It>::ValueType, typename Utility::RemoveCVReference<typename Utility::IteratorTraits<It>::Reference>::Type> && requires(It it) {
                {  it++ } -> ConvertibleTo<It const&>;
                { *it++ } -> SameAs<typename Utility::IteratorTraits<It>::Reference>;
            };
        }
    }