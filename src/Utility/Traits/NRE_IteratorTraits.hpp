    
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
             * @struct BidirectionnalIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct BidirectionnalIteratorCategory : public ForwardIteratorCategory {
            };
    
            /**
             * @struct RandomAccessIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct RandomAccessIteratorCategory : public BidirectionnalIteratorCategory {
            };
    
            /**
             * @struct ContiguousIteratorCategory
             * @brief Define an iterator category for concept differenciation
             */
            struct ContiguousIteratorCategory : public RandomAccessIteratorCategory {
            };
    
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
                using ValueType = RemoveCVT <RemoveExtentT<T>>;
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