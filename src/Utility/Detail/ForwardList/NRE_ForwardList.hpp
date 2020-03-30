
    /**
     * @file Detail/ForwardList/NRE_ForwardList.hpp
     * @brief Declaration of Utility's API's Container : ForwardList
     * @author Louis ABEL
     * @date 10/06/2019
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
                
                namespace ForwardListInner {
                    /**
                     * @class NodeBase
                     * @brief Internal data structure to store forward list node
                     */
                    class NodeBase {
                        public :    // Fields
                            NodeBase* next;    /**< The next node */
        
                        public :    // Methods
                            //## Constructor ##//
                                /**
                                 * Construct the node
                                 * @param node  the next node
                                 */
                                NodeBase(NodeBase* node = nullptr);
                        };
                    /**
                     * @class Node
                     * @brief Internal data structure to store forward list node
                     */
                    template <class T>
                    class Node : public NodeBase {
                        public :    // Fields
                            T data;     /**< The data from the node */
        
                        public :    // Methods
                            //## Constructor ##//
                                /**
                                 * Construct the node
                                 * @param value the node data
                                 * @param node  the next node
                                 */
                                Node(T const& value, NodeBase* node);
                                /**
                                 * Construct the node
                                 * @param value the node data
                                 * @param node  the next node
                                 */
                                Node(T && value, NodeBase* node);
                    };
                    /**
                     * @class ForwardIterator
                     * @brief Internal iterator for forward list
                     */
                    template <class T, class Category>
                    class ForwardIterator : public IteratorTraits<ForwardIterator<T, Category>, T, Category> {
                        public :    // Traits
                            /** Inherited iterator traits */
                            using Traits = IteratorTraits<ForwardIterator<T, Category>, T, Category>;
                            /** The iterated object */
                            using ValueType         = typename Traits::ValueType;
                            /** The pointer on iterated object */
                            using Pointer           = typename Traits::Pointer;
                            /** The reference on iterated object */
                            using Reference         = typename Traits::Reference;
                            /** The iterator difference type */
                            using DifferenceType    = typename Traits::DifferenceType;
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
        
                        private :   // Fields
                            NodeBase* current;      /**< The current iterator node */
        
                        public :    // Methods
                            //## Constructor ##//
                                /**
                                 * Default constructor with nullptr node
                                 */
                                ForwardIterator() = default;
                                /**
                                 * Construct the iterator with the given node
                                 * @param node   the iterator node
                                 */
                                ForwardIterator(NodeBase* node);
                                /**
                                 * Construct the iterator with the given node
                                 * @param node   the iterator node
                                 */
                                ForwardIterator(const NodeBase* node);
            
                            //## Copy Constructor ##//
                                /**
                                 * Copy it into this
                                 * @param it the iterator to copy
                                 */
                                ForwardIterator(ForwardIterator const& it) = default;
            
                            //## Move Constructor ##//
                                /**
                                 * Move it into this
                                 * @param it the iterator to move
                                 */
                                ForwardIterator(ForwardIterator && it) = default;
            
                            //## Deconstructor ##//
                                /**
                                 * ForwardIterator Deconstructor
                                 */
                                ~ForwardIterator() = default;
    
                            //## Getter ##//
                                /**
                                 * @return the current node
                                 */
                                NodeBase* getCurrent();
            
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
                                 * Test if the given iterator point to the same position
                                 * @param it the other iterator
                                 * @return   the test's result
                                 */
                                bool equal(ForwardIterator const& it) const;
            
                            //## Assignment Operator ##//
                                /**
                                 * Copy assignment of it into this
                                 * @param it the iterator to copy
                                 * @return   the reference of himself
                                 */
                                ForwardIterator& operator =(ForwardIterator const& it) = default;
                                /**
                                 * Move assignment of it into this
                                 * @param it the iterator to move
                                 * @return   the reference of himself
                                 */
                                ForwardIterator& operator =(ForwardIterator && it) = default;
        
                    };
                }
    
                /**
                 * @class ForwardList
                 * @brief A simple linked list
                 */
                template <class T, class Allocator>
                class ForwardList : public Stringable<ForwardList<T, Allocator>>, public Allocator::template Rebind<ForwardListInner::Node<T>> {
                    static_assert(Memory::IsAllocatorV<Allocator>);                     /**< Check if the given AllocatorType inherit from NRE::Memory::AllocatorTraits */
                    static_assert(std::is_same_v<T, typename Allocator::ValueType>);    /**< Make sure the allocator is set for the container inner type */

                    public :    // Traits
                        /** The container's allocated type */
                        using ValueType             = T;
                        /** The container's allocator */
                        using AllocatorType         = typename Allocator::template Rebind<ForwardListInner::Node<T>>;
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
                        /** Mutable forward access iterator */
                        using Iterator              = ForwardListInner::ForwardIterator<ValueType, InOutForwardIterator>;
                        /** Immuable forward access iterator */
                        using ConstIterator         = ForwardListInner::ForwardIterator<ValueType, Utility::ForwardIterator>;
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

                    private :   // Traits
                        /** Inner container */
                        using NodeBase = ForwardListInner::NodeBase;
                        /** Inner container */
                        using Node = ForwardListInner::Node<ValueType>;
                        
                    private :   // Fields
                        NodeBase front;  /**< The front node of the list */
                        SizeType length; /**< The size of the list */
    
                    public :    // Methods
                        //## Constructor ##//
                            /**
                             * Construct an empty list
                             * @param alloc the list's memory allocator
                             */
                            ForwardList(Allocator const& alloc = Allocator());
                            /**
                             * Construct a list with count copy of value
                             * @param count the number of copy
                             * @param value the value to use for copy
                             * @param alloc the list's memory allocator
                             */
                            ForwardList(SizeType count, ConstReference value = ValueType(), Allocator const& alloc = Allocator());
                            /**
                             * Construct a list using elements in the given range
                             * @param begin the iterator on the first element
                             * @param end   the iterator after the last element
                             * @param alloc the list's memory allocator
                             */
                            template <class InputIterator>
                            ForwardList(InputIterator begin, InputIterator end, Allocator const& alloc = Allocator());
                            /**
                             * Construct a list using elements in the given list
                             * @param list  the initializer list
                             * @param alloc the list's memory allocator
                             */
                            ForwardList(std::initializer_list<ValueType> list, Allocator const& alloc = Allocator());
    
                        //## Copy Constructor ##//
                            /**
                             * Copy list into this
                             * @param list the list to copy
                             */
                            ForwardList(ForwardList const& list);
                            /**
                             * Copy list into this
                             * @param list  the list to copy
                             * @param alloc the list's memory allocator
                             */
                            ForwardList(ForwardList const& list, Allocator const& alloc);
    
                        //## Move Constructor ##//
                            /**
                             * Move list into this
                             * @param list the list to move
                             */
                            ForwardList(ForwardList && list);
                            /**
                             * Move list into this
                             * @param list  the list to move
                             * @param alloc the list's memory allocator
                             */
                            ForwardList(ForwardList && list, Allocator const& alloc);
            
                        //## Deconstructor ##//
                            /**
                             * ForwardList Deconstructor
                             */
                            ~ForwardList();
    
                        //## Getter ##//
                            /**
                             * @return the list head
                             */
                            Reference getFront();
                            /**
                             * @return the list head
                             */
                            ConstReference getFront() const;
                            /**
                             * @return the maximum list size
                             */
                            constexpr SizeType getMaxSize() const;
                            /**
                             * @return the list's memory allocator
                             */
                            Allocator getAllocator() const;
                            /**
                             * @return the list size
                             */
                            SizeType getSize() const;
                            /**
                             * @return if the list is empty
                             */
                            bool isEmpty() const;
    
                        //## Iterator Access ##//
                            /**
                             * @return an iterator on the element before the first element
                             */
                            Iterator beforeBegin();
                            /**
                             * @return a const iterator on the element before the first element
                             */
                            ConstIterator beforeBegin() const;
                            /**
                             * @return a const iterator on the element before the first element
                             */
                            ConstIterator cbeforeBegin() const;
                            /**
                             * @return an iterator on the first element
                             */
                            Iterator begin();
                            /**
                             * @return a const iterator on the first element
                             */
                            ConstIterator begin() const;
                            /**
                             * @return a const iterator on the first element
                             */
                            ConstIterator cbegin() const;
                            /**
                             * @return an iterator on the end of the container
                             */
                            Iterator end();
                            /**
                             * @return a const iterator on the end of the container
                             */
                            ConstIterator end() const;
                            /**
                             * @return a const iterator on the end of the container
                             */
                            ConstIterator cend() const;
    
                        //## Methods ##//
                            /**
                             * Assign count copy of value in the list
                             * @param count the number of copy
                             * @param value the value to use for copy
                             */
                            void assign(SizeType count, ConstReference value);
                            /**
                             * Assign the list with element in the given range
                             * @param begin the iterator on the first element
                             * @param end   the iterator after the last element
                             */
                            template <class InputIterator>
                            void assign(InputIterator begin, InputIterator end);
                            /**
                             * Clear all objects in the list
                             */
                            void clear();
                            /**
                             * Insert a copy of the given element after the given position
                             * @param  pos   the position to insert after
                             * @param  value the element to insert
                             * @return       an iterator on the inserted element
                             */
                            Iterator insertAfter(ConstIterator pos, ConstReference value);
                            /**
                             * Insert the given element after the given position
                             * @param  pos   the position to insert after
                             * @param  value the element to insert
                             * @return       an iterator on the inserted element
                             */
                            Iterator insertAfter(ConstIterator pos, ValueType && value);
                            /**
                             * Insert count copy of the given element after the given position
                             * @param  pos   the position to insert after
                             * @param  count the number of copy to insert
                             * @param  value the element to insert
                             * @return       an iterator on the last copy
                             */
                            Iterator insertAfter(ConstIterator pos, SizeType count, ConstReference value);
                            /**
                             * Insert copy of elements in the given range after the given position
                             * @param  pos   the position to insert after
                             * @param  begin the iterator on the first element
                             * @param  end   the iterator after the last element
                             * @return       an iterator on the last inserted element
                             */
                            template <class InputIterator>
                            Iterator insertAfter(ConstIterator pos, InputIterator begin, InputIterator end);
                            /**
                             * Insert copy of elements in the given list after the given position
                             * @param  pos  the position to insert after
                             * @param  list the list containing elements
                             * @return      an iterator on the last inserted element
                             */
                            Iterator insertAfter(ConstIterator pos, std::initializer_list<ValueType> list);
                            /**
                             * Emplace an element after the given position
                             * @param  pos  the position to insert after
                             * @param  args the parameters pack used to create the element
                             * @return      an interator on the inserted element
                             */
                            template <class ... Args>
                            Iterator emplaceAfter(ConstIterator pos, Args && ... args);
                            /**
                             * Erase the element after the given position
                             * @param  pos the position to erase after
                             * @return     the iterator on the element after the erased element
                             */
                            Iterator eraseAfter(ConstIterator pos);
                            /**
                             * Erase all element in the given range except the begin and end
                             * @param  begin the begin position to erase after
                             * @param  end   the end iterator
                             * @return       the end iterator
                             */
                            Iterator eraseAfter(ConstIterator begin, ConstIterator end);
                            /**
                             * Insert a copy of the given element to the front of the list
                             * @param value the value to insert
                             */
                            void pushFront(ConstReference value);
                            /**
                             * Insert the given element to the front of the list
                             * @param value the value to insert
                             */
                            void pushFront(ValueType && value);
                            /**
                             * Emplace an element to the the front of the list
                             * @param args the parameters pack used to create the element
                             */
                            template <class ... Args>
                            void emplaceFront(Args && ... args);
                            /**
                             * Pop the front of the list
                             */
                            void popFront();
                            /**
                             * Resize the container up the given size, insert value if needed
                             * @param count the new capacity
                             */
                            void resize(SizeType count);
                            /**
                             * Resize the container up the given size, insert value if needed
                             * @param count the new capacity
                             * @param value the value used when inserting
                             */
                            void resize(SizeType count, ConstReference value);
                            /**
                             * Swap the content of the given list with this
                             * @param list the other list
                             */
                            void swap(ForwardList& list);
                            /**
                             * Merge this with list, both need to be sorted, list becomes empty
                             * @param list the other list to merge with this
                             */
                            void merge(ForwardList& list);
                            /**
                             * Merge this with list, both need to be sorted, list becomes empty
                             * @param list the other list to merge with this
                             */
                            void merge(ForwardList && list);
                            /**
                             * Merge this with list, both need to be sorted, list becomes empty
                             * @param list the other list to merge with this
                             * @param comp function which returns ​true if the first argument is less than the second
                             */
                            template <class Comparator>
                            void merge(ForwardList& list, Comparator comp);
                            /**
                             * Merge this with list, both need to be sorted, list becomes empty
                             * @param list the other list to merge with this
                             * @param comp function which returns ​true if the first argument is less than the second
                             */
                            template <class Comparator>
                            void merge(ForwardList && list, Comparator comp);
                            /**
                             * Move elements from list into this, insertion start after pos
                             * @param pos  the position to insert after
                             * @param list the list to empty
                             */
                            void spliceAfter(ConstIterator pos, ForwardList& list);
                            /**
                             * Move elements from list into this, insertion start after pos
                             * @param pos  the position to insert after
                             * @param list the list to empty
                             */
                            void spliceAfter(ConstIterator pos, ForwardList && list);
                            /**
                             * Move the element pointed by it from list into this, insertion start after pos
                             * @param pos  the position to insert after
                             * @param list the list to empty
                             * @param it   the element to move
                             */
                            void spliceAfter(ConstIterator pos, ForwardList& list, ConstIterator it);
                            /**
                             * Move the element pointed by it from list into this, insertion start after pos
                             * @param pos  the position to insert after
                             * @param list the list to empty
                             * @param it   the element to move
                             */
                            void spliceAfter(ConstIterator pos, ForwardList && list, ConstIterator it);
                            /**
                             * Move elements in the given range (begin, end) from list into this, insertion start after pos
                             * @param pos   the position to insert after
                             * @param list  the list to empty
                             * @param begin the range start to take elements from
                             * @param end   the range end to take elements from
                             */
                            void spliceAfter(ConstIterator pos, ForwardList& list, ConstIterator begin, ConstIterator end);
                            /**
                             * Move elements in the given range (begin, end) from list into this, insertion start after pos
                             * @param pos   the position to insert after
                             * @param list  the list to empty
                             * @param begin the range start to take elements from
                             * @param end   the range end to take elements from
                             */
                            void spliceAfter(ConstIterator pos, ForwardList && list, ConstIterator begin, ConstIterator end);
                            /**
                             * Remove all elements in the list equals to the given value
                             * @param value the value to erase
                             */
                            void remove(ConstReference value);
                            /**
                             * Remove all elements in the list where p return true
                             * @param p the predicate used to remove
                             */
                            template <class UnaryPredicate>
                            void removeIf(UnaryPredicate p);
                            /**
                             * Reverse the list
                             */
                            void reverse();
                            /**
                             * Remove successive redondants elements
                             */
                            void unique();
    
                        //## Assignment Operator ##//
                            /**
                             * Copy list into this
                             * @param list the list to copy into this
                             * @return     the reference of himself
                             */
                            ForwardList& operator =(ForwardList const& list);
                            /**
                             * Move list into this
                             * @param list the list to move into this
                             * @return     the reference of himself
                             */
                            ForwardList& operator =(ForwardList && list);
    
                        //## Comparison Operator ##//
                            /**
                             * Equality test between this and list
                             * @param list the other list to compare with this
                             * @return     the test result
                             */
                            bool operator==(ForwardList const& list) const;
                            /**
                             * Inequality test between this and list
                             * @param list the other list to compare with this
                             * @return     the test result
                             */
                            bool operator!=(ForwardList const& list) const;
    
                        //## Stream Operator ##//
                            /**
                             * Convert the object into a string representation
                             * @return the converted object
                             */
                            [[nodiscard]] String toString() const;

                };
            }
        }
    }

    #include "NRE_ForwardList.tpp"
