
    /**
     * @file NRE_String.hpp
     * @brief Declaration of Utility's API's Container : String
     * @author Louis ABEL
     * @date 16/05/2019
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
             * @class BasicString
             * @brief A basic template string, with dynamic size, guarantee to be in contiguous memory
             */
            template <class T>
            class BasicString {
                static_assert(std::is_scalar<T>::value, "You can't use BasicString with non-scalar types"); // Only work with POD types but restreign to scalar type
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
                         * Construct an empty string
                         */
                        BasicString();
                        /**
                         * Construct a string filled with count copy of value
                         * @param count the number of copy to perform, will be the string capacity and length
                         * @param value the value to fill the string with
                         * @pre value don't reference a string item
                         */
                        BasicString(std::size_t count, T value);
                        /**
                         * Construct a string with count element starting at pos from str
                         * @param pos   the start position
                         * @param count the number of element to take from str
                         * @param str   the other string
                         */
                        BasicString(std::size_t pos, std::size_t count, BasicString const& str);
                        /**
                         * Construct a string with count first element from str
                         * @param count the number of element to take from str
                         * @param str   the other string
                         */
                        BasicString(std::size_t count, const T* str);
                        /**
                         * Construct a string filled with str element, str need to be terminated by a null character
                         * @param str the other string
                         */
                        BasicString(const T* str);
                        /**
                         * Construct a string filled with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @pre begin and end are not iterator from the string
                         */
                        template <class InputIterator>
                        BasicString(InputIterator begin, InputIterator end);
                        /**
                         * Construct a string from an initializer list
                         * @param  init the list to fill the string with
                         * @pre list don't contain string reference
                         */
                        BasicString(std::initializer_list<T> init);

                    //## Copy Constructor ##//
                        /**
                         * Copy str into this
                         * @param  str the string to copy
                         */
                        BasicString(BasicString const& str);

                    //## Move Constructor ##//
                        /**
                         * Move str into this
                         * @param  str the string to copy
                         */
                        BasicString(BasicString && str);

                    //## Deconstructor ##//
                        /**
                         * BasicString Deconstructor
                         */
                        ~BasicString();

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
                        const T* getData() const;
                        /**
                         * @return the internal data array
                         */
                        const T* getCData() const;
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
                         * @return the string effective size
                         */
                        std::size_t getSize() const;
                        /**
                         * @return the string effective size
                         */
                        std::size_t getLength() const;
                        /**
                         * @return the maximum array size
                         */
                        constexpr std::size_t getMaxSize() const;
                        /**
                         * @return the string capacity
                         */
                        std::size_t getCapacity() const;
                        /**
                         * @return if the array is empty
                         */
                        constexpr bool isEmpty() const;

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
                         * @return an iterator on the end of the container
                         */
                        Iterator end();
                        /**
                         * @return a const iterator on the end of the container
                         */
                        ConstIterator end() const;
                        /**
                         * @return a reverse iterator on the first element
                         */
                        ReverseIterator rbegin();
                        /**
                         * @return a const reverse iterator on the first element
                         */
                        ConstReverseIterator rbegin() const;
                        /**
                         * @return a reverse iterator on the end of the container
                         */
                        ReverseIterator rend();
                        /**
                         * @return a const reverse iterator on the end of the container
                         */
                        ConstReverseIterator rend() const;

                    //## Methods ##//
                        /**
                         * Assign the string with count copy of value, starting from the beginning
                         * @param count the number of copy
                         * @param value the copy to fill the string with
                         * @pre value don't reference a string item
                         */
                        BasicString& assign(std::size_t count, T value);
                        /**
                         * Replace the string content with the given one
                         * @param str  the other string
                         * @return     the reference on himself
                         */
                        BasicString& assign(BasicString const& str);
                        /**
                         * Replace the string content with count element starting at pos from str
                         * @param pos   the start position
                         * @param count the number of element to take from str
                         * @param str   the other string
                         */
                        BasicString& assign(std::size_t pos, std::size_t count, BasicString const& str);
                        /**
                         * Replace the string content with the given one
                         * @param str  the other string
                         * @return     the reference on himself
                         */
                        BasicString& assign(BasicString && str);
                        /**
                         * Replace the string content with count first element from str
                         * @param count the number of element to take from str
                         * @param str   the other string
                         */
                        BasicString& assign(std::size_t count, const T* str);
                        /**
                         * Replace the string content filled with str element, str need to be terminated by a null character
                         * @param str the other string
                         */
                        BasicString& assign(const T* str);
                        /**
                         * Replace the string content with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @pre begin and end are not iterator from the string
                         */
                        template <class InputIterator>
                        BasicString& assign(InputIterator begin, InputIterator end);
                        /**
                         * Replace the string content with content from an initializer list
                         * @param  init the list to fill the string with
                         * @pre list don't contain string reference
                         */
                        BasicString& assign(std::initializer_list<T> init);

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
                         * Copy str into this
                         * @param str the string to copy into this
                         * @return    the reference of himself
                         */
                        BasicString& operator =(BasicString const& str);
                        /**
                         * Move str into this
                         * @param str the string to move into this
                         * @return    the reference of himself
                         */
                        BasicString& operator =(BasicString && str);

                private :   // Methods
                    /**
                     * Reallocate and grow the storage capacity
                     */
                    void reallocate();
                    /**
                     * Rellocate the data to the given size
                     * @param newSize the new capacity
                     */
                    void reallocate(std::size_t newSize);
                    /**
                     * Reallocate the string with the neareast grow factor value
                     * @param size the new minimum capacity
                     */
                    void reserveWithGrowFactor(std::size_t size);
                    /**
                     * Add the null terminated character at the end
                     */
                    void addNullTerminated();

                private :    // Static
                    static constexpr float GROW_FACTOR = 1.5;
                    static constexpr std::size_t BASE_ALLOCATION_SIZE = 8;
            };

            typedef BasicString<char>    String;
            typedef BasicString<wchar_t> WideString;
        }
    }

    #include "NRE_String.tpp"
