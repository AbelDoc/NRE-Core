    
    /**
     * @file NRE_StaticVector.hpp
     * @brief Declaration of Utility's API's Container : StaticVector
     * @author Louis ABEL
     * @date 05/02/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <stdexcept>
    #include <utility>
    #include <limits>
    #include <cstring>
    
    #include <Memory/Allocator/NRE_Allocator.hpp>
    
    #include "../String/NRE_String.hpp"
    #include "../Interfaces/Stringable/NRE_Stringable.hpp"
    
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
            
            /**
             * @class StaticVector
             * @brief A static vector, with a fixed size capacity on the stack but vector behavior
             */
            template <class T, std::size_t Size = 128>
            class StaticVector : public Stringable<StaticVector<T, Size>> {
                public :    // Traits
                    /**< The container's allocated type */
                    using ValueType             = T;
                    /**< The object's size type */
                    using SizeType              = std::size_t;
                    /**< The object's difference type */
                    using DifferenceType        = std::ptrdiff_t;
                    /**< The allocated type reference */
                    using Reference             = ValueType&;
                    /**< The allocated type const reference */
                    using ConstReference        = ValueType const&;
                    /**< The allocated type pointer */
                    using Pointer               = ValueType*;
                    /**< The allocated type const pointer */
                    using ConstPointer          = const ValueType*;
                    /**< Mutable random access iterator */
                    using Iterator              = Pointer;
                    /**< Immuable random access iterator */
                    using ConstIterator         = ConstPointer;
                    /**< Mutable reverse random access iterator */
                    using ReverseIterator       = std::reverse_iterator<Iterator>;
                    /**< Immuable reverse random access iterator */
                    using ConstReverseIterator  = std::reverse_iterator<ConstIterator>;
                    /**< STL compatibility */
                    using value_type            = ValueType;
                    /**< STL compatibility */
                    using size_type             = SizeType;
                    /**< STL compatibility */
                    using difference_type       = DifferenceType;
                    /**< STL compatibility */
                    using reference             = Reference;
                    /**< STL compatibility */
                    using const_reference       = ConstReference;
                    /**< STL compatibility */
                    using pointer               = Pointer;
                    /**< STL compatibility */
                    using const_pointer         = ConstPointer;
                    /**< STL compatibility */
                    using iterator              = Iterator;
                    /**< STL compatibility */
                    using const_iterator        = ConstIterator;
                    /**< STL compatibility */
                    using reverse_iterator      = ReverseIterator;
                    /**< STL compatibility */
                    using const_reverse_iterator= ConstReverseIterator;

                private :   // Fields
                    SizeType length;       /**< The data length */
                    ValueType data[Size];  /**< The internal data */
                    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct an empty static vector
                         */
                        StaticVector();
                        /**
                         * Construct a static vector filled with count copy of value
                         * @param count the number of copy to perform, will be the static vector capacity and length
                         * @param value the value to fill the static vector with
                         * @pre value don't reference a static vector item
                         */
                        StaticVector(SizeType count, ConstReference value);
                        /**
                         * Construct a static vector filled with count default value
                         * @param count the number of default element, will be the static vector capacity and length
                         */
                        StaticVector(SizeType count);
                        /**
                         * Construct a static vector filled with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @pre begin and end are not iterator from the static vector
                         */
                        template <class InputIterator>
                        StaticVector(InputIterator begin, InputIterator end);
                        /**
                         * Construct a static vector from an initializer list
                         * @param  init the list to fill the static vector with
                         * @pre list don't contain static vector reference
                         */
                        StaticVector(std::initializer_list<ValueType> init);
        
                    //## Copy Constructor ##//
                        /**
                         * Copy vec into this
                         * @param  vec the static vector to copy
                         */
                        StaticVector(StaticVector const& vec);
        
                    //## Move Constructor ##//
                        /**
                         * Move vec into this
                         * @param  vec the static vector to move
                         */
                        StaticVector(StaticVector && vec);
        
                    //## Deconstructor ##//
                        /**
                         * StaticVector Deconstructor
                         */
                        ~StaticVector();
        
                    //## Getter ##//
                        /**
                         * Access a particular element with bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        Reference get(SizeType index);
                        /**
                         * Access a particular element with bound checking
                         * @param  index the element index
                         * @return       the corresponding element
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
                         * @return the static vector effective size
                         */
                        SizeType getSize() const;
                        /**
                         * @return the maximum array size
                         */
                        constexpr SizeType getMaxSize() const;
                        /**
                         * @return the static vector capacity
                         */
                        SizeType getCapacity() const;
                        /**
                         * @return if the array is empty
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
                         * Assign the static vector with count copy of value, starting from the beginning
                         * @param count the number of copy
                         * @param value the copy to fill the static vector with
                         * @pre value don't reference a static vector item
                         */
                        void assign(SizeType count, ConstReference value);
                        /**
                         * Assign the static vector with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @pre begin and end are not iterator from the static vector
                         */
                        template <class InputIterator>
                        void assign(InputIterator begin, InputIterator end);
                        /**
                         * Clear all object in the static vector, not actually releasing memory
                         */
                        void clear() noexcept;
                        /**
                         * Insert a copy of value at the specified position
                         * @param  start the position to insert the value
                         * @param  value the value to insert
                         * @return       the iterator on the inserted value
                         * @pre value don't reference a static vector item
                         */
                        Iterator insert(ConstIterator start, ConstReference value);
                        /**
                         * Insert count copy of value at the specified position
                         * @param  start the position to insert values
                         * @param  count the number of copy
                         * @param  value the value to insert
                         * @return       the iterator on the first inserted value
                         * @pre value don't reference a static vector item
                         */
                        Iterator insert(ConstIterator start, SizeType count, ConstReference value);
                        /**
                         * Insert a copy of element between begin and end at the specified position
                         * @param  start the position to insert values
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @return       the iterator on the first inserted value
                         * @pre begin and end are not iterator from the static vector
                         */
                        template <class InputIterator>
                        Iterator insert(ConstIterator start, InputIterator begin, InputIterator end);
                        /**
                         * Insert a list of value at the specified position
                         * @param  start the position to insert values
                         * @param  list  the list to fill the static vector with
                         * @return       the iterator on the first inserted value
                         * @pre list don't contain static vector reference
                         */
                        Iterator insert(ConstIterator start, std::initializer_list<ValueType> list);
                        /**
                         * Emplace an element at the specified position
                         * @param  start the position to insert the value
                         * @param  args  the value construction arguments
                         * @return       the iterator on the inserted value
                         */
                        template <class ... Args>
                        Iterator emplace(ConstIterator start, Args && ... args);
                        /**
                         * Erase an element in the static vector
                         * @param  pos  the position to erase
                         * @return       an iterator on the next valid element
                         */
                        Iterator erase(ConstIterator pos);
                        /**
                         * Erase a set of element from the static vector
                         * @param  begin the start position for erasing
                         * @param  end   the end position for erasing
                         * @return       an iterator on the next valid element
                         */
                        Iterator erase(ConstIterator begin, ConstIterator end);
                        /**
                         * Insert a copy of value at the end of the static vector
                         * @param value the value to insert
                         * @pre value don't reference a static vector item
                         */
                        void pushBack(ConstReference value);
                        /**
                         * Emplace a value at the end of the static vector
                         * @param value the value to insert
                         */
                        void pushBack(ValueType && value);
                        /**
                         * Emplace a value at the end of the static vector
                         * @param args the arguments for the value construction
                         */
                        template <class ... Args>
                        void emplaceBack(Args && ... args);
                        /**
                         * Pop the last element in the static vector
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
                         * Swap the static vector with another static vector
                         * @param vec the other static vector
                         */
                        void swap(StaticVector& vec);
        
                    //## Access Operator ##//
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        Reference operator[](SizeType index);
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        ConstReference operator[](SizeType index) const;
        
                    //## Assignment Operator ##//
                        /**
                         * Copy vec into this
                         * @param vec the static vector to copy into this
                         * @return    the reference of himself
                         */
                        StaticVector& operator =(StaticVector const& vec);
                        /**
                         * Move vec into this
                         * @param vec the static vector to move into this
                         * @return    the reference of himself
                         */
                        StaticVector& operator =(StaticVector && vec);
        
                    //## Comparison Operator ##//
                        /**
                         * Equality test between this and vec
                         * @param vec the other static vector
                         * @return the test result
                         */
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        bool operator ==(StaticVector const& vec) const {
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
                         * @param vec the other static vector
                         * @return the test result
                         */
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                        bool operator ==(StaticVector const& vec) const {
                            if (length != vec.length) {
                                return false;
                            }
                            return std::memcmp(data, vec.data, length * sizeof(ValueType)) == 0;
                        }
                        /**
                         * Inequality test between this and vec
                         * @param vec the other static vector
                         * @return the test result
                         */
                        bool operator !=(StaticVector const& vec) const;
        
                    //## Stream Operator ##//
                        /**
                         * Convert the object into a string representation
                         * @return the converted object
                         */
                        [[nodiscard]] String toString() const;
    
                private :   // Methods
                        /**
                         * Shift all element in the static vector, don't do reallocation
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        void shift(SizeType start, SizeType count) {
                            for (SizeType index = length + count - 1; index != start + count - 1; index--) {
                                data[index] = std::move(data[index - count]);
                            }
                        }
                        /**
                         * Shift all element in the static vector, don't do reallocation
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                        void shift(SizeType start, SizeType count) {
                            std::memmove(data + start + count, data + start, (length - start) * sizeof(ValueType));
                        }
                        /**
                         * Shift back all element in the static vector, don't call deconstructor
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        void shiftBack(SizeType start, SizeType count) {
                            for (SizeType index = start; index < start + count; index++) {
                                data[index] = std::move(data[index + count]);
                            }
                        }
                        /**
                         * Shift back all element in the static vector, don't call deconstructor
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                        void shiftBack(SizeType start, SizeType count) {
                            std::memmove(data + start, data + start + count, (length - start) * sizeof(ValueType));
                        }
                        /**
                         * Copy the given vector into this
                         * @param vec the vector to copy
                         */
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        void copy(StaticVector const& vec) {
                            length = vec.length;
                            for (SizeType index = 0; index < length; index++) {
                                data[index] = vec.data[index];
                            }
                        }
                        /**
                         * Copy the given vector into this
                         * @param vec the vector to copy
                         */
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                        void copy(StaticVector const& vec) {
                            length = vec.length;
                            std::memcpy(data, vec.data, length * sizeof(ValueType));
                        }
                        /**
                         * Move the given vector into this
                         * @param vec the vector to move
                         */
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        void move(StaticVector && vec) {
                            length = vec.length;
                            vec.length = 0;
                            for (SizeType index = 0; index < length; index++) {
                                data[index] = std::move(vec.data[index]);
                            }
                        }
                        /**
                         * Move the given vector into this
                         * @param vec the vector to move
                         */
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
                        void move(StaticVector && vec) {
                            length = vec.length;
                            vec.length = 0;
                            std::memmove(data, vec.data, length * sizeof(ValueType));
                        }
            };
        
        }
    }

    #include "NRE_StaticVector.tpp"
