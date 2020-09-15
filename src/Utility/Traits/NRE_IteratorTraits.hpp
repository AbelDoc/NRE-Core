    
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
             * @brief Allow an abstract access to incrementable traits with STL compatiblity (STL -> NRE, NRE -> STL)
             */
            template <class T>
            struct IncrementableTraits {
            };
    
            template <Concept::Object T>
            struct IncrementableTraits<T*> {
                using DifferenceType = Utility::DifferenceType;
                using difference_type = DifferenceType;
            };
    
            template <class T>
            struct IncrementableTraits<const T> : IncrementableTraits<T> {
            };
    
            template <class T> requires requires {
                typename T::DifferenceType;
            } && !requires {
                typename T::difference_type;
            }
            struct IncrementableTraits<T> {
                using DifferenceType = typename T::DifferenceType;
                using difference_type = DifferenceType;
            };
    
            template <class T> requires requires {
                typename T::difference_type;
            } && !requires {
                typename T::DifferenceType;
            }
            struct IncrementableTraits<T> {
                using DifferenceType = typename T::difference_type;
                using difference_type = DifferenceType;
            };
    
            template <class T> requires requires {
                typename T::DifferenceType;
                typename T::difference_type;
                Concept::SameAs<typename T::DifferenceType, typename T::difference_type>;
            }
            struct IncrementableTraits<T> {
                using DifferenceType = typename T::DifferenceType;
                using difference_type = DifferenceType;
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
                using difference_type = DifferenceType;
            };
            
            /**
             * @struct IncrementableTraits
             * @brief Allow an abstract access to indirectly readable traits with STL compatiblity (STL -> NRE, NRE -> STL)
             */
            template <class T>
            struct IndirectlyReadableTraits {
            };
    
            template <Concept::Object T>
            struct IndirectlyReadableTraits<T*> {
                using ValueType = RemoveCVT<T>;
                using value_type = ValueType;
            };
    
            template <Concept::Array T>
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT <RemoveExtentT<T>>;
                using value_type = ValueType;
            };
    
            template <class T>
            struct IndirectlyReadableTraits<const T> : IndirectlyReadableTraits<T> {
            };
    
            template <class T> requires requires {
                typename T::ValueType;
            } && !requires {
                typename T::value_type;
            }
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<typename T::ValueType>;
                using value_type = ValueType;
            };
    
            template <class T> requires requires {
                typename T::value_type;
            } && !requires {
                typename T::ValueType;
            }
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<typename T::value_type>;
                using value_type = ValueType;
            };
    
    
            template <class T> requires requires {
                typename T::ValueType;
                typename T::value_type;
                Concept::SameAs<typename T::ValueType, typename T::value_type>;
            }
            struct IndirectlyReadableTraits<T> {
                using ValueType = RemoveCVT<typename T::ValueType>;
                using value_type = ValueType;
            };
        }
    }