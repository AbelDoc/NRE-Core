    
    /**
     * @file NRE_Algorithm.hpp
     * @brief Declaration of Core's API's Algorithm
     * @author Louis ABEL
     * @date 16/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../../Concept/NRE_IteratorConcept.hpp"
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Core
         * @brief Core's API
         */
        namespace Core {
            namespace Detail {
                /**
                 * @struct InOutResult
                 * @brief Define a function result returning an input and output values (usually iterators and/or sentinel)
                 */
                template <class It, class Out>
                struct InOutResult {
                    [[no_unique_address]] It in;
                    [[no_unique_address]] Out out;
        
                    /**
                     * @return the copy-converted Detail::InOutResult
                     */
                    template <class It2, class Out2> requires Concept::ConvertibleTo<It const&, It2> &&
                                                              Concept::ConvertibleTo<Out const&, Out2>
                    constexpr operator InOutResult<It2, Out2>() const & {
                        return {in, out};
                    }
                    
                    /**
                     * @return the move-converted Detail::InOutResult
                     */
                    template <class It2, class Out2>  requires Concept::ConvertibleTo<It, It2> &&
                                                               Concept::ConvertibleTo<Out, Out2>
                    constexpr operator InOutResult<It2, Out2>() {
                        return {std::move(in), std::move(out)};
                    }
                };
                /**
                 * @struct InInOutResult
                 * @brief Define a function result returning two inputs and one output values (usually iterators and/or sentinel)
                 */
                template <class It1, class It2, class Out>
                struct InInOutResult {
                    [[no_unique_address]] It1 in1;
                    [[no_unique_address]] It2 in2;
                    [[no_unique_address]] Out out;
    
                    /**
                     * @return the copy-converted Detail::InInOutResult
                     */
                    template <class It21, class It22, class Out2> requires Concept::ConvertibleTo<It1 const&, It21> &&
                                                                           Concept::ConvertibleTo<It2 const&, It22> &&
                                                                           Concept::ConvertibleTo<Out const&, Out2>
                    constexpr operator InInOutResult<It21, It22, Out2>() const & {
                        return {in1, in2, out};
                    }
    
                    /**
                     * @return the move-converted Detail::InInOutResult
                     */
                    template <class It21, class It22, class Out2> requires Concept::ConvertibleTo<It1, It21> &&
                                                                           Concept::ConvertibleTo<It2, It22> &&
                                                                           Concept::ConvertibleTo<Out, Out2>
                    constexpr operator InInOutResult<It21, It22, Out2>() {
                        return {std::move(in1), std::move(in2), std::move(out)};
                    }
                };
            }
    
            /**
             * Fill a range of data [begin, end) with a given value, no optimization
             * @param begin the range start
             * @param end   the range end
             * @param value the value to fill the range with
             */
            template <class T, Concept::OutputIterator<T const&> It, Concept::SentinelFor<It> S> requires (!Concept::SizedSentinelFor<S, It>)
            constexpr It fill(It begin, S end, T const& value) {
                for (; begin != end; ++begin) {
                    *begin = value;
                }
                return begin;
            }
        
            /**
             * Fill a range of data [begin, end) with a given value, optimized for sized sentinels
             * @param begin the range start
             * @param end   the range end
             * @param value the value to fill the range with
             */
            template <class T, Concept::OutputIterator<T const&> It, Concept::SizedSentinelFor<It> S> requires (!Concept::MemFillable<IteratorValueT<It>> || !Concept::ContiguousIterator<It>)
            constexpr It fill(It begin, S end, T const& value) {
                for (IteratorDifferenceT<It> n = end - begin; n > 0; --n) {
                    *begin = value;
                    ++begin;
                }
                return begin;
            }

            /**
             * Fill a range of data [begin, end) with a given value, optimized for contiguous iterators and bytes-like types
             * @param begin the range start
             * @param end   the range end
             * @param value the value to fill the range with
             */
            template <class T, Concept::OutputIterator<T const&> It, Concept::SizedSentinelFor<It> S> requires Concept::MemFillable<IteratorValueT<It>> && Concept::ContiguousIterator<It>
            constexpr It fill(It begin, S end, T const& value) {
                IteratorValueT<It>* memBegin = addressOf(*begin);
                IteratorDifferenceT<It> n = end - begin;
                std::memset(memBegin, value, n);
                return begin + n;
            }
            
            /**
             * Fill a range of data with a given value
             * @param range the range to fill
             * @param value the value to fill the range with
             */
            template <class T, Concept::OutputRange<T const&> R>
            constexpr BorrowedIteratorT<R> fill(R && range, T const& value) {
                return fill(begin(range), end(range), value);
            }

            /**
             * Fill N data starting at begin with a given value, no optimization
             * @param begin the range start
             * @param n     the number of object to fill
             * @param value the value to fill the range with
             */
            template <class T, Concept::OutputIterator<T const&> It, Concept::Integral Size> requires (!Concept::DerivedFrom<IteratorCategoryT<It>, RandomAccessIteratorCategory>)
            constexpr void fillN(It begin, Size n, T const& value) {
                for ( ; n > 0; --n) {
                    *begin = value;
                    ++begin;
                }
            }
        
            /**
             * Fill N data starting at begin with a given value, optimized for random access iterators
             * @param begin the range start
             * @param n     the number of object to fill
             * @param value the value to fill the range with
             */
            template <class T, Concept::OutputIterator<T const&> It, Concept::Integral Size> requires Concept::DerivedFrom<IteratorCategoryT<It>, RandomAccessIteratorCategory>
            constexpr void fillN(It begin, Size n, T const& value) {
                return fill(begin, begin + n, value);
            }

            /** Helper for copy-function result type */
            template <class It, class Out>
            using CopyResult = Detail::InOutResult<It, Out>;
            
            /**
             * Copy a range of data [begin, end) into a given destination, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last element accessed and one pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::SizedSentinelFor<S, InputIt>)
            constexpr CopyResult<InputIt, OutputIt> copy(InputIt begin, S end, OutputIt first) {
                for (; begin != end; ++begin, ++first) {
                    *first = *begin;
                }
                return {begin, first};
            }

            /**
             * Copy a range of data [begin, end) into a given destination, optimized for sized sentinels
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last element accessed and one pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::OutputIterator<IteratorReferenceT<InputIt>> OutputIt> requires
                (!Concept::MemCopyable<IteratorValueT<InputIt>>  ||
                 !Concept::MemCopyable<IteratorValueT<OutputIt>> ||
                 !Concept::ContiguousIterator<InputIt>           ||
                 !Concept::ContiguousIterator<OutputIt>)
            constexpr CopyResult<InputIt, OutputIt> copy(InputIt begin, S end, OutputIt first) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *first = *begin;
                    ++first;
                    ++begin;
                }
                return {begin, first};
            }

            /**
             * Copy a range of data [begin, end) into a given destination, optimized for contiguous iterators and trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last element accessed and one pointing after the last copied element
             */
            template <Concept::ContiguousIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::ContiguousIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorReferenceT<InputIt>> &&
                Concept::MemCopyable<IteratorValueT<InputIt>> &&
                Concept::MemCopyable<IteratorValueT<OutputIt>>
            constexpr CopyResult<InputIt, OutputIt> copy(InputIt begin, S end, OutputIt first) {
                IteratorValueT<OutputIt>* memFirst = addressOf(*first);
                IteratorValueT<InputIt>*  memBegin = addressOf(*begin);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memFirst, memBegin, n * sizeof(IteratorValueT<InputIt>));
                return {begin + n, first + n};
            }
            
            /**
             * Copy a range of data into a given destination
             * @param range the source range
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::InputRange R, Concept::OutputIterator<RangeReferenceT<R>> OutputIt>
            constexpr CopyResult<BorrowedIteratorT<R>, OutputIt> copy(R && range, OutputIt first) {
                return copy(begin(range), end(range), std::move(first));
            }

            /** Helper for copyBackward-function result type */
            template <class It, class Out>
            using CopyBackwardResult = Detail::InOutResult<It, Out>;

            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::BidirectionalIterator OutputIt> requires Concept::IndirectlyWritable<OutputIt, IteratorReferenceT<InputIt>> && (!Concept::SizedSentinelFor<S, InputIt>)
            constexpr CopyBackwardResult<InputIt, OutputIt> copyBackward(S begin, InputIt end, OutputIt last) {
                while (begin != end) {
                    *(--last) = *(--end);
                }
                return {end, last};
            }
        
            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, optimized for sized sentinel
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::BidirectionalIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorReferenceT<InputIt>> &&
                (!Concept::MemCopyable<IteratorValueT<InputIt>>  ||
                 !Concept::MemCopyable<IteratorValueT<OutputIt>> ||
                 !Concept::ContiguousIterator<InputIt>           ||
                 !Concept::ContiguousIterator<OutputIt>)
            constexpr CopyBackwardResult<InputIt, OutputIt> copyBackward(S begin, InputIt end, OutputIt last) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *(--last) = *(--end);
                }
                return {end, last};
            }
        
            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, optimized for contiguous iterators and trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::ContiguousIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::ContiguousIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorReferenceT<InputIt>> &&
                Concept::MemCopyable<IteratorValueT<InputIt>> &&
                Concept::MemCopyable<IteratorValueT<OutputIt>>
            constexpr CopyBackwardResult<InputIt, OutputIt> copyBackward(S begin, InputIt end, OutputIt last) {
                IteratorValueT<OutputIt>* memLast = addressOf(*last);
                IteratorValueT<InputIt>*  memEnd = addressOf(*end);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memLast - n, memEnd - n, n * sizeof(IteratorValueT<InputIt>));
                return {end - n, last - n};
            }

            /**
             * Copy a range of data into a given destination but start from the end
             * @param range the source range
             * @param last  the destination end
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::BidirectionalRange R, Concept::OutputIterator<RangeReferenceT<R>> OutputIt> requires Concept::IndirectlyWritable<OutputIt, RangeReferenceT<R>>
            constexpr CopyBackwardResult<BorrowedIteratorT<R>, OutputIt> copyBackward(R && range, OutputIt last) {
                return copyBackward(begin(range), end(range), std::move(last));
            }

            /** Helper for copyIf-function result type */
            template <class It, class Out>
            using CopyIfResult = Detail::InOutResult<It, Out>;
            
            /**
             * Copy a range of data [begin, end), if they satisfies a given unary predicate, into a given destination
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @param p     the used predicate
             * @param proj  the projection used when sending element to the predicate
             * @return an iterator pointing after the last element accessed and one pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::OutputIterator<IteratorReferenceT<InputIt>> OutputIt, Concept::IndirectlyRegularUnaryInvocable<InputIt> Proj = Identity, Concept::IndirectUnaryPredicate<Projected<InputIt, Proj>> Pred>
            constexpr CopyIfResult<InputIt, OutputIt> copyIf(InputIt begin, S end, OutputIt first, Pred p, Proj proj = {}) {
                for (; begin != end; ++begin) {
                    if (std::invoke(p, std::invoke(proj, *begin))) {
                        *first = *begin;
                        ++first;
                    }
                }
                return {begin, first};
            }
            
            /**
             * Copy a range of data, if they satisfies a given unary predicate, into a given destination
             * @param range the source range
             * @param first the destination start
             * @param p     the used predicate
             * @return an iterator pointing after the last element accessed and one pointing after the last copied element
             */
            template <Concept::InputRange R, Concept::OutputIterator<RangeReferenceT<R>> OutputIt, Concept::IndirectlyRegularUnaryInvocable<IteratorT<R>> Proj = Identity, Concept::IndirectUnaryPredicate<Projected<IteratorT<R>, Proj>> Pred>
            constexpr CopyIfResult<BorrowedIteratorT<R>, OutputIt> copyIf(R && range, OutputIt first, Pred p, Proj proj) {
                return copyIf(begin(range), end(range), std::move(first), std::move(p), std::move(proj));
            }

            /** Helper for copyN-function result type */
            template <class It, class Out>
            using CopyNResult = Detail::InOutResult<It, Out>;
            
            /**
             * Copy N data starting at begin into a given destination, no optimization
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an iterator pointing after the last element accessed and one pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::OutputIterator<IteratorReferenceT<InputIt>> OutputIt> requires (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            constexpr CopyNResult<InputIt, OutputIt> copyN(InputIt begin, Size n, OutputIt first) {
                for (; n > 0; --n) {
                    *first = *begin;
                    ++first;
                    ++begin;
                }
                return {begin, first};
            }

            /**
             * Copy N data starting at begin into a given destination, optimized for random access iterators
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an iterator pointing after the last element accessed and one pointing after the last copied element
             */
            template <Concept::RandomAccessIterator InputIt, Concept::Integral Size, Concept::OutputIterator<IteratorReferenceT<InputIt>> OutputIt>
            constexpr CopyNResult<InputIt, OutputIt> copyN(InputIt begin, Size n, OutputIt first) {
                return copy(std::move(begin), begin + n, std::move(first));
            }

            /** Helper for move-function result type */
            template <class It, class Out>
            using MoveResult = Detail::InOutResult<It, Out>;

            /**
             * Move a range of data [begin, end) into a given destination, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last element accessed and one pointing after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::OutputIterator<IteratorRValueReferenceT<InputIt>> OutputIt> requires (!Concept::SizedSentinelFor<S, InputIt>)
            constexpr MoveResult<InputIt, OutputIt> move(InputIt begin, S end, OutputIt first) {
                for (; begin != end; ++begin, ++first) {
                    *first = std::move(*begin);
                }
                return {begin, first};
            }
        
            /**
             * Move a range of data [begin, end) into a given destination, optimized for sized sentinels
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last element accessed and one pointing after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::OutputIterator<IteratorRValueReferenceT<InputIt>> OutputIt> requires
                (!Concept::MemMoveable<IteratorValueT<InputIt>>  ||
                 !Concept::MemMoveable<IteratorValueT<OutputIt>> ||
                 !Concept::ContiguousIterator<InputIt>           ||
                 !Concept::ContiguousIterator<OutputIt>)
            constexpr MoveResult<InputIt, OutputIt> move(InputIt begin, S end, OutputIt first) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *first = std::move(*begin);
                    ++first;
                    ++begin;
                }
                return {begin, first};
            }
        
            /**
             * Move a range of data [begin, end) into a given destination, optimized for contiguous iterators and trivially moveable types
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last element accessed and one pointing after the last moved element
             */
            template <Concept::ContiguousIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::ContiguousIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorRValueReferenceT<InputIt>> &&
                Concept::MemMoveable<IteratorValueT<InputIt>> &&
                Concept::MemMoveable<IteratorValueT<OutputIt>>
            constexpr MoveResult<InputIt, OutputIt> move(InputIt begin, S end, OutputIt first) {
                IteratorValueT<OutputIt>* memFirst = addressOf(*first);
                IteratorValueT<InputIt>*  memBegin = addressOf(*begin);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memFirst, memBegin, n * sizeof(IteratorValueT<InputIt>));
                return {begin + n, first + n};
            }
        
            /**
             * Move a range of data into a given destination
             * @param range the source range
             * @param first the destination start
             * @return an iterator pointing after the last element accessed and one pointing after the last moved element
             */
            template <Concept::InputRange R, Concept::OutputIterator<RangeRValueReferenceT<R>> OutputIt>
            constexpr MoveResult<BorrowedIteratorT<R>, OutputIt> move(R && range, OutputIt first) {
                return move(begin(range), end(range), std::move(first));
            }

            /** Helper for moveBackward-function result type */
            template <class It, class Out>
            using MoveBackwardResult = Detail::InOutResult<It, Out>;

            /**
             * Move a range of data [begin, end) into a given destination but start from the end, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last element accessed and one pointing to the last moved element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::BidirectionalIterator OutputIt> requires Concept::IndirectlyWritable<OutputIt, IteratorRValueReferenceT<InputIt>> && (!Concept::SizedSentinelFor<S, InputIt>)
            constexpr MoveBackwardResult<InputIt, OutputIt> moveBackward(S begin, InputIt end, OutputIt last) {
                while (begin != end) {
                    *(--last) = std::move(*(--end));
                }
                return {end, last};
            }
        
            /**
             * Move a range of data [begin, end) into a given destination but start from the end, optimized for sized sentinels
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last element accessed and one pointing to the last moved element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::BidirectionalIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorRValueReferenceT<InputIt>> &&
                (!Concept::MemMoveable<IteratorValueT<InputIt>>  ||
                 !Concept::MemMoveable<IteratorValueT<OutputIt>> ||
                 !Concept::ContiguousIterator<InputIt>           ||
                 !Concept::ContiguousIterator<OutputIt>)
            constexpr MoveBackwardResult<InputIt, OutputIt> moveBackward(S begin, InputIt end, OutputIt last) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *(--last) = std::move(*(--end));
                }
                return {end, last};
            }
        
            /**
             * Move a range of data [begin, end) into a given destination but start from the end, optimized for contiguous iterators and trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last element accessed and one pointing to the last moved element
             */
            template <Concept::ContiguousIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::ContiguousIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorRValueReferenceT<InputIt>> &&
                Concept::MemMoveable<IteratorValueT<InputIt>> &&
                Concept::MemMoveable<IteratorValueT<OutputIt>>
            constexpr MoveBackwardResult<InputIt, OutputIt> moveBackward(S begin, InputIt end, OutputIt last) {
                IteratorValueT<OutputIt>* memLast = addressOf(*last);
                IteratorValueT<InputIt>*  memEnd = addressOf(*end);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memLast - n, memEnd - n, n * sizeof(IteratorValueT<InputIt>));
                return {end - n, last - n};
            }

            /**
             * Move a range of data into a given destination but start from the end
             * @param range the source range
             * @param last  the destination end
             * @return an iterator pointing to the last element accessed and one pointing to the last moved element
             */
            template <Concept::BidirectionalRange R, Concept::BidirectionalIterator OutputIt> requires Concept::IndirectlyWritable<OutputIt, RangeRValueReferenceT<R>>
            constexpr MoveBackwardResult<BorrowedIteratorT<R>, OutputIt> moveBackward(R && range, OutputIt last) {
                return moveBackward(begin(range), end(range), std::move(last));
            }

            /** Helper for unitializedCopy-function result type */
            template <class It, class Out>
            using UninitializedCopyResult = Detail::InOutResult<It, Out>;

            /**
             * Copy a range of data [begin, end) into an uninitialized memory destination, destroy copied data in case of exception
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorReferenceT<InputIt>> && (!Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>)
            UninitializedCopyResult<InputIt, ForwardIt> uninitializedCopy(InputIt begin, S end, ForwardIt first) {
                ForwardIt current = first;
                try {
                    for (; begin != end; ++begin, ++current) {
                        Memory::constructAt(addressOf(*current), *begin);
                    }
                    return {begin, current};
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }

            /**
             * Copy a range of data [begin, end) into an uninitialized memory destination, destroy copied data in case of exception, optimized for trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorReferenceT<InputIt>> && Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>
            UninitializedCopyResult<InputIt, ForwardIt> uninitializedCopy(InputIt begin, S end, ForwardIt first) {
                return copy(std::move(begin), std::move(end), std::move(first));
            }

            /**
             * Copy a range of data into an uninitialized memory destination, destroy copied data in case of exception
             * @param range the source range
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::InputRange R, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, RangeReferenceT<R>>
            UninitializedCopyResult<BorrowedIteratorT<R>, ForwardIt> uninitializedCopy(R && range, ForwardIt first) {
                return uninitializedCopy(begin(range), end(range), std::move(first));
            }

            /** Helper for unitializedCopyN-function result type */
            template <class It, class Out>
            using UninitializedCopyNResult = Detail::InOutResult<It, Out>;

            /**
             * Copy N data starting at begin into an uninitialized memory destination, destroy copied data in case of exception
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorReferenceT<InputIt>> && (!Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>)
            UninitializedCopyNResult<InputIt, ForwardIt> uninitializedCopyN(InputIt begin, Size n, ForwardIt first) {
                ForwardIt current = first;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAt(addressOf(*current), *begin);
                        ++begin;
                        ++current;
                    }
                    return {begin, current};
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }

            /**
             * Copy N data starting at begin into an uninitialized memory destination, destroy copied data in case of exception, optimized for trivially copyable types
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorReferenceT<InputIt>>  && Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>
            UninitializedCopyNResult<InputIt, ForwardIt> uninitializedCopyN(InputIt begin, Size n, ForwardIt first) {
                return copyN(std::move(begin), n, std::move(first));
            }

            /** Helper for unitializedMove-function result type */
            template <class It, class Out>
            using UninitializedMoveResult = Detail::InOutResult<It, Out>;

            /**
             * Move a range of data [begin, end) into an uninitialized memory destination, destroy moved data in case of exception
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<InputIt>> && (!Concept::TriviallyMoveable<IteratorValueT<ForwardIt>>)
            UninitializedMoveResult<InputIt, ForwardIt> uninitializedMove(InputIt begin, S end, ForwardIt first) {
                ForwardIt current = first;
                try {
                    for (; begin != end; ++begin, ++current) {
                        Memory::constructAt(addressOf(*current), std::move(*begin));
                    }
                    return {begin, current};
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }
        
            /**
             * Move a range of data [begin, end) into an uninitialized memory destination, destroy moved data in case of exception, optimized for trivially moveable types
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<InputIt>> && Concept::TriviallyMoveable<IteratorValueT<ForwardIt>>
            UninitializedMoveResult<InputIt, ForwardIt> uninitializedMove(InputIt begin, S end, ForwardIt first) {
                return move(std::move(begin), std::move(end), std::move(first));
            }

            /**
             * Move a range of data into an uninitialized memory destination, destroy moved data in case of exception
             * @param range the source range
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last moved element
             */
            template <Concept::InputRange R, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, RangeRValueReferenceT<R>>
            UninitializedMoveResult<BorrowedIteratorT<R>, ForwardIt> uninitializedMove(R && range, ForwardIt first) {
                return uninitializedMove(begin(range), end(range), std::move(first));
            }

            /** Helper for unitializedMove-function result type */
            template <class It, class Out>
            using UninitializedMoveNResult = Detail::InOutResult<It, Out>;

            /**
             * Move N data starting at begin into an uninitialized memory destination, destroy moved data in case of exception
             * @param begin the source range start
             * @param n     the number of data to moved
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<InputIt>> && (!Concept::TriviallyMoveable<IteratorValueT<InputIt>>)
            UninitializedMoveNResult<InputIt, ForwardIt> uninitializedMoveN(InputIt begin, Size n, ForwardIt first) {
                ForwardIt current = first;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAt(addressOf(*current), std::move(*begin));
                        ++begin;
                        ++current;
                    }
                    return {begin, current};
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }
        
            /**
             * Move N data starting at begin into an uninitialized memory destination, destroy moved data in case of exception, optimized for random access iterators
             * @param begin the source range start
             * @param n     the number of data to moved
             * @param first the destination start
             * @return an iterator pointing to the last element accessed and one pointing to the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<InputIt>> && Concept::TriviallyMoveable<IteratorValueT<InputIt>>
            UninitializedMoveNResult<InputIt, ForwardIt> uninitializedMoveN(InputIt begin, Size n, ForwardIt first) {
                return moveN(std::move(begin), n, std::move(first));
            }

            /**
             * Fill an uninitiliazed range of memory [begin, end) with a given value, no optimization
             * @param begin the destination start
             * @param end   the destination end
             * @param value the value to fill the range with
             * @return an iterator pointing after the last filled element
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, T const&> && (!Concept::TriviallyAssignable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedFill(ForwardIt begin, S end, T const& value) {
                ForwardIt current = begin;
                try {
                    for (; current != end; ++current) {
                        Memory::constructAt(addressOf(*current), value);
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(begin, current);
                    throw e;
                }
            }

            /**
             * Fill an uninitiliazed range of memory [begin, end) with a given value, optimized for trivially copyable types
             * @param begin the destination start
             * @param end   the destination end
             * @param value the value to fill the range with
             * @return an iterator pointing after the last filled element
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, T const&> && Concept::TriviallyAssignable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedFill(ForwardIt begin, S end, T const& value) {
                return fill(std::move(begin), std::move(end), value);
            }

            /**
             * Fill an uninitiliazed range of memory with a given value
             * @param range the destination range
             * @param value the value to fill the range with
             * @return an iterator pointing after the last filled element
             */
            template <class T, Concept::ForwardRange R> requires Concept::IndirectlyWritable<IteratorT<R>, T const&>
            BorrowedIteratorT<R> uninitializedFill(R && range, T const& value) {
                return uninitializedFill(begin(range), end(range), value);
            }
            
            /**
             * Fill N uninitialized data starting at begin with a given value, no optimization
             * @param begin the destination start
             * @param n     the number of data to fill
             * @param value the value to fill the datas with
             * @return an iterator pointing after the last filled element
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, T const&> && (!Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedFillN(ForwardIt begin, Size n, T const& value) {
                ForwardIt current = begin;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAt(addressOf(*current), value);
                        ++current;
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(begin, current);
                    throw e;
                }
            }

            /**
             * Fill N uninitialized data starting at begin with a given value, optimized for trivially copyable types
             * @param begin the destination start
             * @param n     the number of data to fill
             * @param value the value to fill the datas with
             * @return an iterator pointing after the last filled element
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, T const&> && Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedFillN(ForwardIt first, Size n, T const& value) {
                return fillN(std::move(first), n, std::move(value));
            }
            
            /**
             * Initialize a range of data [begin, end) with default constructed value, no optimization
             * @param begin the destination start
             * @param end   the destination end
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && (!Concept::TriviallyConstructible<IteratorValueT<ForwardIt>>)
            void uninitializedDefaultConstruct(ForwardIt begin, S end) {
                ForwardIt current = begin;
                try {
                    for (; current != end; ++current) {
                        Memory::constructAtNoValue(addressOf(*current));
                    }
                } catch (std::exception& e) {
                    Memory::destroy(begin, current);
                    throw e;
                }
            }

            /**
             * Initialize a range of data [begin, end) with default constructed value, optimized for trivially constructible types
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && Concept::TriviallyConstructible<IteratorValueT<ForwardIt>>
            void uninitializedDefaultConstruct(ForwardIt, S) {
            }
            
            /**
             * Initialize a range of data with default constructed value
             * @param range the destination range
             */
            template <Concept::ForwardRange R> requires Concept::IndirectlyWritable<IteratorT<R>, RangeValueT<R>>
            void uninitializedDefaultConstruct(R && range) {
                uninitializedDefaultConstrct(begin(range), end(range));
            }

            /**
             * Initialize N data with default constructed value
             * @param begin the destination start
             * @param n     the number of data to initialize
             */
            template <Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && (!Concept::TriviallyConstructible<IteratorValueT<ForwardIt>>)
            void uninitializedDefaultConstructN(ForwardIt begin, Size n) {
                ForwardIt current = begin;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAtNoValue(addressOf(*current));
                        ++current;
                    }
                } catch (std::exception& e) {
                    Memory::destroy(begin, current);
                    throw e;
                }
            }
        
            /**
             * Initialize N data with default constructed value
             */
            template <Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && Concept::TriviallyConstructible<IteratorValueT<ForwardIt>>
            void uninitializedDefaultConstructN(ForwardIt, Size) {
            }
        
            /**
             * Initialize a range of data [begin, end) with value constructed value, no optimization
             * @param begin the destination start
             * @param end   the destination end
             * @return an iterator pointing after the last constructed element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && (!Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedValueConstruct(ForwardIt begin, S end) {
                ForwardIt current = begin;
                try {
                    for (; current != end; ++current) {
                        Memory::constructAt(addressOf(*current));
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(begin, current);
                    throw e;
                }
            }
        
            /**
             * Initialize a range of data [begin, end) with default constructed value, optimized for trivially constructible types
             * @param begin the destination start
             * @param end   the destination end
             * @return an iterator pointing after the last constructed element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedValueConstruct(ForwardIt begin, S end) {
                return fill(std::move(begin), std::move(end), IteratorValueT<ForwardIt>());
            }
        
            /**
             * Initialize a range of data with default constructed value
             * @param range the destination range
             * @return an iterator pointing after the last constructed element
             */
            template <Concept::ForwardRange R> requires Concept::IndirectlyWritable<IteratorT<R>, RangeValueT<R>>
            BorrowedIteratorT<R> uninitializedValueConstruct(R && range) {
                return uninitializedValueConstruct(begin(range), end(range));
            }
            
            /**
             * Initialize N data with default constructed value
             * @param begin the destination start
             * @param n     the number of element to initialize
             * @return an iterator pointing after the last constructed element
             */
            template<Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && (!Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedValueConstructN(ForwardIt begin, Size n) {
                ForwardIt current = begin;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAt(addressOf(*current));
                        ++current;
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(begin, current);
                    throw e;
                }
            }

            /**
             * Initialize N data with default constructed value
             * @param begin the destination start
             * @param n     the number of element to initialize
             * @return an iterator pointing after the last constructed element
             */
            template<Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedValueConstructN(ForwardIt begin, Size n) {
                return fillN(std::move(begin), n, IteratorValueT<ForwardIt>());
            }
            
            /**
             * Fill a range of data [begin, end) with generated data from a given generator, no optimization
             * @param begin the destination start
             * @param end   the destination end
             * @param g     the data generator
             * @return an iterator pointing after the last generated element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S, Concept::Generator Gen> requires Concept::IndirectlyWritable<ForwardIt, Core::InvokeResultT<Gen>> && (!Concept::SizedSentinelFor<S, ForwardIt>)
            constexpr ForwardIt generate(ForwardIt begin, S end, Gen g) {
                for ( ; begin != end; ++begin) {
                    *begin = std::move(g());
                }
                return begin;
            }

            /**
             * Fill a range of data [begin, end) with generated data from a given generator, optimized for sized sentinels
             * @param begin the destination start
             * @param end   the destination end
             * @param g     the data generator
             * @return an iterator pointing after the last generated element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SizedSentinelFor<ForwardIt> S, Concept::Generator Gen> requires Concept::IndirectlyWritable<ForwardIt, Core::InvokeResultT<Gen>>
            constexpr ForwardIt generate(ForwardIt begin, S end, Gen g) {
                for (auto n = end - begin; n > 0; --n) {
                    *begin = std::move(std::invoke(g));
                    ++begin;
                }
                return begin;
            }
            
            /**
             * Fill a range of data with generated data from a given generator
             * @param range the destination range
             * @param g     the data generator
             * @return an iterator pointing after the last generated element
             */
            template <Concept::ForwardRange R, Concept::Generator Gen>  requires Concept::IndirectlyWritable<Core::IteratorT<R>, Core::InvokeResultT<Gen>>
            constexpr BorrowedIteratorT<R> generate(R && range, Gen g) {
                return generate(Core::begin(range), Core::end(range), std::move(g));
            }
            
            /**
             * Fill N data with generated data from a given generator
             * @param begin the destination start
             * @param g     the data generator
             * @return an iterator pointing after the last generated element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::Integral Size, Concept::Generator Gen> requires Concept::IndirectlyWritable<ForwardIt, Core::InvokeResultT<Gen>>
            constexpr ForwardIt generateN(ForwardIt begin, Size n, Gen g) {
                for (; n > 0; --n) {
                    *begin = std::move(std::invoke(g));
                    ++begin;
                }
                return begin;
            }
            
            /**
             * Shift the given range by n if distance(begin, end) > n > 0, otherwise no effect
             * @param begin the range start to shift
             * @param end   the range end to shift
             * @param n     the shift amount
             * @return an iterator pointing after the last element shifted, last if n == 0, first if n >= distance(begin, end)
             */
            template <Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<ForwardIt>>
            constexpr ForwardIt shiftLeft(ForwardIt begin, ForwardIt end, IteratorDifferenceT<ForwardIt> n) {
                if (n == 0) {
                    return end;
                }
                
                auto middle = next(begin, n, end);
                if (middle == end) {
                    return begin;
                }
                return move(std::move(middle), std::move(end), std::move(begin)).out;
            }

            /**
             * Shift the given range by n if distance(begin(range), end(range)) > n > 0, otherwise no effect
             * @param range the range to shift
             * @param n     the shift amount
             * @return an iterator pointing after the last element shifted, end(range) if n == 0, begin(range) if n >= distance(begin(range), end(range))
             */
            template <Concept::ForwardRange R> requires Concept::IndirectlyWritable<IteratorT<R>, IteratorRValueReferenceT<IteratorT<R>>>
            constexpr BorrowedIteratorT<R> shiftLeft(R && range, IteratorDifferenceT<IteratorT<R>> n) {
                return shiftLeft(begin(range), end(range), n);
            }
            
            /**
             * Shift the given range by n if distance(begin, end) > n > 0, otherwhise no effect, no optimization
             * @param begin the range start to shift
             * @param end   the range end to shift
             * @param n     the shift amount
             * @return an iterator pointing after the last element shifted, last if first == 0, end if n >= distance(begin, end)
             */
            template <Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<ForwardIt>> && (!Concept::BidirectionalIterator<ForwardIt>)
            constexpr ForwardIt shiftRight(ForwardIt begin, ForwardIt end, IteratorDifferenceT<ForwardIt> n) {
                if (n == 0) {
                    return begin;
                }
                
                auto result = next(begin, n, end);
                if (result == end) {
                    return end;
                }
                
                auto destinationHead = begin;
                auto destinationTail = result;
                while (destinationHead != result) {
                    if (destinationTail == end) {
                        move(std::move(begin), std::move(destinationHead), std::move(result));
                        return result;
                    }
                    ++destinationHead;
                    ++destinationTail;
                }
                for (;;) {  // Ended when [begin, result) and [destinationHead, destinationTail) are disjoint,
                            // no for end condition in order to have direct return when last moving,
                            // avoiding extra instructions after
                    auto cursor = begin;
                    while (cursor != result) {
                        if (destinationTail == end) {
                            destinationHead = move(cursor, result, std::move(destinationHead));
                            move(std::move(begin), std::move(cursor), std::move(destinationHead));
                            return result;
                        }
                        std::iter_swap(cursor, destinationHead);
                        ++destinationHead;
                        ++destinationTail;
                        ++cursor;
                    }
                }
            }

            /**
             * Shift the given range by n if distance(begin, end) > n > 0, otherwhise no effect, optimized for bidirectional iterator
             * @param begin the range start to shift
             * @param end   the range end to shift
             * @param n     the shift amount
             * @return an iterator pointing after the last element shifted, last if first == 0, end if n >= distance(begin, end)
             */
            template <Concept::BidirectionalIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<ForwardIt>>
            constexpr ForwardIt shiftRight(ForwardIt begin, ForwardIt end, IteratorDifferenceT<ForwardIt> n) {
                if (n == 0) {
                    return begin;
                }
                
                auto mid = next(end, -n, begin);
                if (mid == begin) {
                    return end;
                }
                return moveBackward(std::move(begin), std::move(mid), std::move(end)).out;
            }

            /**
             * Shift the given range by n if distance(begin(range), end(range)) > n > 0, otherwhise no effect
             * @param range the range to shift
             * @param n     the shift amount
             * @return an iterator pointing after the last element shifted, last if begin(range) == 0, end(range) if n >= distance(begin(range), end(range))
             */
            template <Concept::ForwardRange R> requires Concept::IndirectlyWritable<IteratorT<R>, IteratorRValueReferenceT<IteratorT<R>>>
            constexpr BorrowedIteratorT<R> shiftRight(R && range, IteratorDifferenceT<IteratorT<R>> n) {
                return shiftRight(begin(range), end(range), n);
            }


            /** Helper for unary transform-function result type */
            template<class It, class Out>
            using UnaryTransformResult = Detail::InOutResult<It, Out>;

            /** Helper for binary transform-function result type */
            template<class It1, class It2, class Out>
            using BinaryTransformResult = Detail::InInOutResult<It1, It2, Out>;
            
            /**
             * Apply a given transformation and a projection to a given range and store the result into another range, no optimization
             * @param begin the source start
             * @param end   the source end
             * @param first the destination start
             * @param op    the transformation to apply
             * @param proj  the projection to apply
             * @return an iterator pointing to the last element accessed and one pointing to the last transformed element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::IndirectlyRegularUnaryInvocable<InputIt> Proj = Identity,
                      Concept::IndirectlyRegularUnaryInvocable<Projected<InputIt, Proj>> UnaryOp,
                      Concept::OutputIterator<IndirectInvokeResultT<UnaryOp, Projected<InputIt, Proj>>> OutputIt> requires (!Concept::SizedSentinelFor<S, InputIt>)
            constexpr UnaryTransformResult<InputIt, OutputIt> transform(InputIt begin, S end, OutputIt first, UnaryOp op, Proj proj = {}) {
                for ( ; begin != end; ++begin, ++first) {
                    *first = std::invoke(op, std::invoke(proj, *begin));
                }
                return {begin, first};
            }

            /**
             * Apply a given transformation and a projection to a given range and store the result into another range, optimized for sized sentinels
             * @param begin the source start
             * @param end   the source end
             * @param first the destination start
             * @param op    the transformation to apply
             * @param proj  the projection to apply
             * @return an iterator pointing to the last element accessed and one pointing to the last transformed element
             */
            template <Concept::InputIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::IndirectlyRegularUnaryInvocable<InputIt> Proj = Identity,
                      Concept::IndirectlyRegularUnaryInvocable<Projected<InputIt, Proj>> UnaryOp,
                      Concept::OutputIterator<IndirectInvokeResultT<UnaryOp, Projected<InputIt, Proj>>> OutputIt>
            constexpr UnaryTransformResult<InputIt, OutputIt> transform(InputIt begin, S end, OutputIt first, UnaryOp op, Proj proj = {}) {
                for (auto n = end - begin; n > 0; --n) {
                    *first = std::invoke(op, std::invoke(proj, *begin));
                    ++first;
                    ++begin;
                }
                return {begin, first};
            }

            /**
             * Apply a given transformation and a projection to a given range and store the result into another range
             * @param range the source range
             * @param first the destination start
             * @param op    the transformation to apply
             * @param proj  the projection to apply
             * @return an iterator pointing to the last element accessed and one pointing to the last transformed element
             */
            template <Concept::InputRange R, Concept::IndirectlyRegularUnaryInvocable<IteratorT<R>> Proj = Identity,
                      Concept::IndirectlyRegularUnaryInvocable<Projected<IteratorT<R>, Proj>> UnaryOp,
                      Concept::OutputIterator<IndirectInvokeResultT<UnaryOp, Projected<IteratorT<R>, Proj>>> OutputIt>
            constexpr UnaryTransformResult<BorrowedIteratorT<R>, OutputIt> transform(R && range, OutputIt first, UnaryOp op, Proj proj = {}) {
                return transform(begin(range), end(range), std::move(first), std::move(op), std::move(proj));
            }

            /**
             * Apply a given transformation and a projection to two given range and store the result into another range, no optimization
             * @param begin1 the first source start
             * @param end1   the first source end
             * @param begin2 the second source start
             * @param end2   the second source end
             * @param first  the destination start
             * @param op     the transformation to apply
             * @param proj1  the projection to apply on the first range
             * @param proj2  the projection to apply on the second range
             * @return an iterator pointing to the last element accessed in the first range, one pointing to the last element accessed in the second range and one pointing to the last transformed element
             */
            template <Concept::InputIterator InputIt1, Concept::SentinelFor<InputIt1> S1, Concept::InputIterator InputIt2, Concept::SentinelFor<InputIt2> S2,
                      Concept::IndirectlyRegularUnaryInvocable<InputIt1> Proj1 = Identity, Concept::IndirectlyRegularUnaryInvocable<InputIt2> Proj2 = Identity,
                      Concept::IndirectlyRegularBinaryInvocable<Projected<InputIt1, Proj1>, Projected<InputIt2, Proj2>> BinaryOp,
                      Concept::OutputIterator<IndirectInvokeResultT<BinaryOp, Projected<InputIt1, Proj1>, Projected<InputIt2, Proj2>>> OutputIt> requires (!Concept::SizedSentinelFor<S1, InputIt1> || !Concept::SizedSentinelFor<S2, InputIt2>)
            constexpr BinaryTransformResult<InputIt1, InputIt2, OutputIt> transform(InputIt1 begin1, S1 end1, InputIt2 begin2, S2 end2, OutputIt first, BinaryOp op, Proj1 proj1 = {}, Proj2 proj2 = {}) {
                for ( ; begin1 != end1 && begin2 != end2; ++begin1, ++begin2, ++first) {
                    *first = std::invoke(op, std::invoke(proj1, *begin1), std::invoke(proj2, *begin2));
                }
                return {begin1, begin2, first};
            }

            /**
             * Apply a given transformation and a projection to two given range and store the result into another range, optimized for sized sentinels
             * @param begin1 the first source start
             * @param end1   the first source end
             * @param begin2 the second source start
             * @param end2   the second source end
             * @param first  the destination start
             * @param op     the transformation to apply
             * @param proj1  the projection to apply on the first range
             * @param proj2  the projection to apply on the second range
             * @return an iterator pointing to the last element accessed in the first range, one pointing to the last element accessed in the second range and one pointing to the last transformed element
             */
            template <Concept::InputIterator InputIt1, Concept::SizedSentinelFor<InputIt1> S1, Concept::InputIterator InputIt2, Concept::SizedSentinelFor<InputIt2> S2,
                      Concept::IndirectlyRegularUnaryInvocable<InputIt1> Proj1 = Identity, Concept::IndirectlyRegularUnaryInvocable<InputIt2> Proj2 = Identity,
                      Concept::IndirectlyRegularBinaryInvocable<Projected<InputIt1, Proj1>, Projected<InputIt2, Proj2>> BinaryOp,
                      Concept::OutputIterator<IndirectInvokeResultT<BinaryOp, Projected<InputIt1, Proj1>, Projected<InputIt2, Proj2>>> OutputIt>
            constexpr BinaryTransformResult<InputIt1, InputIt2, OutputIt> transform(InputIt1 begin1, S1 end1, InputIt2 begin2, S2 end2, OutputIt first, BinaryOp op, Proj1 proj1 = {}, Proj2 proj2 = {}) {
                for (auto n = std::min(end1 - begin1, end2 - begin2); n > 0; --n) {
                    *first = std::invoke(op, std::invoke(proj1, *begin1), std::invoke(proj2, *begin2));
                    ++begin1;
                    ++begin2;
                    ++first;
                }
                return {begin1, begin2, first};
            }

            /**
             * Apply a given transformation and a projection to two given range and store the result into another range
             * @param range1 the first source range
             * @param range2 the second source range
             * @param first  the destination start
             * @param op     the transformation to apply
             * @param proj1  the projection to apply on the first range
             * @param proj2  the projection to apply on the second range
             * @return an iterator pointing to the last element accessed in the first range, one pointing to the last element accessed in the second range and one pointing to the last transformed element
             */
            template <Concept::InputRange R1, Concept::InputRange R2,
                      Concept::IndirectlyRegularUnaryInvocable<IteratorT<R1>> Proj1 = Identity, Concept::IndirectlyRegularUnaryInvocable<IteratorT<R2>> Proj2 = Identity,
                      Concept::IndirectlyRegularBinaryInvocable<Projected<IteratorT<R1>, Proj1>, Projected<IteratorT<R2>, Proj2>> BinaryOp,
                      Concept::OutputIterator<IndirectInvokeResultT<BinaryOp, Projected<IteratorT<R1>, Proj1>, Projected<IteratorT<R2>, Proj2>>> OutputIt>
            constexpr BinaryTransformResult<BorrowedIteratorT<R1>, BorrowedIteratorT<R2>, OutputIt> transform(R1 && range1, R2 && range2, OutputIt first, BinaryOp op, Proj1 proj1 = {}, Proj2 proj2 = {}) {
                return transform(begin(range1), end(range1), begin(range2), end(range2), std::move(first), std::move(op), std::move(proj1), std::move(proj2));
            }
    
        }
    }