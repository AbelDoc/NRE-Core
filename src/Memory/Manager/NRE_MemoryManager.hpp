    
    /**
     * @file NRE_MemoryManager.hpp
     * @brief Declaration of Memory's API's Object : MemoryManager
     * @author Louis ABEL
     * @date 21/03/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <algorithm>
    #include <Core/Singleton/NRE_Singleton.hpp>
    #include <Core/Detail/Vector/NRE_Vector.hpp>
    #include "../Allocator/Direct/NRE_DirectAllocator.hpp"

    #include "Data/NRE_Memory.hpp"
    
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
             * @class MemoryManager
             * @brief Store current allocated memory and tell if any memory leak occurs
             */
            class MemoryManager {
                private:    // Fields
                    Core::Detail::Vector<MemoryHelper*, DirectAllocator<MemoryHelper*>> allocated;   /**< Store all allocated pointer */
        
                public :    // Methods
                    //## Methods ##//
                        /**
                         * Store a memory pointer
                         * @param data the pointer to memory
                         */
                        template <class T>
                        void storeMemory(T* data) {
                            DirectAllocator<Memory<T>> alloc;
                            allocated.emplaceBack(alloc.construct(alloc.allocate(1), data));
                        }
                        /**
                         * Remove a memory pointer
                         * @param data the pointer to memory
                         */
                        template <class T>
                        void removeMemory(T* data) {
                            MemoryHelper* toRemove = nullptr;
                            for (MemoryHelper* mem : allocated) {
                                if (mem->getData() == data) {
                                    toRemove = mem;
                                    break;
                                }
                            }
                            if (toRemove != nullptr) {
                                allocated.erase(std::remove(allocated.begin(), allocated.end(), toRemove), allocated.end());
                                delete toRemove;
                            }
                        }

            public:   // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        MemoryManager() = default;
            
                    //## Deconstructor ##//
                        /**
                         * MemoryManager Deconstructor
                         */
                        ~MemoryManager() {
                            if (allocated.isEmpty()) {
                                std::cout << "Everything's fine !" << std::endl;
                            } else {
                                for (MemoryHelper* p : allocated) {
                                    std::cout << "Memory at : " << p->getData() << " has not been freed !" << std::endl;
                                    p->free();
            
                                    p->~MemoryHelper();
                                    free(p);
                                }
                            }
                        }
                    
                public :    // Static
                    static MemoryManager& _memoryManager;    /**< The unique memory manager instance */
                    
                    /**
                     * Store a memory pointer
                     * @param data the pointer to memory
                     */
                    template <class T>
                    static void store(T* data) {
                        _memoryManager.storeMemory(data);
                    }
                    /**
                     * Remove a memory pointer
                     * @param data the pointer to memory
                     */
                    template <class T>
                    static void remove(T* data) {
                        _memoryManager.removeMemory(data);
                    }
            };
            
            inline int _memoryManagerNiftyCounter = 0;                                                                          /**< Nifty counter to manage memory manager initialization */
            inline typename std::aligned_storage<sizeof (MemoryManager), alignof (MemoryManager)>::type _memoryManagerBuffer;   /**< Memory manager buffer */
            inline MemoryManager& MemoryManager::_memoryManager = reinterpret_cast<MemoryManager&> (_memoryManagerBuffer);      /**< Initialize memory manager with buffer */
            
            /**
             * @struct MemoryManagerInitializer
             * @brief Manage MemoryManager initialization using nifty counter
             */
            static struct MemoryManagerInitializer {
                MemoryManagerInitializer() {
                    if (_memoryManagerNiftyCounter++ == 0) {
                        new (&MemoryManager::_memoryManager) MemoryManager();
                    }
                }
                ~MemoryManagerInitializer() {
                    if (--_memoryManagerNiftyCounter == 0) {
                        (&MemoryManager::_memoryManager)->~MemoryManager();
                    }
                }
            } _memoryManagerInitializer;
            
        }
    }

    #ifdef NRE_USE_MEMORY_MANAGER
        /**
         * Allocate a given number of bytes
         * @param size the number of bytes to allocate
         * @return     a pointer on the first allocated byte
         */
        [[nodiscard]] inline void* operator new(std::size_t size) {
            if (void* data = malloc(size)) {
                NRE::Memory::MemoryManager::store(data);
                return data;
            }
            throw std::bad_alloc();
        }
        /**
         * Delete a raw pointer
         * @param p the pointer to free
         */
        inline void operator delete(void* p) noexcept {
            NRE::Memory::MemoryManager::remove(p);
            free(p);
        }
        /**
         * Delete a raw pointer
         * @param p the pointer to free
         * @param n the allocated size
         */
        inline void operator delete(void* p, std::size_t n) noexcept {
            (void)n;
            NRE::Memory::MemoryManager::remove(p);
            free(p);
        }
    #endif