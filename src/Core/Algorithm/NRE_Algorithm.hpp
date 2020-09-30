    
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
             * @param begin the source range start
             * @param end   the source range end
             * @param value the value to fill the range with
             */
            template <Concept::ForwardIterator It> requires (!Concept::MemFillable<IteratorValueT<It>> && !Concept::DerivedFrom<IteratorCategoryT<It>, RandomAccessIteratorCategory>)
            constexpr void fill(It begin, It end, IteratorValueT<It>& value) {
                for (; begin != end; ++begin) {
                    *begin = value;
                }
            }
        
            /**
             * Fill a range of data [begin, end) with a given value, random access iterator optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param value the value to fill the range with
             */
            template <Concept::ForwardIterator It> requires (!Concept::MemFillable<IteratorValueT<It>>) && Concept::DerivedFrom<IteratorCategoryT<It>, RandomAccessIteratorCategory>
            constexpr void fill(It begin, It end, IteratorValueT<It>& value) {
                for (IteratorDifferenceT<It> n = end - begin; n > 0; --n) {
                    *begin = value;
                    ++begin;
                }
            }

            /**
             * Fill a range of data [begin, end) with a given value, optimized for contiguous iterator and bytes-like type
             * @param begin the source range start
             * @param end   the source range end
             * @param value the value to fill the range with
             */
            template <Concept::ForwardIterator It> requires Concept::MemFillable<IteratorValueT<It>> && Concept::SameAs<IteratorCategoryT<It>, ContiguousIteratorCategory>
            constexpr void fill(It begin, It end, IteratorValueT<It>& value) {
                IteratorValueT<It>* memBegin = addressOf(*begin);
                IteratorDifferenceT<It> n = end - begin;
                std::memset(memBegin, value, n);
            }

            /**
             * Fill N data starting at begin with a given value, no optimization
             * @param begin the source range start
             * @param n     the number of object to fill
             * @param value the value to fill the range with
             */
            template <Concept::ForwardIterator It, Concept::Integral Size> requires (!Concept::DerivedFrom<IteratorCategoryT<It>, RandomAccessIteratorCategory>)
            constexpr void fillN(It begin, Size n, IteratorValueT<It>& value) {
                for ( ; n > 0; --n) {
                    *begin = value;
                    ++begin;
                }
            }
        
            /**
             * Fill N data starting at begin with a given value, optimized for random access iterator
             * @param begin the source range start
             * @param n     the number of object to fill
             * @param value the value to fill the range with
             */
            template <Concept::ForwardIterator It, Concept::Integral Size> requires Concept::DerivedFrom<IteratorCategoryT<It>, RandomAccessIteratorCategory>
            constexpr void fillN(It begin, Size n, IteratorValueT<It>& value) {
                return fill(begin, begin + n, value);
            }
    
            /**
             * Copy a range of data [begin, end) into a given destination, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::MemCopyable<IteratorValueT<InputIt>> || !Concept::MemCopyable<IteratorValueT<OutputIt>>) &&
                                                                                                                          (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            constexpr OutputIt copy(InputIt begin, InputIt end, OutputIt first) {
                for (; begin != end; ++begin, ++first) {
                    *first = *begin;
                }
                return first;
            }

            /**
             * Copy a range of data [begin, end) into a given destination, optimized for random access iterator
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::MemCopyable<IteratorValueT<InputIt>> || !Concept::MemCopyable<IteratorValueT<OutputIt>>) &&
                                                                                                                            Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>
            constexpr OutputIt copy(InputIt begin, InputIt end, OutputIt first) {
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
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires Concept::MemCopyable<IteratorValueT<InputIt>> && Concept::MemCopyable<IteratorValueT<OutputIt>> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<InputIt>,  ContiguousIteratorCategory> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<OutputIt>, ContiguousIteratorCategory>
            constexpr OutputIt copy(InputIt begin, InputIt end, OutputIt first) {
                IteratorValueT<OutputIt>* memFirst = addressOf(*first);
                IteratorValueT<InputIt>*  memBegin = addressOf(*begin);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memFirst, memBegin, n * sizeof(IteratorValueT<InputIt>));
                return first + n;
            }

            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last copied element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::BidirectionalIterator OutputIt> requires (!Concept::MemCopyable<IteratorValueT<InputIt>> || !Concept::MemCopyable<IteratorValueT<OutputIt>>) &&
                                                                                                                (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            constexpr OutputIt copyBackward(InputIt begin, InputIt end, OutputIt first) {
                while (begin != end) {
                    *(--first) = *(--begin);
                }
                return first;
            }
        
            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, optimized for random access iterator
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::MemCopyable<IteratorValueT<InputIt>> || !Concept::MemCopyable<IteratorValueT<OutputIt>>) &&
                                                                                                                            Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>
            constexpr OutputIt copyBackward(InputIt begin, InputIt end, OutputIt first) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *(--first) = *(--begin);
                }
                return first;
            }
        
            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, optimized for contiguous iterator and trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires Concept::MemCopyable<IteratorValueT<InputIt>> && Concept::MemCopyable<IteratorValueT<OutputIt>> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<InputIt>,  ContiguousIteratorCategory> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<OutputIt>, ContiguousIteratorCategory>
            constexpr OutputIt copyBackward(InputIt begin, InputIt end, OutputIt first) {
                IteratorValueT<OutputIt>* memFirst = addressOf(*first);
                IteratorValueT<InputIt>*  memBegin = addressOf(*begin);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(first - n, memBegin, n * sizeof(IteratorValueT<InputIt>));
                return first - n;
            }
            
            /**
             * Copy data in a given range [begin, end) if they satisfies a given unary predicate
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @param p     the used predicate
             * @return an iterator pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt, Concept::UnaryPredicate<IteratorValueT<InputIt>> Pred>
            constexpr OutputIt copyIf(InputIt begin, InputIt end, OutputIt first, Pred p) {
                for (; begin != end; ++begin) {
                    if (p(*begin)) {
                        *first = *begin;
                        ++first;
                    }
                }
                return first;
            }
            
            /**
             * Copy N data in the range [begin, begin + N) into a given destination, no optimization
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an interator pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            constexpr OutputIt copyN(InputIt begin, Size n, OutputIt first) {
                for (; n > 0; --n) {
                    *first = *begin;
                    ++first;
                    ++begin;
                }
                return first;
            }

            /**
             * Copy N data in the range [begin, begin + N) into a given destination, optimized for random access iterator
             * @param begin the source range start
             * @param n     the number of data to copy
             * @param first the destination start
             * @return an interator pointing after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::Integral Size, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>
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
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::MemMoveable<IteratorValueT<InputIt>> || !Concept::MemMoveable<IteratorValueT<OutputIt>>) &&
                                                                                                                          (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            constexpr OutputIt move(InputIt begin, InputIt end, OutputIt first) {
                for (; begin != end; ++begin, ++first) {
                    *first = std::move(*begin);
                }
                return first;
            }
        
            /**
             * Move a range of data [begin, end) into a given destination, optimized for random access iterator
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::MemMoveable<IteratorValueT<InputIt>> || !Concept::MemMoveable<IteratorValueT<OutputIt>>) &&
                                                                                                                            Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>
            constexpr OutputIt move(InputIt begin, InputIt end, OutputIt first) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *first = std::move(*begin);
                    ++first;
                    ++begin;
                }
                return first;
            }
        
            /**
             * Move a range of data [begin, end) into a given destination, optimized for contiguous iterator and trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires Concept::MemMoveable<IteratorValueT<InputIt>> && Concept::MemMoveable<IteratorValueT<OutputIt>> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<InputIt>,  ContiguousIteratorCategory> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<OutputIt>, ContiguousIteratorCategory>
            constexpr OutputIt move(InputIt begin, InputIt end, OutputIt first) {
                IteratorValueT<OutputIt>* memFirst = addressOf(*first);
                IteratorValueT<InputIt>*  memBegin = addressOf(*begin);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(memFirst, memBegin, n * sizeof(IteratorValueT<InputIt>));
                return first + n;
            }

            /**
             * Move a range of data [begin, end) into a given destination but start from the end, no optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last moved element
             */
            template <Concept::BidirectionalIterator InputIt, Concept::BidirectionalIterator OutputIt> requires (!Concept::MemMoveable<IteratorValueT<InputIt>> || !Concept::MemMoveable<IteratorValueT<OutputIt>>) &&
                                                                                                                (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            constexpr OutputIt moveBackward(InputIt begin, InputIt end, OutputIt first) {
                while (begin != end) {
                    *(--first) = std::move(*(--begin));
                }
                return first;
            }
        
            /**
             * Move a range of data [begin, end) into a given destination but start from the end, optimized for random access iterator
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::MemMoveable<IteratorValueT<InputIt>> || !Concept::MemMoveable<IteratorValueT<OutputIt>>) &&
                                                                                                                            Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>
            constexpr OutputIt moveBackward(InputIt begin, InputIt end, OutputIt first) {
                for (IteratorDifferenceT<InputIt> n = end - begin; n > 0; --n) {
                    *(--first) = std::move(*(--begin));
                }
                return first;
            }
        
            /**
             * Copy a range of data [begin, end) into a given destination but start from the end, optimized for contiguous iterator and trivially copyable types
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointing to the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires Concept::MemMoveable<IteratorValueT<InputIt>> && Concept::MemMoveable<IteratorValueT<OutputIt>> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<InputIt>,  ContiguousIteratorCategory> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<OutputIt>, ContiguousIteratorCategory>
            constexpr OutputIt moveBackward(InputIt begin, InputIt end, OutputIt first) {
                IteratorValueT<OutputIt>* memFirst = addressOf(*first);
                IteratorValueT<InputIt>*  memBegin = addressOf(*begin);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memmove(first - n, memBegin, n * sizeof(IteratorValueT<InputIt>));
                return first - n;
            }

            /**
             * Copy a range of data [begin, end) into an uninitialized memory destination, destroy copied data in case of exception
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::ForwardIterator ForwardIt> requires (!Concept::MemCopyable<IteratorValueT<InputIt>> || !Concept::MemCopyable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedCopy(InputIt begin, InputIt end, ForwardIt first) {
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
            template <Concept::InputIterator InputIt, Concept::ForwardIterator ForwardIt> requires Concept::MemCopyable<IteratorValueT<InputIt>> && Concept::MemCopyable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedCopy(InputIt begin, InputIt end, ForwardIt first) {
                return copy(begin, end, first);
            }

            /**
             * Move a range of data [begin, end) into an uninitialized memory destination, destroy copied data in case of exception
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::ForwardIterator ForwardIt> requires (!Concept::MemMoveable<IteratorValueT<InputIt>> || !Concept::MemMoveable<IteratorValueT<ForwardIt>>)
            ForwardIt uninitializedMove(InputIt begin, InputIt end, ForwardIt first) {
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
             * Move a range of data [begin, end) into an uninitialized memory destination, destroy copied data in case of exception, trivially types optimization
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last moved element
             */
            template <Concept::InputIterator InputIt, Concept::ForwardIterator ForwardIt> requires Concept::MemMoveable<IteratorValueT<InputIt>> && Concept::MemMoveable<IteratorValueT<ForwardIt>>
            ForwardIt uninitializedMove(InputIt begin, InputIt end, ForwardIt first) {
                return move(begin, end, first);
            }
        }
    }