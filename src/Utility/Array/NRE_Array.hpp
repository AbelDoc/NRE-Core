
    /**
     * @file NRE_Array.hpp
     * @brief Declaration of Utility's API's Container : Array
     * @author Louis ABEL
     * @date 14/05/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <string>
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
             * @class Array
             * @brief A fixed size array
             */
            template <class T, std::size_t Size>
            class Array {
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
                    T data[Size];   /**< The internal array */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the default array
                         */
                        Array() = default;
                        /**
                         * Cosntruct the array from an initialisation pack
                         * @param args the pack of value to set in the array
                         */
                        template <class ... Args>
                        Array(Args && ... args) : data{static_cast <T> (std::forward<Args>(args))...} {
                        }

                    //## Copy Constructor ##//
                        /**
                         * Copy arr into this
                         * @param arr the array to copy
                         */
                        Array(Array const& arr) {
                            copy(arr);
                        }

                    //## Move Constructor ##//
                        /**
                         * Move arr into this
                         * @param arr the array to move
                         */
                        Array(Array && arr) {
                            move(arr);
                        }

                    //## Deconstructor ##//
                        /**
                         * Array Deconstructor
                         */
                        ~Array() = default;

                    //## Getter ##//
                        /**
                         * Access a particular element with bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        T& get(std::size_t index) {
                            if (index >= Size) {
                                throw std::out_of_range("Accessing NRE::Utility::Array element : " + std::to_string(index) + " while array has " + std::to_string(Size) + " maximum capacity.");
                            }
                            return data[index];
                        }
                        /**
                         * Access a particular element with bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        T const& get(std::size_t index) const {
                            if (index >= Size) {
                                throw std::out_of_range("Accessing NRE::Utility::Array element : " + std::to_string(index) + " while array has " + std::to_string(Size) + " maximum capacity.");
                            }
                            return data[index];
                        }
                        /**
                         * @return the internal data array
                         */
                        T* getData() {
                            return data;
                        }
                        /**
                         * @return the internal data array
                         */
                        const T* getData() const {
                            return data;
                        }
                        /**
                         * @return the first element
                         */
                        T& getFront() {
                            return data[0];
                        }
                        /**
                         * @return the first element
                         */
                        T const& getFront() const {
                            return data[0];
                        }
                        /**
                         * @return the last element
                         */
                        T& getLast() {
                            return data[Size - 1];
                        }
                        /**
                         * @return the last element
                         */
                        T const& getLast() const {
                            return data[Size - 1];
                        }
                        /**
                         * @return if the array is empty
                         */
                        constexpr bool isEmpty() const {
                            return Size == 0;
                        }
                        /**
                         * @return the array size
                         */
                        constexpr std::size_t getSize() const {
                            return Size;
                        }
                        /**
                         * @return the maximum array size
                         */
                        constexpr std::size_t getMaxSize() const {
                            return Size;
                        }

                    //## Iterator Access ##//
                        /**
                         * @return an iterator on the first element
                         */
                        Iterator begin() {
                            return data;
                        }
                        /**
                         * @return a const iterator on the first element
                         */
                        ConstIterator begin() const {
                            return data;
                        }
                        /**
                         * @return an iterator on the end of the container
                         */
                        Iterator end() {
                            return data + Size;
                        }
                        /**
                         * @return a const iterator on the end of the container
                         */
                        ConstIterator end() const {
                            return data + Size;
                        }
                        /**
                         * @return a reverse iterator on the first element
                         */
                        ReverseIterator rbegin() {
                            return ReverseIterator(data + Size);
                        }
                        /**
                         * @return a const reverse iterator on the first element
                         */
                        ConstReverseIterator rbegin() const {
                            return ConstReverseIterator(data + Size);
                        }
                        /**
                         * @return a reverse iterator on the end of the container
                         */
                        ReverseIterator rend() {
                            return ReverseIterator(data);
                        }
                        /**
                         * @return a const reverse iterator on the end of the container
                         */
                        ConstReverseIterator rend() const {
                            return ConstReverseIterator(data);
                        }

                    //## Methods ##//
                        /**
                         * Fill the array with the same value
                         * @param value the value to fill the array with
                         */
                        void fill(T const& value) {
                            for (std::size_t i = 0; i < Size; i++) {
                                data[i] = value;
                            }
                        }
                        /**
                         * Swap this data with arr data
                         * @param arr the container to swap with
                         */
                        void swap(Array& arr) noexcept {
                            using namespace std;
                            swap(data, arr.data);
                        }

                    //## Access Operator ##//
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        T& operator[](std::size_t index) {
                            return data[index];
                        }
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        T const& operator[](std::size_t index) const {
                            return data[index];
                        }

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of o into this
                         * @param arr the observable to copy into this
                         * @return    the reference of himself
                         */
                        Array& operator =(Array const& arr) {
                            copy(arr);
                            return *this;
                        }
                        /**
                         * Move assignment of o into this, leaving o empty
                         * @param arr the observable to move into this
                         * @return    the reference of himself
                         */
                        Array& operator =(Array && arr) {
                            move(arr);
                            return *this;
                        }

                    //## Comparison Operator ##//
                        /**
                         * Equality test between this and arr
                         * @param arr the other array
                         * @return the test result
                         */
                        template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                        bool operator ==(Array const& arr) const {
                            bool equal = true;
                            std::size_t current = 0;
                            while (equal && current < Size) {
                                equal = data[current] == arr[current];
                                current++;
                            }
                            return equal;
                        }
                        /**
                         * Equality test between this and arr
                         * @param arr the other array
                         * @return the test result
                         */
                        template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                        bool operator ==(Array const& arr) const {
                            return std::memcmp(data, arr.data, Size * sizeof(T));
                        }
                        /**
                         * Inequality test between this and arr
                         * @param arr the other array
                         * @return the test result
                         */
                        bool operator !=(Array const& arr) const {
                            return !(*this == arr);
                        }
                private :   // Methods
                    /**
                     * Copy the array content
                     * @param arr the array to copy
                     */
                    template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                    void copy(Array const& arr) {
                        for (std::size_t index = 0; index < Size; index++) {
                            data[index] = arr[index];
                        }
                    }
                    /**
                     * Copy the array content
                     * @param arr the array to copy
                     */
                    template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                    void copy(Array const& arr) {
                        std::memcpy(data, arr.data, Size * sizeof(T));
                    }
                    /**
                     * Move the array content
                     * @param arr the array to move
                     */
                    template <typename U = T, typename std::enable_if<!std::is_pod<U>::value, int>::type = 0>
                    void move(Array && arr) {
                        for (std::size_t index = 0; index < Size; index++) {
                            data[index] = std::move(arr[index]);
                        }
                    }
                    /**
                     * Move the array content
                     * @param arr the array to move
                     */
                    template <typename U = T, typename std::enable_if<std::is_pod<U>::value, int>::type = 0>
                    void move(Array && arr) {
                        std::memcpy(data, arr.data, Size * sizeof(T));
                    }
            };

        }
    }
