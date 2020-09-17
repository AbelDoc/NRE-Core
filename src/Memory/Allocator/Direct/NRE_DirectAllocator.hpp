    
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
    #include "../NRE_AllocatorTraits.hpp"
    
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
            class DirectAllocator : public AllocatorTraits<DirectAllocator<T>> {
                public:     // Traits
                    /** Inherited allocator traits */
                    using Traits = AllocatorTraits<DirectAllocator<T>>;
                    /** The allocated type */
                    using ValueType     = typename Traits::ValueType;
                    /** The pointer on allocated type */
                    using Pointer       = typename Traits::Pointer;
                    /** The pointer on constant allocated type */
                    using ConstPointer  = typename Traits::ConstPointer;
                    /** The allocator size type */
                    using SizeType      = typename Traits::SizeType;
    
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
                        /**
                         * Construct a K-type object in the given pointer with given arguments
                         * @param p    the pointer to construct the object
                         * @param args the construction arguments
                         * @return     the input pointer
                         */
                        template <class K, class ... Args>
                        K* construct(K* p, Args && ... args);
                        /**
                         * Destroy an given to the given pointer
                         * @param p the object address
                         * @return  the input pointer
                         */
                        template <class K>
                        K* destroy(K* p);
            };
            
        }
    }

    #include "NRE_DirectAllocator.tpp"