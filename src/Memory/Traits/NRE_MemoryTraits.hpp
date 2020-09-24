    
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
    
            template <template <class, class...> class M, class T, class ... Args>
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
                typename T::Pointer;
                typename T::pointer;
                Concept::SameAs<typename T::pointer, typename T::Pointer>;
            }
            struct AllocatorPointerTraits<T> {
                using Pointer = typename T::Pointer;
            };
    
            template <class T> requires requires {
                typename AllocatorValueT<T>;
            } && (!requires {
                typename T::Pointer;
            } && !requires {
                typename T::pointer;
            } && !requires {
                typename T::Pointer;
                typename T::pointer;
                Concept::SameAs<typename T::Pointer, typename T::pointer>;
            })
            struct AllocatorPointerTraits<T> {
                using Pointer = AllocatorValueT<T>*;
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
                typename T::ConstPointer;
            } && !requires {
                typename T::const_pointer;
            } && !requires {
                typename T::ConstPointer;
                typename T::const_pointer;
                Concept::SameAs<typename T::ConstPointer, typename T::const_pointer>;
            })
            struct AllocatorConstPointerTraits<T> {
                using ConstPointer = typename PointerTraits<AllocatorPointerT<T>>::Rebind<const AllocatorValueT<T>>;
            };
    
            /** Helper to access AllocatorConstPointerTraits type */
            template <class T>
            using AllocatorConstPointerT = typename AllocatorConstPointerTraits<T>::ConstPointer;
    
            /**
             * @struct AllocatorVoidPointerTraits
             * @brief Allow uniform access to allocator's void pointer type
             */
            template <class T>
            struct AllocatorVoidPointerTraits {
            };
    
            template <class T> requires requires {
                typename T::VoidPointer;
            } && (!requires {
                typename T::void_pointer;
            })
            struct AllocatorVoidPointerTraits<T> {
                using VoidPointer = typename T::VoidPointer;
            };
    
            template <class T> requires requires {
                typename T::void_pointer;
            } && (!requires {
                typename T::VoidPointer;
            })
            struct AllocatorVoidPointerTraits<T> {
                using VoidPointer = typename T::void_pointer;
            };
    
            template <class T> requires requires {
                typename T::VoidPointer;
                typename T::void_pointer;
                Concept::SameAs<typename T::VoidPointer, typename T::void_pointer>;
            }
            struct AllocatorVoidPointerTraits<T> {
                using VoidPointer = typename T::VoidPointer;
            };
    
            template <class T> requires requires {
                typename AllocatorPointerT<T>;
            } && (!requires {
                typename T::VoidPointer;
            } && !requires {
                typename T::void_pointer;
            } && !requires {
                typename T::VoidPointer;
                typename T::void_pointer;
                Concept::SameAs<typename T::VoidPointer, typename T::void_pointer>;
            })
            struct AllocatorVoidPointerTraits<T> {
                using VoidPointer = typename PointerTraits<AllocatorPointerT<T>>::Rebind<void>;
            };
    
            /** Helper to access AllocatorVoidPointerTraits type */
            template <class T>
            using AllocatorVoidPointerT = typename AllocatorVoidPointerTraits<T>::VoidPointer;
    
            /**
             * @struct AllocatorConstVoidPointerTraits
             * @brief Allow uniform access to allocator's const void pointer type
             */
            template <class T>
            struct AllocatorConstVoidPointerTraits {
            };
    
            template <class T> requires requires {
                typename T::ConstVoidPointer;
            } && (!requires {
                typename T::const_void_pointer;
            })
            struct AllocatorConstVoidPointerTraits<T> {
                using ConstVoidPointer = typename T::ConstVoidPointer;
            };
    
            template <class T> requires requires {
                typename T::const_void_pointer;
            } && (!requires {
                typename T::ConstVoidPointer;
            })
            struct AllocatorConstVoidPointerTraits<T> {
                using ConstVoidPointer = typename T::const_void_pointer;
            };
    
            template <class T> requires requires {
                typename T::ConstVoidPointer;
                typename T::const_void_pointer;
                Concept::SameAs<typename T::ConstVoidPointer, typename T::const_void_pointer>;
            }
            struct AllocatorConstVoidPointerTraits<T> {
                using ConstVoidPointer = typename T::ConstVoidPointer;
            };
    
            template <class T> requires requires {
                typename AllocatorPointerT<T>;
            } && (!requires {
                typename T::ConstVoidPointer;
            } && !requires {
                typename T::const_void_pointer;
            } && !requires {
                typename T::ConstVoidPointer;
                typename T::const_void_pointer;
                Concept::SameAs<typename T::ConstVoidPointer, typename T::const_void_pointer>;
            })
            struct AllocatorConstVoidPointerTraits<T> {
                using ConstVoidPointer = typename PointerTraits<AllocatorPointerT<T>>::Rebind<const void>;
            };
    
            /** Helper to access AllocatorConstVoidPointerTraits type */
            template <class T>
            using AllocatorConstVoidPointerT = typename AllocatorConstVoidPointerTraits<T>::ConstVoidPointer;
    
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
            } && !requires {
                typename T::difference_type;
            } && !requires {
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
    
            template <class T> requires requires {
                typename AllocatorDifferenceT<T>;
            } && (!requires {
                typename T::SizeType;
            } && !requires {
                typename T::size_type;
            } && !requires {
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
        }
        /**
         * @namespace Concept
         * @brief Concept's API
         */
        namespace Concept {
    
            /**
             * @interface Allocator
             * @brief Define an allocator type which need to have several members functions
             */
            template <class T>
            concept Allocator = requires {
                typename Memory::AllocatorSizeT<T>;
                typename Memory::AllocatorPointerT<T>;
            } && requires(T t, Memory::AllocatorSizeT<T> n) {
                { t.allocate(n) } -> SameAs<Memory::AllocatorPointerT<T>>;
            } && requires(T t, Memory::AllocatorPointerT<T> p, Memory::AllocatorSizeT<T> n) {
                { t.deallocate(p, n) } -> SameAs<void>;
            };
        }
        /**
         * @namespace Memory
         * @brief Memory's API
         */
        namespace Memory {
            
            /**
             * @struct AllocatorHintAllocationHepler
             * @brief Allow to verify if an allocator can use the hint allocation
             */
            template <Concept::Allocator T>
            struct AllocatorHintAllocationHelper {
                /**
                 * Allocate n bytes of uninitialized memory with the given allocator, call to simple allocate as hint allocation is not supported
                 * @param a the used allocator
                 * @param n the number of bytes to allocate
                 * @return a pointer returned by a.allocate(n, hint)
                 */
                [[nodiscard]] static constexpr AllocatorPointerT<T> allocate(T& a, AllocatorSizeT<T> n, AllocatorConstVoidPointerT<T>) {
                    return a.allocate(n);
                }
            };
    
            template <Concept::Allocator T> requires requires (T t, AllocatorSizeT<T> n, AllocatorConstVoidPointerT<T> hint) {
                { t.allocate(n, hint) } -> Concept::SameAs<AllocatorPointerT<T>>;
            }
            struct AllocatorHintAllocationHelper<T> {
                /**
                 * Allocate n bytes of uninitialized memory with the given allocator using the hint address
                 * @param a    the used allocator
                 * @param n    the number of bytes to allocate
                 * @param hint an address which can be used by the allocator to allocate nearby
                 * @return a pointer returned by a.allocate(n, hint)
                 */
                [[nodiscard]] static constexpr AllocatorPointerT<T> allocate(T& a, AllocatorSizeT<T> n, AllocatorConstVoidPointerT<T> hint) {
                    return a.allocate(n, hint);
                }
            };
            
            /**
             * @struct AllocatorTraits
             * @brief Allow uniform access to all allocator's traits
             */
            template <Concept::Allocator T>
            struct AllocatorTraits {
                using AllocatorType = T;
                using ValueType = AllocatorValueT<T>;
                using Pointer = AllocatorPointerT<T>;
                using ConstPointer = AllocatorConstPointerT<T>;
                using VoidPointer = AllocatorVoidPointerT<T>;
                using ConstVoidPointer = AllocatorConstVoidPointerT<T>;
                using DifferenceType = AllocatorDifferenceT<T>;
                using SizeType = AllocatorSizeT<T>;
                
                template <class K>
                using Rebind = typename T::Rebind<K>;
                
                template <class K>
                using RebindTraits = AllocatorTraits<Rebind<K>>;
                
                /**
                 * Allocate n bytes of uninitialized memory with the given allocator
                 * @param a the used allocator
                 * @param n the number of bytes to allocate
                 * @return a pointer returned by a.allocate(n)
                 */
                [[nodiscard]] static constexpr Pointer allocate(AllocatorType& a, SizeType n) {
                    return a.allocate(n);
                }
                /**
                 * Allocate n bytes of uninitialized memory with the given allocator using the hint address
                 * @param a    the used allocator
                 * @param n    the number of bytes to allocate
                 * @param hint an address which can be used by the allocator to allocate nearby
                 * @return a pointer returned by a.allocate(n, hint)
                 */
                [[nodiscard]] static constexpr Pointer allocate(AllocatorType& a, SizeType n, ConstVoidPointer hint) {
                    return AllocatorHintAllocationHelper<AllocatorType>::allocate(a, n, hint);
                }
                /**
                 * Deallocate n bytes from a given address alocated with the given allocator
                 * @param a the allocator responsible from p's allocation
                 * @param p the memory address for the deallocation
                 * @param n the number of bytes to deallocate
                 */
                static constexpr void deallocate(AllocatorType& a, Pointer p, SizeType n) {
                    a.deallocate(p, n);
                }
            };
            
            template <template <class, class ...> class M, class T, class ... Args> requires Concept::Allocator<M<T, Args...>>
            struct AllocatorTraits <M<T, Args...>> {
                using AllocatorType = M<T, Args...>;
                using ValueType = AllocatorValueT<M<T, Args...>>;
                using Pointer = AllocatorPointerT<M<T, Args...>>;
                using ConstPointer = AllocatorConstPointerT<M<T, Args...>>;
                using DifferenceType = AllocatorDifferenceT<M<T, Args...>>;
                using VoidPointer = AllocatorVoidPointerT<M<T, Args...>>;
                using ConstVoidPointer = AllocatorConstVoidPointerT<M<T, Args...>>;
                using SizeType = AllocatorSizeT<M<T, Args...>>;
    
                template <class K>
                using Rebind = M<K, Args...>;
    
                template <class K>
                using RebindTraits = AllocatorTraits<Rebind<K>>;
    
                /**
                 * Allocate n bytes of uninitialized memory with the given allocator
                 * @param a the used allocator
                 * @param n the number of bytes to allocate
                 * @return a pointer returned by a.allocate(n)
                 */
                [[nodiscard]] static constexpr Pointer allocate(AllocatorType& a, SizeType n) {
                    return a.allocate(n);
                }
                /**
                 * Allocate n bytes of uninitialized memory with the given allocator using the hint address
                 * @param a    the used allocator
                 * @param n    the number of bytes to allocate
                 * @param hint an address which can be used by the allocator to allocate nearby
                 * @return a pointer returned by a.allocate(n, hint)
                 */
                [[nodiscard]] static constexpr Pointer allocate(AllocatorType& a, SizeType n, ConstVoidPointer hint) {
                    return AllocatorHintAllocationHelper<AllocatorType>::allocate(a, n, hint);
                }
                /**
                 * Deallocate n bytes from a given address alocated with the given allocator
                 * @param a the allocator responsible from p's allocation
                 * @param p the memory address for the deallocation
                 * @param n the number of bytes to deallocate
                 */
                static constexpr void deallocate(AllocatorType& a, Pointer p, SizeType n) {
                    a.deallocate(p, n);
                }
            };
        }
    }