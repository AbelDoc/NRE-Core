    
    /**
     * @file NRE_IteratorTraits.hpp
     * @brief Declaration of Core's API's Iterator Traits
     * @author Louis ABEL
     * @date 15/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../../Concept/NRE_Concept.hpp"
    
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
             * Query a value's address even if the value type overload address operator
             * @param t the value to obtain the adress
             * @return the computed address
             */
            template <Concept::Object T>
            [[nodiscard]] constexpr T* addressOf(T& t) noexcept {
                return reinterpret_cast <T*> (const_cast <char&> (reinterpret_cast <const volatile char&> (t)));
            }
    
            template <class T> requires (!Concept::Object<T>)
            [[nodiscard]] constexpr T* addressOf(T& t) noexcept {
                return &t;
            }
    
            /**
             * Inhibit addressOf so user can't get address of const r-value
             * @param t the value to obtain the adress
             * @return the computed address
             */
            template <class T>
            [[nodiscard]] const T* addressOf(T && t) = delete;
            
            /**
             * @struct InputIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct InputIteratorCategory {
            };
    
            /**
             * @struct OutputIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct OutputIteratorCategory {
            };
    
            /**
             * @struct ForwardIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct ForwardIteratorCategory : public InputIteratorCategory {
            };
    
            /**
             * @struct BidirectionalIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct BidirectionalIteratorCategory : public ForwardIteratorCategory {
            };
    
            /**
             * @struct RandomAccessIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct RandomAccessIteratorCategory : public BidirectionalIteratorCategory {
            };
    
            /**
             * @struct ContiguousIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct ContiguousIteratorCategory : public RandomAccessIteratorCategory {
            };
            
            /**
             * @struct IteratorCategoryAdapter
             * @brief Allow to adapt STL iterator tag to NRE iterator tag
             */
            template <class T>
            struct IteratorCategoryAdapter {
            };
            
            template <class T> requires Concept::SameAs<T, std::input_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = InputIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::output_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = OutputIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::forward_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = ForwardIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::bidirectional_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = BidirectionalIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::random_access_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = RandomAccessIteratorCategory;
            };
    
            template <class T> requires Concept::SameAs<T, std::contiguous_iterator_tag>
            struct IteratorCategoryAdapter<T> {
                using Type = ContiguousIteratorCategory;
            };
            
            /** Helper to access IteratorCategoryAdapter type */
            template <class T>
            using IteratorCategoryAdapterT = typename IteratorCategoryAdapter<T>::Type;
    
            /**
             * @struct IncrementableTraits
             * @brief Allow an abstract access to incrementable traits with STL compatiblity (STL -> NRE)
             */
            template <class T>
            struct IncrementableTraits {
            };
    
            template <Concept::Object T>
            struct IncrementableTraits<T*> {
                using DifferenceType = Core::DifferenceType;
            };
    
            template <class T>
            struct IncrementableTraits<const T> : IncrementableTraits<T> {
            };
    
            template <class T> requires requires {
                typename T::DifferenceType;
            } && (!requires {
                typename T::difference_type;
            })
            struct IncrementableTraits<T> {
                using DifferenceType = typename T::DifferenceType;
            };
    
            template <class T> requires requires {
                typename T::difference_type;
            } && (!requires {
                typename T::DifferenceType;
            })
            struct IncrementableTraits<T> {
                using DifferenceType = typename T::difference_type;
            };
    
            template <class T> requires requires {
                typename T::DifferenceType;
                typename T::difference_type;
                Concept::SameAs<typename T::DifferenceType, typename T::difference_type>;
            }
            struct IncrementableTraits<T> {
                using DifferenceType = typename T::DifferenceType;
            };
    
            template <class T> requires (!requires {
                typename T::DifferenceType;
            } && !requires {
                typename T::difference_type;
            } && !requires {
                typename T::DifferenceType;
                typename T::difference_type;
                Concept::SameAs<typename T::DifferenceType, typename T::difference_type>;
            }) && requires (T const& a, T const& b) {
                { a - b } -> Concept::Integral;
            }
            struct IncrementableTraits<T> {
                using DifferenceType = MakeSignedT<decltype(std::declval<T>() - std::declval<T>())>;
            };
            
            /**
             * @struct IndirectlyReadableTraits
             * @brief Allow an abstract access to indirectly readable traits with STL compatiblity (STL -> NRE)
             */
            template <class T>
            struct IndirectlyReadableTraits {
            };
    
            template <Concept::Object T>
            struct IndirectlyReadableTraits<T*> {
                using ValueType = RemoveCVT<T>;
            };
    
            template <Concept::Array T>
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<RemoveExtentT<T>>;
            };
    
            template <class T>
            struct IndirectlyReadableTraits<const T> : IndirectlyReadableTraits<T> {
            };
    
            template <class T> requires requires {
                typename T::ValueType;
            } && (!requires {
                typename T::value_type;
            })
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<typename T::ValueType>;
            };
    
            template <class T> requires requires {
                typename T::value_type;
            } && (!requires {
                typename T::ValueType;
            })
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<typename T::value_type>;
            };
    
    
            template <class T> requires requires {
                typename T::ValueType;
                typename T::value_type;
                Concept::SameAs<typename T::ValueType, typename T::value_type>;
            }
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<typename T::ValueType>;
            };
            
            template <class T>
            struct IteratorCategoryTraits {
            };
            
            template <Concept::Object T>
            struct IteratorCategoryTraits<T*> {
                using Category = ContiguousIteratorCategory;
            };
            
            template <class T>
            struct IteratorCategoryTraits<const T> : IteratorCategoryTraits<T> {
            };
            
            template <class T> requires requires {
                typename T::Category;
            } && (!requires {
                typename T::iterator_category;
            } && !requires {
                typename T::iterator_concept;
            })
            struct IteratorCategoryTraits<T> {
                using Category = typename T::Category;
            };
    
            template <class T> requires requires {
                typename T::iterator_category;
            } && (!requires {
                typename T::Category;
            } && !requires {
                typename T::iterator_concept;
            })
            struct IteratorCategoryTraits<T> {
                using Category = IteratorCategoryAdapterT<typename T::iterator_category>;
            };
            
            template <class T> requires requires {
                typename T::iterator_concept;
            } && (!requires {
                typename T::Category;
            })
            struct IteratorCategoryTraits<T> {
                using Category = IteratorCategoryAdapterT<typename T::iterator_concept>;
            };
            
            template <class T> requires requires {
                typename T::Category;
                typename T::iterator_category;
                Concept::SameAs<typename T::Category, IteratorCategoryAdapterT<typename T::iterator_category>>;
            } && (!requires {
                typename T::iterator_concept;
            })
            struct IteratorCategoryTraits<T> {
                using Category = typename T::Category;
            };
            
            template <class T> requires requires {
                typename T::Category;
                typename T::iterator_concept;
                Concept::SameAs<typename T::Category, IteratorCategoryAdapterT<typename T::iterator_concept>>;
            }
            struct IteratorCategoryTraits<T> {
                using Category = typename T::Category;
            };
            
            template <class T>
            using IteratorCategoryT = typename IteratorCategoryTraits<RemoveCVReferenceT<T>>::Category;

            /** Helper to access an iterator ValueType */
            template <class T>
            using IteratorValueT = typename IndirectlyReadableTraits<RemoveCVReferenceT<T>>::ValueType;
            
            /** Helper to access an iterator DifferenceType */
            template <class T>
            using IteratorDifferenceT = typename IncrementableTraits<RemoveCVReferenceT<T>>::DifferenceType;
            
            /** Compute the reference type of a given type */
            template <Concept::Dereferenceable T>
            using IteratorReferenceT = decltype(*std::declval<T&>());
            
            /** Compute the r-value reference type of a given type */
            template <class T> requires requires (T& t) {
                { std::ranges::iter_move(t) } -> Concept::Referenceable;
            }
            using IteratorRValueReferenceT = decltype(std::ranges::iter_move(std::declval<T&>()));
            
            /** Allow to prevent iterators and sentinels that can be subtracted to satisfy the concept */
            template <class S, class T>
            inline constexpr bool DISABLE_SIZED_SENTINEL_FOR = false || std::disable_sized_sentinel_for<S, T>;
            
            /**
             * @struct IteratorTraits
             * @brief Allow uniform access to iterator's traits
             */
            template <class T>
            struct IteratorTraits {
                using DifferenceType = IteratorDifferenceT<T>;
                using ValueType = IteratorValueT<T>;
                using Reference = IteratorReferenceT<T>;
                using Category = IteratorCategoryT<T>;
            };
    
            /**
             * Return an iterator to the beginning of the given container
             * @param t the object to query a begin iterator
             * @return the corresponding iterator
             */
            template <class T> requires requires (T& t) {
                { t.begin() };
            }
            constexpr auto begin(T& t) -> decltype(t.begin()) {
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
            constexpr auto begin(T const& t) -> decltype(t.begin()) {
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
            constexpr auto cbegin(T const& t) noexcept(noexcept(begin(t))) -> decltype(begin(t)) {
                return begin(t);
            }
    
            /**
             * Return an iterator to the end of the given container
             * @param t the object to query an end iterator
             * @return the corresponding iterator
             */
            template <class T> requires requires (T& t) {
                { t.end() };
            }
            constexpr auto end(T& t) -> decltype(t.end()) {
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
            constexpr auto end(T const& t) -> decltype(t.end()) {
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
            constexpr auto cend(T const& t) noexcept(noexcept(end(t))) -> decltype(end(t)) {
                return end(t);
            }
        }
    }