    
    /**
     * @file NRE_AllocatorBase.hpp
     * @brief Declaration of Memory's API's Interface : AllocatorBase
     * @author Louis ABEL
     * @date 14/03/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <limits>
    #include <type_traits>
    #include <utility>
    #include <Core/Interfaces/NRE_StaticInterface.hpp>
    
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
             * @class AllocatorBase
             * @brief Describe an allocator object
             */
            template <class Alloc>
            class AllocatorBase {
            };
            /**
             * @class AllocatorBase
             * @brief Describe an allocator object
             */
            template <template <class, class ...> class Alloc, class T, class ... AllocArgs>
            class AllocatorBase<Alloc<T, AllocArgs...>> : public Core::StaticInterface<AllocatorBase<Alloc<T, AllocArgs...>>> {
                public:     // Traits
                    /** The allocator type */
                    using AllocatorType = Alloc<T, AllocArgs...>;
                    /** The allocated type */
                    using ValueType     = T;
                    /** The pointer on allocated type */
                    using Pointer       = T*;
                    /** The pointer on constant allocated type */
                    using ConstPointer  = const T*;
                    /** The allocator size type */
                    using SizeType      = std::size_t;
                    
                    /**
                     * @class Rebinded
                     * Allow to rebind the given allocator to another type while keeping other arguments
                     */
                    template <class K>
                    struct Rebinded {
                        /** The rebinded allocator type */
                        using Type = Alloc<K, AllocArgs...>;
                    };
    
                    /** The rebinded allocator type */
                    template <class K>
                    using Rebind = typename Rebinded<K>::Type;
                    
                public: // Methods
                    //## Getter ##//
                        /**
                         * @return the maximum allocation size
                         */
                        [[nodiscard]] SizeType getMaxSize() const noexcept {
                            return std::numeric_limits<std::size_t>::max() / sizeof(ValueType);
                        }
                        /**
                         * Retrieve the address of an object
                         * @param object the object to return his address
                         * @return       the object's address
                         */
                        [[nodiscard]] Pointer getAddress(ValueType& object) const noexcept {
                            return std::addressof(object);
                        }
                        /**
                         * Retrieve the address of an object
                         * @param object the object to return his address
                         * @return       the object's address
                         */
                        [[nodiscard]] ConstPointer getAddress(ValueType const& object) const noexcept {
                            return std::addressof(object);
                        }
    
                    //## Methods ##//
                        /**
                         * Allocate n * sizeof(T) bytes
                         * @param n the number of object
                         * @return  a pointer on the first allocated bytes
                         */
                        [[nodiscard]] Pointer allocate(SizeType n = 1) {
                            return this->impl().allocate(n);
                        }
                        /**
                         * Deallocate a pointer given by an allocate call
                         * @param p the pointer on the first bytes allocated
                         */
                        void deallocate(Pointer p) {
                            this->impl().deallocate(p);
                        }
                        /**
                         * Deallocate a pointer given by an allocate call
                         * @param p the pointer on the first bytes allocated
                         * @param n the number of object allocated
                         */
                        void deallocate(Pointer p, SizeType n) {
                            this->impl().deallocate(p, n);
                        }
                        /**
                         * Construct a K-type object in the given pointer with given arguments
                         * @param p    the pointer to construct the object
                         * @param args the construction arguments
                         * @return     the input pointer
                         */
                        template <class K, class ... Args>
                        K* construct(K* p, Args && ... args) {
                            return this->impl().construct(p, std::forward<Args>(args)...);
                        }
                        /**
                         * Destroy an given to the given pointer
                         * @param p the object address
                         * @return  the input pointer
                         */
                        template <class K>
                        K* destroy(K* p) {
                            return this->impl().destroy(p);
                        }
            };
    
            /**
             * @class IsAllocator
             * @brief Check if the given template is an allocator class
             */
            template <class T>
            struct IsAllocator : std::is_base_of<AllocatorBase<T>, T> {
            };
    
            /** Shortcut to check if a template is an allocator */
            template <class T>
            constexpr bool IsAllocatorV = IsAllocator<T>::value;
        }
    }