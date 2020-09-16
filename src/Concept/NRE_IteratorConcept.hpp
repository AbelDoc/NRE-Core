    
    /**
     * @file NRE_IteratorConcept.hpp
     * @brief Declaration of Utility's API's Concept
     * @author Louis ABEL
     * @date 15/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../Utility/Traits/NRE_IteratorTraits.hpp"
    
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
            namespace Detail {
                /**
                 * @interface IndirectlyReadable
                 * @brief Define an indirectly readable type through operator* like pointer or input iterator
                 */
                template <class T>
                concept IndirectlyReadable = requires (const T t) {
                    typename Utility::IteratorValueT<T>;
                    typename Utility::IteratorReferenceT<T>;
                    typename Utility::IteratorRValueReferenceT<T>;
                    { *t } -> SameAs<Utility::IteratorReferenceT<T>>;
                    { std::ranges::iter_move(t) } -> SameAs<Utility::IteratorRValueReferenceT<T>>;
                } && CommonReferenceWith<Utility::IteratorReferenceT<T>&&, Utility::IteratorValueT<T>&>
                  && CommonReferenceWith<Utility::IteratorReferenceT<T>&&, Utility::IteratorRValueReferenceT<T>&&>
                  && CommonReferenceWith<Utility::IteratorReferenceT<T>&&, Utility::IteratorValueT<T> const&>;
            }
            
            /**
             * @interface IndirectlyReadable
             * @brief Define an indirectly readable type through operator* like pointer or input iterator
             */
            template <class T>
            concept IndirectlyReadable = Detail::IndirectlyReadable<Utility::RemoveCVReferenceT<T>>;
            
            /**
             * @interface
             * @brief Define an iterator type T which can be indirectly writed by a type Value through operator*
             */
            template <class T, class Value>
            concept IndirectlyWritable = requires (T&& t, Value&& v) {
                *t = std::forward<Value>(v);
                *std::forward<T>(t) = std::forward<Value>(v);
                const_cast <const Utility::IteratorReferenceT<T>&&>(*t) = std::forward<Value>(v);
                const_cast <const Utility::IteratorReferenceT<T>&&>(*std::forward<T>(t)) = std::forward<Value>(v);
            };
            
        }
        /**
         * @namespace Utility
         * @brief Utility's API
         */
        namespace Utility {
            /** Compute the common reference between the the reference type and a reference on the value type of a given type */
            template <Concept::IndirectlyReadable T>
            using IteratorCommonReferenceT = CommonReferenceT<IteratorReferenceT<T>, IteratorValueT<T>&>;
        }
        namespace Concept {
            
            /**
             * @interface WeaklyIncrementable
             * @brief Define an incrementable type without equality preserving incrementation
             */
            template <class T>
            concept WeaklyIncrementable = DefaultInitializable<T> && Moveable<T> && requires (T t) {
                typename Utility::IteratorDifferenceT<T>;
                requires SignedIntegerLike<Utility::IteratorDifferenceT<T>>;
                { ++t } -> SameAs<T&>;
                t++;
            };
            
            /**
             * @interface Incrementable
             * @brief Define an incrementable type with equality perserving incrementation
             */
            template <class T>
            concept Incrementable = Regular<T> && WeaklyIncrementable<T> && requires (T t) {
                { t++ } -> SameAs<T>;
            };
            
            /**
             * @interface InputOrOutputIterator
             * @brief Define a base iterator type for later input/output iterators
             */
            template <class T>
            concept InputOrOutputIterator = requires (T t) {
                { *t } -> Referenceable;
            } && WeaklyIncrementable<T>;
    

            /**
             * @interface SentinelFor
             * @brief Define a type modeling a relationship between an input/output iterator and a semiregular type whose values denote a range
             */
            template <class S, class T>
            concept SentinelFor = SemiRegular<S> && InputOrOutputIterator<T> && EqualityComparableWith<S, T>;
            
            /**
             * @interface SizedSentinelFor
             * @brief Define a type modeling a sentinel relationship between S and T and which can be subtracted to compute distance between them in constant time
             */
            template <class S, class T>
            concept SizedSentinelFor = SentinelFor<S, T> && !Utility::DISABLE_SIZED_SENTINEL_FOR<Utility::RemoveCVT<S>, Utility::RemoveCVT<T>> && requires (T const& t, S const& s) {
                { s - t } -> SameAs<Utility::IteratorDifferenceT<T>>;
                { t - s } -> SameAs<Utility::IteratorDifferenceT<T>>;
            };
    
            /**
             * @interface InputIterator
             * @brief Define an input iterator supporting read and incrementation operation
             */
            template <class T>
            concept InputIterator = InputOrOutputIterator<T> && IndirectlyReadable<T> && requires {
                typename Utility::IteratorCategoryT<T>;
            } && DerivedFrom<Utility::IteratorCategoryT<T>, Utility::InputIteratorCategory>;
            
            /**
             * @interface OutputIterator
             * @brief Define an output iterator supporting write and incrementation operation
             */
            template <class T, class Value>
            concept OutputIterator = InputOrOutputIterator<T> && IndirectlyWritable<T, Value> && requires (T t, Value&& v) {
                *t++ = std::forward<Value>(v);
            };
            
            /**
             * @interface ForwardIterator
             * @brief Define a forward iterator supporting multi pass iteration
             */
            template <class T>
            concept ForwardIterator = InputIterator<T>
                    && DerivedFrom<Utility::IteratorCategoryT<T>, Utility::ForwardIteratorCategory>
                    && Incrementable<T>
                    && SentinelFor<T, T>;
            
            /**
             * @interface BidirectionalIterator
             * @brief Define a bidirectional iterator supporting both direction iteration
             */
            template <class T>
            concept BidirectionalIterator = ForwardIterator<T>
                    && DerivedFrom<Utility::IteratorCategoryT<T>, Utility::BidirectionalIteratorCategory>
                    && requires (T t) {
                        { --t } -> SameAs<T&>;
                        { t-- } -> SameAs<T>;
                    };
            
            /**
             * @interface RandomAccessIterator
             * @brief Define a random access iterator supporting constant time distant iteration
             */
            template <class T>
            concept RandomAccessIterator = BidirectionalIterator<T>
                    && DerivedFrom<Utility::IteratorCategoryT<T>, Utility::RandomAccessIteratorCategory>
                    && TotallyOrdered<T>
                    && SizedSentinelFor<T, T>
                    && requires (T i, const T j, const Utility::IteratorDifferenceT<T> n) {
                        { i += n } -> SameAs<T&>;
                        { j +  n } -> SameAs<T>;
                        { n +  j } -> SameAs<T>;
                        { i -= n } -> SameAs<T&>;
                        { j -  n } -> SameAs<T>;
                        {  j[n]  } -> SameAs<Utility::IteratorReferenceT<T>>;
                    };
        }
    }