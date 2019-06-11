
    /**
     * @file NRE_ForwardList.hpp
     * @brief Declaration of Utility's API's Container : ForwardList
     * @author Louis ABEL
     * @date 10/06/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <stdexcept>
     #include <utility>
     #include <cstring>
     #include <cmath>

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
             * @class ForwardList
             * @brief A simple linked list
             */
            template <class T>
            class ForwardList {
                private :   // Structures
                    /**
                     * @class Node
                     * @brief Internal data structure to store forward list node
                     */
                    class Node {
                        public :    // Fields
                            T data;     /**< The data from the node */
                            T* next;    /**< The next node */

                        public :    // Methods
                            /**
                             * Construct the node
                             * @param value the node data
                             * @param node  the next node
                             */
                            Node(T const& value, T* node);
                            /**
                             * Construct the node
                             * @param value the node data
                             * @param node  the next node
                             */
                            Node(T && value, T* node);
                    };

                public :    // Iterator
                    /**
                     * @class ForwardIterator
                     * @brief Internal iterator for forward list
                     */
                    template <class K>
                    class ForwardIterator {
                        private :   // Fields
                            K* current;         /**< The current iterator node */
                            bool beforeBegin;   /**< Tell if we are before the begin */

                        public :    // Methods
                            //## Constructor ##//
                                /**
                                 * Default constructor with nullptr node
                                 */
                                ForwardIterator() = default;
                                /**
                                 * Construct the iterator with the give node
                                 * @param node   the iterator node
                                 * @param before if we are before the begin
                                 */
                                ForwardIterator(K* node, bool before = false);

                            //## Copy Constructor ##//
                                /**
                                 * Copy it into this
                                 * @param  it the iterator to copy
                                 */
                                ForwardIterator(ForwardIterator const& it) = default;

                            //## Deconstructor ##//
                                /**
                                 * ForwardIterator Deconstructor
                                 */
                                ~ForwardIterator() = default;

                            //## Assignment Operator ##//
                                /**
                                 * Copy assignment of it into this
                                 * @param it the iterator to copy into this
                                 * @return   the reference of himself
                                 */
                                ForwardIterator& operator =(ForwardIterator const& it) = default;

                            //## Access Operator ##//
                                /**
                                 * Dereference operator, allow access to the data
                                 * @return the iterator data
                                 */
                                T& operator*() const;
                                /**
                                 * Arrow dereference operator, allow access to the data
                                 * @return the iterator data
                                 */
                                T& operator->() const;

                            //## Increment Operator ##//
                                /**
                                 * Pre increment operator, access the next element
                                 * @return the reference of himself
                                 */
                                ForwardIterator& operator++();
                                /**
                                 * Post increment operator, access the next element
                                 * @return the iterator on the current element
                                 */
                                ForwardIterator operator++(int);

                            //## Comparison Operator ##//
                                /**
                                 * Equality test between this and it
                                 * @param it the other iterator
                                 * @return   the test result
                                 */
                                bool operator==(ForwardIterator const& it) const;
                                /**
                                 * Inequality test between this and it
                                 * @param it the other iterator
                                 * @return   the test result
                                 */
                                bool operator!=(ForwardIterator const& it) const;

                    };

                    /**< Shortcut to hide Iterator implementation */
                    typedef ForwardIterator<Node>          Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef ForwardIterator<const Node>    ConstIterator;

                private :   // Fields
                    Node* front;    /**< The front node of the list */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct an empty list
                         */
                        ForwardList();
                        /**
                         * Construct a list with count copy of value
                         * @param count the number of copy
                         * @param value the value to use for copy
                         */
                        ForwardList(std::size_t count, T const& value = T());
                        /**
                         * Construct a list using elements in the given range
                         * @param begin the iterator on the first element
                         * @param end   the iterator after the last element
                         */
                        template <class InputIterator>
                        ForwardList(InputIterator begin, InputIterator end);
                        /**
                         * Construct a list using elements in the given list
                         * @param list the initializer list
                         */
                        ForwardList(std::initializer_list<T> list);

                    //## Copy Constructor ##//
                        /**
                         * Copy list into this
                         * @param  list the list to copy
                         */
                        ForwardList(ForwardList const& list);

                    //## Move Constructor ##//
                        /**
                         * Move list into this
                         * @param  list the list to move
                         */
                        ForwardList(ForwardList && list);

                    //## Deconstructor ##//
                        /**
                         * ForwardList Deconstructor
                         */
                        ~ForwardList();

                    //## Getter ##//
                        /**
                         * @return the list head
                         */
                        T& getFront();
                        /**
                         * @return the list head
                         */
                        T const& getFront() const;
                        /**
                         * @return the maximum array size
                         */
                        constexpr std::size_t getMaxSize() const;
                        /**
                         * @return if the list is empty
                         */
                        bool isEmpty() const;

                    //## Iterator Access ##//
                        /**
                         * @return an iterator on the element before the first element
                         */
                        Iterator beforeBegin();
                        /**
                         * @return a const iterator on the element before the first element
                         */
                        ConstIterator beforeBegin() const;
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

                    //## Methods ##//
                        /**
                         * Assign count copy of value in the list
                         * @param count the number of copy
                         * @param value the value to use for copy
                         */
                        void assign(std::size_t count, T const& value);
                        /**
                         * Assign the list with element in the given range
                         * @param begin the iterator on the first element
                         * @param end   the iterator after the last element
                         */
                        template <class InputIterator>
                        void assign(InputIterator begin, InputIterator end);
                        /**
                         * Clear all objects in the list
                         */
                        void clear();
                        /**
                         * Insert a copy of the given element after the given position
                         * @param  pos   the position to insert after
                         * @param  value the element to insert
                         * @return       an iterator on the inserted element
                         */
                        Iterator insertAfter(ConstIterator pos, T const& value);
                        /**
                         * Insert the given element after the given position
                         * @param  pos   the position to insert after
                         * @param  value the element to insert
                         * @return       an iterator on the inserted element
                         */
                        Iterator insertAfter(ConstIterator pos, T && value);
                        /**
                         * Insert count copy of the given element after the given position
                         * @param  pos   the position to insert after
                         * @param  count the number of copy to insert
                         * @param  value the element to insert
                         * @return       an iterator on the last copy
                         */
                        Iterator insertAfter(ConstIterator pos, std::size_t count, T const& value);
                        /**
                         * Insert copy of elements in the given range after the given position
                         * @param  pos   the position to insert after
                         * @param  begin the iterator on the first element
                         * @param  end   the iterator after the last element
                         * @return       an iterator on the last inserted element
                         */
                        template <class InputIterator>
                        Iterator insertAfter(ConstIterator pos, InputIterator begin, InputIterator end);
                        /**
                         * Insert copy of elements in the given list after the given position
                         * @param  pos  the position to insert after
                         * @param  list the list containing elements
                         * @return      an iterator on the last inserted element
                         */
                        Iterator insertAfter(ConstIterator pos, std::initializer_list<T> list);

                    //## Assignment Operator ##//
                        /**
                         * Copy list into this
                         * @param list the list to copy into this
                         * @return     the reference of himself
                         */
                        ForwardList& operator =(ForwardList const& list);
                        /**
                         * Move list into this
                         * @param list the list to move into this
                         * @return     the reference of himself
                         */
                        ForwardList& operator =(ForwardList && list);

            };
        }
    }
