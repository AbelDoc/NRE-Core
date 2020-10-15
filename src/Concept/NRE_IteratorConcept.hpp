    
    /**
     * @file NRE_IteratorConcept.hpp
     * @brief Declaration of Core's API's Concept
     * @author Louis ABEL
     * @date 15/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../Core/Traits/NRE_IteratorTraits.hpp"
    
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
                    typename Core::IteratorValueT<T>;
                    typename Core::IteratorReferenceT<T>;
                    typename Core::IteratorRValueReferenceT<T>;
                    { *t } -> SameAs<Core::IteratorReferenceT<T>>;
                    { std::ranges::iter_move(t) } -> SameAs<Core::IteratorRValueReferenceT<T>>;
                } && CommonReferenceWith<Core::IteratorReferenceT<T>&&, Core::IteratorValueT<T>&>
                  && CommonReferenceWith<Core::IteratorReferenceT<T>&&, Core::IteratorRValueReferenceT<T>&&>
                  && CommonReferenceWith<Core::IteratorReferenceT<T>&&, Core::IteratorValueT<T> const&>;
            }
            
            /**
             * @interface IndirectlyReadable
             * @brief Define an indirectly readable type through operator* like pointer or input iterator
             */
            template <class T>
            concept IndirectlyReadable = Detail::IndirectlyReadable<Core::RemoveCVReferenceT<T>>;
            
            /**
             * @interface
             * @brief Define an iterator type T which can be indirectly writed by a type Value through operator*
             */
            template <class T, class Value>
            concept IndirectlyWritable = requires (T&& t, Value&& v) {
                *t = std::forward<Value>(v);
                *std::forward<T>(t) = std::forward<Value>(v);
                const_cast <const Core::IteratorReferenceT<T>&&>(*t) = std::forward<Value>(v);
                const_cast <const Core::IteratorReferenceT<T>&&>(*std::forward<T>(t)) = std::forward<Value>(v);
            };
            
        }
        /**
         * @namespace Core
         * @brief Core's API
         */
        namespace Core {
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
                typename Core::IteratorDifferenceT<T>;
                requires SignedIntegerLike<Core::IteratorDifferenceT<T>>;
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
            concept SizedSentinelFor = SentinelFor<S, T> && !Core::DISABLE_SIZED_SENTINEL_FOR<Core::RemoveCVT<S>, Core::RemoveCVT<T>> && requires (T const& t, S const& s) {
                { s - t } -> SameAs<Core::IteratorDifferenceT<T>>;
                { t - s } -> SameAs<Core::IteratorDifferenceT<T>>;
            };
    
            /**
             * @interface InputIterator
             * @brief Define an input iterator supporting read and incrementation operation
             */
            template <class T>
            concept InputIterator = InputOrOutputIterator<T> && IndirectlyReadable<T> && EqualityComparable<T> && requires {
                typename Core::IteratorCategoryT<T>;
            } && DerivedFrom<Core::IteratorCategoryT<T>, Core::InputIteratorCategory>;
            
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
                    && DerivedFrom<Core::IteratorCategoryT<T>, Core::ForwardIteratorCategory>
                    && Incrementable<T>
                    && SentinelFor<T, T>;
            
            /**
             * @interface BidirectionalIterator
             * @brief Define a bidirectional iterator supporting both direction iteration
             */
            template <class T>
            concept BidirectionalIterator = ForwardIterator<T>
                    && DerivedFrom<Core::IteratorCategoryT<T>, Core::BidirectionalIteratorCategory>
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
                    && DerivedFrom<Core::IteratorCategoryT<T>, Core::RandomAccessIteratorCategory>
                    && TotallyOrdered<T>
                    && SizedSentinelFor<T, T>
                    && requires (T i, const T j, const Core::IteratorDifferenceT<T> n) {
                        { i += n } -> SameAs<T&>;
                        { j +  n } -> SameAs<T>;
                        { n +  j } -> SameAs<T>;
                        { i -= n } -> SameAs<T&>;
                        { j -  n } -> SameAs<T>;
                        {  j[n]  } -> SameAs<Core::IteratorReferenceT<T>>;
                    };
            
            /**
             * @interface ContiguousIterator
             * @brief Define a contiguous iterator, a refined version of random access iterator with contiguous storage constraints
             */
            template <class T>
            concept ContiguousIterator = RandomAccessIterator<T>
                    && DerivedFrom<Core::IteratorCategoryT<T>, Core::ContiguousIteratorCategory>
                    && Core::IsLValueReferenceV<Core::IteratorReferenceT<T>>
                    && SameAs<Core::IteratorValueT<T>, Core::RemoveCVReferenceT<Core::IteratorReferenceT<T>>>
                    && requires (T const& t) {
                        { std::to_address(t) } -> SameAs<Core::AddPointerT<Core::IteratorReferenceT<T>>>;
                    };
        }
        namespace Core {
            /**
             * Return an iterator to the beginning of the given container
             * @param t the object to query a begin iterator
             * @return the corresponding iterator
             */
            template <class T> requires requires (T& t) {
                { t.begin() };
            }
            constexpr Concept::InputOrOutputIterator auto begin(T& t) -> decltype(t.begin()) {
                return t.begin();
            }
    
            /**
             * Return a const iterator to the beginning of the given container
             * @param t the object to query a begin iterator
             * @return the corresponding iterator
             */
            template <class T> requires requires (T const& t) {
                { t.begin() };
            }
            constexpr Concept::InputOrOutputIterator auto begin(T const& t) -> decltype(t.begin()) {
                return t.begin();
            }
    
            /**
             * Return an iterator to the beginning of an array
             * @param t the array to query a begin iterator
             * @return the corresponding iterator
             */
            template <class T, SizeType N>
            constexpr T* begin(T (&array)[N] ) noexcept {
                return addressOf(array[0]);
            }
    
            /**
             * Return a const iterator to the beginning of the given container or array
             * @param t the object to query a begin iterator
             * @return the corresponding iterator
             */
            template <class T> requires requires (T const& t) {
                { begin(t) };
            }
            constexpr Concept::InputOrOutputIterator auto cbegin(T const& t) noexcept(noexcept(begin(t))) -> decltype(begin(t)) {
                return begin(t);
            }
        }
        namespace Core {
            
            /** Helper to access a type's iterator type */
            template <class R>
            using IteratorT = decltype(begin(std::declval<R&>()));
            
            /**
             * Return an iterator to the end of the given container
             * @param t the object to query an end iterator
             * @return the corresponding iterator
             */
            template <class T> requires requires (T& t) {
                { t.end() };
            }
            constexpr Concept::SentinelFor<IteratorT<T>> auto end(T& t) -> decltype(t.end()) {
                return t.end();
            }

            /**
             * Return a const iterator to the end of the given container
             * @param t the object to query an end iterator
             * @return the corresponding iterator
             */
            template <class T> requires requires (T const& t) {
                { t.end() };
            }
            constexpr Concept::SentinelFor<IteratorT<T>> auto end(T const& t) -> decltype(t.end()) {
            return t.end();
            }
        
        
            /**
             * Return an iterator to the end of an array
             * @param t the array to query an end iterator
             * @return the corresponding iterator
             */
            template <class T, SizeType N>
            constexpr T* end(T (&array)[N]) noexcept {
                return addressOf(array[0]) + N;
            }
        
            /**
             * Return a const iterator to the end of the given container or array
             * @param t the object to query an end iterator
             * @return the corresponding iterator
             */
            template <class T> requires requires (T const& t) {
                { t.end() };
            }
            constexpr Concept::SentinelFor<IteratorT<T>> auto cend(T const& t) noexcept(noexcept(end(t))) -> decltype(end(t)) {
                return end(t);
            }

            /** Helper to access a type's sentinel type */
            template <class R>
            using SentinelT = decltype(end(std::declval<R&>()));
            
            /** Helper to access a range's iterator's difference type */
            template <class R>
            using RangeDifferenceT = IteratorDifferenceT<IteratorT<R>>;
            
            /** Helper to access a range's iterator's value type */
            template <class R>
            using RangeValueT = IteratorValueT<IteratorT<R>>;
            
            /** Helper to access a range's iterator's reference type */
            template <class R>
            using RangeReferenceT = IteratorReferenceT<IteratorT<R>>;
            
            /** Helper to access a range's iterator's r-value reference type */
            template <class R>
            using RangeRValueReferenceT = IteratorRValueReferenceT<IteratorT<R>>;
        }
        namespace Concept {
    
            /**
             * @interface Range
             * @brief Define a base range with an input or output begin iterator and an end sentinel
             */
            template <class T>
            concept Range = requires (T& t) {
                Core::begin(t);
                Core::end(t);
            };
            
            /**
             * @interface BorrowedRange
             * @brief Define a range which support borrowed iterator (taked on object'sreference or enabled of object passed by value)
             */
            template <class T>
            concept BorrowedRange = Range<T> && (Core::IsLValueReferenceV<T> || Core::ENABLE_BORROWED_RANGE<Core::RemoveCVReferenceT<T>>);
    
            /**
             * @interface OutputRange
             * @brief Define an output range with an output begin iterator and an end sentinel
             */
            template <class R, class T>
            concept OutputRange = Range<R> && OutputIterator<Core::IteratorT<R>, T>;
    
            /**
             * @interface InputRange
             * @brief Define an input range with an input begin iterator and an end sentinel
             */
            template <class R>
            concept InputRange = Range<R> && InputIterator<Core::IteratorT<R>>;
    
            /**
             * @interface ForwardRange
             * @brief Define a forward range with a forward begin iterator and an end sentinel
             */
            template <class R>
            concept ForwardRange = InputRange<R> && ForwardIterator<Core::IteratorT<R>>;
    
            /**
             * @interface BidirectionalRange
             * @brief Define a bidirectional range with a bidirectional begin iterator and an end sentinel
             */
            template <class R>
            concept BidirectionalRange = ForwardRange<R> && BidirectionalIterator<Core::IteratorT<R>>;
    
            /**
             * @interface RandomAccessRange
             * @brief Define a random access range with a random access begin iterator and an end sentinel
             */
            template <class R>
            concept RandomAccessRange = BidirectionalRange<R> && RandomAccessIterator<Core::IteratorT<R>>;
    
            /**
             * @interface ContiguousRange
             * @brief Define a contiguous range with a random access begin iterator and an end sentinel
             */
            template <class R>
            concept ContiguousRange = RandomAccessRange<R> && ContiguousIterator<Core::IteratorT<R>>;
    
            /**
             * @interface IndirectlyUnaryInvocable
             * @brief Define an invocable on indirectly readable object
             */
            template <class F, class It>
            concept IndirectlyUnaryInvocable = IndirectlyReadable<It> &&
                CopyConstructible<F> &&
                Invocable<F&, Core::IteratorValueT<It>> &&
                Invocable<F&, Core::IteratorReferenceT<It>> &&
                Invocable<F&, Core::IteratorCommonReferenceT<It>> &&
                CommonReferenceWith<Core::InvokeResultT<F&, Core::IteratorValueT<It>&>,
                                    Core::InvokeResultT<F&, Core::IteratorReferenceT<It>>>;
    
            /**
             * @interface IndirectlyRegularUnaryInvocable
             * @brief Define a regular invocable on indirectly readable object
             */
            template <class F, class It>
            concept IndirectlyRegularUnaryInvocable = IndirectlyReadable<It> &&
                CopyConstructible<F> &&
                RegularInvocable<F&, Core::IteratorValueT<It>> &&
                RegularInvocable<F&, Core::IteratorReferenceT<It>> &&
                RegularInvocable<F&, Core::IteratorCommonReferenceT<It>> &&
                CommonReferenceWith<Core::InvokeResultT<F&, Core::IteratorValueT<It>&>,
                                    Core::InvokeResultT<F&, Core::IteratorReferenceT<It>>>;
            
        }
        namespace Core {
            
            /**
             * @struct Dangling
             * @brief Placeholder used to avoid returning dangling iterators by some algorithms
             */
            struct Dangling;
            
            /** Helper to access a range's borrowed iterator type */
            template <Concept::Range R>
            using BorrowedIteratorT = ConditionalT<Concept::BorrowedRange<R>, IteratorT<R>, Dangling>;
            
            /** Helper to access InvokeResultT type for a set of iterators */
            template <class F, class ... Iters> requires (Concept::IndirectlyReadable<Iters> && ...) && Concept::Invocable<F, IteratorReferenceT<Iters>...>
            using IndirectInvokeResultT = InvokeResultT<F, IteratorReferenceT<Iters>...>;
            
            /**
             * @struct Projected
             * @brief Define a new indirectly readable iterator from a base one and a projection to apply
             */
            template <Concept::IndirectlyReadable It, Concept::IndirectlyRegularUnaryInvocable<It> Proj>
            struct Projected {
                using ValueType = RemoveCVReferenceT<IndirectInvokeResultT<Proj&, It>>;
                IndirectInvokeResultT<Proj&, It> operator*() const;
            };
            
            template <Concept::WeaklyIncrementable It, class Proj>
            struct IncrementableTraits<Projected<It, Proj>> {
                using DifferenceType  = IteratorDifferenceT<It>;
            };
            
        }
        namespace Concept {
            /**
             * @interface Predicate
             * @brief Define a n-arity predicate, taking n parameters and return a boolean testable value
             */
            template <class P, class ... Args>
            concept Predicate = RegularInvocable<P, Args...> && BooleanTestable<Core::InvokeResultT<P, Args...>>;
    
            /**
             * @interface IndirectUnaryPredicate
             * @brief Define an unary predicate callable on dereferenced iterator
             */
            template <class F, class I>
            concept IndirectUnaryPredicate = IndirectlyReadable<I> && CopyConstructible<F> &&
                Predicate<F&, Core::IteratorValueT<I>&> &&
                Predicate<F&, Core::IteratorReferenceT<I>> &&
                Predicate<F&, Core::IteratorCommonReferenceT<I>>;
    
            /**
             * @interface IndirectUnaryPredicate
             * @brief Define a binary predicate callable on dereferenced iterators
             */
            template <class F, class I1, class I2>
            concept IndirectBinaryPredicate = IndirectlyReadable<I1> && IndirectlyReadable<I2> && CopyConstructible<F> &&
                Predicate<F&, Core::IteratorValueT<I1>&, Core::IteratorValueT<I2>&> &&
                Predicate<F&, Core::IteratorValueT<I1>&, Core::IteratorReferenceT<I2>> &&
                Predicate<F&, Core::IteratorReferenceT<I1>, Core::IteratorValueT<I2>&> &&
                Predicate<F&, Core::IteratorReferenceT<I1>, Core::IteratorReferenceT<I2>> &&
                Predicate<F&, Core::IteratorCommonReferenceT<I1>, Core::IteratorCommonReferenceT<I2>>;
            
        }
        namespace Core {
    
    
            /**
             * Increment an iterator n times, no optimization
             * @param it the iterator to increment
             * @param n  the number of incrementation
             */
            template <Concept::InputOrOutputIterator It> requires (!Concept::BidirectionalIterator<It>)
            constexpr void advance(It& it, IteratorDifferenceT<It> n) {
                for (; n > 0; --n) {
                    ++it;
                }
            }
    
            /**
             * Increment an iterator n times, allow negatif n
             * @param it the iterator to increment
             * @param n  the number of incrementation
             */
            template <Concept::BidirectionalIterator It> requires (!Concept::RandomAccessIterator<It>)
            constexpr void advance(It& it, IteratorDifferenceT<It> n) {
                for (; n > 0; --n) {
                    ++it;
                }
                for (; n < 0; ++n) {
                    --it;
                }
            }
    
            /**
             * Increment an iterator n times, optimized for random access iterator
             * @param it the iterator to increment
             * @param n  the number of incrementation
             */
            template <Concept::RandomAccessIterator It>
            constexpr void advance(It& it, IteratorDifferenceT<It> n) {
                it += n;
            }
    
            /**
             * Increment an iterator to a given bound, no optimization
             * @param it    the iterator to increment
             * @param bound the incrementation bound
             */
            template <Concept::InputOrOutputIterator It, Concept::SentinelFor<It> S> requires (!Concept::AssignableFrom<It&, S> && !Concept::SizedSentinelFor<S, It>)
            constexpr void advance(It& it, S bound) {
                while (it != bound) {
                    ++it;
                }
            }

            /**
             * Increment an iterator to a given bound, optimized for assignable sentinel
             * @param it    the iterator to increment
             * @param bound the incrementation bound
             */
            template <Concept::InputOrOutputIterator It, Concept::SentinelFor<It> S> requires Concept::AssignableFrom<It&, S>
            constexpr void advance(It& it, S bound) {
                it = std::move(bound);
            }

            /**
             * Increment an iterator to a given bound, optimized for sized sentinel
             * @param it    the iterator to increment
             * @param bound the incrementation bound
             */
            template <Concept::InputOrOutputIterator It, Concept::SizedSentinelFor<It> S> requires (!Concept::AssignableFrom<It&, S>)
            constexpr void advance(It& it, S bound) {
                advance(it, bound - it);
            }
            
            /**
             * Increment an iterator n times or a given bound, depend on the first that happen, no optimization
             * @param it    the iterator to increment
             * @param n     the number of incrementation
             * @param bound the incrementation bound
             */
            template <Concept::InputOrOutputIterator It, Concept::SentinelFor<It> S> requires (!Concept::BidirectionalIterator<It> && !Concept::SizedSentinelFor<S, It>)
            constexpr IteratorDifferenceT<It> advance(It& it, IteratorDifferenceT<It> n, S bound) {
                while (n > 0 && it != bound) {
                    --n;
                    ++it;
                }
                return n;
            }
        
            /**
             * Increment an iterator n times or a given bound, depend on the first that happen, allow negatif n and bound to be before it
             * @param it    the iterator to increment
             * @param n     the number of incrementation
             * @param bound the incrementation bound
             */
            template <Concept::BidirectionalIterator It, Concept::SentinelFor<It> S> requires (!Concept::SizedSentinelFor<S, It>)
            constexpr IteratorDifferenceT<It> advance(It& it, IteratorDifferenceT<It> n, S bound) {
                while (n > 0 && it != bound) {
                    --n;
                    ++it;
                }
                while (n < 0 && it != bound) {
                    ++n;
                    --it;
                }
                return n;
            }

            /**
             * Increment an iterator n times or a given bound, whichever is first, optimized for sized sentinel
             * @param it    the iterator to increment
             * @param n     the number of incrementation
             * @param bound the incrementation bound
             */
            template <Concept::InputOrOutputIterator It, Concept::SizedSentinelFor<It> S>
            constexpr IteratorDifferenceT<It> advance(It& it, IteratorDifferenceT<It> n, S bound) {
                const auto diff = bound - it;
                const auto absDiff = diff < 0 ? -diff : diff;
                const auto absN = n < 0 ? -n : n;
                if (absN >= absDiff) {
                    advance(it, bound);
                    return n - diff;
                } else {
                    advance(it, n);
                    return 0;
                }
            }
            
            /**
             * Compute the successor of an iterator
             * @param it the iterator to query the successor
             * @return the successor
             */
            template <Concept::InputOrOutputIterator It>
            constexpr It next(It it) {
                return ++it;
            }
        
            /**
             * Compute the nth successor of an iterator
             * @param it the iterator to query the successor
             * @param n  the number of incrementation
             * @return the nth successor
             */
            template <Concept::InputOrOutputIterator It>
            constexpr It next(It it, IteratorDifferenceT<It> n) {
                advance(it, n);
                return it;
            }

            /**
             * Compute the first successor equivalent to bound of an iterator
             * @param it    the iterator to query the successor
             * @param bound the incrementation bound
             * @return the first successor equivalent to bound
             */
            template <Concept::InputOrOutputIterator It, Concept::SentinelFor<It> S>
            constexpr It next(It it, S bound) {
                advance(it, bound);
                return it;
            }
        
            /**
             * Compute the nth successor or the first successor equivalent to bound, whichever is first, of an iterator
             * @param it    the iterator to query the successor
             * @param n     the number of incrementation
             * @param bound the incrementation bound
             * @return the nth successor or the first successor equivalent to bound
             */
            template <Concept::InputOrOutputIterator It, Concept::SentinelFor<It> S>
            constexpr It next(It it, IteratorDifferenceT<It> n, S bound) {
                advance(it, n, bound);
                return it;
            }
        }
    }