    
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
             * @struct PointerDifferenceTraits
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
             * @struct PointerValueTraits
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
             * @struct PointerTraits
             * @brief Allow uniform access to pointer's traits and utilities functions for pointers
             */
            template <class T>
            struct PointerTraits {
                using DifferenceType = PointerDifferenceT<T>;
                using ValueType = PointerValueT<T>;
    
                /** The rebinded pointer type */
                template <class K>
                using Rebind = typename T::Rebind<K>;
    
                /** The rebinded pointer traits */
                template <class K>
                using RebindTraits = PointerTraits<Rebind<K>>;
            };
            
            template <template <class, class...> class M, class T, class ... Args>
            struct PointerTraits<M<T, Args...>> {
                using DifferenceType = PointerDifferenceT<M<T, Args...>>;
                using ValueType = PointerValueT<M<T, Args...>>;
    
                /** The rebinded pointer type */
                template <class K>
                using Rebind = M<K, Args...>;
    
                /** The rebinded pointer traits */
                template <class K>
                using RebindTraits = PointerTraits<Rebind<K>>;
            };
            
            template <Concept::Object T>
            struct PointerTraits<T*> {
                using DifferenceType = PointerDifferenceT<T*>;
                using ValueType = PointerValueT<T*>;
    
                /** The rebinded pointer type */
                template <class K>
                using Rebind = K*;
                
                /** The rebinded pointer traits */
                template <class K>
                using RebindTraits = PointerTraits<Rebind<K>>;
            };

            /**
             * @struct AllocatorValueTraits
             * @brief Allow uniform access to allocator's value type
             */
            template <class T>
            struct AllocatorValueTraits {
            };
            
            template <class T> requires requires {
                typename T::ValueType;
            } && (!requires {
                typename T::value_type;
            })
            struct AllocatorValueTraits<T> {
                using ValueType = typename T::ValueType;
            };
            
            template <class T> requires requires {
                typename T::value_type;
            } && (!requires {
                typename T::ValueType;
            })
            struct AllocatorValueTraits<T> {
                using ValueType = typename T::value_type;
            };
            
            template <class T> requires requires {
                typename T::ValueType;
                typename T::value_type;
                Concept::SameAs<typename T::ValueType, typename T::value_type>;
            }
            struct AllocatorValueTraits<T> {
                using ValueType = typename T::ValueType;
            };
            
            /** Helper to access AllocatorValueTraits type */
            template <class T>
            using AllocatorValueT = typename AllocatorValueTraits<T>::ValueType;
            
            /**
             * @struct AllocatorPointerTraits
             * @brief ALlow uniform access to allocator's pointer type
             */
            template <class T>
            struct AllocatorPointerTraits {
            };
            
            template <class T> requires requires {
                typename T::Pointer;
            } && (!requires {
                typename T::pointer;
            })
            struct AllocatorPointerTraits<T> {
                using Pointer = typename T::Pointer;
            };
            
            template <class T> requires requires {
                typename T::pointer;
            } && (!requires {
                typename T::Pointer;
            })
            struct AllocatorPointerTraits<T> {
                using Pointer = typename T::pointer;
            };
            
            template <class T> requires requires {
                typename T::pointer;
                typename T::Pointer;
                Concept::SameAs<typename T::pointer, typename T::Pointer>;
            }
            struct AllocatorPointerTraits<T> {
                using Pointer = typename T::Pointer;
            };
            
            template <class T> requires requires {
                typename AllocatorValueT<T>;
            } && (!requires {
                typename T::pointer;
                typename T::Pointer;
                Concept::SameAs<typename T::pointer, typename T::Pointer>;
            })
            struct AllocatorPointerTraits<T> {
                using Pointer = AllocatorValueT<T>;
            };
            
            /** Helper to access AllocatorPointerTraits type */
            template <class T>
            using AllocatorPointerT = typename AllocatorPointerTraits<T>::Pointer;
            
            /**
             * @struct AllocatorConstPointerTraits
             * @brief Allow uniform access to allocator's const pointer type
             */
            template <class T>
            struct AllocatorConstPointerTraits {
            };
            
            template <class T> requires requires {
                typename T::ConstPointer;
            } && (!requires {
                typename T::const_pointer;
            })
            struct AllocatorConstPointerTraits<T> {
                using ConstPointer = typename T::ConstPointer;
            };
            
            template <class T> requires requires {
                typename T::const_pointer;
            } && (!requires {
                typename T::ConstPointer;
            })
            struct AllocatorConstPointerTraits<T> {
                using ConstPointer = typename T::const_pointer;
            };
            
            template <class T> requires requires {
                typename T::ConstPointer;
                typename T::const_pointer;
                Concept::SameAs<typename T::ConstPointer, typename T::const_pointer>;
            }
            struct AllocatorConstPointerTraits<T> {
                using ConstPointer = typename T::ConstPointer;
            };
            
            template <class T> requires requires {
                typename AllocatorValueT<T>;
                typename AllocatorPointerT<T>;
            } && (!requires {
                typename T::DifferenceType;
                typename T::difference_type;
                Concept::SameAs<typename T::ConstPointer, typename T::const_pointer>;
            })
            struct AllocatorConstPointerTraits<T> {
                using ConstPointer = typename PointerTraits<AllocatorPointerT<T>>::Rebind<const AllocatorValueT<T>>;
            };
            
            /** Helper to access AllocatorConstPointerTraits type */
            template <class T>
            using AllocatorConstPointerT = typename AllocatorConstPointerTraits<T>;
            
            template <class T>
            struct AllocatorDifferenceTraits {
            };
            
            template <class T> requires requires {
                typename T::DifferenceType;
            } && (!requires {
                typename T::difference_type;
            })
            struct AllocatorDifferenceTraits<T> {
                using DifferenceType = typename T::DifferenceType;
            };
            
            template <class T> requires requires {
                typename T::difference_type;
            } && (!requires {
                typename T::DifferenceType;
            })
            struct AllocatorDifferenceTraits<T> {
                using DifferenceType = typename T::difference_type;
            };
            
            template <class T> requires requires {
                typename T::DifferenceType;
                typename T::difference_type;
                Concept::SameAs<typename T::DifferenceType, typename T::difference_type>;
            }
            struct AllocatorDifferenceTraits<T> {
                using DifferenceType = typename T::DifferenceType;
            };
            
            template <class T> requires requires {
                typename AllocatorPointerT<T>;
            } && (!requires {
                typename T::DifferenceType;
                typename T::difference_type;
                Concept::SameAs<typename T::DifferenceType, typename T::difference_type>;
            })
            struct AllocatorDifferenceTraits<T> {
                using DifferenceType = PointerTraits<AllocatorPointerT<T>>::DifferenceType;
            };
            
            /** Helper to access AllocatorDifferenceTraits type */
            template <class T>
            using AllocatorDifferenceT = typename AllocatorDifferenceTraits<T>::DifferenceType;
            
            /**
             * @struct AllocatorSizeTraits
             * @brief Allow uniform access to allocator's size type
             */
            template <class T>
            struct AllocatorSizeTraits {
            };
            
            template <class T> requires requires {
                typename T::SizeType;
            } && (!requires {
                typename T::size_type;
            })
            struct AllocatorSizeTraits<T> {
                using SizeType = typename T::SizeType;
            };
            
            template <class T> requires requires {
                typename T::size_type;
            } && (!requires {
                typename T::SizeType;
            })
            struct AllocatorSizeTraits<T> {
                using SizeType = typename T::size_type;
            };
            
            template <class T> requires requires {
                typename T::SizeType;
                typename T::size_type;
                Concept::SameAs<typename T::SizeType, typename T::size_type>;
            }
            struct AllocatorSizeTraits<T> {
                using SizeType = typename T::SizeType;
            };
            
            template <class T> requires {
                typename AllocatorDifferenceT<T>;
            } && (!requires {
                typename T::SizeType;
                typename T::size_type;
                Concept::SameAs<typename T::SizeType, typename T::size_type>;
            })
            struct AllocatorSizeTraits<T> {
                using SizeType = Core::MakeUnsignedT<AllocatorDifferenceT<T>>;
            };
            
            /** Helper to access AllocatorSizeTraits type */
            template <class T>
            using AllocatorSizeT = typename AllocatorSizeTraits<T>::SizeType;
            
            /**
             * @struct AllocatorTraits
             * @brief Allow uniform access to all allocator's traits
             */
            template <class T>
            struct AllocatorTraits {
                using ValueType = AllocatorValueT<T>;
                using Pointer = AllocatorPointerT<T>;
                using ConstPointer = AllocatorConstPointerT<T>;
                using DifferenceType = AllocatorDifferenceT<T>;
                using SizeType = AllocatorSizeT<T>;
                
                template <class K>
                using Rebind = typename T::Rebind<K>;
                
                template <class K>
                using RebindTraits = AllocatorTraits<Rebind<K>>;
            };
            
            template <template <class, class ...> class M, class T, class ... Args>
            struct AllocatorTraits <M<T, Args...>> {
                using ValueType = AllocatorValueT<M<T, Args...>>;
                using Pointer = AllocatorPointerT<M<T, Args...>>;
                using ConstPointer = AllocatorConstPointerT<M<T, Args...>>;
                using DifferenceType = AllocatorDifferenceT<M<T, Args...>>;
                using SizeType = AllocatorSizeT<M<T, Args...>>;
    
                template <class K>
                using Rebind = M<K, Args...>;
    
                template <class K>
                using RebindTraits = AllocatorTraits<Rebind<K>>;
            };
        }
    }