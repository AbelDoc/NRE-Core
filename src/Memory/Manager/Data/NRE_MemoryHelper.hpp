    
    /**
     * @file NRE_MemoryHelper.hpp
     * @brief Declaration of Memory's API's Object : MemoryHelper
     * @author Louis ABEL
     * @date 21/03/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include <Core/Interfaces/Uncopyable/NRE_Uncopyable.hpp>
    
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
             * @class MemoryHelper
             * @brief Store a memory pointer, need to be used from derived class
             */
            class MemoryHelper : public Core::Uncopyable<MemoryHelper> {
                protected : // Fields
                    void* data; /**< The stored pointer */
                
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the helper from it's data
                         * @param d the data to store
                         */
                        MemoryHelper(void* d) : data(d) {
                        }
    
                    //## Move Constructor ##//
                        /**
                         * Move m into this
                         * @param m the helper to move
                         */
                        MemoryHelper(MemoryHelper && m) : data(m.data) {
                            m.data = nullptr;
                        }
                    
                    //## Deconstructor ##//
                        /**
                         * MemoryHelper Deconstructor
                         */
                        virtual ~MemoryHelper() = default;
    
                    //## Getter ##//
                        /**
                         * @return the stored pointer
                         */
                        void* getData() const {
                            return data;
                        }
    
                    //## Methods ##//
                        /**
                         * Free the stored pointer, only the memory manager should call this function
                         */
                        virtual void free() = 0;
    
                    //## Assignment Operator ##//
                        /**
                         * Move m into this
                         * @param m the helper to move into this
                         * @return    the reference of himself
                         */
                        MemoryHelper& operator =(MemoryHelper && m) {
                            if (this != &m) {
                                data = m.data;
                                m.data = nullptr;
                            }
                            return *this;
                        }
            };
        
        }
    }