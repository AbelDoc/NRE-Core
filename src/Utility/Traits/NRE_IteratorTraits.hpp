    
    /**
     * @file NRE_IteratorTraits.hpp
     * @brief Declaration of Utility's API's Iterator Traits
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
         * @namespace Utility
         * @brief Utility's API
         */
        namespace Utility {
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
                using DifferenceType = Utility::DifferenceType;
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
            } || !requires {
                typename T::difference_type;
            } || !requires {
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
            })
            struct IteratorCategoryTraits<T> {
                using Category = typename T::Category;
            };
    
            template <class T> requires requires {
                typename T::iterator_category;
            } && (!requires {
                typename T::Category;
            })
            struct IteratorCategoryTraits<T> {
                using Category = IteratorCategoryAdapterT<typename T::iterator_category>;
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
            
        }
    }