    
    /**
     * @file NRE_DefaultAllocator.hpp
     * @brief Declaration of Memory's API's Object : DefaultAllocator
     * @author Louis ABEL
     * @date 14/03/2020
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
             * @class DefaultAllocator
             * @brief Default allocator using global new and delete
             */
            template <class T>
            class DefaultAllocator : public AllocatorTraits<DefaultAllocator<T>> {
                public:     // Traits
                    /** Inherited allocator traits */
                    using Traits = AllocatorTraits<DefaultAllocator<T>>;
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
                        DefaultAllocator() noexcept = default;
                        
                    //## Convertor ##//
                        /**
                         * Convert a K-type allocator into a T-type allocator
                         * @param alloc the allocator to convert
                         */
                        template <class K>
                        DefaultAllocator(DefaultAllocator<K> const& alloc) noexcept;
                        
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
            
            #ifndef NRE_USE_MEMORY_MANAGER
                /** Hide Allocator real implementation */
                template <class T>
                using Allocator = DefaultAllocator<T>;
            #endif
            
        }
    }

    #include "NRE_DefaultAllocator.tpp"