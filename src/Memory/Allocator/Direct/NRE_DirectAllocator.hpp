    
    /**
     * @file NRE_DirectAllocator.hpp
     * @brief Declaration of Memory's API's Object : DirectAllocator
     * @author Louis ABEL
     * @date 21/03/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include <cassert>
    #include <memory>

    #include "../Traits/NRE_MemoryTraits.hpp"
    
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
             * @class DirectAllocator
             * @brief Allocate memory using malloc and free directly
             */
            template <class T>
            class DirectAllocator {
                public:     // Traits
                    using ValueType = T;
                    using SizeType  = Core::SizeType;
                    using Pointer   = ValueType*;
                    using value_type    = ValueType;
                    using size_type     = SizeType;
                    using pointer       = Pointer;
    
                public:     // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        DirectAllocator() noexcept = default;
            
                    //## Convertor ##//
                        /**
                         * Convert a K-type allocator into a T-type allocator
                         * @param alloc the allocator to convert
                         */
                        template <class K>
                        DirectAllocator(DirectAllocator<K> const& alloc) noexcept;
        
                    //## Methods ##//
                        /**
                         * Allocate n * sizeof(T) bytes
                         * @param n the number of object
                         * @return  a pointer on the first allocated bytes
                         */
                        [[nodiscard]] Pointer allocate(SizeType n = 1);
                        /**
                         * Deallocate a pointer given by an allocate call
                         * @param p the pointer on the first bytes allocated
                         */
                        void deallocate(Pointer p);
                        /**
                         * Deallocate a pointer given by an allocate call
                         * @param p the pointer on the first bytes allocated
                         * @param n the number of object allocated
                         */
                        void deallocate(Pointer p, SizeType n);
            };
            
        }
    }

    #include "NRE_DirectAllocator.tpp"