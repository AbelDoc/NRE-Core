    
    /**
     * @file NRE_MemoryTraits.hpp
     * @brief Declaration of Memory's API's Memory Traits
     * @author Louis ABEL
     * @date 23/09/2020
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
         * @namespace Memory
         * @brief Memory's API
         */
        namespace Memory {
    
    
            /**
             * @class PointerDifferenceTraits
             * @brief Allow uniform access to a pointer's difference type trait
             */
            template <class T>
            struct PointerDifferenceTraits {
                using DifferenceType = Core::DifferenceType;
            };
    
            template <class T> requires requires {
                typename T::DifferenceType;
            } && (!requires {
                typename T::difference_type;
            })
            struct PointerDifferenceTraits<T> {
                using DifferenceType = typename T::DifferenceType;
            };
    
            template <class T> requires requires {
                typename T::difference_type;
            } && (!requires {
                typename T::DifferenceType;
            })
            struct PointerDifferenceTraits<T> {
                using DifferenceType = typename T::difference_type;
            };
    
            template <class T> requires requires {
                typename T::DifferenceType;
                typename T::difference_type;
                Concept::SameAs<typename T::DifferenceType, typename T::difference_type>;
            }
            struct PointerDifferenceTraits<T> {
                using DifferenceType = typename T::DifferenceType;
            };
    
            /** Helper to access PointerDifferenceTraits type */
            template <class T>
            using PointerDifferenceT = typename PointerDifferenceTraits<T>::DifferenceType;
    
            /**
             * @class PointerValueTraits
             * @brief Allow uniform access to a pointer's value type
             */
            template <class T>
            struct PointerValueTraits {
            };
            
            template <Concept::Object T>
            struct PointerValueTraits<T*> {
                using ValueType = T;
            };
    
            template <template<class, class...> class M, class T, class ... Args>
            struct PointerValueTraits<M<T, Args...>> {
                using ValueType = T;
            };
    
            template <class T> requires requires {
                typename T::ValueType;
            } && (!requires {
                typename T::element_type;
            })
            struct PointerValueTraits<T> {
                using ValueType = T::ValueType;
            };
    
            template <class T> requires requires {
                typename T::element_type;
            } && (!requires {
                typename T::ValueType;
            })
            struct PointerValueTraits<T> {
                using ValueType = T::element_type;
            };
    
            template <class T> requires requires {
                typename T::ValueType;
                typename T::element_type;
                Concept::SameAs<typename T::ValueType, typename T::element_type>;
            }
            struct PointerValueTraits<T> {
                using ValueType = T::ValueType;
            };
    
            /** Helper to access PointerValueTraits type */
            template <class T>
            using PointerValueT = typename PointerValueTraits<T>::ValueType;
            
            /**
             * @class PointerTraits
             * @brief Allow uniform access to pointer's traits and utilities functions for pointers
             */
            template <class T>
            struct PointerTraits {
                using DifferenceType = PointerDifferenceT<T>;
                using ValueType = PointerValueT<T>;
    
                /** The rebinded pointer type */
                template <class K>
                using Rebind = typename T::Rebind<K>;
            };
            
            template <template <class, class...> class M, class T, class ... Args>
            struct PointerTraits<M<T, Args...>> {
                using DifferenceType = PointerDifferenceT<M<T, Args...>>;
                using ValueType = PointerValueT<M<T, Args...>>;
    
                /** The rebinded pointer type */
                template <class K>
                using Rebind = M<K, Args...>;
            };
            
            template <Concept::Object T>
            struct PointerTraits<T*> {
                using DifferenceType = PointerDifferenceT<T*>;
                using ValueType = PointerValueT<T*>;
    
                /** The rebinded pointer type */
                template <class K>
                using Rebind = K*;
            };
        
        }
    }