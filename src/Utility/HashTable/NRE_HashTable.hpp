
    /**
     * @file NRE_HashTable.hpp
     * @brief Declaration of Utility's API's Object : HashTable
     * @author Louis ABEL
     * @date 25/65/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../String/NRE_String.hpp"
     #include "../Pair/NRE_Pair.hpp"
     #include "../Vector/NRE_Vector.hpp"

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
             * @class HashTable
             * @brief An hashtable used in map and set, an associative container using linear probing, robin hood and shift back optimisation
             */
            template <class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
            class HashTable : private Hash, private KeyEqual {
                private :    // Structures
                    /**
                     * @class BucketEntry
                     * @brief A bucket entry used as the hash table elements
                     */
                    class BucketEntry {
                        private :   // Fields
                            std::ptrdiff_t distanceToNext;  /**< The ideal distance to the next bucket */
                            bool last;                      /**< Tell if the bucket is the last filled */
                            Pair<Key, T> data;              /**< The bucket entry data */

                        public :    // Methods
                            //## Constructor ##//
                                /**
                                 * Construct an empty bucket
                                 */
                                BucketEntry();
                                /**
                                 * Construct an empty bucket with user defined last marker
                                 * @param state tell if the bucket is the last
                                 */
                                BucketEntry(bool state);

                            //## Copy Constructor ##//
                                /**
                                 * Copy bucket into this
                                 * @param bucket the bucket entry to copy
                                 */
                                BucketEntry(BucketEntry const& bucket);

                            //## Move Constructor ##//
                                /**
                                 * Move bucket into this
                                 * @param bucket the bucket entry to move
                                 */
                                BucketEntry(BucketEntry && bucket);

                            //## Deconstructor ##//
                                /**
                                 * BucketEntry Deconstructor
                                 */
                                ~BucketEntry();

                            //## Getter ##//
                                /**
                                 * @return if the bucket is empty
                                 */
                                bool isEmpty() const;
                                /**
                                 * @return if the bucket is the last
                                 */
                                bool isLastBucket() const;
                                /**
                                 * @return the distance to the next bucket
                                 */
                                std::ptrdiff_t getDistanceToNext() const;
                                /**
                                 * @return the bucket key
                                 */
                                Key const& getKey() const;
                                /**
                                 * @return the bucket data
                                 */
                                Pair<Key, T>& getData();
                                /**
                                 * @return the bucket data
                                 */
                                Pair<Key, T> const& getData() const;

                            //## Setter ##//
                                /**
                                 * Set this as the last bucket
                                 */
                                void setAsLastBucket();
                                /**
                                 * Set the bucket data, must be empty
                                 * @param distance the distance to the next bucket
                                 * @param newData  the data to set
                                 */
                                void setData(std::ptrdiff_t distance, Pair<Key, T> && newData);

                            //## Methods ##//
                                /**
                                 * Clear the bucket data if not empty
                                 */
                                void clear();
                                /**
                                 * Swap the bucket entry with another bucket entry
                                 * @param bucket the other bucket
                                 */
                                void swap(BucketEntry& bucket);
                                /**
                                 * Swap the bucket data with given one
                                 * @param distance the distance to the next bucket
                                 * @param newData  the data to set
                                 */
                                void swapWithData(std::ptrdiff_t& distance, Pair<Key, T> && newData);

                            //## Assignment Operator ##//
                                /**
                                 * Copy bucket into this
                                 * @param bucket the bucket entry to copy into this
                                 * @return    the reference of himself
                                 */
                                BucketEntry& operator =(BucketEntry const& bucket);
                                /**
                                 * Move bucket into this
                                 * @param bucket the bucket entry to move into this
                                 * @return       the reference of himself
                                 */
                                BucketEntry& operator =(BucketEntry && bucket);

                        public :    // Static
                            static const std::ptrdiff_t EMPTY_BUCKET_DISTANCE = -1; /**< The distance used to mark a bucket as empty */

                    };

                public :     // Iterator
                    template <class K>
                    class ForwardIterator {
                        friend class HashTable;
                        private :   // Fields
                            BucketEntry* current;   /**< The current iterator bucket */

                        public :    // Methods
                            typedef std::ptrdiff_t difference_type;
                            typedef Pair<Key, T> value_type;
                            typedef Pair<Key, T>* pointer;
                            typedef Pair<Key, T>& reference;
                            typedef std::forward_iterator_tag iterator_category;

                            //## Constructor ##//
                                /**
                                 * Default constructor with nullptr node
                                 */
                                ForwardIterator() = default;
                                /**
                                 * Construct the iterator with the given node
                                 * @param bucket the iterator bucket
                                 */
                                ForwardIterator(BucketEntry* bucket);
                                /**
                                 * Construct the iterator with the given node
                                 * @param bucket the iterator bucket
                                 */
                                ForwardIterator(const BucketEntry* bucket);

                            //## Copy Constructor ##//
                                /**
                                 * Copy it into this
                                 * @param it the iterator to copy
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
                                K& operator*() const;
                                /**
                                 * Arrow dereference operator, allow access to the data
                                 * @return the iterator data pointer
                                 */
                                K* operator->() const;

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
                    typedef ForwardIterator<Pair<Key, T>>          Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef ForwardIterator<const Pair<Key, T>>    ConstIterator;

                private :    // Fields
                    Vector<BucketEntry> data;   /**< The hash table data */
                    std::size_t nbElements;     /**< The number in the table */
                    std::size_t mask;           /**< The mask used with the power of two policy */
                    float maxLoadFactor;        /**< The maximum load factor before rehash and grow */

                public :     // Methods
                    //## Constructor ##//
                        /**
                         * Construct an empty hashtable with a number of bucket
                         * @param bucketCount the base bucket count
                         * @param hasher      the hash function used in the table
                         * @param equal       the equal function used in the table
                         */
                        HashTable(std::size_t bucketCount = DEFAULT_BUCKET_COUNT , Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual());
                        /**
                         * Construct an hashtable with a number of bucket and filled with elements in the given range
                         * @param begin       the begin iterator
                         * @param end         the end iterator
                         * @param bucketCount the base bucket count
                         * @param hasher      the hash function used in the table
                         * @param equal       the equal function used in the table
                         */
                        template <class InputIterator>
                        HashTable(InputIterator begin, InputIterator end, std::size_t bucketCount = DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual());
                        /**
                         * Construct an hashtable with a number of bucket and filled with elements in the given list
                         * @param list        the list to fill the table with
                         * @param bucketCount the base bucket count
                         * @param haser       the hash function used in the table
                         * @param equal       the equal function used in the table
                         */
                        HashTable(std::initializer_list<Pair<Key, T>> list, std::size_t bucketCount = DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual());

                    //## Copy Constructor ##//
                        /**
                         * Copy table into this
                         * @param table the table to copy
                         */
                        HashTable(HashTable const& table);

                    //## Move Constructor ##//
                        /**
                         * Move table into this
                         * @param table the table to move
                         */
                        HashTable(HashTable && table);

                    //## Getter ##//
                        /**
                         * Access a particular element with bound checking
                         * @param  k the element key
                         * @return   the corresponding element
                         */
                        T& get(Key const& k);
                        /**
                         * Access a particular element with bound checking
                         * @param  k the element key
                         * @return   the corresponding element
                         */
                        T const& get(Key const& k) const;
                        /**
                         * @return the number of buckets in the table
                         */
                        std::size_t getBucketCount() const;
                        /**
                         * @return the maximum number of bucket in the table
                         */
                        constexpr std::size_t getMaxBucketCount() const;
                        /**
                         * @return the number of elements in the table
                         */
                        std::size_t getSize() const;
                        /**
                         * @return the maximum load factor
                         */
                        float getMaxLoadFactor() const;
                        /**
                         * @return the current load factor
                         */
                        float getLoadFactor() const;
                        /**
                         * @return the maximum hash table size
                         */
                        constexpr std::size_t getMaxSize() const;
                        /**
                         * @return if the table is empty
                         */
                        bool isEmpty() const;
                        /**
                         * Find the number of element with the given key
                         * @param  k the key to search
                         * @return   the number of corresponding elements
                         */
                        std::size_t getCount(Key const& k) const;

                    //## Setter ##//
                        /**
                         * Set the new max load factor, must be between 0.0 and 1.0
                         * @param factor the new factor
                         */
                        void setMaxLoadFactor(float factor);

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

                    //## Methods ##//
                        /**
                         * Insert the given value in the table
                         * @param value the pair with the key and the corresponding element
                         * @return      a pair containing an iterator on the inserted element, and a boolean telling if the insertion has been done
                         */
                        Pair<Iterator, bool> insert(Pair<Key, T> const& value);
                        /**
                         * Insert the given value in the table
                         * @param value the pair with the key and the corresponding element
                         * @return      a pair containing an iterator on the inserted element, and a boolean telling if the insertion has been done
                         */
                        template <class P>
                        Pair<Iterator, bool> insert(P && value);
                        /**
                         * Insert elements in the given range
                         * @param begin the begin iterator
                         * @param end   the end iterator
                         */
                        template <class InputIterator>
                        void insert(InputIterator begin, InputIterator end);
                        /**
                         * Insert elements in the given list
                         * @param list the list of value to insert
                         */
                        void insert(std::initializer_list<Pair<Key, T>> list);
                        /**
                         * Insert the given value in the table using the hint as a suggestion for the search start
                         * @param  hint  the hint used for the search
                         * @param  value the value to insert
                         * @return       an iterator on the inserted element
                         */
                        Iterator insertHint(ConstIterator hint, Pair<Key, T> const& value);
                        /**
                         * Insert the given value in the table using the hint as a suggestion for the search start
                         * @param  hint  the hint used for the search
                         * @param  value the value to insert
                         * @return       an iterator on the inserted element
                         */
                        template <class P>
                        Iterator insertHint(ConstIterator hint, P && value);
                        /**
                         * Emplace an element using the given elements
                         * @param args the parameter pack used to create the inserted pair
                         * @return     a pair containing an iterator on the inserted element, and a boolean telling if the insertion has been done
                         */
                        template <class ... Args>
                        Pair<Iterator, bool> emplace(Args && ... args);
                        /**
                         * Emplace an element using the given elements
                         * @param args the parameter pack used to create the inserted pair
                         * @return     an iterator on the inserted element
                         */
                        template <class ... Args>
                        Iterator emplaceHint(ConstIterator hint, Args && ... args);
                        /**
                         * Clear all buckets
                         */
                        void clear();
                        /**
                         * Swap the hash table with another hash table
                         * @param table the other hash table
                         */
                        void swap(HashTable& table);
                        /**
                         * Reserve at least count bucket in the table and rehash the table
                         * @param count the number of desired bucket
                         */
                        void reserve(std::size_t count);
                        /**
                         * Reserve at least coutn bucket in the table and rehash the table
                         * @param count the number of desired bucket
                         */
                        void rehash(std::size_t count);
                        /**
                         * Find a range of iterator containing all elements with the given key, both end if not found
                         * @param key the key to search
                         * @return    a pair of iterator
                         */
                        Pair<Iterator, Iterator> equalRange(Key const& key);
                        /**
                         * Find a range of iterator containing all elements with the given key, both end if not found
                         * @param key the key to search
                         * @return    a pair of iterator
                         */
                        Pair<ConstIterator, ConstIterator> equalRange(Key const& key) const;
                        /**
                         * Find the element corresponding with the given key
                         * @param  k the key to search
                         * @return   the iterator pointing on the element, or end if not found
                         */
                        Iterator find(Key const& k);
                        /**
                         * Find the element corresponding with the given key
                         * @param  k the key to search
                         * @return   the iterator pointing on the element, or end if not found
                         */
                        ConstIterator find(Key const& k) const;
                        /**
                         * Erase the element pointed by the iterator
                         * @param  pos the iterator on the erased element
                         * @return      an iterator after the erased element
                         */
                        Iterator erase(Iterator pos);
                        /**
                         * Erase the element pointed by the iterator
                         * @param  pos the iterator on the erased element
                         * @return      an iterator after the erased element
                         */
                        Iterator erase(ConstIterator pos);
                        /**
                         * Erase the element in the given range
                         * @param  begin the begin iterator for erasing
                         * @param  end   the end iterator for erasing
                         * @return       an iterator after the last erased element
                         */
                        Iterator erase(ConstIterator begin, ConstIterator end);
                        /**
                         * Erase all element with the given key
                         * @param  k the key to search and erase
                         * @return   the number of erased elements
                         */
                        std::size_t erase(Key const& k);

                    //## Assignment Operator ##//
                        /**
                         * Copy table into this
                         * @param table the hash table to copy into this
                         * @return      the reference of himself
                         */
                        HashTable& operator =(HashTable const& table);
                        /**
                         * Move table into this
                         * @param table the hash table to move into this
                         * @return      the reference of himself
                         */
                        HashTable& operator =(HashTable && table);

                    //## Access Operator ##//
                        /**
                         * Try to access the element designed by the given key, if not found insert a default one
                         * @param  k the key used for access
                         * @return   the found/inserted element
                         */
                        T& operator[](Key const& k);
                        /**
                         * Try to access the element designed by the given key, if not found insert a default one
                         * @param  k the key used for access
                         * @return   the found/inserted element
                         */
                        T& operator[](Key && k);

                    //## Stream Operator ##//
                        /**
                         * Convert the object into a string representation
                         * @return the converted object
                         */
                        String toString() const;

                private :   // Methods
                    /**
                     * Compute the hash value from the given key
                     * @param  k the key to hash
                     * @return   the corresponding hash value
                     */
                    std::size_t hashKey(Key const& k) const;
                    /**
                     * Compare two key and return if they are equals
                     * @param  k1 the first key
                     * @param  k2 the second key
                     * @return    if both key are equals
                     */
                    bool compareKey(Key const& k1, Key const& k2) const;
                    /**
                     * Compute the next index using the probing function
                     * @param  index the index to advance
                     * @return       the new index
                     */
                    std::size_t next(std::size_t index) const;
                    /**
                     * Get the corresponding bucket from a given hash
                     * @param  hash the hash value
                     * @return      the corresponding bucket index
                     */
                    std::size_t bucketFromHash(std::size_t hash) const;
                    /**
                     * Round up to the next power of two value
                     * @param  count the value to round up
                     * @return       the rounded value
                     */
                    std::size_t roundUpToPowerOfTwo(std::size_t count) const;
                    /**
                     * Insert a value in a full bucket
                     * @param index          the bucket index
                     * @param distanceToNext the distance to the next bucket
                     * @param pair           the data to insert
                     */
                    void insertValue(std::size_t index, std::ptrdiff_t distanceToNext, Pair<Key, T> && pair);
                    /**
                     * Insert a value from a rehash call
                     * @param index          the bucket index
                     * @param distanceToNext the distance to the next bucket
                     * @param pair           the data to insert
                     */
                    void insertOnRehash(std::size_t index, std::ptrdiff_t distanceToNext, Pair<Key, T> && pair);
                    /**
                     * @return the next valid size for the table
                     */
                    std::size_t getNewSize() const;

                private :    // Static
                    static constexpr float DEFAULT_MAX_LOAD_FACTOR = 0.9f;
                    static constexpr float REHASH_MIN_LOAD_FACTOR = 0.15f;
                    static const std::ptrdiff_t REHASH_HIGH_PROBE = 128;
                    static const std::size_t DEFAULT_BUCKET_COUNT = 0;
            };

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return        the modified stream
             */
            template <class Key, class T, class Hash, class KeyEqual>
            std::ostream& operator <<(std::ostream& stream, HashTable<Key, T, Hash, KeyEqual> const& o);
        }
    }

    #include "NRE_HashTable.tpp"
