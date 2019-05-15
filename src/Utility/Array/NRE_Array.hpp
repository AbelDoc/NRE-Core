
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
             * @brief Describe an observable object, coupled with observer
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
                        inline Array(Args && ... args) : data{static_cast <T> (std::forward<Args>(args))...} {
                        }

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
                        inline T& get(std::size_t index) {
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
                        inline T const& get(std::size_t index) const {
                            if (index >= Size) {
                                throw std::out_of_range("Accessing NRE::Utility::Array element : " + std::to_string(index) + " while array has " + std::to_string(Size) + " maximum capacity.");
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
                            return data[Size - 1];
                        }
                        /**
                         * @return the last element
                         */
                        inline T const& getLast() const {
                            return data[Size - 1];
                        }

                    //## Iterator Access ##//
                        /**
                         * @return an iterator on the first element
                         */
                        inline Iterator begin() {
                            return data;
                        }
                        /**
                         * @return an iterator on the first element
                         */
                        inline ConstIterator begin() const {
                            return data;
                        }
                        /**
                         * @return an iterator on the end of the container
                         */
                        inline Iterator end() {
                            return data + Size;
                        }
                        /**
                         * @return an iterator on the end of the container
                         */
                        inline ConstIterator end() const {
                            return data + Size;
                        }
                        /**
                         * @return an iterator on the first element
                         */
                        inline ReverseIterator rbegin() {
                            return ReverseIterator(data + Size);
                        }
                        /**
                         * @return an iterator on the first element
                         */
                        inline ConstReverseIterator rbegin() const {
                            return ConstReverseIterator(data + Size);
                        }
                        /**
                         * @return an iterator on the end of the container
                         */
                        inline ReverseIterator rend() {
                            return ReverseIterator(data - 1);
                        }
                        /**
                         * @return an iterator on the end of the container
                         */
                        inline ConstReverseIterator rend() const {
                            return ConstReverseIterator(data - 1);
                        }

                    //## Methods ##//
                        /**
                         * @return if the array is empty
                         */
                        inline constexpr bool isEmpty() const {
                            return Size == 0;
                        }
                        /**
                         * @return the array size
                         */
                        inline constexpr std::size_t getSize() const {
                            return Size;
                        }
                        /**
                         * @return the maximum array size
                         */
                        inline constexpr std::size_t getMaxSize() const {
                            return std::numeric_limits<std::size_t>::max();
                        }
                        /**
                         * Fill the array with the same value
                         * @param value the value to fill the array with
                         */
                        inline void fill(T const& value) {
                            for (std::size_t i = 0; i < Size; i++) {
                                data[i] = value;
                            }
                        }
                        /**
                         * Swap this data with arr data
                         * @param arr the container to swap with
                         */
                        inline void swap(Array& arr) noexcept {
                            std::swap(data, arr.data);
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
                         * Copy assignment of o into this
                         * @param arr the observable to copy into this
                         * @return    the reference of himself
                         */
                        inline Array& operator =(Array const& arr) = default;
                        /**
                         * Move assignment of o into this, leaving o empty
                         * @param arr the observable to move into this
                         * @return    the reference of himself
                         */
                        inline Array& operator =(Array && arr) = default;
            };

        }
    }
