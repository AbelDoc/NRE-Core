
    /**
     * @file Detail/Vector/NRE_Vector.hpp
     * @brief Declaration of Core's API's Container : Vector
     * @author Louis ABEL
     * @date 15/05/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <stdexcept>
    #include <utility>
    #include <cstring>

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
    
                /**
                 * @class Vector
                 * @brief A dynamic array, guarantee to be in contiguous memory
                 */
                template <class T, Concept::Allocator Alloc>
                class Vector : public Stringable<Vector<T, Alloc>>, public Alloc {
                    static_assert(Concept::SameAs<T, typename Alloc::ValueType>);    /**< Make sure the allocator is set for the container inner type */
                    
                    public :    // Traits
                        using AllocatorType         = Alloc;
                        using AllocatorTraits       = Memory::AllocatorTraits<AllocatorType>;
                        using ValueType             = typename AllocatorTraits::ValueType;
                        using SizeType              = typename AllocatorTraits::SizeType;
                        using DifferenceType        = typename AllocatorTraits::DifferenceType;
                        using Reference             = ValueType&;
                        using ConstReference        = ValueType const&;
                        using Pointer               = typename AllocatorTraits::Pointer;
                        using ConstPointer          = typename AllocatorTraits::ConstPointer;
                        using Iterator              = Pointer;
                        using ConstIterator         = ConstPointer;
                        using ReverseIterator       = Core::ReverseIterator<Iterator>;
                        using ConstReverseIterator  = Core::ReverseIterator<ConstIterator>;
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
        
                    private :   // Fields
                        SizeType length;     /**< The data length */
                        SizeType capacity;   /**< The data capacity */
                        Pointer data;        /**< The internal data array */
        
                    public :    // Methods
                        //## Constructor ##//
                            /**
                             * Construct an empty vector with a base capacity
                             * @param alloc the vector's memory allocator
                             */
                            Vector(AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a vector filled with count copy of value
                             * @param count the number of copy to perform, will be the vector capacity and length
                             * @param value the value to fill the vector with
                             * @param alloc the vector's memory allocator
                             */
                            Vector(SizeType count, ConstReference value, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a vector filled with count default value
                             * @param count the number of default element, will be the vector capacity and length
                             * @param alloc the vector's memory allocator
                             */
                            Vector(SizeType count, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a vector filled with element between 2 iterators
                             * @param begin the begin iterator
                             * @param end   the end iterator, pointing after the last element
                             * @param alloc the vector's memory allocator
                             */
                            template <Concept::InputIterator It, Concept::SentinelFor<It> S>
                            Vector(It begin, S end, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a vector filled with element from a given range
                             * @param range the input range
                             * @param alloc the vector's memory allocator
                             */
                            template <Concept::InputRange R>
                            Vector(R && range, AllocatorType const& alloc = AllocatorType());
                            /**
                             * Construct a vector from an initializer list
                             * @param init  the list to fill the vector with
                             * @param alloc the vector's memory allocator
                             */
                            Vector(std::initializer_list<T> init, AllocatorType const& alloc = AllocatorType());
            
                        //## Copy Constructor ##//
                            /**
                             * Copy vec into this
                             * @param vec the vector to copy
                             */
                            Vector(Vector const& vec);
                            /**
                             * Copy vec into this
                             * @param vec   the vector to copy
                             * @param alloc the vector's memory allocator
                             */
                            Vector(Vector const& vec, AllocatorType const& alloc);
            
                        //## Move Constructor ##//
                            /**
                             * Move vec into this
                             * @param vec the vector to move
                             */
                            Vector(Vector && vec);
                            /**
                             * Move vec into this
                             * @param vec   the vector to move
                             * @param alloc the vector's memory allocator
                             */
                            Vector(Vector && vec, AllocatorType const& alloc);
            
                        //## Deconstructor ##//
                            /**
                             * Vector Deconstructor
                             */
                            ~Vector();
            
                        //## Getter ##//
                            /**
                             * Access a particular element with bound checking
                             * @param  index the element index
                             * @return the corresponding element
                             */
                            Reference get(SizeType index);
                            /**
                             * Access a particular element with bound checking
                             * @param  index the element index
                             * @return the corresponding element
                             */
                            ConstReference get(SizeType index) const;
                            /**
                             * @return the internal data array
                             */
                            Pointer getData();
                            /**
                             * @return the internal data array
                             */
                            ConstPointer getData() const;
                            /**
                             * @return the internal data array
                             */
                            ConstPointer getCData() const;
                            /**
                             * @return the first element
                             */
                            Reference getFront();
                            /**
                             * @return the first element
                             */
                            ConstReference getFront() const;
                            /**
                             * @return the last element
                             */
                            Reference getLast();
                            /**
                             * @return the last element
                             */
                            ConstReference getLast() const;
                            /**
                             * @return the vector effective size
                             */
                            SizeType getSize() const;
                            /**
                             * @return the maximum vector size
                             */
                            constexpr SizeType getMaxSize() const;
                            /**
                             * @return the vector capacity
                             */
                            SizeType getCapacity() const;
                            /**
                             * @return the vector's memory allocator
                             */
                            AllocatorType getAllocator() const;
                            /**
                             * @return if the vector is empty
                             */
                            bool isEmpty() const;
            
                        //## Iterator Access ##//
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
                            /**
                             * @return a reverse iterator on the first element
                             */
                            ReverseIterator rbegin();
                            /**
                             * @return a const reverse iterator on the first element
                             */
                            ConstReverseIterator rbegin() const;
                            /**
                             * @return a const reverse iterator on the first element
                             */
                            ConstReverseIterator crbegin() const;
                            /**
                             * @return a reverse iterator on the end of the container
                             */
                            ReverseIterator rend();
                            /**
                             * @return a const reverse iterator on the end of the container
                             */
                            ConstReverseIterator rend() const;
                            /**
                             * @return a const reverse iterator on the end of the container
                             */
                            ConstReverseIterator crend() const;
            
                        //## Methods ##//
                            /**
                             * Assign the vector with count copy of value, starting from the beginning
                             * @param count the number of copy
                             * @param value the copy to fill the vector with
                             * @pre value don't reference a vector item
                             */
                            void assign(SizeType count, ConstReference value);
                            /**
                             * Assign the vector with element between 2 iterators, no optimization
                             * @param begin the begin iterator
                             * @param end   the end iterator, pointing after the last element
                             * @pre begin and end are not iterator from the vector
                             */
                            template <Concept::InputIterator It, Concept::SentinelFor<It> S> requires (!Concept::SizedSentinelFor<It, S>)
                            void assign(It begin, S end) {
                                clear();
                                SizeType size = Core::distance(begin, end);
                                if (capacity < size) {
                                    reserveWithGrowFactor(size);
                                }
                                SizeType current = 0;
                                for ( ; begin != end; begin++) {
                                    AllocatorTraits::construct(*this, &data[current], *begin);
                                    ++current;
                                }
                                length = current;
                            }
                            /**
                             * Assign the vector with element between 2 iterators, optimized for sized sentinel
                             * @param begin the begin iterator
                             * @param end   the end iterator, pointing after the last element
                             * @pre begin and end are not iterator from the vector
                             */
                            template <Concept::InputIterator It, Concept::SizedSentinelFor<It> S>
                            void assign(It begin, S end) {
                                clear();
                                SizeType size = Core::distance(begin, end);
                                if (capacity < size) {
                                    reserveWithGrowFactor(size);
                                }
                                SizeType current = 0;
                                for (auto n = end - begin; n > 0; --n) {
                                    AllocatorTraits::construct(*this, &data[current], *begin);
                                    ++current;
                                    ++begin;
                                }
                                length = current;
                            }
                            /**
                             * Assign the vector with element from a range
                             * @param range the input range
                             * @pre range is not part of the vector
                             */
                            template <Concept::InputRange R>
                            void assign(R && range);
                            /**
                             * Set the vector capacity to a minimum of size, reallocating memory if needed
                             * @param size the new capacity
                             * @warning size value is not checked against getMaxSize()
                             */
                            void reserve(SizeType size);
                            /**
                             * Clear all object in the vector, not actually releasing memory
                             */
                            void clear() noexcept;
                            /**
                             * Insert a copy of value at the specified position
                             * @param  start the position to insert the value
                             * @param  value the value to insert
                             * @return       the iterator on the inserted value
                             * @pre value don't reference a vector item
                             */
                            Iterator insert(ConstIterator start, ConstReference value);
                            /**
                             * Insert count copy of value at the specified position
                             * @param  start the position to insert values
                             * @param  count the number of copy
                             * @param  value the value to insert
                             * @return       the iterator on the first inserted value
                             * @pre value don't reference a vector item
                             */
                            Iterator insert(ConstIterator start, SizeType count, ConstReference value);
                            /**
                             * Insert a copy of element between begin and end at the specified position, no optimization
                             * @param start the position to insert values
                             * @param begin the begin iterator
                             * @param end   the end iterator, pointing after the last element
                             * @return the iterator on the first inserted value
                             * @pre begin and end are not iterator from the vector
                             */
                            template <Concept::InputIterator It, Concept::SentinelFor<It> S> requires (!Concept::SizedSentinelFor<It, S>)
                            Iterator insert(ConstIterator start, It begin, S end) {
                                SizeType count = Core::distance(begin, end);
                                SizeType index = Core::distance(ConstIterator(data), start);
                                if (capacity < length + count) {
                                    reserveWithGrowFactor(length + count);
                                }
                                if (index < length) {
                                    Core::shiftRight(data + index, data + length + count, count);
                                }
                                for ( ; begin != end; ++begin) {
                                    AllocatorTraits::construct(*this, &data[index], *begin);
                                    ++index;
                                }
                                length += count;
                                return Iterator(data + index);
                            }
                            /**
                             * Insert a copy of element between begin and end at the specified position, optimized for sized sentinel
                             * @param start the position to insert values
                             * @param begin the begin iterator
                             * @param end   the end iterator, pointing after the last element
                             * @return the iterator on the first inserted value
                             * @pre begin and end are not iterator from the vector
                             */
                            template <Concept::InputIterator It, Concept::SizedSentinelFor<It> S>
                            Iterator insert(ConstIterator start, It begin, S end) {
                                SizeType count = Core::distance(begin, end);
                                SizeType index = Core::distance(ConstIterator(data), start);
                                if (capacity < length + count) {
                                    reserveWithGrowFactor(length + count);
                                }
                                if (index < length) {
                                    Core::shiftRight(data + index, data + length + count, count);
                                }
                                for (auto n = end - begin; n > 0; --n) {
                                    AllocatorTraits::construct(*this, &data[index], *begin);
                                    ++index;
                                    ++begin;
                                }
                                length += count;
                                return Iterator(data + index);
                            }
                            /**
                             * Insert a copy of element in the given range at the specified position
                             * @param start the position to insert values
                             * @param range the input range
                             * @return the iterator on the first inserted value
                             * @pre range is not part of the vector
                             */
                            template <Concept::InputRange R>
                            Iterator insert(ConstIterator start, R && range);
                            /**
                             * Insert a list of value at the specified position
                             * @param start the position to insert values
                             * @param list  the list to fill the vector with
                             * @return the iterator on the first inserted value
                             * @pre list don't contain vector reference
                             */
                            Iterator insert(ConstIterator start, std::initializer_list<T> list);
                            /**
                             * Emplace an element at the specified position
                             * @param start the position to insert the value
                             * @param args  the value construction arguments
                             * @return the iterator on the inserted value
                             */
                            template <class ... Args>
                            Iterator emplace(ConstIterator start, Args && ... args);
                            /**
                             * Erase an element in the vector
                             * @param pos the position to erase
                             * @return an iterator on the next valid element
                             */
                            Iterator erase(ConstIterator pos);
                            /**
                             * Erase a set of element from the vector
                             * @param  begin the start position for erasing
                             * @param  end   the end position for erasing
                             * @return       an iterator on the next valid element
                             */
                            template <Concept::SentinelFor<ConstIterator> S>
                            Iterator erase(ConstIterator begin, S end);
                            /**
                             * Insert a copy of value at the end of the vector
                             * @param value the value to insert
                             * @pre value don't reference a vector item
                             */
                            void pushBack(ConstReference value);
                            /**
                             * Emplace a value at the end of the vector
                             * @param value the value to insert
                             */
                            void pushBack(T && value);
                            /**
                             * Emplace a value at the end of the vector
                             * @param args the arguments for the value construction
                             */
                            template <class ... Args>
                            void emplaceBack(Args && ... args);
                            /**
                             * Pop the last element in the vector
                             */
                            void popBack();
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
                             * Swap the vector with another vector
                             * @param vec the other vector
                             */
                            void swap(Vector& vec);
                            /**
                             * Shrink to fit the actual size, actually freeing memory
                             */
                            void shrinkToFit();
            
                        //## Access Operator ##//
                            /**
                             * Access a particular element without bound checking
                             * @param  index the element index
                             * @return       the corresponding element
                             */
                            Reference operator [](SizeType index);
                            /**
                             * Access a particular element without bound checking
                             * @param  index the element index
                             * @return       the corresponding element
                             */
                            ConstReference operator [](SizeType index) const;
            
                        //## Assignment Operator ##//
                            /**
                             * Copy vec into this
                             * @param vec the vector to copy into this
                             * @return    the reference of himself
                             */
                            Vector& operator =(Vector const& vec);
                            /**
                             * Move vec into this
                             * @param vec the vector to move into this
                             * @return    the reference of himself
                             */
                            Vector& operator =(Vector && vec);
            
                        //## Comparison Operator ##//
                            /**
                             * Equality test between this and vec
                             * @param vec the other vector
                             * @return    the test result
                             */
                            bool operator ==(Vector const& vec) const requires (!Concept::MemComparable<ValueType>) {
                                if (length != vec.length) {
                                    return false;
                                }
                                bool equal = true;
                                SizeType current = 0;
                                while (equal && current < length) {
                                    equal = data[current] == vec[current];
                                    current++;
                                }
                                return equal;
                            }
                            /**
                             * Equality test between this and vec
                             * @param vec the other vector
                             * @return    the test result
                             */
                            bool operator ==(Vector const& vec) const requires (Concept::MemComparable<ValueType>) {
                                if (length != vec.length) {
                                    return false;
                                }
                                return std::memcmp(data, vec.data, length * sizeof(T)) == 0;
                            }
                            /**
                             * Inequality test between this and vec
                             * @param vec the other vector
                             * @return    the test result
                             */
                            bool operator !=(Vector const& vec) const;
            
                        //## Stream Operator ##//
                            /**
                             * Convert the object into a string representation
                             * @return the converted object
                             */
                            [[nodiscard]] String toString() const;
        
                    private :   // Methods
                        /**
                         * Reallocate and grow the storage capacity
                         */
                        void reallocate();
                        /**
                         * Rellocate the data to the given size
                         * @param newSize the new capacity
                         */
                        void reallocate(SizeType newSize);
                        /**
                         * Reallocate the vector with the neareast grow factor value
                         * @param size the new minimum capacity
                         */
                        void reserveWithGrowFactor(SizeType size);
        
                    private :    // Static
                        static constexpr float GROW_FACTOR = 2;                 /**< The container's reallocation growth factor */
                        static constexpr SizeType BASE_ALLOCATION_SIZE = 16;    /**< The container's base size if not given */
                };
            }
        }
    }

    #include "NRE_Vector.tpp"
