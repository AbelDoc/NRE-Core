    
    /**
     * @file Data/NRE_Memory.hpp
     * @brief Declaration of Memory's API's Object : Memory
     * @author Louis ABEL
     * @date 21/03/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "NRE_MemoryHelper.hpp"
    
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
             * @class Memory
             * @brief Store a memory pointer, and manage it in a typed manner
             */
            template <class T>
            class Memory : public MemoryHelper {
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the memory from it's data
                         * @param d the data to store
                         */
                        Memory(void* d) : MemoryHelper(d) {
                        }
    
                    //## Methods ##//
                        /**
                         * Free the stored pointer, only the memory manager should call this function
                         */
                        void free() override {
                            std::cout << "Deallocating and Deconstruct : " << data << std::endl;
                            T* typed = static_cast <T*> (data);
                            typed->~T();
                            ::free(typed);
                            data = nullptr;
                        }
            };
    
            /**
             * @class Memory
             * @brief Store a memory pointer, and manage it in a typed manner
             */
            template <>
            class Memory<void> : public MemoryHelper {
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the memory from it's data
                         * @param d the data to store
                         */
                        Memory(void* d) : MemoryHelper(d) {
                        }
            
                    //## Methods ##//
                        /**
                         * Free the stored pointer, only the memory manager should call this function
                         */
                        void free() override {
                            std::cout << "Deallocating but can't deconstruct : " << data << std::endl;
                            ::free(data);
                            data = nullptr;
                        }
            };
        
        }
    }