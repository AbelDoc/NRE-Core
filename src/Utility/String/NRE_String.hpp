
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
     #include <limits>
     #include <cstring>
     #include <cmath>
     #include <iostream>

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
                static_assert(std::is_integral<T>::value, "You can't use BasicString with non-integral types"); // Only work with POD types but restreign to integral type
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
                         * @param  str the string to move
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
                         * Assign the string with count copy of value, starting from the beginning
                         * @param count the number of copy
                         * @param value the copy to fill the string with
                         * @return      the reference on himself
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
                         * @return     the reference on himself
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
                         * @return      the reference on himself
                         */
                        BasicString& assign(std::size_t count, const T* str);
                        /**
                         * Replace the string content filled with str element, str need to be terminated by a null character
                         * @param str the other string
                         * @return    the reference on himself
                         */
                        BasicString& assign(const T* str);
                        /**
                         * Replace the string content with element between 2 iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @pre begin and end are not iterator from the string
                         * @return       the reference on himself
                         */
                        template <class InputIterator>
                        BasicString& assign(InputIterator begin, InputIterator end);
                        /**
                         * Replace the string content with content from an initializer list
                         * @param  init the list to fill the string with
                         * @pre list don't contain string reference
                         * @return      the reference on himself
                         */
                        BasicString& assign(std::initializer_list<T> init);
                        /**
                         * Set the string capacity to a minimum of size, reallocating memory if needed
                         * @param size the new capacity
                         * @warning size value is not checked against getMaxSize()
                         */
                        void reserve(std::size_t size);
                        /**
                         * Clear all object in the vector, not actually releasing memory
                         */
                        void clear();
                        /**
                         * Reverse the whole string
                         */
                        void reverse();
                        /**
                         * Reverse a part of the string
                         * @param pos   the start for the reverse
                         * @param count the number of character to reverse
                         */
                        void reverse(std::size_t pos, std::size_t count);
                        /**
                         * Insert count copy of value at the specified position
                         * @param  start the position to insert values
                         * @param  count the number of copy
                         * @param  value the value to insert
                         * @return       the reference on himself
                         */
                        BasicString& insert(std::size_t start, std::size_t count, T value);
                        /**
                         * Insert str elements, str need to be NULL terminated
                         * @param  start the position to insert values
                         * @param  str   the other string
                         * @return       the reference on himself
                         */
                        BasicString& insert(std::size_t start, const T* str);
                        /**
                         * Insert str elements
                         * @param start the position to insert values
                         * @param count the number of element to take from str
                         * @param str   the other string
                         * @return      the reference on himself
                         */
                        BasicString& insert(std::size_t start,  std::size_t count, const T* str);
                        /**
                         * Insert a string at the specified position
                         * @param  start the position to insert values
                         * @param  str   the string to insert
                         * @return       the reference on himself
                         */
                        BasicString& insert(std::size_t start, BasicString const& str);
                        /**
                         * Insert a string part at the specified position
                         * @param  start the position to insert values
                         * @param  str   the string to insert
                         * @param  index the start index in the string
                         * @param  count the number of character to take from the string
                         * @return       the reference on himself
                         */
                        BasicString& insert(std::size_t start, BasicString const& str, std::size_t index, std::size_t count);
                        /**
                         * Insert the character at the specified position
                         * @param start the position to insert values
                         * @param value the value to insert
                         * @return      the iterator on the first inserted value
                         */
                        Iterator insert(ConstIterator start, T value);
                        /**
                         * Insert count copy of the character at the specified position
                         * @param start the position to insert values
                         * @param count the number of copy
                         * @param value the value to insert
                         * @return      the iterator on the first inserted value
                         */
                        Iterator insert(ConstIterator start, std::size_t count, T value);
                        /**
                         * Insert a copy of element between begin and end at the specified position
                         * @param  start the position to insert values
                         * @param  begin the begin iterator
                         * @param  end   the end iterator, pointing after the last element
                         * @return       the iterator on the first inserted value
                         * @pre begin and end are not iterator from the string
                         */
                        template <class InputIterator>
                        Iterator insert(ConstIterator start, InputIterator begin, InputIterator end);
                        /**
                         * Insert a list of value at the specified position
                         * @param  start the position to insert values
                         * @param  init  the list to fill the vector with
                         * @return       the iterator on the first inserted value
                         * @pre list don't contain string reference
                         */
                        Iterator insert(ConstIterator start, std::initializer_list<T> list);
                        /**
                         * Erase count character starting by index
                         * @param  index the start index
                         * @param  count the number of character to erase
                         * @return       the reference on himself
                         */
                        BasicString& erase(std::size_t index, std::size_t count);
                        /**
                         * Erase the character at the given position
                         * @param  position the position to erase
                         * @return          the iterator after the erased value
                         */
                        Iterator erase(ConstIterator position);
                        /**
                         * Erase character between 2 iterators
                         * @param  begin the start position
                         * @param  end   the end position
                         * @return       the iterator after the erased value
                         */
                        Iterator erase(ConstIterator begin, ConstIterator end);
                        /**
                         * Insert a character at the end of the string
                         * @param value the value to insert
                         */
                        void pushBack(T value);
                        /**
                         * Pop back the last character
                         */
                        void popBack();
                        /**
                         * Append the object to string
                         * @param o the object to append
                         * @return  the reference of himself
                         */
                        template <class K>
                        BasicString& append(K const& o);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(bool value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(T value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(short int value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(int value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(long int value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(long long int value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(unsigned short int value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(unsigned int value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(unsigned long int value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(unsigned long long int value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(float value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(double value);
                        /**
                         * Append the object to string
                         * @param value the object to append
                         * @return      the reference of himself
                         */
                        BasicString& append(long double value);
                        /**
                         * Append count copy of value at the end of the string
                         * @param  count the number of copy
                         * @param  value the value to append
                         * @return       the reference of himself
                         */
                        BasicString& append(std::size_t count, T value);
                        /**
                         * Append the given string at the end of the string
                         * @param  str the string to append
                         * @return     the reference of himself
                         */
                        BasicString& append(BasicString const& str);
                        /**
                         * Append a part of the given string at the end of the string
                         * @param  str   the string to append
                         * @param  index the index of the first character
                         * @param  count the number of character to copy
                         * @return       the reference of himself
                         */
                        BasicString& append(BasicString const& str, std::size_t index, std::size_t count);
                        /**
                         * Append the count first character of the given string at the end
                         * @param  str   the string to append
                         * @param  count the number of character to take
                         * @return       the reference of himself
                         */
                        BasicString& append(const T* str, std::size_t count);
                        /**
                         * Append the given string at the end, the string need to be NULL terminated
                         * @param  str the string to append
                         * @return     the reference of himself
                         */
                        BasicString& append(const T* str);
                        /**
                         * Append all character between given iterators
                         * @param  begin the begin iterator
                         * @param  end   the end iterator
                         * @return       the reference of himself
                         */
                        template <class InputIterator>
                        BasicString& append(InputIterator begin, InputIterator end);
                        /**
                         * Append all character in the list
                         * @param  list the initializer list
                         * @return      the reference of himself
                         */
                        BasicString& append(std::initializer_list<T> list);
                        /**
                         * Compare the given string to this, by first comparing size then memory
                         * @param  str the string to compare with this
                         * @return     <0 if this is lesser than str, >0 if this is greater than str, 0 if equals
                         */
                        int compare(BasicString const& str) const;
                        /**
                         * Compare the given string to a part of this, by first comparing size then memory
                         * @param  tPos   the first character of this
                         * @param  tCount the number of character from this
                         * @param  str    the string to compare with this
                         * @return        <0 if this is lesser than str, >0 if this is greater than str, 0 if equals
                         */
                        int compare(std::size_t tPos, std::size_t tCount, BasicString const& str) const;
                        /**
                         * Compare a part of the given string to a part of this, by first comparing size then memory
                         * @param  tPos   the first character of this
                         * @param  tCount the number of character from this
                         * @param  str    the string to compare with this
                         * @param  sPos   the first character of str
                         * @param  sCount the number of character from str
                         * @return        <0 if this is lesser than str, >0 if this is greater than str, 0 if equals
                         */
                        int compare(std::size_t tPos, std::size_t tCount, BasicString const& str, std::size_t sPos, std::size_t sCount) const;
                        /**
                         * Compare the given NULL terminated string to this, by first comparing size then memory
                         * @param  str the string to compare with this
                         * @return     <0 if this is lesser than str, >0 if this is greater than str, 0 if equals
                         */
                        int compare(const T* str) const;
                        /**
                         * Compare the given NULL terminated string to a part of this, by first comparing size then memory
                         * @param  tPos   the first character of this
                         * @param  tCount the number of character from this
                         * @param  str    the string to compare with this
                         * @return        <0 if this is lesser than str, >0 if this is greater than str, 0 if equals
                         */
                        int compare(std::size_t tPos, std::size_t tCount, const T* str) const;
                        /**
                         * Compare a part of the given NULL terminated string to a part of this, by first comparing size then memory
                         * @param  tPos   the first character of this
                         * @param  tCount the number of character from this
                         * @param  str    the string to compare with this
                         * @param  sPos   the first character of str
                         * @param  sCount the number of character from str
                         * @return        <0 if this is lesser than str, >0 if this is greater than str, 0 if equals
                         */
                        int compare(std::size_t tPos, std::size_t tCount, const T* str, std::size_t sPos, std::size_t sCount) const;
                        /**
                         * Check if the string starts with the given one
                         * @param  str the prefix to check
                         * @return     if the string starts with the prefix
                         */
                        bool startsWith(BasicString const& str) const;
                        /**
                         * Check if the string starts with the given character
                         * @param  value the prefix to check
                         * @return       if the string starts with the prefix
                         */
                        bool startsWith(T value) const;
                        /**
                         * Check if the string starts with the given one, need to be NULL terminated
                         * @param  str the prefix to check
                         * @return     if the string starts with the prefix
                         */
                        bool startsWith(const T* str) const;
                        /**
                         * Check if the string ends with the given one
                         * @param  str the suffix to check
                         * @return     if the string ends with the suffix
                         */
                        bool endsWith(BasicString const& str) const;
                        /**
                         * Check if the string ends with the given character
                         * @param  value the suffix to check
                         * @return       if the string ends with the suffix
                         */
                        bool endsWith(T value) const;
                        /**
                         * Check if the string ends with the given one, need to be NULL terminated
                         * @param  str the suffix to check
                         * @return     if the string ends with the suffix
                         */
                        bool endsWith(const T* str) const;
                        /**
                         * Replace the given part by the given string
                         * @param  pos   the start position to replace
                         * @param  count the number of character to replace
                         * @param  str   the replacement string
                         * @return       the reference of himself
                         */
                        BasicString& replace(std::size_t pos, std::size_t count, BasicString const& str);
                        /**
                         * Replace the given part by the given string
                         * @param  start the start position to replace
                         * @param  end   the end range
                         * @param  str   the replacement string
                         * @return       the reference of himself
                         */
                        BasicString& replace(ConstIterator start, ConstIterator end, BasicString const& str);
                        /**
                         * Replace the given part by a part of the given string
                         * @param  tPos   the start position to replace
                         * @param  tCount the number of character to replace
                         * @param  str    the replacement string
                         * @param  sPos   the start position in the replacement string
                         * @param  sCount the number of character in the replacement string
                         * @return        the reference of himself
                         */
                        BasicString& replace(std::size_t tPos, std::size_t tCount, BasicString const& str, std::size_t sPos, std::size_t sCount);
                        /**
                         * Replace the given part by a part of the given string
                         * @param  tStart the start position to replace
                         * @param  tEnd   the end range
                         * @param  str    the replacement string
                         * @param  sStart the start position in the replacement string
                         * @param  sEnd   the end range in the replacement string
                         * @return        the reference of himself
                         */
                        template <class InputIterator>
                        BasicString& replace(ConstIterator tStart, ConstIterator tEnd, BasicString const& str, InputIterator sStart, InputIterator sEnd);
                        /**
                         * Replace the given part by the given string
                         * @param  pos    the start position to replace
                         * @param  tCount the number of character to replace
                         * @param  str    the replacement string
                         * @param  sCount the number of character in the replacement string
                         * @return        the reference of himself
                         */
                        BasicString& replace(std::size_t pos, std::size_t tCount, const T* str, std::size_t sCount);
                        /**
                         * Replace the given part by the given string
                         * @param  start  the start position to replace
                         * @param  end    the end range
                         * @param  str    the replacement string
                         * @param  sCount the number of character in the replacement string
                         * @return        the reference of himself
                         */
                        BasicString& replace(ConstIterator start, ConstIterator end, const T* str, std::size_t sCount);
                        /**
                         * Replace the given part by the given string, need to be NULL terminated
                         * @param  pos   the start position to replace
                         * @param  count the number of character to replace
                         * @param  str   the replacement string
                         * @return       the reference of himself
                         */
                        BasicString& replace(std::size_t pos, std::size_t count, const T* str);
                        /**
                         * Replace the given part by the given string, need to be NULL terminated
                         * @param  start  the start position to replace
                         * @param  end    the end range
                         * @param  str    the replacement string
                         * @return        the reference of himself
                         */
                        BasicString& replace(ConstIterator start, ConstIterator end, const T* str);
                        /**
                         * Replace the given part by sCount copy of the given character
                         * @param  pos    the start position to replace
                         * @param  tCount the number of character to replace
                         * @param  value  the character to copy
                         * @param  sCount the number of copy
                         * @return        the reference of himself
                         */
                        BasicString& replace(std::size_t pos, std::size_t tCount, T value, std::size_t sCount);
                        /**
                         * Replace the given part by sCount copy of the given character
                         * @param  start  the start position to replace
                         * @param  end    the end range
                         * @param  value  the character to copy
                         * @param  sCount the number of copy
                         * @return        the reference of himself
                         */
                        BasicString& replace(ConstIterator start, ConstIterator end, T value, std::size_t sCount);
                        /**
                         * Replace the given part by the given character list
                         * @param  start  the start position to replace
                         * @param  end    the end range
                         * @param  list   the character list
                         * @return        the reference of himself
                         */
                        BasicString& replace(ConstIterator start, ConstIterator end, std::initializer_list<T> list);
                        /**
                         * Create a copy of the given range
                         * @param  pos   the start index
                         * @param  count the number of character to copy
                         * @return       the sub string
                         */
                        BasicString substr(std::size_t pos, std::size_t count) const;
                        /**
                         * Copy the given range into the given string
                         * @param  str   the string to copy in
                         * @param  pos   the start index
                         * @param  count the number of character to copy
                         * @return       the number of copied character
                         */
                        std::size_t copy(T* str, std::size_t pos, std::size_t count) const;
                        /**
                         * Resize the string up the given size, insert value if needed
                         * @param count the new capacity
                         */
                        void resize(std::size_t count);
                        /**
                         * Resize the string up the given size, insert value if needed
                         * @param count the new capacity
                         * @param value the value used when inserting
                         */
                        void resize(std::size_t count, T value);
                        /**
                         * Swap the string with an other string
                         * @param str the other string
                         */
                        void swap(BasicString& str);
                        /**
                         * Shrink to fit the actual size, actually freeing memory
                         */
                        void shrinkToFit();
                        /**
                         * Search the first occurrence of the given string, start the search at the given position

                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t find(BasicString const& str, std::size_t pos = 0) const;
                        /**
                         * Search the first occurrence of the given string part, start the search at the given position
                         * @param  count the max range in the given string
                         * @param  str   the string to search
                         * @param  pos   the search start
                         * @return       the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t find(std::size_t count, const T* str, std::size_t pos = 0) const;
                        /**
                         * Search the first occurrence of the given string, need to be NULL terminated, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t find(const T* str, std::size_t pos = 0) const;
                        /**
                         * Search the first occurrence of the given character, start the search at the given position
                         * @param  value the character to search
                         * @param  pos   the search start
                         * @return       the position of the found character, NOT_FOUND if no occurrence found
                         */
                        std::size_t find(T value, std::size_t pos = 0) const;
                        /**
                         * Search the first occurrence of the given string, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t rfind(BasicString const& str, std::size_t pos) const;
                        /**
                         * Search the first occurrence of the given string part, start the search at the given position
                         * @param  count the max range in the given string
                         * @param  str   the string to search
                         * @param  pos   the search start
                         * @return       the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t rfind(std::size_t count, const T* str, std::size_t pos) const;
                        /**
                         * Search the first occurrence of the given string, need to be NULL terminated, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t rfind(const T* str, std::size_t pos) const;
                        /**
                         * Search the first occurrence of the given character, start the search at the given position
                         * @param  value the character to search
                         * @param  pos   the search start
                         * @return       the position of the found character, NOT_FOUND if no occurrence found
                         */
                        std::size_t rfind(T value, std::size_t pos) const;
                        /**
                         * Search the first character that match a character in the given string, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findFirstOf(BasicString const& str, std::size_t pos = 0) const;
                        /**
                         * Search the first character that match a character in the given string part, start the search at the given position
                         * @param  count the max range in the given string
                         * @param  str   the string to search
                         * @param  pos   the search start
                         * @return       the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findFirstOf(std::size_t count, const T* str, std::size_t pos = 0) const;
                        /**
                         * Search the first character that match a character in the given string, need to be NULL terminated, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findFirstOf(const T* str, std::size_t pos = 0) const;
                        /**
                         * Search the first character that match the given character, start the search at the given position
                         * @param  value the character to search
                         * @param  pos   the search start
                         * @return       the position of the found character, NOT_FOUND if no occurrence found
                         */
                        std::size_t findFirstOf(T value, std::size_t pos = 0) const;
                        /**
                         * Search the first character that match no character in the given string, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findFirstNotOf(BasicString const& str, std::size_t pos = 0) const;
                        /**
                         * Search the first character that match no character in the given string part, start the search at the given position
                         * @param  count the max range in the given string
                         * @param  str   the string to search
                         * @param  pos   the search start
                         * @return       the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findFirstNotOf(std::size_t count, const T* str, std::size_t pos = 0) const;
                        /**
                         * Search the first character that match no character in the given string, need to be NULL terminated, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findFirstNotOf(const T* str, std::size_t pos = 0) const;
                        /**
                         * Search the first character that doesn't match with the given character, start the search at the given position
                         * @param  value the character to search
                         * @param  pos   the search start
                         * @return       the position of the found character, NOT_FOUND if no occurrence found
                         */
                        std::size_t findFirstNotOf(T value, std::size_t pos = 0) const;
                        /**
                         * Search the first character that match a character in the given string, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findLastOf(BasicString const& str, std::size_t pos) const;
                        /**
                         * Search the first character that match a character in the given string part, start the search at the given position
                         * @param  count the max range in the given string
                         * @param  str   the string to search
                         * @param  pos   the search start
                         * @return       the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findLastOf(std::size_t count, const T* str, std::size_t pos) const;
                        /**
                         * Search the first character that match a character in the given string, need to be NULL terminated, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findLastOf(const T* str, std::size_t pos) const;
                        /**
                         * Search the first character that match the given character, start the search at the given position
                         * @param  value the character to search
                         * @param  pos   the search start
                         * @return       the position of the found character, NOT_FOUND if no occurrence found
                         */
                        std::size_t findLastOf(T value, std::size_t pos) const;
                        /**
                         * Search the first character that match no character in the given string, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findLastNotOf(BasicString const& str, std::size_t pos) const;
                        /**
                         * Search the first character that match no character in the given string part, start the search at the given position
                         * @param  count the max range in the given string
                         * @param  str   the string to search
                         * @param  pos   the search start
                         * @return       the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findLastNotOf(std::size_t count, const T* str, std::size_t pos) const;
                        /**
                         * Search the first character that match no character in the given string, need to be NULL terminated, start the search at the given position
                         * @param  str the string to search
                         * @param  pos the search start
                         * @return     the position of the found string, NOT_FOUND if no occurrence found
                         */
                        std::size_t findLastNotOf(const T* str, std::size_t pos) const;
                        /**
                         * Search the first character that doesn't match with the given character, start the search at the given position
                         * @param  value the character to search
                         * @param  pos   the search start
                         * @return       the position of the found character, NOT_FOUND if no occurrence found
                         */
                        std::size_t findLastNotOf(T value, std::size_t pos) const;

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
                        /**
                         * Copy str into this
                         * @param str the string to copy into this
                         * @return    the reference of himself
                         */
                        BasicString& operator =(const T* str);
                        /**
                         * Copy value into this
                         * @param value the character to copy into this
                         * @return      the reference of himself
                         */
                        BasicString& operator =(T value);
                        /**
                         * Copy list elements into this
                         * @param list the list of character to copy into this
                         * @return     the reference of himself
                         */
                        BasicString& operator =(std::initializer_list<T> list);

                    //## Shortcut Operator ##//
                        /**
                         * Append the given string to this
                         * @param str the string to append
                         * @return    the reference of himself
                         */
                        BasicString& operator+=(BasicString const& str);
                        /**
                         * Append the given character to this
                         * @param value the character to append
                         * @return      the reference of himself
                         */
                        BasicString& operator+=(T value);
                        /**
                         * Append the given string to this, the string need to be NULL terminated
                         * @param str the string to append
                         * @return    the reference of himself
                         */
                        BasicString& operator+=(const T* str);
                        /**
                         * Append the given character list to this
                         * @param list the list to append
                         * @return     the reference of himself
                         */
                        BasicString& operator+=(std::initializer_list<T> list);

                    //## Comparison Operator ##//
                        /**
                         * Equality test between this and str
                         * @param str the other string to compare with this
                         * @return    the test result
                         */
                        bool operator==(BasicString const& str) const;
                        /**
                         * Inequality test between this and str
                         * @param str the other string to compare with this
                         * @return    the test result
                         */
                        bool operator!=(BasicString const& str) const;
                        /**
                         * Inferiority test between this and str
                         * @param str the other string to compare with this
                         * @return    the test result
                         */
                        bool operator<(BasicString const& str) const;
                        /**
                         * Inferior or Equal test between this and str
                         * @param str the other string to compare with this
                         * @return    the test result
                         */
                        bool operator<=(BasicString const& str) const;
                        /**
                         * Superiority test between this and str
                         * @param str the other string to compare with this
                         * @return    the test result
                         */
                        bool operator>(BasicString const& str) const;
                        /**
                         * Superior or Equal or Equal test between this and str
                         * @param str the other string to compare with this
                         * @return    the test result
                         */
                        bool operator>=(BasicString const& str) const;

                    //## Stream Operator ##//
                        /**
                         * Convert the object into a string representation
                         * @return the converted object
                         */
                        BasicString const& toString() const;
                        /**
                         * Output stream operator for object
                         * @param o the object to add in the string
                         * @return  the reference of himself
                         */
                        template <class K>
                        BasicString& operator <<(K const& o);

                private :   // Methods
                    /**
                     * Reallocate and grow the storage capacity
                     */
                    void reallocate();
                    /**
                     * Reallocate the data to the given size
                     * @param newSize the new capacity
                     */
                    void reallocate(std::size_t newSize);
                    /**
                     * Reallocate the string with the nearest grow factor value
                     * @param size the new minimum capacity
                     */
                    void reserveWithGrowFactor(std::size_t size);
                    /**
                     * Add the null terminated character at the end
                     */
                    void addNullTerminated();
                    /**
                     * Shift all element in the string, don't do reallocation
                     * @param start the start position for shifting
                     * @param count the number of shift to do
                     */
                    void shift(std::size_t start, std::size_t count);
                    /**
                     * Shift back all element in the string, don't call deconstructor
                     * @param start the start position for shifting
                     * @param count the number of shift to do
                     */
                    void shiftBack(std::size_t start, std::size_t count);

                public :     // Static
                    static constexpr std::size_t NOT_FOUND = -1;

                private :    // Static
                    static constexpr float GROW_FACTOR = 1.5;
                    static constexpr std::size_t BASE_ALLOCATION_SIZE = 8;
            };

            typedef BasicString<char>    String;
            typedef BasicString<wchar_t> WideString;

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return        the modified stream
             */
            template <class T>
            std::ostream& operator <<(std::ostream& stream, BasicString<T> const& o);
            /**
             * Input stream operator for the object
             * @param  stream the stream to take the object data
             * @param  o      the object to fill from the stream
             * @return        the modified stream
             */
            template <class T>
            std::istream& operator >>(std::istream& stream, BasicString<T>& o);

            /**
             * Concatenate two strings into a new one
             * @param lhs the left string part
             * @param rhs the right string part
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(BasicString<T> const& lhs, BasicString<T> const& rhs);
            /**
             * Concatenate two strings into a new one
             * @param lhs the left string part
             * @param rhs the right string part
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(const T* lhs, BasicString<T> const& rhs);
            /**
             * Concatenate a character with a string into a new string
             * @param lhs the character
             * @param rhs the string
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(T lhs, BasicString<T> const& rhs);
            /**
             * Concatenate two strings into a new one
             * @param lhs the left string part
             * @param rhs the right string part
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(BasicString<T> const& lhs, const T* rhs);
            /**
             * Concatenate a string with a character into a new string
             * @param lhs the string
             * @param rhs the character
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(BasicString<T> const& lhs, T rhs);
            /**
             * Concatenate two strings into a new one
             * @param lhs the left string part
             * @param rhs the right string part
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(BasicString<T> && lhs, BasicString<T> const& rhs);
            /**
             * Concatenate two strings into a new one
             * @param lhs the left string part
             * @param rhs the right string part
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(BasicString<T> const& lhs, BasicString<T> && rhs);
            /**
             * Concatenate two strings into a new one
             * @param lhs the left string part
             * @param rhs the right string part
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(BasicString<T> && lhs, BasicString<T> && rhs);
            /**
             * Concatenate two strings into a new one
             * @param lhs the left string part
             * @param rhs the right string part
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(const T* lhs, BasicString<T> && rhs);
            /**
             * Concatenate a character with a string into a new string
             * @param lhs the character
             * @param rhs the string
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(T lhs, BasicString<T> && rhs);
            /**
             * Concatenate two strings into a new one
             * @param lhs the left string part
             * @param rhs the right string part
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(BasicString<T> && lhs, const T* rhs);
            /**
             * Concatenate a string with a character into a new string
             * @param lhs the string
             * @param rhs the character
             * @return    the new string
             */
            template <class T>
            BasicString<T> operator+(BasicString<T> && lhs, T rhs);
        }
    }

    #include "NRE_String.tpp"
