
    /**
     * @file NRE_HashTable.hpp
     * @brief Declaration of Utility's API's Object : HashTable
     * @author Louis ABEL
     * @date 25/06/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <climits>

    #include "../../String/NRE_String.hpp"
    #include "../../Pair/NRE_Pair.hpp"
    #include "../../Vector/NRE_Vector.hpp"
    #include "../../Interfaces/Stringable/NRE_Stringable.hpp"

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
            
            namespace Detail {
                typedef std::uint_least32_t TruncatedHash;
    
                /**
                 * @class BucketEntryHash
                 * @brief Used to store the key hash, or not depending on the template value
                 */
                template <bool StoreHash>
                class BucketEntryHash {
                public :    // Methods
                    /**
                     * Compare the given hash with the stored one and test if they are equals
                     * @return if both hash are equals
                     */
                    bool bucketHashEquals(std::size_t) const {
                        return true;
                    }
                    /**
                     * @return the truncated hash
                     */
                    TruncatedHash getTruncatedHash() const {
                        return 0;
                    }
    
                protected : // Methods
                    /**
                     * Set the internal stored hash
                     */
                    void setHash(TruncatedHash) {
                    }
                };
    
                /**
                 * @class BucketEntryHash
                 * @brief Used to store the key hash, or not depending on the template value
                 */
                template <>
                class BucketEntryHash<true> {
                private :   // Fields
                    TruncatedHash hash;     /**< The internal stored hash */
    
                public :    // Methods
                    /**
                     * Compare the given hash with the stored one and test if they are equals
                     * @param h the hash to compare
                     * @return  if both hash are equals
                     */
                    bool bucketHashEquals(std::size_t h) const {
                        return hash == TruncatedHash(h);
                    }
                    /**
                     * @return the truncated hash
                     */
                    TruncatedHash getTruncatedHash() const {
                        return hash;
                    }
    
                protected : // Methods
                    /**
                     * Set the internal stored hash
                     * @param h the new hash
                     */
                    void setHash(TruncatedHash h) {
                        hash = TruncatedHash(h);
                    }
                };
    
                /**
                 * @class BucketEntry
                 * @brief A bucket entry used as the hash table elements
                 */
                template <class ValueType, bool StoreHash>
                class BucketEntry : public BucketEntryHash<StoreHash> {
                public :    // Typedef
                    typedef std::int_least16_t DistanceType;
                    typedef typename std::aligned_storage<sizeof(ValueType), alignof(ValueType)>::type Storage;
    
                private :   // Fields
                    DistanceType distanceToNext;    /**< The ideal distance to the next bucket */
                    bool last;                      /**< Tell if the bucket is the last filled */
                    Storage data;                   /**< The bucket entry data */
    
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
                    DistanceType getDistanceToNext() const;
                    /**
                     * @return the bucket data
                     */
                    ValueType& getData();
                    /**
                     * @return the bucket data
                     */
                    ValueType const& getData() const;
        
                    //## Setter ##//
                    /**
                     * Set this as the last bucket
                     */
                    void setAsLastBucket();
                    /**
                     * Set the bucket data, must be empty
                     * @param distance the distance to the next bucket
                     * @param h        the new truncated hash
                     * @param newData  the data to set
                     */
                    void setData(DistanceType distance, TruncatedHash h, ValueType && newData);
        
                    //## Methods ##//
                    /**
                     * Clear the bucket data if not empty
                     */
                    void clear();
                    /**
                     * Swap the bucket data with given one
                     * @param distance the distance to the next bucket
                     * @param h        the new truncated hash
                     * @param newData  the data to set
                     */
                    void swapWithData(DistanceType& distance, TruncatedHash& h, ValueType& newData);
        
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
                    static const DistanceType EMPTY_BUCKET_DISTANCE = -1; /**< The distance used to mark a bucket as empty */
        
                };
    
                /**
                 * @class HashTable
                 * @brief Based on TSL Robin Hash, An hashtable used in map and set, an associative container using linear probing, robin hood and shift back optimisation
                 */
                template <class Key, class T, bool StoreHash = false, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
                class HashTable : public Stringable<HashTable<Key, T, StoreHash, Hash, KeyEqual>>, private Hash, private KeyEqual {
                public :    // Typedef
                    typedef Pair<Key, T> ValueType;
    
                private :   // Static
                    static constexpr bool STORE_HASH = StoreHash || ((sizeof(BucketEntry<ValueType, true>) == sizeof(BucketEntry<ValueType, false>)) && (!std::is_arithmetic<Key>::value || !std::is_same<Hash, std::hash<Key>>::value));    /**< Tell if we store the hash in the bucket with the key */
    
                public :     // Iterator
                    typedef typename BucketEntry<ValueType, STORE_HASH>::DistanceType DistanceType;
        
                    /**
                     * @class ForwardIterator
                     * @brief Hash table forward iterator
                     */
                    template <class K>
                    class ForwardIterator {
                        friend class HashTable;
                    private :   // Fields
                        BucketEntry<ValueType, STORE_HASH>* current;   /**< The current iterator bucket */
        
                    public :    // Methods
                        typedef std::ptrdiff_t difference_type;
                        typedef typename HashTable::ValueType value_type;
                        typedef value_type* pointer;
                        typedef value_type& reference;
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
                        ForwardIterator(BucketEntry<ValueType, STORE_HASH>* bucket);
                        /**
                         * Construct the iterator with the given node
                         * @param bucket the iterator bucket
                         */
                        ForwardIterator(const BucketEntry<ValueType, STORE_HASH>* bucket);
            
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
        
                    /**
                     * @class LocalForwardIterator
                     * @brief Hash table local forward iterator
                     */
                    template <class K>
                    class LocalForwardIterator {
                        friend class HashTable;
                    private :   // Fields
                        BucketEntry<ValueType, STORE_HASH>* current;   /**< The current iterator bucket */
        
                    public :    // Methods
                        typedef std::ptrdiff_t difference_type;
                        typedef typename HashTable::ValueType value_type;
                        typedef value_type* pointer;
                        typedef value_type& reference;
                        typedef std::forward_iterator_tag iterator_category;
            
                        //## Constructor ##//
                        /**
                         * Default constructor with nullptr node
                         */
                        LocalForwardIterator() = default;
                        /**
                         * Construct the iterator with the given node
                         * @param bucket the iterator bucket
                         */
                        LocalForwardIterator(BucketEntry<ValueType, STORE_HASH>* bucket);
                        /**
                         * Construct the iterator with the given node
                         * @param bucket the iterator bucket
                         */
                        LocalForwardIterator(const BucketEntry<ValueType, STORE_HASH>* bucket);
            
                        //## Copy Constructor ##//
                        /**
                         * Copy it into this
                         * @param it the iterator to copy
                         */
                        LocalForwardIterator(LocalForwardIterator const& it) = default;
            
                        //## Deconstructor ##//
                        /**
                         * LocalForwardIterator Deconstructor
                         */
                        ~LocalForwardIterator() = default;
            
                        //## Assignment Operator ##//
                        /**
                         * Copy assignment of it into this
                         * @param it the iterator to copy into this
                         * @return   the reference of himself
                         */
                        LocalForwardIterator& operator =(LocalForwardIterator const& it) = default;
            
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
                        LocalForwardIterator& operator++();
                        /**
                         * Post increment operator, access the next element
                         * @return the iterator on the current element
                         */
                        LocalForwardIterator operator++(int);
            
                        //## Comparison Operator ##//
                        /**
                         * Equality test between this and it
                         * @param it the other iterator
                         * @return   the test result
                         */
                        bool operator==(LocalForwardIterator const& it) const;
                        /**
                         * Inequality test between this and it
                         * @param it the other iterator
                         * @return   the test result
                         */
                        bool operator!=(LocalForwardIterator const& it) const;
                    };
        
                    /**< Shortcut to hide Iterator implementation */
                    typedef ForwardIterator<ValueType>          Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef ForwardIterator<const ValueType>    ConstIterator;
        
                    /**< Shortcut to hide Iterator implementation */
                    typedef LocalForwardIterator<ValueType>          LocalIterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef LocalForwardIterator<const ValueType>    ConstLocalIterator;
    
                private :    // Fields
                    Utility::Vector<BucketEntry<ValueType, STORE_HASH>> data;   /**< The hash table data */
                    std::size_t nbElements;     /**< The number in the table */
                    std::size_t mask;           /**< The mask used with the power of two policy */
                    std::size_t loadThresHold;  /**< The number of element before growing the table */
                    float maxLoadFactor;        /**< The maximum load factor before rehash and grow */
                    bool growAtNextInsert;      /**< Used to grow at the next insert call */
    
                public :     // Methods
                    //## Constructor ##//
                    /**
                     * Construct an empty hashtable with a number of bucket
                     * @param bucketCount the base bucket count
                     * @param hasher      the hash function used in the table
                     * @param equal       the equal function used in the table
                     */
                    HashTable(std::size_t bucketCount , Hash const& hasher, KeyEqual const& equal);
                    /**
                     * Construct an hashtable with a number of bucket and filled with elements in the given range
                     * @param begin       the begin iterator
                     * @param end         the end iterator
                     * @param bucketCount the base bucket count
                     * @param hasher      the hash function used in the table
                     * @param equal       the equal function used in the table
                     */
                    template <class InputIterator>
                    HashTable(InputIterator begin, InputIterator end, std::size_t bucketCount, Hash const& hasher, KeyEqual const& equal);
                    /**
                     * Construct an hashtable with a number of bucket and filled with elements in the given list
                     * @param list        the list to fill the table with
                     * @param bucketCount the base bucket count
                     * @param hasher      the hash function used in the table
                     * @param equal       the equal function used in the table
                     */
                    HashTable(std::initializer_list<ValueType> list, std::size_t bucketCount, Hash const& hasher, KeyEqual const& equal);
        
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
                    /**
                     * Get the bucket index from a given key
                     * @param  k the key to search
                     * @return   the corresponding bucket
                     */
                    std::size_t getBucket(Key const& k) const;
        
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
                    /**
                     * Grab an iterator on a given bucket
                     * @param index the bucket index
                     * @return the iterator on the bucket
                     */
                    LocalIterator begin(std::size_t index);
                    /**
                     * Grab a const iterator on a given bucket
                     * @param index the bucket index
                     * @return the iterator on the bucket
                     */
                    ConstLocalIterator begin(std::size_t index) const;
                    /**
                     * Grab a const iterator on a given bucket
                     * @param index the bucket index
                     * @return the iterator on the bucket
                     */
                    ConstLocalIterator cbegin(std::size_t index) const;
                    /**
                     * Grab an iterator on a given bucket end
                     * @param index the bucket index
                     * @return the iterator on the bucket end
                     */
                    LocalIterator end(std::size_t index);
                    /**
                     * Grab a const iterator on a given bucket end
                     * @param index the bucket index
                     * @return the iterator on the bucket end
                     */
                    ConstLocalIterator end(std::size_t index) const;
                    /**
                     * Grab a const iterator on a given bucket end
                     * @param index the bucket index
                     * @return the iterator on the bucket end
                     */
                    ConstLocalIterator cend(std::size_t index) const;
        
                    //## Methods ##//
                    /**
                     * Insert the given value in the table
                     * @param value the pair with the key and the corresponding element
                     * @return      a pair containing an iterator on the inserted element, and a boolean telling if the insertion has been done
                     */
                    Pair<Iterator, bool> insert(ValueType const& value);
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
                    void insert(std::initializer_list<ValueType> list);
                    /**
                     * Insert the given value in the table using the hint as a suggestion for the search start
                     * @param  hint  the hint used for the search
                     * @param  value the value to insert
                     * @return       an iterator on the inserted element
                     */
                    Iterator insertHint(ConstIterator hint, ValueType const& value);
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
                     * @param hint the iterator used as a hint to emplace the element
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
                    /**
                     * @return the hash function
                     */
                    Hash getHash() const;
                    /**
                     * @return the key equal function
                     */
                    KeyEqual getKeyEqual() const;
        
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
                     * @param h              the truncated hash
                     * @param pair           the data to insert
                     */
                    void insertValue(std::size_t index, DistanceType distanceToNext, TruncatedHash h, ValueType& pair);
                    /**
                     * Insert a value from a rehash call
                     * @param index          the bucket index
                     * @param distanceToNext the distance to the next bucket
                     * @param h              the truncated hash
                     * @param pair           the data to insert
                     */
                    void insertOnRehash(std::size_t index, DistanceType distanceToNext, TruncatedHash h, ValueType && pair);
                    /**
                     * Rehash the table if it's under extreme load
                     * @return if the table has been rehashed
                     */
                    bool rehashOnExtremeLoad();
                    /**
                     * @return the next valid size for the table
                     */
                    std::size_t getNewSize() const;
    
                private :    // Static
                    static constexpr bool USE_STORED_HASH_ON_LOOKUP = StoreHash;    /**< Tell if we use the stored hash on lookup */
                    static constexpr float DEFAULT_MAX_LOAD_FACTOR = 0.9f;          /**< The default max load factor before growing */
                    static constexpr float REHASH_MIN_LOAD_FACTOR = 0.15f;          /**< The minimum load factor for rehash */
                    static const DistanceType REHASH_HIGH_PROBE = 128;              /**< The maximum distance between 2 bucket before rehash */
        
                    /**
                     * Tell if we use the stored hash on rehash
                     * @param  count the current bucket count
                     * @return       if we use the stored hash
                     */
                    static bool USE_STORED_HASH_ON_REHASH(std::size_t count) {
                        return STORE_HASH && count - 1 <= std::numeric_limits<TruncatedHash>::max();
                    }
    
                public :    // Static
                    static const std::size_t DEFAULT_BUCKET_COUNT = 0;              /**< The default bucket count */
                };
            }
        }
    }

    #include "NRE_HashTable.tpp"
