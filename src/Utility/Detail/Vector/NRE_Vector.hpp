
    /**
     * @file NRE_Vector.hpp
     * @brief Declaration of Utility's API's Container : Vector
     * @author Louis ABEL
     * @date 15/05/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <stdexcept>
     #include <utility>
     #include <cstring>

     #include "../../String/NRE_String.hpp"
     #include "../../Interfaces/Stringable/NRE_Stringable.hpp"

     #include <Memory/Allocator/NRE_IAllocator.hpp>
    

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
    
                /**
                 * @class Vector
                 * @brief A dynamic array, guarantee to be in contiguous memory
                 */
                template <class T, class Allocator>
                class Vector : public Stringable<Vector<T, Allocator>> {
                    static_assert(std::is_base_of_v<Memory::IAllocator<Allocator>, Allocator>);
                    
                    public :    // Iterator
                        /**< Shortcut to hide Iterator implementation */
                        typedef T* Iterator;
                        /**< Shortcut to hide ConstIterator implementation */
                        typedef const T* ConstIterator;
                        /**< Shortcut to hide ReverseIterator implementation */
                        typedef std::reverse_iterator<T*> ReverseIterator;
                        /**< Shortcut to hide ConstReverseIterator implementation */
                        typedef std::reverse_iterator<const T*> ConstReverseIterator;
        
                    private :   // Fields
                        std::size_t length;     /**< The data length */
                        std::size_t capacity;   /**< The data capacity */
                        Allocator allocator;    /**< The memory allocator */
                        T* data;                /**< The internal data array */
        
                    public :    // Methods
                        //## Constructor ##//
                        /**
                         * Construct an empty vector with a base capacity
                         * @param alloc the vector's memory allocator
                         */
                        Vector(Allocator const& alloc = Allocator());
            
                        /**
                         * Construct a vector filled with count copy of value
                         * @param count the number of copy to perform, will be the vector capacity and length
                         * @param value the value to fill the vector with
                         * @param alloc the vector's memory allocator
                         * @pre value don't reference a vector item
                         */
                        Vector(std::size_t count, T const& value, Allocator const& alloc = Allocator());
            
                        /**
                         * Construct a vector filled with count default value
                         * @param count the number of default element, will be the vector capacity and length
                         * @param alloc the vector's memory allocator
                         */
                        Vector(std::size_t count, Allocator const& alloc = Allocator());
            
                        /**
                         * Construct a vector filled with element between 2 iterators
                         * @param begin the begin iterator
                         * @param end   the end iterator, pointing after the last element
                         * @param alloc the vector's memory allocator
                         * @pre begin and end are not iterator from the vector
                         */
                        template <class InputIterator>
                        Vector(InputIterator begin, InputIterator end, Allocator const& alloc = Allocator());
            
                        /**
                         * Construct a vector from an initializer list
                         * @param init  the list to fill the vector with
                         * @param alloc the vector's memory allocator
                         * @pre list don't contain vector reference
                         */
                        Vector(std::initializer_list<T> init, Allocator const& alloc = Allocator());
            
                        //## Copy Constructor ##//
                        /**
                         * Copy vec into this
                         * @param vec   the vector to copy
                         * @param alloc the vector's memory allocator
                         */
                        Vector(Vector const& vec, Allocator const& alloc = Allocator());
            
                        //## Move Constructor ##//
                        /**
                         * Move vec into this
                         * @param vec   the vector to move
                         * @param alloc the vector's memory allocator
                         */
                        Vector(Vector&& vec, Allocator const& alloc = Allocator());
            
                        //## Deconstructor ##//
                        /**
                         * Vector Deconstructor
                         */
                        ~Vector();
            
                        //## Getter ##//
                        /**
                         * Access a particular element with bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        T& get(std::size_t index);
            
                        /**
                         * Access a particular element with bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        T const& get(std::size_t index) const;
            
                        /**
                         * @return the internal data array
                         */
                        T* getData();
            
                        /**
                         * @return the internal data array
                         */
                        const T* getData() const;
            
                        /**
                         * @return the first element
                         */
                        T& getFront();
            
                        /**
                         * @return the first element
                         */
                        T const& getFront() const;
            
                        /**
                         * @return the last element
                         */
                        T& getLast();
            
                        /**
                         * @return the last element
                         */
                        T const& getLast() const;
            
                        /**
                         * @return the vector effective size
                         */
                        std::size_t getSize() const;
            
                        /**
                         * @return the maximum vector size
                         */
                        constexpr std::size_t getMaxSize() const;
            
                        /**
                         * @return the vector capacity
                         */
                        std::size_t getCapacity() const;
            
                        /**
                         * @return the vector's memory allocator
                         */
                        Allocator getAllocator() const;
            
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
                        void assign(std::size_t count, T const& value);
            
                        /**
                         * Assign the vector with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @pre begin and end are not iterator from the vector
                         */
                        template <class InputIterator>
                        void assign(InputIterator begin, InputIterator end);
            
                        /**
                         * Set the vector capacity to a minimum of size, reallocating memory if needed
                         * @param size the new capacity
                         * @warning size value is not checked against getMaxSize()
                         */
                        void reserve(std::size_t size);
            
                        /**
                         * Clear all object in the vector, not actually releasing memory
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void clear() noexcept {
                            for (std::size_t i = 0; i < length; i++) {
                                allocator.destroy(&data[i]);
                            }
                            length = 0;
                        }
            
                        /**
                         * Clear all object in the vector, not actually releasing memory
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void clear() noexcept {
                            length = 0;
                        }
            
                        /**
                         * Insert a copy of value at the specified position
                         * @param  start the position to insert the value
                         * @param  value the value to insert
                         * @return       the iterator on the inserted value
                         * @pre value don't reference a vector item
                         */
                        Iterator insert(ConstIterator start, T const& value);
            
                        /**
                         * Insert count copy of value at the specified position
                         * @param  start the position to insert values
                         * @param  count the number of copy
                         * @param  value the value to insert
                         * @return       the iterator on the first inserted value
                         * @pre value don't reference a vector item
                         */
                        Iterator insert(ConstIterator start, std::size_t count, T const& value);
            
                        /**
                         * Insert a copy of element between begin and end at the specified position
                         * @param  start the position to insert values
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @return       the iterator on the first inserted value
                         * @pre begin and end are not iterator from the vector
                         */
                        template <class InputIterator>
                        Iterator insert(ConstIterator start, InputIterator begin, InputIterator end);
            
                        /**
                         * Insert a list of value at the specified position
                         * @param  start the position to insert values
                         * @param  list  the list to fill the vector with
                         * @return       the iterator on the first inserted value
                         * @pre list don't contain vector reference
                         */
                        Iterator insert(ConstIterator start, std::initializer_list<T> list);
            
                        /**
                         * Emplace an element at the specified position
                         * @param  start the position to insert the value
                         * @param  args  the value construction arguments
                         * @return       the iterator on the inserted value
                         */
                        template <class ... Args>
                        Iterator emplace(ConstIterator start, Args&& ... args);
            
                        /**
                         * Erase an element in the vector
                         * @param  pos  the position to erase
                         * @return       an iterator on the next valid element
                         */
                        Iterator erase(ConstIterator pos);
            
                        /**
                         * Erase a set of element from the vector
                         * @param  begin the start position for erasing
                         * @param  end   the end position for erasing
                         * @return       an iterator on the next valid element
                         */
                        Iterator erase(ConstIterator begin, ConstIterator end);
            
                        /**
                         * Insert a copy of value at the end of the vector
                         * @param value the value to insert
                         * @pre value don't reference a vector item
                         */
                        void pushBack(T const& value);
            
                        /**
                         * Emplace a value at the end of the vector
                         * @param value the value to insert
                         */
                        void pushBack(T&& value);
            
                        /**
                         * Emplace a value at the end of the vector
                         * @param args the arguments for the value construction
                         */
                        template <class ... Args>
                        void emplaceBack(Args&& ... args);
            
                        /**
                         * Pop the last element in the vector
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void popBack() {
                            allocator.destroy(end() - 1);
                            length--;
                        }
            
                        /**
                         * Pop the last element in the vector
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void popBack() {
                            length--;
                        }
            
                        /**
                         * Resize the container up the given size, insert value if needed
                         * @param count the new capacity
                         */
                        void resize(std::size_t count);
            
                        /**
                         * Resize the container up the given size, insert value if needed
                         * @param count the new capacity
                         * @param value the value used when inserting
                         */
                        void resize(std::size_t count, T const& value);
            
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
                        T& operator [](std::size_t index);
            
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        T const& operator [](std::size_t index) const;
            
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
                        Vector& operator =(Vector&& vec);
            
                        //## Comparison Operator ##//
                        /**
                         * Equality test between this and vec
                         * @param vec the other vector
                         * @return    the test result
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        bool operator ==(Vector const& vec) const {
                            bool equal = true;
                            std::size_t current = 0;
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
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        bool operator ==(Vector const& vec) const {
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
                        String toString() const;
        
                    private :   // Methods
                        /**
                         * Reallocate and grow the storage capacity
                         */
                        void reallocate();
            
                        /**
                         * Rellocate the data to the given size
                         * @param newSize the new capacity
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void reallocate(std::size_t newSize) {
                            std::size_t tmp = capacity;
                            capacity = newSize;
                            T* newData = allocator.allocate(capacity);
                
                            for (std::size_t current = 0; current < length; current++) {
                                allocator.construct(&newData[current], std::move(data[current]));
                            }
                            allocator.deallocate(data, tmp);
                            data = newData;
                        }
            
                        /**
                         * Rellocate the data to the given size
                         * @param newSize the new capacity
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void reallocate(std::size_t newSize) {
                            std::size_t tmp = capacity;
                            capacity = newSize;
                            T* newData = allocator.allocate(capacity);
                
                            std::memmove(newData, data, length * sizeof(T));
                            allocator.deallocate(data, tmp);
                            data = newData;
                        }
            
                        /**
                         * Reallocate the vector with the neareast grow factor value
                         * @param size the new minimum capacity
                         */
                        void reserveWithGrowFactor(std::size_t size);
            
                        /**
                         * Shift all element in the vector, don't do reallocation
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void shift(std::size_t start, std::size_t count) {
                            for (std::size_t index = length + count - 1; index != start + count - 1; index--) {
                                allocator.construct(&data[index], std::move(data[index - count]));
                            }
                        }
            
                        /**
                         * Shift all element in the vector, don't do reallocation
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void shift(std::size_t start, std::size_t count) {
                            std::memmove(data + start + count, data + start, (length - start) * sizeof(T));
                        }
            
                        /**
                         * Shift back all element in the vector, don't call deconstructor
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void shiftBack(std::size_t start, std::size_t count) {
                            for (std::size_t index = start; index < start + count; index++) {
                                allocator.construct(&data[index], std::move(data[index + count]));
                            }
                        }
            
                        /**
                         * Shift back all element in the vector, don't call deconstructor
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void shiftBack(std::size_t start, std::size_t count) {
                            std::memmove(data + start, data + start + count, (length - start) * sizeof(T));
                        }
            
                        /**
                         * Copy the vector content
                         * @param vec the vector to copy
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void copy(Vector const& vec) {
                            std::size_t current = 0;
                            for (T const& it : vec) {
                                allocator.construct(&data[current], it);
                                current++;
                            }
                        }
            
                        /**
                         * Copy the vector content
                         * @param vec the vector to copy
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void copy(Vector const& vec) {
                            std::memcpy(data, vec.data, vec.length * sizeof(T));
                        }
        
                    private :    // Static
                        static constexpr float GROW_FACTOR = 1.5;
                        static constexpr std::size_t BASE_ALLOCATION_SIZE = 16;
                };
            }
        }
    }

    #include "NRE_Vector.tpp"
