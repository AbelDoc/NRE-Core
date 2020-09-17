    
    /**
     * @file Detail/Deque/NRE_Deque.hpp
     * @brief Declaration of Core's API's Container : Deque
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
         * @namespace Core
         * @brief Core's API
         */
        namespace Core {
        
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
                        /** The container's map allocator */
                        using MapAllocator          = typename Allocator::Rebind<T*>::Type;
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
                        /** The pointer on parent map */
                        using MapPointer            = Pointer*;
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

                    private :   // Static
                        static constexpr SizeType BUFFER_SIZE = Iterator::BUFFER_SIZE;
                        static constexpr SizeType INITIAL_MAP_SIZE = 8;
                    
                    private :   // Fields
                        Pointer* map;
                        SizeType mapSize;
                        Iterator start;
                        Iterator finish;
                        
                    public :    // Methods
                        //## Constructor ##//
                            /**
                             * Construct an empty deque with a base capacity
                             * @param alloc the deque's memory allocator
                             */
                            Deque(Allocator const& alloc = Allocator());
                            /**
                             * Construct a deque filled with count copy of value
                             * @param count the number of copy to perform
                             * @param value the value to fill the deque with
                             * @param alloc the deque's memory allocator
                             */
                            Deque(SizeType count, ConstReference value, Allocator const& alloc = Allocator());
                            /**
                             * Construct a deque filled with count default value
                             * @param count the number of default element
                             * @param alloc the deque's memory allocator
                             */
                            Deque(SizeType count, Allocator const& alloc = Allocator());
                            /**
                             * Construct a deque filled with element between 2 iterators
                             * @param begin the begin iterator
                             * @param end   the end iterator, pointing after the last element
                             * @param alloc the deque's memory allocator
                             */
                            template <class InputIterator>
                            Deque(InputIterator begin, InputIterator end, Allocator const& alloc = Allocator());
                            /**
                             * Construct a deque from an initializer list
                             * @param init  the list to fill the deque with
                             * @param alloc the deque's memory allocator
                             */
                            Deque(std::initializer_list<T> init, Allocator const& alloc = Allocator());
    
                        //## Copy Constructor ##//
                            /**
                             * Copy d into this
                             * @param d the deque to copy
                             */
                            Deque(Deque const& d);
                            /**
                             * Copy d into this
                             * @param d     the deque to copy
                             * @param alloc the deque's memory allocator
                             */
                            Deque(Deque const& d, Allocator const& alloc);
        
                        //## Move Constructor ##//
                            /**
                             * Move d into this
                             * @param d the deque to move
                             */
                            Deque(Deque && d);
                            /**
                             * Move d into this
                             * @param d     the deque to move
                             * @param alloc the deque's memory allocator
                             */
                            Deque(Deque && d, Allocator const& alloc);
        
                        //## Deconstructor ##//
                            /**
                             * Deque Deconstructor
                             */
                            ~Deque();
                            
                    private :   // Methods
                        /**
                         * Initialize the map memory layout
                         * @param nbElements the start number of elements in the map
                         */
                        void initializeMap(SizeType nbElements);
                        /**
                         * Allocate and create nodes between 2 addresses
                         * @param begin the begin address
                         * @param end   the end address
                         */
                        void createNodes(Pointer* begin, Pointer* end);
                        /**
                         * Deallocate nodes between 2 address
                         * @param begin the begin address
                         * @param end   the end address
                         */
                        void destroyNodes(Pointer* begin, Pointer* end);
                        /**
                         * @return a new allocated node
                         */
                        Pointer allocateNode();
                        /**
                         * Deallocate a node
                         * @param p the node's pointer
                         */
                        void deallocateNode(Pointer p);
                        /**
                         * Allocate a map layout
                         * @param nbElements the number of nodes in the map
                         * @return the allocated map
                         */
                        MapPointer allocateMap(SizeType nbElements);
                        /**
                         * Deallocate a map layout
                         * @param p          the map's pointer
                         * @param nbElements the number of nodes in the map
                         */
                        void deallocateMap(MapPointer p, SizeType nbElements);
                        /**
                         * Copy the content of d
                         * @param d the deque to copy
                         */
                        void copy(Deque const& d);
                        
                            
                };
            }
        }
    }