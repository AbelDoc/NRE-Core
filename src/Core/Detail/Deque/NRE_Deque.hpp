    
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

    #include "../../Interfaces/Stringable/NRE_Stringable.hpp"
    #include "../../../Memory/Traits/NRE_MemoryTraits.hpp"
    #include "../../Algorithm/NRE_Algorithm.hpp"
    
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
                
                    const SizeType DEQUE_BUFFER_SIZE = 512;
                    
                    /**
                     * @return the deque buffer size
                     */
                    template <class T>
                    constexpr [[nodiscard]] SizeType getDequeBufferSize() {
                        return (sizeof(T) < DEQUE_BUFFER_SIZE ? static_cast <SizeType> (DEQUE_BUFFER_SIZE / sizeof(T))
                                                              : static_cast <SizeType> (1));
                    }
        
                    /**
                     * @class DequeIterator
                     * @brief Internal iterator for deque
                     */
                    template <class T>
                    class DequeIterator : public Iterator<DequeIterator<T>, RandomAccessIteratorCategory, T> {
                        public :    // Traits
                            using Base              = Iterator<DequeIterator<It>, RandomAccessIteratorCategory, T>;
                            using DifferenceType    = typename Base::DifferenceType;
                            using ValueType         = typename Base::ValueType;
                            using Pointer           = typename Base::Pointer;
                            using Reference         = typename Base::Reference;
                            using Category          = typename Base::Category;
                            using MapPointer        = Pointer*;
                            using difference_type   = typename Base::difference_type;
                            using value_type        = typename Base::value_type;
                            using pointer           = typename Base::pointer;
                            using reference         = typename Base::reference;
                            using iterator_category = typename Base::iterator_category;
                            using iterator_concept  = typename Base::iterator_concept;
                            
                        private :   // Static
                            static constexpr SizeType BUFFER_SIZE = getDequeBufferSize<ValueType>();
                        
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
    
                        //## Assignment Operator ##//
                            /**
                             * Copy it into this
                             * @param it the deque iterator to copy into this
                             * @return the reference of himself
                             */
                            DequeIterator& operator=(DequeIterator const& it) = default;
                            /**
                             * Move it into this
                             * @param it the deque iterator to move into this
                             * @return the reference of himself
                             */
                            DequeIterator& operator=(DequeIterator && it) = default;
                    };
                }
    
                /**
                 * @class Deque
                 * @brief A double ended queue implemented with a dynamic array of fixed size array
                 */
                template <class T, Concept::Allocator Alloc>
                class Deque : public Stringable<Deque<T, Alloc>>, public Alloc {
                    static_assert(std::is_same_v<T, typename Alloc::ValueType>);    /**< Make sure the allocator is set for the container inner type */

                    public :    // Traits
                        using AllocatorType         = Alloc;
                        using AllocatorTraits       = Memory::AllocatorTraits<AllocatorType>;
                        using ValueType             = typename AllocatorTraits::ValueType;
                        using SizeType              = typename AllocatorTraits::SizeType;
                        using DifferenceType        = typename AllocatorTraits::DifferenceType;
                        using MapAllocator          = typename AllocatorTraits::Rebind<T*>;
                        using MapAllocatorTraits    = typename AllocatorTraits::RebindTraits<T*>;
                        using Reference             = ValueType&;
                        using ConstReference        = ValueType const&;
                        using Pointer               = typename AllocatorTraits::Pointer;
                        using ConstPointer          = typename AllocatorTraits::ConstPointer;
                        using Iterator              = DequeInner::DequeIterator<ValueType>;
                        using ConstIterator         = DequeInner::DequeIterator<const ValueType>;
                        using ReverseIterator       = Core::ReverseIterator<Iterator>;
                        using ConstReverseIterator  = Core::ReverseIterator<ConstIterator>;
                        using MapPointer            = Pointer*;
                        using value_type            = ValueType;
                        using allocator_type        = AllocatorType;
                        using size_type             = SizeType;
                        using difference_type       = DifferenceType;
                        using reference             = Reference;
                        using const_reference       = ConstReference;
                        using pointer               = Pointer;
                        using const_pointer         = ConstPointer;
                        using iterator              = Iterator;
                        using const_iterator        = ConstIterator;
                        using reverse_iterator      = ReverseIterator;
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
                            Deque(AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a deque filled with count copy of value
                             * @param count the number of copy to perform
                             * @param value the value to fill the deque with
                             * @param alloc the deque's memory allocator
                             */
                            Deque(SizeType count, ConstReference value, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a deque filled with count default value
                             * @param count the number of default element
                             * @param alloc the deque's memory allocator
                             */
                            Deque(SizeType count, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a deque filled with element between 2 iterators
                             * @param begin the begin iterator
                             * @param end   the end iterator, pointing after the last element
                             * @param alloc the deque's memory allocator
                             */
                            template <Concept::InputIterator It, Concept::SentinelFor<It> S>
                            Deque(It begin, S end, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a deque filled with element from a given range
                             * @param range the input range
                             * @param alloc the deque's memory allocator
                             */
                            template <Concept::InputRange R>
                            Deque(R && range, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a deque from an initializer list
                             * @param init  the list to fill the deque with
                             * @param alloc the deque's memory allocator
                             */
                            Deque(std::initializer_list<T> init, AllocatorType const& alloc = AllocatorType());
    
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
                            Deque(Deque const& d, AllocatorType const& alloc);
        
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
                            Deque(Deque && d, AllocatorType const& alloc);
        
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
                        
                            
                };
            }
        }
    }

    #include "NRE_Deque.tpp"
