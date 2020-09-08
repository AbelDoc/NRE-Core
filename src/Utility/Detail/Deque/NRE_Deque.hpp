    
    /**
     * @file Detail/Deque/NRE_Deque.hpp
     * @brief Declaration of Utility's API's Container : Deque
     * @author Louis ABEL
     * @date 8/09/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <stdexcept>
    #include <utility>
    #include <cstring>
    #include <cmath>
    #include "../../Interfaces/Iterator/NRE_IteratorTraits.hpp"
    #include "../../Interfaces/Stringable/NRE_Stringable.hpp"
    #include "../../Traits/NRE_TypeTraits.hpp"
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Utility
         * @brief Utility's API
         */
        namespace Utility {
        
            namespace Detail {
                namespace DequeInner {
                
                    const std::size_t DEQUE_BUFFER_SIZE = 512;
                    
                    /**
                     * Compute the deque buffer size from it's element type size
                     * @param typeSize the element type size in bytes
                     * @return the deque buffer size
                     */
                    constexpr [[nodiscard]] std::size_t getDequeBufferSize(std::size_t typeSize) {
                        return (typeSize < DEQUE_BUFFER_SIZE ? static_cast <std::size_t> (DEQUE_BUFFER_SIZE / typeSize) : static_cast <std::size_t> (1));
                    }
        
                    /**
                     * @class DequeIterator
                     * @brief Internal iterator for deque
                     */
                    template <class T, class Category>
                    class DequeIterator : public IteratorTraits<DequeIterator<T, Category>, T, Category> {
                        public :    // Traits
                            /** Inherited iterator traits */
                            using Traits = IteratorTraits<DequeIterator<T, Category>, T, Category>;
                            /** The iterated object */
                            using ValueType         = typename Traits::ValueType;
                            /** The pointer on iterated object */
                            using Pointer           = typename Traits::Pointer;
                            /** The reference on iterated object */
                            using Reference         = typename Traits::Reference;
                            /** The iterator difference type */
                            using DifferenceType    = typename Traits::DifferenceType;
                            /** The pointer on parent map */
                            using MapPointer        = Pointer*;
                            /** STL compatibility */
                            using value_type        = ValueType;
                            /** STL compatibility */
                            using pointer           = Pointer;
                            /** STL compatibility */
                            using reference         = Reference;
                            /** STL compatibility */
                            using difference_type   = DifferenceType;
                            /** STL compatibility */
                            using iterator_category = typename Traits::iterator_category;
                            
                        private :   // Static
                            static constexpr SizeType BUFFER_SIZE = getDequeBufferSize(sizeof(ValueType));
                        
                        private:    // Fields
                            Pointer current;    /**< The current pointed element */
                            Pointer first;      /**< The first element of the node */
                            Pointer last;       /**< The last element of the node */
                            MapPointer node;    /**< The current iterated node */
    
                        public :    // Methods
                            //## Constructor ##//
                                /**
                                 * Default constructor with nullptr node
                                 */
                                DequeIterator() = default;
            
                            //## Copy Constructor ##//
                                /**
                                 * Copy it into this
                                 * @param it the iterator to copy
                                 */
                                DequeIterator(DequeIterator const& it) = default;
            
                            //## Move Constructor ##//
                                /**
                                 * Move it into this
                                 * @param it the iterator to move
                                 */
                                DequeIterator(DequeIterator && it) = default;
            
                            //## Deconstructor ##//
                                /**
                                 * DequeIterator Deconstructor
                                 */
                                ~DequeIterator() = default;
                                
                            //## Methods ##//
                                /**
                                 * @return a reference on the iterated data
                                 */
                                Reference dereference() const;
                                /**
                                 * Increment the iterator position by one
                                 */
                                void increment();
                                /**
                                 * Decrement the iterator position by one
                                 */
                                void decrement();
                                /**
                                 * Move the iterator by a given number (can be negative)
                                 * @param n the distance to move
                                 */
                                void advance(DifferenceType n);
                                /**
                                 * Tell the distance between the given iterator
                                 * @param it the other iterator
                                 * @return   the distance between it and this
                                 */
                                DifferenceType distanceTo(Iterator const& it) const;
                                /**
                                 * Test if the given iterator point to the same position
                                 * @param it the other iterator
                                 * @return   the test's result
                                 */
                                bool equal(Iterator const& it) const;
                                /**
                                 * Change the iterator node
                                 * @param newNode the new node to iterate over
                                 */
                                void setNode(MapPointer newNode);
                    };
                }
    
                /**
                 * @class Deque
                 * @brief A double ended queue implemented with a dynamic array of fixed size array
                 */
                template <class T, class Allocator>
                class Deque : public Stringable<Deque<T, Allocator>>, public Allocator {
                    static_assert(Memory::IsAllocatorV<Allocator>);                     /**< Check if the given AllocatorType inherit from NRE::Memory::AllocatorTraits */
                    static_assert(std::is_same_v<T, typename Allocator::ValueType>);    /**< Make sure the allocator is set for the container inner type */

                    public :    // Traits
                        /** The container's allocated type */
                        using ValueType             = T;
                        /** The container's allocator */
                        using AllocatorType         = Allocator;
                        /** The object's size type */
                        using SizeType              = std::size_t;
                        /** The object's difference type */
                        using DifferenceType        = std::ptrdiff_t;
                        /** The allocated type reference */
                        using Reference             = ValueType&;
                        /** The allocated type const reference */
                        using ConstReference        = ValueType const&;
                        /** The allocated type pointer */
                        using Pointer               = typename AllocatorType::Pointer;
                        /** The allocated type const pointer */
                        using ConstPointer          = typename AllocatorType::ConstPointer;
                        /** Mutable random access iterator */
                        using Iterator              = DequeInner::DequeIterator<ValueType, InOutRandomAccessIterator>;
                        /** Immuable random access iterator */
                        using ConstIterator         = DequeInner::DequeIterator<ValueType, RandomAccessIterator>;
                        /** Mutable reverse random access iterator */
                        using ReverseIterator       = std::reverse_iterator<Iterator>;
                        /** Immuable reverse random access iterator */
                        using ConstReverseIterator  = std::reverse_iterator<ConstIterator>;
                        /** STL compatibility */
                        using value_type            = ValueType;
                        /** STL compatibility */
                        using allocator_type        = AllocatorType;
                        /** STL compatibility */
                        using size_type             = SizeType;
                        /** STL compatibility */
                        using difference_type       = DifferenceType;
                        /** STL compatibility */
                        using reference             = Reference;
                        /** STL compatibility */
                        using const_reference       = ConstReference;
                        /** STL compatibility */
                        using pointer               = Pointer;
                        /** STL compatibility */
                        using const_pointer         = ConstPointer;
                        /** STL compatibility */
                        using iterator              = Iterator;
                        /** STL compatibility */
                        using const_iterator        = ConstIterator;
                        /** STL compatibility */
                        using reverse_iterator      = ReverseIterator;
                        /** STL compatibility */
                        using const_reverse_iterator= ConstReverseIterator;
                    
                    private :   // Fields
                        Pointer* data;
                };
            }
        }
    }