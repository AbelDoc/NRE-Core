    
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

            /** Helper for unitializedFill-function result type */
            template <class It, class Out>
            using UninitializedFillResult = Detail::InOutResult<It, Out>;
            
            /**
             * Fill an uninitiliazed range of memory [first, last) with a given value, no optimization
             * @param first the destination start
             * @param last  the destination end
             * @param value the value to fill the range with
             * @return an iterator pointing after the last filled element
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, T const&> && (!Concept::TriviallyAssignable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedFill(ForwardIt first, S last, T const& value) {
                ForwardIt current = first;
                try {
                    for (; current != last; ++current) {
                        Memory::constructAt(addressOf(*current), value);
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }

            /**
             * Fill an uninitiliazed range of memory [first, last) with a given value, optimized for trivially copyable types
             * @param first the destination start
             * @param last  the destination end
             * @param value the value to fill the range with
             * @return an iterator pointing after the last filled element
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, T const&> && Concept::TriviallyAssignable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedFill(ForwardIt first, S last, T const& value) {
                return fill(std::move(first), std::move(last), value);
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
             * Fill N uninitialized data starting at first with a given value, no optimization
             * @param first the destination start
             * @param n     the number of data to fill
             * @param value the value to fill the datas with
             * @return an iterator pointing after the last filled element
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, T const&> && (!Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedFillN(ForwardIt first, Size n, T const& value) {
                ForwardIt current = first;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAt(addressOf(*current), value);
                        ++current;
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }

            /**
             * Fill N uninitialized data starting at first with a given value, optimized for trivially copyable types
             * @param first the destination start
             * @param n     the number of data to fill
             * @param value the value to fill the datas with
             * @return an iterator pointing after the last filled element
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, T const&> && Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedFillN(ForwardIt first, Size n, T const& value) {
                return fillN(std::move(first), n, std::move(value));
            }
            
            /**
             * Initialize a range of data [first, last) with default constructed value, no optimization
             * @param first the destination start
             * @param last  the destination end
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && (!Concept::TriviallyConstructible<IteratorValueT<ForwardIt>>)
            void uninitializedDefaultConstruct(ForwardIt first, S last) {
                ForwardIt current = first;
                try {
                    for (; current != last; ++current) {
                        Memory::constructAtNoValue(addressOf(*current));
                    }
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }

            /**
             * Initialize a range of data [first, last) with default constructed value, optimized for trivially constructible types
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
             * @param first the destination start
             * @param n     the number of data to initialize
             */
            template <Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && (!Concept::TriviallyConstructible<IteratorValueT<ForwardIt>>)
            void uninitializedDefaultConstructN(ForwardIt first, Size n) {
                ForwardIt current = first;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAtNoValue(addressOf(*current));
                        ++current;
                    }
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
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
             * Initialize a range of data [first, last) with value constructed value, no optimization
             * @param first the destination start
             * @param last  the destination end
             * @return an iterator pointing after the last constructed element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && (!Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedValueConstruct(ForwardIt first, S last) {
                ForwardIt current = first;
                try {
                    for (; current != last; ++current) {
                        Memory::constructAt(addressOf(*current));
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }
        
            /**
             * Initialize a range of data [first, last) with default constructed value, optimized for trivially constructible types
             * @param first the destination start
             * @param last  the destination end
             * @return an iterator pointing after the last constructed element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedValueConstruct(ForwardIt first, S last) {
                return fill(std::move(first), std::move(last), IteratorValueT<ForwardIt>());
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
             * @param first the destination start
             * @param n     the number of element to initialize
             * @return an iterator pointing after the last constructed element
             */
            template<Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && (!Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedValueConstructN(ForwardIt first, Size n) {
                ForwardIt current = first;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAt(addressOf(*current));
                        ++current;
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }

            /**
             * Initialize N data with default constructed value
             * @param first the destination start
             * @param n     the number of element to initialize
             * @return an iterator pointing after the last constructed element
             */
            template<Concept::ForwardIterator ForwardIt, Concept::Integral Size> requires Concept::IndirectlyWritable<ForwardIt, IteratorValueT<ForwardIt>> && Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedValueConstructN(ForwardIt first, Size n) {
                return fillN(std::move(first), n, IteratorValueT<ForwardIt>());
            }
            
            /**
             * Fill a range of data [first, last) with generated data from a given generator, no optimization
             * @param first the destination start
             * @param last  the destination end
             * @param g     the data generator
             * @return an iterator pointing after the last generated element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S, Concept::Generator Gen> requires Concept::IndirectlyWritable<ForwardIt, Core::InvokeResultT<Gen>> && (!Concept::SizedSentinelFor<S, ForwardIt>)
            constexpr ForwardIt generate(ForwardIt first, S last, Gen g) {
                for ( ; first != last; ++first) {
                    *first = std::move(g());
                }
                return first;
            }

            /**
             * Fill a range of data [first, last) with generated data from a given generator, optimized for sized sentinels
             * @param first the destination start
             * @param last  the destination end
             * @param g     the data generator
             * @return an iterator pointing after the last generated element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::SizedSentinelFor<ForwardIt> S, Concept::Generator Gen> requires Concept::IndirectlyWritable<ForwardIt, Core::InvokeResultT<Gen>>
            constexpr ForwardIt generate(ForwardIt first, S last, Gen g) {
                for (auto n = last - first; n > 0; --n) {
                    *first = std::move(std::invoke(g));
                    ++first;
                }
                return first;
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
             * @param first the destination start
             * @param g     the data generator
             * @return an iterator pointing after the last generated element
             */
            template <Concept::ForwardIterator ForwardIt, Concept::Integral Size, Concept::Generator Gen> requires Concept::IndirectlyWritable<ForwardIt, Core::InvokeResultT<Gen>>
            constexpr ForwardIt generateN(ForwardIt first, Size n, Gen g) {
                for (; n > 0; --n) {
                    *first = std::move(std::invoke(g));
                    ++first;
                }
                return first;
            }
            
            /**
             * Shift the given range by n if distance(first, last) > n > 0, otherwise no effect
             * @param first the range start to shift
             * @param last  the range end to shift
             * @param n     the shift amount
             * @return an iterator pointing after the last element shifted, last if n == 0, first if n >= distance(first, last)
             */
            template <Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<ForwardIt>>
            constexpr ForwardIt shiftLeft(ForwardIt first, ForwardIt last, IteratorDifferenceT<ForwardIt> n) {
                if (n == 0) {
                    return last;
                }
                
                auto middle = next(first, n, last);
                if (middle == last) {
                    return first;
                }
                return move(std::move(middle), std::move(last), std::move(first)).out;
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
             * Shift the given range by n if distance(first, last) > n > 0, otherwhise no effect, no optimization
             * @param first the range start to shift
             * @param last  the range end to shift
             * @param n     the shift amount
             * @return an iterator pointing after the last element shifted, last if first == 0, end if n >= distance(first, last)
             */
            template <Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<ForwardIt>> && (!Concept::BidirectionalIterator<ForwardIt>)
            constexpr ForwardIt shiftRight(ForwardIt first, ForwardIt last, IteratorDifferenceT<ForwardIt> n) {
                if (n == 0) {
                    return first;
                }
                
                auto result = next(first, n, last);
                if (result == last) {
                    return last;
                }
                
                auto destinationHead = first;
                auto destinationTail = result;
                while (destinationHead != result) {
                    if (destinationTail == last) {
                        move(std::move(first), std::move(destinationHead), std::move(result));
                        return result;
                    }
                    ++destinationHead;
                    ++destinationTail;
                }
                for (;;) {  // Ended when [first, result) and [destinationHead, destinationTail) are disjoint,
                            // no for end condition in order to have direct return when last moving,
                            // avoiding extra instructions after
                    auto cursor = first;
                    while (cursor != result) {
                        if (destinationTail == last) {
                            destinationHead = move(cursor, result, std::move(destinationHead));
                            move(std::move(first), std::move(cursor), std::move(destinationHead));
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
             * Shift the given range by n if distance(first, last) > n > 0, otherwhise no effect, optimized for bidirectional iterator
             * @param first the range start to shift
             * @param last  the range end to shift
             * @param n     the shift amount
             * @return an iterator pointing after the last element shifted, last if first == 0, end if n >= distance(first, last)
             */
            template <Concept::BidirectionalIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<ForwardIt>>
            constexpr ForwardIt shiftRight(ForwardIt first, ForwardIt last, IteratorDifferenceT<ForwardIt> n) {
                if (n == 0) {
                    return first;
                }
                
                auto mid = next(last, -n, first);
                if (mid == first) {
                    return last;
                }
                return moveBackward(std::move(first), std::move(mid), std::move(last)).out;
            }

            /**
             * Shift the given range by n if distance(first, last) > n > 0, otherwhise no effect
             * @param range the range to shift
             * @param n     the shift amount
             * @return an iterator pointing after the last element shifted, last if begin(range) == 0, end(range) if n >= distance(begin(range), end(range))
             */
            template <Concept::ForwardRange R> requires Concept::IndirectlyWritable<IteratorT<R>, IteratorRValueReferenceT<IteratorT<R>>>
            constexpr BorrowedIteratorT<R> shiftRight(R && range, IteratorDifferenceT<IteratorT<R>> n) {
                return shiftRight(begin(range), end(range), n);
            }
            
        }
    }