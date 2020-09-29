    
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
             * Copy a range of data [begin, end) into a given destination, no optimisation
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::TriviallyCopyable<IteratorValueT<InputIt>> || !Concept::TriviallyCopyable<IteratorValueT<OutputIt>>) &&
                                                                                                                          (!Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>)
            OutputIt copy(InputIt begin, InputIt end, OutputIt first) {
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
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires (!Concept::TriviallyCopyable<IteratorValueT<InputIt>> || !Concept::TriviallyCopyable<IteratorValueT<OutputIt>>) &&
                                                                                                                           Concept::DerivedFrom<IteratorCategoryT<InputIt>, RandomAccessIteratorCategory>
            OutputIt copy(InputIt begin, InputIt end, OutputIt first) {
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
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt> requires Concept::TriviallyCopyable<IteratorValueT<InputIt>> && Concept::TriviallyCopyable<IteratorValueT<OutputIt>> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<InputIt>,  ContiguousIteratorCategory> &&
                                                                                                                          Concept::SameAs<IteratorCategoryT<OutputIt>, ContiguousIteratorCategory>
            OutputIt copy(InputIt begin, InputIt end, OutputIt first) {
                IteratorValueT<OutputIt>* memFirst = addressOf(*first);
                IteratorValueT<InputIt>*  memBegin = addressOf(*begin);
                IteratorDifferenceT<InputIt> n = end - begin;
                std::memcpy(memFirst, memBegin, n * sizeof(IteratorValueT<InputIt>));
                return first + n;
            }
            
            template <Concept::InputIterator InputIt, Concept::OutputIterator<IteratorValueT<InputIt>> OutputIt, Concept::UnaryPredicate<IteratorValueT<InputIt>> Predicate>
            OutputIt copyIf(InputIt begin, InputIt end, OutputIt first, Predicate p) {
                for (; begin != end; ++begin) {
                    if (p(*begin)) {
                        *first = *begin;
                        ++first;
                    }
                }
                return first;
            }
            
            /**
             * Copy a range of data [begin, end) into an uninitialized memory destination, destroy copied data in case of exception
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::ForwardIterator ForwardIt> requires (!Concept::TriviallyCopyable<IteratorValueT<InputIt>> || !Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>)
            ForwardIt unitializedCopy(InputIt begin, InputIt end, ForwardIt first) {
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
             * Copy a range of data [begin, end) into an uninitialized memory destination, destroy copied data in case of exception, trivially types optimisation
             * @param begin the source range start
             * @param end   the source range end
             * @param first the destination start
             * @return an iterator pointer after the last copied element
             */
            template <Concept::InputIterator InputIt, Concept::ForwardIterator ForwardIt> requires Concept::TriviallyCopyable<IteratorValueT<InputIt>> && Concept::TriviallyCopyable<IteratorValueT<ForwardIt>>
            ForwardIt unitializedCopy(InputIt begin, InputIt end, ForwardIt first) {
                return copy(begin, end, first);
            }
        }
    }