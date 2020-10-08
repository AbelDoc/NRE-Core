    
    /**
     * @file NRE_Concept.hpp
     * @brief Declaration of Core's API's Concept
     * @author Louis ABEL
     * @date 13/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../Core/Traits/NRE_TypeTraits.hpp"
    
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
            concept SameAs = Core::IsSameAsV<T, U> && Core::IsSameAsV<U, T>;
    
            /**
             * @interface Pointer
             * @brief Define a pointer type
             */
            template <class T>
            concept Pointer = Core::IsPointerV<T>;
    
            /**
             * @interface MemberPointer
             * @brief Define a pointer on non-static member type
             */
            template <class T>
            concept MemberPointer = Core::IsMemberPointerV<T>;
    
            /**
             * @interface NullPointer
             * @brief Define a null pointer type
             */
            template <class T>
            concept NullPointer = SameAs < Core::NullPointer, Core::RemoveCVT <T>>;
    
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
            concept Array = Core::IsArrayV<T>;
    
    
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
            concept Signed = Core::IsSignedV<T>;
            
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
            concept SignedIntegerLike = SignedInteger<T> || SameAs<T, Core::MaxDifferenceType>;
            
            /**
             * @interface Trivial
             * @brief Define a trivial type (either scalar or trivially copyable)
             */
            template <class T>
            concept Trivial = std::is_trivial_v<T>;
            
            /**
             * @interface TriviallyConstructible
             * @brief Define a type trivially constructible from a set of others
             */
            template <class T, class ... Args>
            concept TriviallyConstructible = std::is_trivially_constructible_v<T, Args...>;
            
            /**
             * @interface TriviallyCopyable
             * @brief Define a trivially copyable type
             */
            template <class T>
            concept TriviallyCopyable = TriviallyConstructible<T, Core::AddLValueReferenceT<Core::AddConstT<T>>>;
            
            /**
             * @interface TriviallyMoveable
             * @brief Define a trivially moveable type
             */
            template <class T>
            concept TriviallyMoveable = TriviallyConstructible<T, Core::AddRValueReference<T>>;
            
            /**
             * @interface TriviallyDestructible
             * @brief Define a trivially destructible type
             */
            template <class T>
            concept TriviallyDestructible = std::is_trivially_destructible_v<T>;
            
            /**
             * @interface Volatile
             * @brief Define a volatile type
             */
            template <class T>
            concept Volatile = Core::IsVolatileV<T>;
            
            /**
             * @interface NonVolatileTriviallyCopyable
             * @brief Define a non-volatile type which can be trivially copied
             */
            template <class T>
            concept NonVolatileTriviallyCopyable = TriviallyCopyable<T> && !Volatile<T>;
    
            /**
             * @interface NonVolatileTriviallyMoveable
             * @brief Define a non-volatile type which can be trivially moved
             */
            template <class T>
            concept NonVolatileTriviallyMoveable = TriviallyMoveable<T> && !Volatile<T>;
            
            /**
             * @interface MemCopyable
             * @brief Define a memory copyable type
             */
            template <class T>
            concept MemCopyable = NonVolatileTriviallyCopyable<T>;
    
            /**
             * @interface MemMoveable
             * @brief Define a memory moveable type
             */
            template <class T>
            concept MemMoveable = NonVolatileTriviallyMoveable<T>;
    
            /**
             * @interface MemFillable
             * @brief Define a memory fillable type
             */
            template <class T>
            concept MemFillable = MemCopyable<T> && sizeof(T) == 1;
            
            /**
             * @interface TriviallyAssignable
             * @brief Define a trivially assignable type
             */
            template <class T>
            concept TriviallyAssignable = std::is_trivially_assignable_v<T>;
            
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
             * @interface Constructible
             * @brief Define a type that's constructible from a given set of arguments
             */
            template <class T, class ... Args>
            concept Constructible = std::is_constructible_v<T, Args...>;
            
            /**
             * @interface ConstructibleFrom
             * @brief Define a type that's destructible and constructible from a given set of arguments
             */
            template <class T, class ... Args>
            concept ConstructibleFrom = Destructible<T> && Constructible<T, Args...>;
            
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
            concept CommonReferenceWith = SameAs<Core::CommonReferenceT<T, U>, Core::CommonReferenceT<U, T>> &&
                                          ConvertibleTo<T, Core::CommonReferenceT<T, U>> &&
                                          ConvertibleTo<U, Core::CommonReferenceT<T, U>>;
            
            /**
             * @interface AssignableFrom
             * @brief Define a type that's l-value is assignable from another type
             */
            template <class L, class R>
            concept AssignableFrom = Core::IsLValueReferenceV<L> && CommonReferenceWith<Core::RemoveReferenceT<L> const&, Core::RemoveReferenceT<R> const&> && requires (L l, R&& r) {
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
            concept EqualityComparableWith = requires(typename Core::RemoveReference<T>::Type const& t,
                                                      typename Core::RemoveReference<U>::Type const& u) {
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
            concept TotallyOrderedWith = EqualityComparableWith<T, U> && requires (typename Core::RemoveReference<T>::Type const& t,
                                                                                   typename Core::RemoveReference<U>::Type const& u) {
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
            concept DerivedFrom = Core::IsBaseOf<B, D>::value && ConvertibleTo<const volatile D*, const volatile B*>;
            
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
            
            /**
             * @interface Predicate
             * @param Define a n-arity predicate, taking n parameters and return a boolean testable value
             */
            template <class P, class ... Args>
            concept Predicate = requires (P const& p, Args && ... args) {
                { p(std::forward<Args>(args)...) } -> BooleanTestable;
            };
            
            /**
             * @interface UnaryPredicate
             * @brief Define an unary predicate, taking one parameter and return a boolean testable value
             */
            template <class P, class T>
            concept UnaryPredicate = Predicate<P, T>;
            
            /**
             * @interface BinaryPredicate
             * @brief Define a binary predicate, taking two parameters and return a boolean testable value
             */
            template <class P, class T, class K>
            concept BinaryPredicate = Predicate<P, T, K>;
            
        }
    }