    
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
             * Fill a range of data [begin, end) with a given value, sized sentinel optimization
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
             * Fill a range of data [begin, end) with a given value, optimized for contiguous iterator and bytes-like type
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
             * Fill N data starting at begin with a given value, optimized for random access iterator
             * @param begin the range start
             * @param n     the number of object to fill
             * @param value the value to fill the range with
             */
            template <class T, Concept::OutputIterator<T const&> It, Concept::Integral Size> requires Concept::DerivedFrom<IteratorCategoryT<It>, RandomAccessIteratorCategory>
            constexpr void fillN(It begin, Size n, T const& value) {
                return fill(begin, begin + n, value);
            }
    
            /**
             * Copy a range of data [begin, end) into a given destination, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::SizedSentinelFor<S, InputIt>)
            constexpr OutputIt copy(InputIt begin, S end, OutputIt first) {
                for (; begin != end; ++begin, ++first) {
                    *first = *begin;
                }
                return first;
            }

            /**
             * Copy a range of data [begin, end) into a given destination, optimized for sized sentinel
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::OutputIterator<IteratorReferenceT<InputIt>> OutputIt> requires
                (!Concept::MemCopyable<IteratorValueT<InputIt>> ||
                 !Concept::ContiguousIterator<InputIt>          ||
                 !Concept::ContiguousIterator<OutputIt>)
            constexpr OutputIt copy(InputIt begin, S end, OutputIt first) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *first = *begin;
                    ++first;
                    ++begin;
                }
                return first;
            }

            /**
             * Copy a range of data [begin, end) into a given destination, optimized for contiguous iterator and trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last copied element
             */
            template <Concept::ContiguousIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::ContiguousIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorReferenceT<InputIt>> &&
                Concept::MemCopyable<IteratorValueT<InputIt>>
            constexpr OutputIt copy(InputIt begin, S end, OutputIt first) {
                IteratorValueT<OutputIt>* memFirst = addressOf(*first);
                IteratorValueT<InputIt>*  memBegin = addressOf(*begin);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memFirst, memBegin, n * sizeof(IteratorValueT<InputIt>));
                return first + n;
            }
            
            /**
             * Copy a range of data into a given destination
             * @param range the source range
             * @param first the destination start
             * @return an iterator pointing after the last copied element
             */
            template <Concept::InputRange R, Concept::OutputIterator<RangeReferenceT<R>> OutputIt>
            constexpr OutputIt copy(R && range, OutputIt first) {
                return copy(begin(range), end(range), first);
            }

            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last copied element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::BidirectionalIterator OutputIt> requires Concept::IndirectlyWritable<OutputIt, IteratorReferenceT<InputIt>> && (!Concept::SizedSentinelFor<S, InputIt>)
            constexpr OutputIt copyBackward(S begin, InputIt end, OutputIt last) {
                while (begin != end) {
                    *(--last) = *(--end);
                }
                return last;
            }
        
            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, optimized for sized sentinel
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last copied element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::BidirectionalIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorReferenceT<InputIt>> &&
                (!Concept::MemCopyable<IteratorValueT<InputIt>> ||
                 !Concept::ContiguousIterator<InputIt>          ||
                 !Concept::ContiguousIterator<OutputIt>)
            constexpr OutputIt copyBackward(S begin, InputIt end, OutputIt last) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *(--last) = *(--end);
                }
                return last;
            }
        
            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, optimized for contiguous iterator and trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last copied element
             */
            template <Concept::ContiguousIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::ContiguousIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorReferenceT<InputIt>> &&
                Concept::MemCopyable<IteratorValueT<InputIt>>
            constexpr OutputIt copyBackward(S begin, InputIt end, OutputIt last) {
                IteratorValueT<OutputIt>* memLast = addressOf(*last);
                IteratorValueT<InputIt>*  memEnd = addressOf(*end);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memLast - n, memEnd - n, n * sizeof(IteratorValueT<InputIt>));
                return last - n;
            }

            /**
             * Copy a range of data into a given destination but start from the end
             * @param range the source range
             * @param last  the destination end
             * @return an iterator pointing to the last copied element
             */
            template <Concept::BidirectionalRange R, Concept::OutputIterator<RangeReferenceT<R>> OutputIt> requires Concept::IndirectlyWritable<OutputIt, RangeReferenceT<R>>
            constexpr OutputIt copyBackward(R && range, OutputIt last) {
                return copyBackward(begin(range), end(range), last);
            }
            
            /**
             * Copy a range of data [begin, end), if they satisfies a given unary predicate, into a given destination
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @param p     the used predicate
             * @return an iterator pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::OutputIterator<IteratorReferenceT<InputIt>> OutputIt, Concept::UnaryPredicate<IteratorReferenceT<InputIt>> Pred>
            constexpr OutputIt copyIf(InputIt begin, S end, OutputIt first, Pred p) {
                for (; begin != end; ++begin) {
                    if (p(*begin)) {
                        *first = *begin;
                        ++first;
                    }
                }
                return first;
            }
            
            /**
             * Copy a range of data, if they satisfies a given unary predicate, into a given destination
             * @param range the source range
             * @param first the destination start
             * @param p     the used predicate
             * @return an iterator pointing after the last copied element
             */
            template <Concept::InputRange R, Concept::OutputIterator<RangeReferenceT<R>> OutputIt, Concept::UnaryPredicate<RangeReferenceT<R>> Pred>
            constexpr OutputIt copyIf(R && range, OutputIt first, Pred p) {
                return copyIf(begin(range), end(range), first, p);
            }
            
            /**
             * Copy N data starting at begin into a given destination, no optimization
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an interator pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::OutputIterator<IteratorReferenceT<InputIt>> OutputIt> requires (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            constexpr OutputIt copyN(InputIt begin, Size n, OutputIt first) {
                for (; n > 0; --n) {
                    *first = *begin;
                    ++first;
                    ++begin;
                }
                return first;
            }

            /**
             * Copy N data starting at begin into a given destination, optimized for random access iterator
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an interator pointing after the last copied element
             */
            template <Concept::RandomAccessIterator InputIt, Concept::Integral Size, Concept::OutputIterator<IteratorReferenceT<InputIt>> OutputIt>
            constexpr OutputIt copyN(InputIt begin, Size n, OutputIt first) {
                return copy(begin, begin + n, first);
            }

            /**
             * Move a range of data [begin, end) into a given destination, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::OutputIterator<IteratorRValueReferenceT<InputIt>> OutputIt> requires (!Concept::SizedSentinelFor<S, InputIt>)
            constexpr OutputIt move(InputIt begin, S end, OutputIt first) {
                for (; begin != end; ++begin, ++first) {
                    *first = std::move(*begin);
                }
                return first;
            }
        
            /**
             * Move a range of data [begin, end) into a given destination, optimized for sized sentinel
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::OutputIterator<IteratorRValueReferenceT<InputIt>> OutputIt> requires
                (!Concept::MemMoveable<IteratorValueT<InputIt>> ||
                 !Concept::ContiguousIterator<InputIt>          ||
                 !Concept::ContiguousIterator<OutputIt>)
            constexpr OutputIt move(InputIt begin, S end, OutputIt first) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *first = std::move(*begin);
                    ++first;
                    ++begin;
                }
                return first;
            }
        
            /**
             * Move a range of data [begin, end) into a given destination, optimized for contiguous iterator and trivially moveable types
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last moved element
             */
            template <Concept::ContiguousIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::ContiguousIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorRValueReferenceT<InputIt>> &&
                Concept::MemMoveable<IteratorValueT<InputIt>>
            constexpr OutputIt move(InputIt begin, S end, OutputIt first) {
                IteratorValueT<OutputIt>* memFirst = addressOf(*first);
                IteratorValueT<InputIt>*  memBegin = addressOf(*begin);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memFirst, memBegin, n * sizeof(IteratorValueT<InputIt>));
                return first + n;
            }
        
            /**
             * Move a range of data into a given destination
             * @param range the source range
             * @param first the destination start
             * @return an iterator pointing after the last moved element
             */
            template <Concept::InputRange R, Concept::OutputIterator<RangeRValueReferenceT<R>> OutputIt>
            constexpr OutputIt move(R && range, OutputIt first) {
                return move(begin(range), end(range), first);
            }

            /**
             * Move a range of data [begin, end) into a given destination but start from the end, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last moved element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::BidirectionalIterator OutputIt> requires Concept::IndirectlyWritable<OutputIt, IteratorRValueReferenceT<InputIt>> && (!Concept::SizedSentinelFor<S, InputIt>)
            constexpr OutputIt moveBackward(S begin, InputIt end, OutputIt last) {
                while (begin != end) {
                    *(--last) = std::move(*(--end));
                }
                return last;
            }
        
            /**
             * Move a range of data [begin, end) into a given destination but start from the end, optimized for sized sentinel
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last moved element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::BidirectionalIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorRValueReferenceT<InputIt>> &&
                (!Concept::MemMoveable<IteratorValueT<InputIt>> ||
                 !Concept::ContiguousIterator<InputIt>          ||
                 !Concept::ContiguousIterator<OutputIt>)
            constexpr OutputIt moveBackward(S begin, InputIt end, OutputIt last) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *(--last) = std::move(*(--end));
                }
                return last;
            }
        
            /**
             * Move a range of data [begin, end) into a given destination but start from the end, optimized for contiguous iterator and trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param last  the destination end
             * @return an iterator pointing to the last moved element
             */
            template <Concept::ContiguousIterator InputIt, Concept::SizedSentinelFor<InputIt> S, Concept::ContiguousIterator OutputIt> requires
                Concept::IndirectlyWritable<OutputIt, IteratorRValueReferenceT<InputIt>> &&
                Concept::MemMoveable<IteratorValueT<InputIt>>
            constexpr OutputIt moveBackward(S begin, InputIt end, OutputIt last) {
                IteratorValueT<OutputIt>* memLast = addressOf(*last);
                IteratorValueT<InputIt>*  memEnd = addressOf(*end);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memLast - n, memEnd - n, n * sizeof(IteratorValueT<InputIt>));
                return last - n;
            }

            /**
             * Move a range of data into a given destination but start from the end
             * @param range the source range
             * @param last  the destination end
             * @return an iterator pointing to the last moved element
             */
            template <Concept::BidirectionalRange R, Concept::BidirectionalIterator OutputIt> requires Concept::IndirectlyWritable<OutputIt, RangeRValueReferenceT<R>>
            constexpr OutputIt moveBackward(R && range, OutputIt last) {
                return moveBackward(begin(range), end(range), last);
            }

            /**
             * Copy a range of data [begin, end) into an uninitialized memory destination, destroy copied data in case of exception
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorReferenceT<InputIt>> && (!Concept::MemCopyable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedCopy(InputIt begin, S end, ForwardIt first) {
                ForwardIt current = first;
                try {
                    for (; begin != end; ++begin, ++current) {
                        Memory::constructAt(addressOf(*current), *begin);
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }

            /**
             * Copy a range of data [begin, end) into an uninitialized memory destination, destroy copied data in case of exception, trivially types optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorReferenceT<InputIt>> && Concept::MemCopyable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedCopy(InputIt begin, S end, ForwardIt first) {
                return copy(begin, end, first);
            }

            /**
             * Copy a range of data into an uninitialized memory destination, destroy copied data in case of exception
             * @param range the source range
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputRange R, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, RangeReferenceT<R>>
            ForwardIt uninitializedCopy(R && range, ForwardIt first) {
                return uninitializedCopy(begin(range), end(range), first);
            }

            /**
             * Copy N data starting at begin into an uninitialized memory destination, destroy copied data in case of exception
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorReferenceT<InputIt>> && (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            ForwardIt uninitializedCopyN(InputIt begin, Size n, ForwardIt first) {
                ForwardIt current = first;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAt(addressOf(*current), *begin);
                        ++begin;
                        ++current;
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }

            /**
             * Copy N data starting at begin into an uninitialized memory destination, destroy copied data in case of exception, optimized for random access iterator
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::RandomAccessIterator InputIt, Concept::Integral Size, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorReferenceT<InputIt>>
            ForwardIt uninitializedCopyN(InputIt begin, Size n, ForwardIt first) {
                return uninitializedCopy(begin, begin + n, first);
            }

            /**
             * Move a range of data [begin, end) into an uninitialized memory destination, destroy moved data in case of exception
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<InputIt>> && (!Concept::MemMoveable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedMove(InputIt begin, S end, ForwardIt first) {
                ForwardIt current = first;
                try {
                    for (; begin != end; ++begin, ++current) {
                        Memory::constructAt(addressOf(*current), std::move(*begin));
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }
        
            /**
             * Move a range of data [begin, end) into an uninitialized memory destination, destroy moved data in case of exception, trivially types optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::SentinelFor<InputIt> S, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<InputIt>> && Concept::MemMoveable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedMove(InputIt begin, S end, ForwardIt first) {
                return move(begin, end, first);
            }

            /**
             * Move a range of data into an uninitialized memory destination, destroy moved data in case of exception
             * @param range the source range
             * @param first the destination start
             * @return an iterator pointer after the last moved element
             */
            template <Concept::InputRange R, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, RangeRValueReferenceT<R>>
            ForwardIt uninitializedMove(R && range, ForwardIt first) {
                return uninitializedMove(begin(range), end(range), first);
            }

            /**
             * Move N data starting at begin into an uninitialized memory destination, destroy moved data in case of exception
             * @param begin the source range start
             * @param n     the number of data to moved
             * @param first the destination start
             * @return an iterator pointer after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<InputIt>> && (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            ForwardIt uninitializedMoveN(InputIt begin, Size n, ForwardIt first) {
                ForwardIt current = first;
                try {
                    for (; n > 0; --n) {
                        Memory::constructAt(addressOf(*current), std::move(*begin));
                        ++begin;
                        ++current;
                    }
                    return current;
                } catch (std::exception& e) {
                    Memory::destroy(first, current);
                    throw e;
                }
            }
        
            /**
             * Move N data starting at begin into an uninitialized memory destination, destroy moved data in case of exception, optimized for random access iterator
             * @param begin the source range start
             * @param n     the number of data to moved
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::RandomAccessIterator InputIt, Concept::Integral Size, Concept::ForwardIterator ForwardIt> requires Concept::IndirectlyWritable<ForwardIt, IteratorRValueReferenceT<InputIt>>
            ForwardIt uninitializedMoveN(InputIt begin, Size n, ForwardIt first) {
                return uninitializedMove(begin, begin + n, first);
            }
            
            /**
             * Fill an uninitiliazed range of memory [first, last) with a given value, no optimization
             * @param first the destination start
             * @param last  the destination end
             * @param value the value to fill the range with
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, T const&> && (!Concept::MemCopyable<IteratorValueT<ForwardIt>>)
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
             */
            template <class T, Concept::ForwardIterator ForwardIt, Concept::SentinelFor<ForwardIt> S> requires Concept::IndirectlyWritable<ForwardIt, T const&> && Concept::MemCopyable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedFill(ForwardIt first, S last, T const& value) {
                return fill(first, last, value);
            }

            /**
             * Fill an uninitiliazed range of memory with a given value
             * @param range the destination
             * @param value the value to fill the range with
             */
            template <class T, Concept::ForwardRange R> requires Concept::IndirectlyWritable<IteratorT<R>, T const&>
            BorrowedIteratorT<R> uninitializedFill(R && range, T const& value) {
                return uninitializedFill(begin(range), end(range), value);
            }
            
        }
    }