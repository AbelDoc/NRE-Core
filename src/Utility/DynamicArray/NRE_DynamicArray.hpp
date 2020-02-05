    
    /**
     * @file NRE_DynamicArray.hpp
     * @brief Declaration of Utility's API's Container : DynamicArray
     * @author Louis ABEL
     * @date 05/02/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <stdexcept>
    #include <utility>
    #include <limits>
    #include <cstring>
    
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
             * @class DynamicArray
             * @brief A dynamic array, with a fixed size capacity on the stack but vector behavior
             */
            template <class T, std::size_t Size = 128>
            class DynamicArray : public Stringable<DynamicArray<T, Size>> {
                public :    // Iterator
                    /**< Shortcut to hide Iterator implementation */
                    typedef T*          Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef const T*    ConstIterator;
                    /**< Shortcut to hide ReverseIterator implementation */
                    typedef std::reverse_iterator<T*>          ReverseIterator;
                    /**< Shortcut to hide ConstReverseIterator implementation */
                    typedef std::reverse_iterator<const T*>    ConstReverseIterator;

                private :   // Fields
                    std::size_t length;     /**< The data length */
                    T data[Size];           /**< The internal data */
                    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct an empty dynamic array
                         */
                        DynamicArray();
                        /**
                         * Construct a dynamic array filled with count copy of value
                         * @param count the number of copy to perform, will be the dynamic array capacity and length
                         * @param value the value to fill the dynamic array with
                         * @pre value don't reference a dynamic array item
                         */
                        DynamicArray(std::size_t count, T const& value);
                        /**
                         * Construct a dynamic array filled with count default value
                         * @param count the number of default element, will be the dynamic array capacity and length
                         */
                        DynamicArray(std::size_t count);
                        /**
                         * Construct a dynamic array filled with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @pre begin and end are not iterator from the dynamic array
                         */
                        template <class InputIterator>
                        DynamicArray(InputIterator begin, InputIterator end);
                        /**
                         * Construct a dynamic array from an initializer list
                         * @param  init the list to fill the dynamic array with
                         * @pre list don't contain dynamic array reference
                         */
                        DynamicArray(std::initializer_list<T> init);
        
                    //## Copy Constructor ##//
                        /**
                         * Copy arr into this
                         * @param  arr the dynamic array to copy
                         */
                        DynamicArray(DynamicArray const& arr);
        
                    //## Move Constructor ##//
                        /**
                         * Move arr into this
                         * @param  arr the dynamic array to move
                         */
                        DynamicArray(DynamicArray && arr);
        
                    //## Deconstructor ##//
                        /**
                         * DynamicArray Deconstructor
                         */
                        ~DynamicArray();
        
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
                         * @return the dynamic array effective size
                         */
                        std::size_t getSize() const;
                        /**
                         * @return the maximum array size
                         */
                        constexpr std::size_t getMaxSize() const;
                        /**
                         * @return the dynamic array capacity
                         */
                        std::size_t getCapacity() const;
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
                         * Assign the dynamic array with count copy of value, starting from the beginning
                         * @param count the number of copy
                         * @param value the copy to fill the dynamic array with
                         * @pre value don't reference a dynamic array item
                         */
                        void assign(std::size_t count, T const& value);
                        /**
                         * Assign the dynamic array with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @pre begin and end are not iterator from the dynamic array
                         */
                        template <class InputIterator>
                        void assign(InputIterator begin, InputIterator end);
                        /**
                         * Clear all object in the dynamic array, not actually releasing memory
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void clear() noexcept {
                            for (std::size_t i = 0; i < length; i++) {
                                data[i].~T();
                            }
                            length = 0;
                        }
                        /**
                         * Clear all object in the dynamic array, not actually releasing memory
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
                         * @pre value don't reference a dynamic array item
                         */
                        Iterator insert(ConstIterator start, T const& value);
                        /**
                         * Insert count copy of value at the specified position
                         * @param  start the position to insert values
                         * @param  count the number of copy
                         * @param  value the value to insert
                         * @return       the iterator on the first inserted value
                         * @pre value don't reference a dynamic array item
                         */
                        Iterator insert(ConstIterator start, std::size_t count, T const& value);
                        /**
                         * Insert a copy of element between begin and end at the specified position
                         * @param  start the position to insert values
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @return       the iterator on the first inserted value
                         * @pre begin and end are not iterator from the dynamic array
                         */
                        template <class InputIterator>
                        Iterator insert(ConstIterator start, InputIterator begin, InputIterator end);
                        /**
                         * Insert a list of value at the specified position
                         * @param  start the position to insert values
                         * @param  list  the list to fill the dynamic array with
                         * @return       the iterator on the first inserted value
                         * @pre list don't contain dynamic array reference
                         */
                        Iterator insert(ConstIterator start, std::initializer_list<T> list);
                        /**
                         * Emplace an element at the specified position
                         * @param  start the position to insert the value
                         * @param  args  the value construction arguments
                         * @return       the iterator on the inserted value
                         */
                        template <class ... Args>
                        Iterator emplace(ConstIterator start, Args && ... args);
                        /**
                         * Erase an element in the dynamic array
                         * @param  pos  the position to erase
                         * @return       an iterator on the next valid element
                         */
                        Iterator erase(ConstIterator pos);
                        /**
                         * Erase a set of element from the dynamic array
                         * @param  begin the start position for erasing
                         * @param  end   the end position for erasing
                         * @return       an iterator on the next valid element
                         */
                        Iterator erase(ConstIterator begin, ConstIterator end);
                        /**
                         * Insert a copy of value at the end of the dynamic array
                         * @param value the value to insert
                         * @pre value don't reference a dynamic array item
                         */
                        void pushBack(T const& value);
                        /**
                         * Emplace a value at the end of the dynamic array
                         * @param value the value to insert
                         */
                        void pushBack(T && value);
                        /**
                         * Emplace a value at the end of the dynamic array
                         * @param args the arguments for the value construction
                         */
                        template <class ... Args>
                        void emplaceBack(Args && ... args);
                        /**
                         * Pop the last element in the dynamic array
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void popBack() {
                            *(end() - 1).~T();
                            length--;
                        }
                        /**
                         * Pop the last element in the dynamic array
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
                         * Swap the dynamic array with another dynamic array
                         * @param arr the other dynamic array
                         */
                        void swap(DynamicArray& arr);
        
                    //## Access Operator ##//
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        T& operator[](std::size_t index);
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        T const& operator[](std::size_t index) const;
        
                    //## Assignment Operator ##//
                        /**
                         * Copy arr into this
                         * @param arr the dynamic array to copy into this
                         * @return    the reference of himself
                         */
                        DynamicArray& operator =(DynamicArray const& arr);
                        /**
                         * Move arr into this
                         * @param arr the dynamic array to move into this
                         * @return    the reference of himself
                         */
                        DynamicArray& operator =(DynamicArray && arr);
        
                    //## Comparison Operator ##//
                        /**
                         * Equality test between this and arr
                         * @param arr the other dynamic array
                         * @return the test result
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        bool operator ==(DynamicArray const& arr) const {
                            bool equal = true;
                            std::size_t current = 0;
                            while (equal && current < length) {
                                equal = data[current] == arr[current];
                                current++;
                            }
                            return equal;
                        }
                        /**
                         * Equality test between this and arr
                         * @param arr the other dynamic array
                         * @return the test result
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        bool operator ==(DynamicArray const& arr) const {
                            if (length != arr.length) {
                                return false;
                            }
                            return std::memcmp(data, arr.data, length * sizeof(T)) == 0;
                        }
                        /**
                         * Inequality test between this and arr
                         * @param arr the other dynamic array
                         * @return the test result
                         */
                        bool operator !=(DynamicArray const& arr) const;
        
                    //## Stream Operator ##//
                        /**
                         * Convert the object into a string representation
                         * @return the converted object
                         */
                        String toString() const;
    
                private :   // Methods
                        /**
                         * Shift all element in the dynamic array, don't do reallocation
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void shift(std::size_t start, std::size_t count) {
                            for (std::size_t index = length + count - 1; index != start + count - 1; index--) {
                                new(&data[index]) T (std::move(data[index - count]));
                            }
                        }
                        /**
                         * Shift all element in the dynamic array, don't do reallocation
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void shift(std::size_t start, std::size_t count) {
                            std::memmove(data + start + count, data + start, (length - start) * sizeof(T));
                        }
                        /**
                         * Shift back all element in the dynamic array, don't call deconstructor
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void shiftBack(std::size_t start, std::size_t count) {
                            for (std::size_t index = start; index < start + count; index++) {
                                new(&data[index]) T (std::move(data[index + count]));
                            }
                        }
                        /**
                         * Shift back all element in the dynamic array, don't call deconstructor
                         * @param start the start position for shifting
                         * @param count the number of shift to do
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void shiftBack(std::size_t start, std::size_t count) {
                            std::memmove(data + start, data + start + count, (length - start) * sizeof(T));
                        }
                        /**
                         * Copy the dynamic array content
                         * @param arr the dynamic array to copy
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void copy(DynamicArray const& arr) {
                            std::size_t current = 0;
                            for (T const& it : arr) {
                                new(&data[current]) T (it);
                                current++;
                            }
                        }
                        /**
                         * Copy the dynamic array content
                         * @param arr the dynamic array to copy
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void copy(DynamicArray const& arr) {
                            std::memcpy(data, arr.data, arr.length * sizeof(T));
                        }
                        /**
                         * Move the dynamic array content
                         * @param arr the dynamic array to move
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        void move(DynamicArray const& arr) {
                            std::size_t current = 0;
                            for (T const& it : arr) {
                                new(&data[current]) T (std::move(it));
                                current++;
                            }
                        }
                        /**
                         * Move the dynamic array content
                         * @param arr the dynamic array to move
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        void move(DynamicArray const& arr) {
                            std::memmove(data, arr.data, arr.length * sizeof(T));
                        }
            };
        
        }
    }

    #include "NRE_DynamicArray.tpp"
