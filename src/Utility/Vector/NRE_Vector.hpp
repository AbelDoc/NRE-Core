
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
             * @class Vector
             * @brief A dynamic array, garantee to be in contiguous memory
             */
            template <class T>
            class Vector {
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
                    std::size_t capacity;   /**< The data length */
                    T* data;                /**< The internal data array */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct an empty vector
                         */
                        inline Vector() : length(0), capacity(1), data(static_cast <T*> (::operator new (sizeof(T)))) {
                        }
                        /**
                         * Construct a vector filled with count copy of value
                         * @param count the number of copy to perform, will be the vector capacity and length
                         * @param value the value to fill the vector with
                         */
                        inline Vector(std::size_t count, T const& value) : length(count), capacity(count), data(static_cast <T*> (::operator new (count * sizeof(T)))) {
                            assign(count, value);
                        }
                        /**
                         * Construct a vector filled with count default value
                         * @paramcount the number of default element, will be the vector capacity and length
                         */
                        inline Vector(std::size_t count) : length(count), capacity(count), data(new T[count]()) {
                        }
                        /**
                         * Construct a vector filled with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         */
                        template <class InputIterator>
                        inline Vector(InputIterator begin, InputIterator end) : length(std::distance(begin, end)), capacity(length), data(static_cast <T*> (::operator new (length * sizeof(T)))) {
                            assign(begin, end);
                        }
                        /**
                         * Construct a vector from an initializer list
                         * @param  init the list to fill the vector with
                         */
                        inline Vector(std::initializer_list<T> init) : length(init.size()), capacity(length), data(static_cast <T*> (::operator new (length * sizeof(T)))) {
                            std::size_t current = 0;
                            for (auto it = init.begin(); it != init.end(); it++) {
                                data[current] = std::move(*it);
                                current++;
                            }
                        }

                    //## Copy Constructor ##//
                        /**
                         * Copy vec into this
                         * @param  vec the vector to copy
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        inline Vector(Vector const& vec) : length(vec.length), capacity(vec.capacity), data(static_cast <T*> (::operator new (capacity * sizeof(T)))) {
                            std::size_t current = 0;
                            for (T const& it : vec) {
                                data[current] = it;
                                current++;
                            }
                        }
                        /**
                         * Copy vec into this
                         * @param  vec the vector to copy
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        inline Vector(Vector const& vec) : length(vec.length), capacity(vec.capacity), data(static_cast <T*> (::operator new (capacity * sizeof(T)))) {
                            std::memcpy(data, vec.data, length * sizeof(T));
                        }

                    //## Move Constructor ##//
                        /**
                         * Move vec into this
                         * @param  vec the vector to copy
                         */
                        inline Vector(Vector && vec) : length(vec.length), capacity(vec.capacity), data(std::move(vec.data)) {
                            vec.length = 0;
                            vec.capacity = 0;
                            vec.data = nullptr;
                        }

                    //## Deconstructor ##//
                        /**
                         * Vector Deconstructor
                         */
                        inline ~Vector() {
                            if (length > 0) {
                                delete[] data;
                            }
                        }

                    //## Getter ##//
                        /**
                         * Access a particular element with bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        inline T& get(std::size_t index) {
                            if (index >= length) {
                                throw std::out_of_range("Accessing NRE::Utility::Vector element : " + std::to_string(index) + " while vector length is " + std::to_string(length) + ".");
                            }
                            return data[index];
                        }
                        /**
                         * Access a particular element with bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        inline T const& get(std::size_t index) const {
                            if (index >= length) {
                                throw std::out_of_range("Accessing NRE::Utility::Vector element : " + std::to_string(index) + " while vector length is " + std::to_string(length) + ".");
                            }
                            return data[index];
                        }
                        /**
                         * @return the internal data array
                         */
                        inline T* getData() {
                            return data;
                        }
                        /**
                         * @return the internal data array
                         */
                        inline const T* getData() const {
                            return data;
                        }
                        /**
                         * @return the first element
                         */
                        inline T& getFront() {
                            return data[0];
                        }
                        /**
                         * @return the first element
                         */
                        inline T const& getFront() const {
                            return data[0];
                        }
                        /**
                         * @return the last element
                         */
                        inline T& getLast() {
                            return data[length - 1];
                        }
                        /**
                         * @return the last element
                         */
                        inline T const& getLast() const {
                            return data[length - 1];
                        }
                        /**
                         * @return the vector effective size
                         */
                        inline std::size_t getSize() const {
                            return length;
                        }
                        /**
                         * @return the maximum array size
                         */
                        inline constexpr std::size_t getMaxSize() const {
                            return std::numeric_limits<std::size_t>::max();
                        }
                        /**
                         * @return the vector capacity
                         */
                        inline std::size_t getCapacity() const {
                            return capacity;
                        }
                        /**
                         * @return if the array is empty
                         */
                        inline constexpr bool isEmpty() const {
                            return length == 0;
                        }

                    //## Iterator Access ##//
                        /**
                         * @return an iterator on the first element
                         */
                        inline Iterator begin() {
                            return data;
                        }
                        /**
                         * @return a const iterator on the first element
                         */
                        inline ConstIterator begin() const {
                            return data;
                        }
                        /**
                         * @return an iterator on the end of the container
                         */
                        inline Iterator end() {
                            return data + length;
                        }
                        /**
                         * @return a const iterator on the end of the container
                         */
                        inline ConstIterator end() const {
                            return data + length;
                        }
                        /**
                         * @return a reverse iterator on the first element
                         */
                        inline ReverseIterator rbegin() {
                            return ReverseIterator(data + length);
                        }
                        /**
                         * @return a const reverse iterator on the first element
                         */
                        inline ConstReverseIterator rbegin() const {
                            return ConstReverseIterator(data + length);
                        }
                        /**
                         * @return a reverse iterator on the end of the container
                         */
                        inline ReverseIterator rend() {
                            return ReverseIterator(data);
                        }
                        /**
                         * @return a const reverse iterator on the end of the container
                         */
                        inline ConstReverseIterator rend() const {
                            return ConstReverseIterator(data);
                        }

                    //## Methods ##//
                        /**
                         * Assign the vector with count copy of value, starting from the beginning
                         * @param count the number of copy
                         * @param value the copy to fill the vector with
                         */
                        inline void assign(std::size_t count, T const& value) {
                            clear();
                            for (std::size_t i = 0; i < count; i++) {
                                data[i] = value;
                            }
                        }
                        /**
                         * Assign the vector with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         */
                        template <class InputIterator>
                        inline void assign(InputIterator begin, InputIterator end) {
                            clear();
                            std::size_t current = 0;
                            for ( ; begin != end; begin++) {
                                data[current] = *(begin);
                                current++;
                            }
                            length = current;
                        }
                        /**
                         * Set the vector capacity to a minimum of size, reallocating memory if needed
                         * @param size the new capacity
                         * @warning size value is not checked against getMaxSize()
                         */
                        inline void reserve(std::size_t size) {
                            if (capacity < size) {
                                reallocate(size);
                            }
                        }
                        /**
                         * Clear all object in the vector, not actually releasing memory
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        inline void clear() noexcept {
                            for (std::size_t i = 0; i < length; i++) {
                                data[i].~T();
                            }
                            length = 0;
                        }
                        /**
                         * Clear all object in the vector, not actually releasing memory
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        inline void clear() noexcept {
                            length = 0;
                        }
                        /**
                         * Insert a copy of value at the specified position
                         * @param  start the position to insert the value
                         * @param  value the value to insert
                         * @return       the iterator on the inserted value
                         */
                        inline Iterator insert(ConstIterator start, T const& value) {
                            std::size_t index = start - ConstIterator(data);
                            if (capacity < length + 1) {
                                reallocate();
                            }
                            shift(index, 1);
                            length++;
                            data[index] = value;
                            return Iterator(data + index);
                        }
                        /**
                         * Insert count copy of value at the specified position
                         * @param  start the position to insert values
                         * @param  count the number of copy
                         * @param  value the value to insert
                         * @return       the iterator on the first inserted value
                         */
                        inline Iterator insert(ConstIterator start, std::size_t count, T const& value) {
                            std::size_t index = start - ConstIterator(data);
                            if (capacity < length + count) {
                                reserveWithGrowFactor(length + count);
                            }
                            shift(index, count);
                            for (std::size_t it = index; it != index + count; it++) {
                                data[it] = value;
                            }
                            length += count;
                            return Iterator(data + index);
                        }
                        /**
                         * Insert a copy of element between begin and end at the specified position
                         * @param  start the position to insert values
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @return       the iterator on the first inserted value
                         */
                        template <class InputIterator>
                        inline Iterator insert(ConstIterator start, InputIterator begin, InputIterator end) {
                            std::size_t count = std::distance(begin, end);
                            std::size_t index = start - ConstIterator(data);
                            if (capacity < length + count) {
                                reserveWithGrowFactor(length + count);
                            }
                            shift(index, count);
                            for ( ; begin != end; begin++) {
                                data[index] = *begin;
                                index++;
                            }
                            length += count;
                            return Iterator(data + index);
                        }
                        /**
                         * Insert a list of value at the specified position
                         * @param  start the position to insert values
                         * @param  init  the list to fill the vector with
                         * @return       the iterator on the first inserted value
                         */
                        inline Iterator insert(ConstIterator start, std::initializer_list<T> list) {
                            std::size_t count = list.size();
                                std::size_t index = start - ConstIterator(data);
                            if (capacity < length + count) {
                                reserveWithGrowFactor(length + count);
                            }
                            shift(index, count);
                            for (auto it = list.begin(); it != list.end(); it++) {
                                data[index] = std::move(*it);
                                index++;
                            }
                            length += count;
                            return Iterator(data + index);
                        }
                        /**
                         * Emplace an element at the specified position
                         * @param  start the position to insert the value
                         * @param  args  the value construction arguments
                         * @return       the iterator on the inserted value
                         */
                        template <class ... Args>
                        inline Iterator emplace(ConstIterator start, Args && ... args) {
                            std::size_t index = start - ConstIterator(data);
                            if (capacity < length + 1) {
                                reallocate();
                            }
                            shift(index, 1);
                            data[index] = T(std::forward<Args>(args)...);
                            return Iterator(data + index);
                        }
                        /**
                         * Erase an element in the vector
                         * @param  pos  the position to erase
                         * @return       an iterator on the next valid element
                         */
                        inline Iterator erase(ConstIterator pos) {
                            (*pos).~T();
                            shiftBack(pos - ConstIterator(data), 1);
                            length--;
                            return Iterator(pos++);
                        }
                        /**
                         * Erase a set of element from the vector
                         * @param  begin the start position for erasing
                         * @param  end   the end position for erasing
                         * @return       an iterator on the next valid element
                         */
                        inline Iterator erase(ConstIterator begin, ConstIterator end) {
                            std::size_t count = std::distance(begin, end);
                            for (auto it = begin; it != end; it++) {
                                (*it).~T();
                            }
                            shiftBack(begin - ConstIterator(data), count);
                            length -= count;
                            return Iterator(end);
                        }
                        /**
                         * Insert a copy of value at the end of the vector
                         * @param value the value to insert
                         */
                        inline void pushBack(T const& value) {
                            if (capacity < length + 1) {
                                reallocate();
                            }
                            *(end()) = value;
                            length++;
                        }
                        /**
                         * Emplace a value at the end of the vector
                         * @param value the value to insert
                         */
                        inline void pushBack(T && value) {
                            if (capacity < length + 1) {
                                reallocate();
                            }
                            *(end()) = value;
                            length++;
                        }
                        /**
                         * Emplace a value at the end of the vector
                         * @param args the arguments for the value construction
                         */
                        template <class ... Args>
                        inline void emplaceBack(Args && ... args) {
                            if (capacity < length + 1) {
                                reallocate();
                            }
                            *(end()) = T(std::forward<Args>(args)...);
                            length++;
                        }
                        /**
                         * Pop the last element in the vector
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        inline void popBack() {
                            *(end() - 1).~T();
                            length--;
                        }
                        /**
                         * Pop the last element in the vector
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        inline void popBack() {
                            length--;
                        }
                        /**
                         * Resize the container up the given size, insert value if needed
                         * @param count the new capacity
                         */
                        inline void resize(std::size_t count) {
                            resize(count, T());
                        }
                        /**
                         * Resize the container up the given size, insert value if needed
                         * @param count the new capacity
                         * @param value the value used when inserting
                         */
                        inline void resize(std::size_t count, T const& value) {
                            if (capacity < count) {
                                reallocate(count);
                                Iterator end(end() + count);
                                for (auto it = end(); it != end; it++) {
                                    *it = value;
                                }
                            }
                        }
                        /**
                         * Swap the vector with an other vector
                         * @param vec the other vector
                         */
                        inline void swap(Vector& vec) {
                            using namespace std;
                            swap(length, vec.length);
                            swap(capacity, vec.capacity);
                            swap(data, vec.data);
                        }

                    //## Access Operator ##//
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        inline T& operator[](std::size_t index) {
                            return data[index];
                        }
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        inline T const& operator[](std::size_t index) const {
                            return data[index];
                        }

                    //## Assignment Operator ##//
                        /**
                         * Copy vec into this
                         * @param vec the vector to copy into this
                         * @return    the reference of himself
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        inline Vector& operator =(Vector const& vec) {
                            if (vec.data != data) {
                                clear();
                                length = vec.length;
                                capacity = vec.capacity;
                                data = static_cast <T*> (::operator new(capacity * sizeof(T)));

                                std::size_t current = 0;
                                for (T const& it : vec) {
                                    data[current] = it;
                                    current++;
                                }
                                return *this;
                            }
                        }
                        /**
                         * Copy vec into this
                         * @param vec the vector to copy into this
                         * @return    the reference of himself
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        inline Vector& operator =(Vector const& vec) {
                            if (vec.data != data) {
                                clear();
                                length = vec.length;
                                capacity = vec.capacity;
                                data = static_cast <T*> (::operator new(capacity * sizeof(T)));

                                std::memcpy(data, vec.data, length * sizeof(T));
                                return *this;
                            }
                        }
                        /**
                         * Move vec into this
                         * @param vec the vector to move into this
                         * @return    the reference of himself
                         */
                        inline Vector& operator =(Vector && vec) {
                            if (vec.data != data) {
                                clear();
                                length = vec.length;
                                capacity = vec.capacity;
                                data = std::move(vec.data);

                                vec.length = 0;
                                vec.capacity = 0;
                                vec.data = nullptr;
                            }
                        }

                    //## Comparison Operator ##//
                        /**
                         * Equality test between this and vec
                         * @param vec the other vector
                         * @return the test result
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        inline bool operator ==(Vector const& vec) const {
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
                         * @return the test result
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        inline bool operator ==(Vector const& vec) const {
                            if (length != vec.length) {
                                return false;
                            }
                            return std::memcmp(data, vec.data, length * sizeof(T)) == 0;
                        }
                        /**
                         * Inequality test between this and vec
                         * @param vec the other vector
                         * @return the test result
                         */
                        inline bool operator !=(Vector const& vec) const {
                            return !(*this == vec);
                        }

                private :   // Methods
                    /**
                     * Reallocate and grow the storage capacity
                     */
                    inline void reallocate() {
                        reallocate(static_cast <std::size_t> (static_cast <float> (capacity) * GROW_FACTOR));
                    }
                    /**
                     * Rellocate the data to the given size
                     * @param newSize the new capacity
                     */
                    template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                    inline void reallocate(std::size_t newSize) {
                        capacity = newSize;
                        T* newData = static_cast <T*> (::operator new(capacity * sizeof(T)));

                        for (std::size_t current = 0; current < length; current++) {
                            newData[current] = std::move(data[current]);
                        }
                        ::operator delete(data);
                        data = newData;
                    }
                    /**
                     * Rellocate the data to the given size
                     * @param newSize the new capacity
                     */
                    template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                    inline void reallocate(std::size_t newSize) {
                        capacity = newSize;
                        T* newData = static_cast <T*> (::operator new(capacity * sizeof(T)));

                        std::memmove(newData, data, length * sizeof(T));
                        ::operator delete(data);
                        data = newData;
                    }
                    /**
                     * Reallocate the vector with the neareast grow factor value
                     * @param size the new minimum capacity
                     */
                    inline void reserveWithGrowFactor(std::size_t size) {
                        std::size_t newSize = static_cast <std::size_t> (static_cast <float> (capacity) * GROW_FACTOR);
                        while (newSize < size) {
                            newSize = static_cast <std::size_t> (static_cast <float> (capacity) * GROW_FACTOR);
                        }
                        reallocate(newSize);
                    }
                    /**
                     * Shift all element in the vector, don't do reallocation
                     * @param start the start position for shifting
                     * @param count the number of shift to do
                     */
                    template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                    inline void shift(std::size_t start, std::size_t count) {
                        for (std::size_t index = length + count - 1; index != start + count - 1; index--) {
                            data[index] = std::move(data[index - count]);
                        }
                    }
                    /**
                     * Shift all element in the vector, don't do reallocation
                     * @param start the start position for shifting
                     * @param count the number of shift to do
                     */
                    template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                    inline void shift(std::size_t start, std::size_t count) {
                        std::memmove(data + start + count, data + start, (length - start) * sizeof(T));
                    }
                    /**
                     * Shift back all element in the vector, don't call deconstructor
                     * @param start the start position for shifting
                     * @param count the number of shift to do
                     */
                    template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                    inline void shiftBack(std::size_t start, std::size_t count) {
                        for (std::size_t it = start; it < start + count; it++) {
                            data[it] = std::move(data[it + count]);
                        }
                    }
                    /**
                     * Shift back all element in the vector, don't call deconstructor
                     * @param start the start position for shifting
                     * @param count the number of shift to do
                     */
                    template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                    inline void shiftBack(std::size_t start, std::size_t count) {
                        std::memmove(data + start, data + start + count, (length - start) * sizeof(T));
                    }

                private :    // Static
                    static constexpr float GROW_FACTOR = 2;
            };
        }
    }
