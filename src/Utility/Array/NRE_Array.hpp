
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
             * @class Array
             * @brief A fixed size array
             */
            template <class T, std::size_t Size>
            class Array : public Stringable<Array<T, Size>> {
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
                         * Cosntruct the array from a list
                         * @param list the list of value
                         */
                        Array(std::initializer_list<T> list);

                    //## Copy Constructor ##//
                        /**
                         * Copy arr into this
                         * @param arr the array to copy
                         */
                        Array(Array const& arr) = default;

                    //## Move Constructor ##//
                        /**
                         * Move arr into this
                         * @param arr the array to move
                         */
                        Array(Array && arr) = default;

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
                         * @return if the array is empty
                         */
                        constexpr bool isEmpty() const;
                        /**
                         * @return the array size
                         */
                        constexpr std::size_t getSize() const;
                        /**
                         * @return the maximum array size
                         */
                        constexpr std::size_t getMaxSize() const;

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
                         * Fill the array with the same value
                         * @param value the value to fill the array with
                         */
                        void fill(T const& value);
                        /**
                         * Swap this data with arr data
                         * @param arr the container to swap with
                         */
                        void swap(Array& arr) noexcept;

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
                         * Copy assignment of arr into this
                         * @param arr the array to copy into this
                         * @return    the reference of himself
                         */
                        Array& operator =(Array const& arr) = default;
                        /**
                         * Move assignment of arr into this, leaving o empty
                         * @param arr the array to move into this
                         * @return    the reference of himself
                         */
                        Array& operator =(Array && arr) = default;

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
                            return std::memcmp(data, arr.data, Size * sizeof(T)) == 0;
                        }
                        /**
                         * Inequality test between this and arr
                         * @param arr the other array
                         * @return the test result
                         */
                        bool operator !=(Array const& arr) const;

                    //## Stream Operator ##//
                        /**
                         * Convert the object into a string representation
                         * @return the converted object
                         */
                        String toString() const;
            };
        }
    }

    #include "NRE_Array.tpp"
