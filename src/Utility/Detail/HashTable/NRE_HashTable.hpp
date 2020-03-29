
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
    #include "../../Interfaces/Stringable/NRE_Stringable.hpp"
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
            
            namespace Detail {
                /**< Hide hash type implementation */
                using TruncatedHash = std::uint_least32_t;
    
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
                        /**< The bucket distance type */
                        using DistanceType  = std::int_least16_t;
                        /**< The bucket internal storage type */
                        using Storage       = typename std::aligned_storage<sizeof(ValueType), alignof(ValueType)>::type;
        
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
                template <class Key, class T, class Allocator, bool StoreHash = false, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
                class HashTable : public Stringable<HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>>, private Hash, private KeyEqual {
                    static_assert(Memory::IsAllocatorV<Allocator>);
                    public :    // Traits
                        /**< The table key type */
                        using KeyType               = Key;
                        /**< The table mapped type */
                        using MappedType            = T;
                        /**< The container's allocated type */
                        using ValueType             = Pair<KeyType, MappedType>;
                        
                    private :     // Static
                        static constexpr bool STORE_HASH = StoreHash || ((sizeof(BucketEntry<ValueType, true>) == sizeof(BucketEntry<ValueType, false>)) && (!std::is_arithmetic<KeyType>::value || !std::is_same<Hash, std::hash<KeyType>>::value));    /**< Tell if we store the hash in the bucket with the key */
                    
                    public :    // Traits
                        /**< The container's internal allocated type */
                        using ContainerType         = BucketEntry<ValueType, STORE_HASH>;
                        /**< The container's allocator */
                        using AllocatorType         = typename Allocator::template Rebind<ContainerType>;
                        /**< The object's size type */
                        using SizeType              = std::size_t;
                        /**< The object's difference type */
                        using DifferenceType        = std::ptrdiff_t;
                        /**< The table distance type */
                        using DistanceType          = typename BucketEntry<ValueType, STORE_HASH>::DistanceType;
                        /**< The allocated type reference */
                        using Reference             = ValueType&;
                        /**< The allocated type const reference */
                        using ConstReference        = ValueType const&;
                        /**< The allocated type pointer */
                        using Pointer               = typename AllocatorType::Pointer;
                        /**< The allocated type const pointer */
                        using ConstPointer          = typename AllocatorType::ConstPointer;
                        /**< STL compatibility */
                        using value_type            = ValueType;
                        /**< STL compatibility */
                        using allocator_type        = AllocatorType;
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
        
                    private :     // Iterator
                        /**
                         * @class ForwardIterator
                         * @brief Hash table forward iterator
                         */
                        template <class Category>
                        class ForwardIterator : public IteratorTraits<ForwardIterator<Category>, ValueType, Category> {
                            friend class HashTable;
                            public :    // Traits
                                /**< Inherited iterator traits */
                                using Traits = IteratorTraits<ForwardIterator<Category>, ValueType, Category>;
                                /**< The iterated object */
                                using ValueType         = typename Traits::ValueType;
                                /**< The pointer on iterated object */
                                using Pointer           = typename Traits::Pointer;
                                /**< The reference on iterated object */
                                using Reference         = typename Traits::Reference;
                                /**< The iterator difference type */
                                using DifferenceType    = typename Traits::DifferenceType;
                                /**< STL compatibility */
                                using value_type        = ValueType;
                                /**< STL compatibility */
                                using pointer           = Pointer;
                                /**< STL compatibility */
                                using reference         = Reference;
                                /**< STL compatibility */
                                using difference_type   = DifferenceType;
                                /**< STL compatibility */
                                using iterator_category = typename Traits::iterator_category;
                                
                            private :   // Fields
                                BucketEntry<ValueType, STORE_HASH>* current;   /**< The current iterator bucket */
                                
                            public :    // Methods
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
    
                                //## Move Constructor ##//
                                    /**
                                     * Move it into this
                                     * @param it the iterator to move
                                     */
                                    ForwardIterator(ForwardIterator && it) = default;
                        
                                //## Deconstructor ##//
                                    /**
                                     * ForwardIterator Deconstructor
                                     */
                                    ~ForwardIterator() = default;
    
                                //## Methods ##//
                                    /**
                                     * @return a reference on the iterated data
                                     */
                                    Reference dereference() const;
                                    /**
                                     * Increment the iterator position by one
                                     */
                                    void increment();
                                    /**
                                     * Test if the given iterator point to the same position
                                     * @param it the other iterator
                                     * @return   the test's result
                                     */
                                    bool equal(ForwardIterator const& it) const;
                    
                                //## Assignment Operator ##//
                                    /**
                                     * Copy assignment of it into this
                                     * @param it the iterator to copy
                                     * @return   the reference of himself
                                     */
                                    ForwardIterator& operator =(ForwardIterator const& it) = default;
                                    /**
                                     * Move assignment of it into this
                                     * @param it the iterator to move
                                     * @return   the reference of himself
                                     */
                                    ForwardIterator& operator =(ForwardIterator && it) = default;
                        };
            
                        /**
                         * @class LocalForwardIterator
                         * @brief Hash table local forward iterator
                         */
                        template <class Category>
                        class LocalForwardIterator : public IteratorTraits<ForwardIterator<Category>, ValueType, Category> {
                            friend class HashTable;
                            public :    // Traits
                                /**< Inherited iterator traits */
                                using Traits = IteratorTraits<ForwardIterator<Category>, ValueType, Category>;
                                /**< The iterated object */
                                using ValueType         = typename Traits::ValueType;
                                /**< The pointer on iterated object */
                                using Pointer           = typename Traits::Pointer;
                                /**< The reference on iterated object */
                                using Reference         = typename Traits::Reference;
                                /**< The iterator difference type */
                                using DifferenceType    = typename Traits::DifferenceType;
                                /**< STL compatibility */
                                using value_type        = ValueType;
                                /**< STL compatibility */
                                using pointer           = Pointer;
                                /**< STL compatibility */
                                using reference         = Reference;
                                /**< STL compatibility */
                                using difference_type   = DifferenceType;
                                /**< STL compatibility */
                                using iterator_category = typename Traits::iterator_category;
                                
                            private :   // Fields
                                BucketEntry<ValueType, STORE_HASH>* current;   /**< The current iterator bucket */

                            public :    // Methods
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
    
                                //## Move Constructor ##//
                                    /**
                                     * Move it into this
                                     * @param it the iterator to move
                                     */
                                    LocalForwardIterator(LocalForwardIterator && it) = default;
                        
                                //## Deconstructor ##//
                                    /**
                                     * LocalForwardIterator Deconstructor
                                     */
                                    ~LocalForwardIterator() = default;
    
                                //## Methods ##//
                                    /**
                                     * @return a reference on the iterated data
                                     */
                                    Reference dereference() const;
                                    /**
                                     * Increment the iterator position by one
                                     */
                                    void increment();
                                    /**
                                     * Test if the given iterator point to the same position
                                     * @param it the other iterator
                                     * @return   the test's result
                                     */
                                    bool equal(LocalForwardIterator const& it) const;
                    
                                //## Assignment Operator ##//
                                    /**
                                     * Copy assignment of it into this
                                     * @param it the iterator to copy
                                     * @return   the reference of himself
                                     */
                                    LocalForwardIterator& operator =(LocalForwardIterator const& it) = default;
                                    /**
                                     * Move assignment of it into this
                                     * @param it the iterator to move
                                     * @return   the reference of himself
                                     */
                                    LocalForwardIterator& operator =(LocalForwardIterator && it) = default;
                        };

                    public :     // Traits
                        /**< Mutable random access iterator */
                        using Iterator              = ForwardIterator<InOutForwardIterator>;
                        /**< Immuable random access iterator */
                        using ConstIterator         = ForwardIterator<Utility::ForwardIterator>;
                        /**< Mutable random access iterator */
                        using LocalIterator         = LocalForwardIterator<InOutForwardIterator>;
                        /**< Immuable random access iterator */
                        using ConstLocalIterator    = LocalForwardIterator<Utility::ForwardIterator>;
                        /**< STL compatibility */
                        using iterator              = Iterator;
                        /**< STL compatibility */
                        using const_iterator        = ConstIterator;
                        /**< STL compatibility */
                        using local_iterator        = LocalIterator;
                        /**< STL compatibility */
                        using const_local_iterator  = ConstLocalIterator;
    
                    private :    // Fields
                        Detail::Vector<ContainerType, AllocatorType> data;   /**< The hash table data */
                        SizeType nbElements;                                 /**< The number in the table */
                        SizeType mask;                                       /**< The mask used with the power of two policy */
                        SizeType loadThresHold;                              /**< The number of element before growing the table */
                        float maxLoadFactor;                                 /**< The maximum load factor before rehash and grow */
                        bool growAtNextInsert;                               /**< Used to grow at the next insert call */
        
                    public :     // Methods
                        //## Constructor ##//
                            /**
                             * Construct an empty hashtable with a number of bucket
                             * @param bucketCount the base bucket count
                             * @param hasher      the hash function used in the table
                             * @param equal       the equal function used in the table
                             * @param alloc       the hashtable's memory allocator
                             */
                            HashTable(SizeType bucketCount = DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual(), Allocator const& alloc = Allocator());
                            /**
                             * Construct an hashtable with a number of bucket and filled with elements in the given range
                             * @param begin       the begin iterator
                             * @param end         the end iterator
                             * @param bucketCount the base bucket count
                             * @param hasher      the hash function used in the table
                             * @param equal       the equal function used in the table
                             * @param alloc       the hashtable's memory allocator
                             */
                            template <class InputIterator>
                            HashTable(InputIterator begin, InputIterator end, SizeType bucketCount = DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual(), Allocator const& alloc = Allocator());
                            /**
                             * Construct an hashtable with a number of bucket and filled with elements in the given list
                             * @param list        the list to fill the table with
                             * @param bucketCount the base bucket count
                             * @param hasher      the hash function used in the table
                             * @param equal       the equal function used in the table
                             * @param alloc       the hashtable's memory allocator
                             */
                            HashTable(std::initializer_list<ValueType> list, SizeType bucketCount = DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual(), Allocator const& alloc = Allocator());
                
                        //## Copy Constructor ##//
                            /**
                             * Copy table into this
                             * @param table the table to copy
                             */
                            HashTable(HashTable const& table);
                            /**
                             * Copy table into this
                             * @param table the table to copy
                             * @param alloc the hashtable's memory allocator
                             */
                            HashTable(HashTable const& table, Allocator const& alloc);
            
                        //## Move Constructor ##//
                            /**
                             * Move table into this
                             * @param table the table to move
                             */
                            HashTable(HashTable && table);
                            /**
                             * Move table into this
                             * @param table the table to move
                             * @param alloc the hashtable's memory allocator
                             */
                            HashTable(HashTable && table, Allocator const& alloc);
            
                        //## Getter ##//
                            /**
                             * Access a particular element with bound checking
                             * @param  k the element key
                             * @return   the corresponding element
                             */
                            MappedType& get(KeyType const& k);
                            /**
                             * Access a particular element with bound checking
                             * @param  k the element key
                             * @return   the corresponding element
                             */
                            MappedType const& get(KeyType const& k) const;
                            /**
                             * @return the number of buckets in the table
                             */
                            SizeType getBucketCount() const;
                            /**
                             * @return the maximum number of bucket in the table
                             */
                            constexpr SizeType getMaxBucketCount() const;
                            /**
                             * @return the number of elements in the table
                             */
                            SizeType getSize() const;
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
                            constexpr SizeType getMaxSize() const;
                            /**
                             * @return the hashtable's memory allocator
                             */
                            Allocator getAllocator() const;
                            /**
                             * @return if the table is empty
                             */
                            bool isEmpty() const;
                            /**
                             * Find the number of element with the given key
                             * @param  k the key to search
                             * @return   the number of corresponding elements
                             */
                            SizeType getCount(KeyType const& k) const;
                            /**
                             * Get the bucket index from a given key
                             * @param  k the key to search
                             * @return   the corresponding bucket
                             */
                            SizeType getBucket(KeyType const& k) const;
            
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
                            LocalIterator begin(SizeType index);
                            /**
                             * Grab a const iterator on a given bucket
                             * @param index the bucket index
                             * @return the iterator on the bucket
                             */
                            ConstLocalIterator begin(SizeType index) const;
                            /**
                             * Grab a const iterator on a given bucket
                             * @param index the bucket index
                             * @return the iterator on the bucket
                             */
                            ConstLocalIterator cbegin(SizeType index) const;
                            /**
                             * Grab an iterator on a given bucket end
                             * @param index the bucket index
                             * @return the iterator on the bucket end
                             */
                            LocalIterator end(SizeType index);
                            /**
                             * Grab a const iterator on a given bucket end
                             * @param index the bucket index
                             * @return the iterator on the bucket end
                             */
                            ConstLocalIterator end(SizeType index) const;
                            /**
                             * Grab a const iterator on a given bucket end
                             * @param index the bucket index
                             * @return the iterator on the bucket end
                             */
                            ConstLocalIterator cend(SizeType index) const;
            
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
                            void reserve(SizeType count);
                            /**
                             * Reserve at least coutn bucket in the table and rehash the table
                             * @param count the number of desired bucket
                             */
                            void rehash(SizeType count);
                            /**
                             * Find a range of iterator containing all elements with the given key, both end if not found
                             * @param key the key to search
                             * @return    a pair of iterator
                             */
                            Pair<Iterator, Iterator> equalRange(KeyType const& key);
                            /**
                             * Find a range of iterator containing all elements with the given key, both end if not found
                             * @param key the key to search
                             * @return    a pair of iterator
                             */
                            Pair<ConstIterator, ConstIterator> equalRange(KeyType const& key) const;
                            /**
                             * Find the element corresponding with the given key
                             * @param  k the key to search
                             * @return   the iterator pointing on the element, or end if not found
                             */
                            Iterator find(KeyType const& k);
                            /**
                             * Find the element corresponding with the given key
                             * @param  k the key to search
                             * @return   the iterator pointing on the element, or end if not found
                             */
                            ConstIterator find(KeyType const& k) const;
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
                            SizeType erase(KeyType const& k);
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
                            MappedType& operator[](KeyType const& k);
                            /**
                             * Try to access the element designed by the given key, if not found insert a default one
                             * @param  k the key used for access
                             * @return   the found/inserted element
                             */
                            MappedType& operator[](KeyType && k);
            
                        //## Stream Operator ##//
                            /**
                             * Convert the object into a string representation
                             * @return the converted object
                             */
                            [[nodiscard]] String toString() const;
        
                    private :   // Methods
                        /**
                         * Compute the hash value from the given key
                         * @param  k the key to hash
                         * @return   the corresponding hash value
                         */
                        SizeType hashKey(KeyType const& k) const;
                        /**
                         * Compare two key and return if they are equals
                         * @param  k1 the first key
                         * @param  k2 the second key
                         * @return    if both key are equals
                         */
                        bool compareKey(KeyType const& k1, KeyType const& k2) const;
                        /**
                         * Compute the next index using the probing function
                         * @param  index the index to advance
                         * @return       the new index
                         */
                        SizeType next(SizeType index) const;
                        /**
                         * Get the corresponding bucket from a given hash
                         * @param  hash the hash value
                         * @return      the corresponding bucket index
                         */
                        SizeType bucketFromHash(SizeType hash) const;
                        /**
                         * Round up to the next power of two value
                         * @param  count the value to round up
                         * @return       the rounded value
                         */
                        SizeType roundUpToPowerOfTwo(SizeType count) const;
                        /**
                         * Insert a value in a full bucket
                         * @param index          the bucket index
                         * @param distanceToNext the distance to the next bucket
                         * @param h              the truncated hash
                         * @param pair           the data to insert
                         */
                        void insertValue(SizeType index, DistanceType distanceToNext, TruncatedHash h, ValueType& pair);
                        /**
                         * Insert a value from a rehash call
                         * @param index          the bucket index
                         * @param distanceToNext the distance to the next bucket
                         * @param h              the truncated hash
                         * @param pair           the data to insert
                         */
                        void insertOnRehash(SizeType index, DistanceType distanceToNext, TruncatedHash h, ValueType && pair);
                        /**
                         * Rehash the table if it's under extreme load
                         * @return if the table has been rehashed
                         */
                        bool rehashOnExtremeLoad();
                        /**
                         * @return the next valid size for the table
                         */
                        SizeType getNewSize() const;
        
                    private :    // Static
                        static constexpr bool USE_STORED_HASH_ON_LOOKUP = StoreHash;    /**< Tell if we use the stored hash on lookup */
                        static constexpr float DEFAULT_MAX_LOAD_FACTOR  = 0.9f;         /**< The default max load factor before growing */
                        static constexpr float REHASH_MIN_LOAD_FACTOR   = 0.15f;        /**< The minimum load factor for rehash */
                        static const DistanceType REHASH_HIGH_PROBE     = 128;          /**< The maximum distance between 2 bucket before rehash */
            
                        /**
                         * Tell if we use the stored hash on rehash
                         * @param  count the current bucket count
                         * @return       if we use the stored hash
                         */
                        static bool USE_STORED_HASH_ON_REHASH(SizeType count) {
                            return STORE_HASH && count - 1 <= std::numeric_limits<TruncatedHash>::max();
                        }
        
                    public :    // Static
                        static const SizeType DEFAULT_BUCKET_COUNT = 0;              /**< The default bucket count */
                };
            }
        }
    }

    #include "NRE_HashTable.tpp"
