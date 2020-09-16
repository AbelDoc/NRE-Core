    
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
            concept SameAs = Utility::IsSameAsV<T, U> && Utility::IsSameAsV<U, T>;
    
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
            concept Dereferenceable = requires(T t) {
                { *t } -> Referenceable;
            };
    
            /**
             * @interface Pointer
             * @brief Define a pointer type
             */
            template <class T>
            concept Pointer = Utility::IsPointerV<T>;
    
            /**
             * @interface MemberPointer
             * @brief Define a pointer on non-static member type
             */
            template <class T>
            concept MemberPointer = Utility::IsMemberPointerV<T>;
    
            /**
             * @interface NullPointer
             * @brief Define a null pointer type
             */
            template <class T>
            concept NullPointer = SameAs < Utility::NullPointer, Utility::RemoveCVT <T>>;
    
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
            concept Array = Utility::IsArrayV<T>;
    
    
            /**
             * @interface Object
             * @brief Define an object type
             */
            template <class T>
            concept Object = Scalar<T> || Array<T> || Union<T> || Class<T>;
    
            /**
             * @interface Signed
             * @brief Define a signed type
             */
            template <class T>
            concept Signed = Utility::IsSignedV<T>;
            
            /**
             * @interface SignedInteger
             * @brief Define a signed integer type
             */
            template <class T>
            concept SignedInteger = Integral<T> && Signed<T>;
            
            /**
             * @interface SignedIntegerLike
             * @brief Define a signed integer type or a type behaving like one
             */
            template <class T>
            concept SignedIntegerLike = SignedInteger<T> || SameAs<T, Utility::MaxDifferenceType>;
            
            /**
             * @interface Trivial
             * @brief Define a trivial type (either scalar or trivially copyable)
             */
            template <class T>
            concept Trivial = std::is_trivial_v<T>;
            
            /**
             * @interface TriviallyCopyable
             * @brief Define a trivally copyable type
             */
            template <class T>
            concept TriviallyCopyable = std::is_trivially_copyable_v<T>;
            
            /**
             * @interface Volatile
             * @brief Define a volatile type
             */
            template <class T>
            concept Volatile = Utility::IsVolatileV<T>;
            
            /**
             * @interface NonVolatileTriviallyCopyable
             * @brief Define a non-volatile type which can be trivially copied
             */
            template <class T>
            concept NonVolatileTriviallyCopyable = TriviallyCopyable<T> && !Volatile<T>;
            
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
             * @interface ConvertibleTo
             * @brief Define a type that's convertible to another
             */
            template <class F, class T>
            concept ConvertibleTo = std::convertible_to<F, T>;
    
            /**
             * @interface ConvertibleToBoolean
             * @brief Define a type convertible to a boolean
             */
            template <class T>
            concept ConvertibleToBoolean = ConvertibleTo<T, bool>;
    
            /**
             * @interface ConstructibleFrom
             * @brief Define a type that's constructible from a given set of arguments
             */
            template <class T, class ... Args>
            concept ConstructibleFrom = Destructible<T> && std::is_constructible_v<T, Args...>;
            
            /**
             * @interface DefaultInitializable
             * @brief Define a type that's default initiazable
             */
            template <class T>
            concept DefaultInitializable = ConstructibleFrom<T> && requires {
                T{};
                ::new (static_cast <void*> (nullptr)) T;
            };
    
            /**
             * @interface MoveConstructible
             * @brief Define a type that's move constructible
             */
            template <class T>
            concept MoveConstructible = ConstructibleFrom<T, T> && ConvertibleTo<T, T>;
    
            /**
             * @interface CommonReferenceWith
             * @brief Define two type sharing a common reference type and convertible to it
             */
            template <class T, class U>
            concept CommonReferenceWith = SameAs<Utility::CommonReferenceT<T, U>, Utility::CommonReferenceT<U, T>> &&
                                          ConvertibleTo<T, Utility::CommonReferenceT<T, U>> &&
                                          ConvertibleTo<U, Utility::CommonReferenceT<T, U>>;
            
            /**
             * @interface AssignableFrom
             * @brief Define a type that's l-value is assignable from another type
             */
            template <class L, class R>
            concept AssignableFrom = Utility::IsLValueReferenceV<L> && CommonReferenceWith<Utility::RemoveReferenceT<L> const&, Utility::RemoveReferenceT<R> const&> && requires (L l, R&& r) {
                { l = std::forward<R>(r) } -> SameAs<L>;
            };
            
            /**
             * @interface Assignable
             * @brief Define a type that's assignable from another type
             */
            template <class L, class R>
            concept Assignable = std::is_assignable_v<L, R>;
            
            /**
             * @interface Swappable
             * @brief Define a type that's swappable with himself
             */
            template <class T>
            concept Swappable = std::swappable<T>;
            
            /**
             * @interface Moveable
             * @brief Define a type that's moveable, can ve move constructed, move assigned, and swappable
             */
            template <class T>
            concept Moveable = Object<T> && MoveConstructible<T> && AssignableFrom<T&, T> && Swappable<T>;
    
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
    
            /**
             * @interface TotallyOrderedWith
             * @brief Define a type that's totally ordered with another
             */
            template <class T, class U>
            concept TotallyOrderedWith = EqualityComparableWith<T, U> && requires (typename Utility::RemoveReference<T>::Type const& t,
                                                                                   typename Utility::RemoveReference<U>::Type const& u) {
                { t <  u } -> BooleanTestable;
                { t >  u } -> BooleanTestable;
                { t <= u } -> BooleanTestable;
                { t >= u } -> BooleanTestable;
                { u <  t } -> BooleanTestable;
                { u >  t } -> BooleanTestable;
                { u <= t } -> BooleanTestable;
                { u >= t } -> BooleanTestable;
            };
    
            /**
             * @interface TotallyOrdered
             * @brief Define a type that's totally ordered with himself
             */
            template <class T>
            concept TotallyOrdered = TotallyOrderedWith<T, T>;
    
            /**
             * @interface DerivedFrom
             * @brief Allow to verify if a type is derived from another
             */
            template <class D, class B>
            concept DerivedFrom = Utility::IsBaseOf<B, D>::value && ConvertibleTo<const volatile D*, const volatile B*>;
            
            /**
             * @interface SemiRegular
             * @brief Define a type that's both copyable and default constructible
             */
            template <class T>
            concept SemiRegular = Copyable<T> && DefaultInitializable<T>;
            
            /**
             * @interface Regular
             * @brief Define a type that's copyable, default constructible and equality comparable
             */
            template <class T>
            concept Regular = SemiRegular<T> && EqualityComparable<T>;
        }
    }