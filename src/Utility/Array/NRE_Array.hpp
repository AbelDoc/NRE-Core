
    /**
     * @file NRE_Array.hpp
     * @brief Declaration of Utility's API's Container : Array
     * @author Louis ABEL
     * @date 14/05/2019
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
             * @class Array
             * @brief A fixed size array
             */
            template <class T, std::size_t Size>
            class Array : public Stringable<Array<T, Size>> {
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
                    ValueType data[Size];   /**< The internal array */

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
                         * @return if the array is empty
                         */
                        constexpr bool isEmpty() const;
                        /**
                         * @return the array size
                         */
                        constexpr SizeType getSize() const;
                        /**
                         * @return the maximum array size
                         */
                        constexpr SizeType getMaxSize() const;

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
                        void fill(ConstReference value);
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
                        Reference operator[](SizeType index);
                        /**
                         * Access a particular element without bound checking
                         * @param  index the element index
                         * @return       the corresponding element
                         */
                        ConstReference operator[](SizeType index) const;

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
                        template <class K = T, typename Utility::UseIfNotTriviallyCopyable<K> = 0>
                        bool operator ==(Array const& arr) const {
                            bool equal = true;
                            SizeType current = 0;
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
                        template <class K = T, typename Utility::UseIfTriviallyCopyable<K> = 0>
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
                        [[nodiscard]] String toString() const;
            };
        }
    }

    #include "NRE_Array.tpp"
