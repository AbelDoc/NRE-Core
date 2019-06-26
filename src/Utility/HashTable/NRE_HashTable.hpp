
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

                            //## Setter ##//
                                /**
                                 * Set this as the last bucket
                                 */
                                void setAsLastBucket();

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
                    float maxLoadFactor;        /**< The maximum load factor before rehash and grow */

                public :     // Methods
                    //## Constructor ##//
                        /**
                         * Construct an empty hashtable with a number of bucket
                         * @param bucketCount the base bucket count
                         * @param hash        the hash function used in the table
                         * @param equal       the equal function used in the table
                         */
                        HashTable(std::size_t bucketCount, Hash const& hash, KeyEqual const& equal);
                        /**
                         * Construct an hashtable with a number of bucket and filled with elements in the given range
                         * @param begin       the begin iterator
                         * @param end         the end iterator
                         * @param bucketCount the base bucket count
                         * @param hash        the hash function used in the table
                         * @param equal       the equal function used in the table
                         */
                        template <class InputIterator>
                        HashTable(InputIterator begin, InputIterator end, std::size_t bucketCount, Hash const& hash, KeyEqual const& equal);
                        /**
                         * Construct an hashtable with a number of bucket and filled with elements in the given list
                         * @param list        the list to fill the table with
                         * @param bucketCount the base bucket count
                         * @param hash        the hash function used in the table
                         * @param equal       the equal function used in the table
                         */
                        HashTable(std::initializer_list<Pair<Key, T>> list, std::size_t bucketCount, Hash const& hash, KeyEqual const& equal);

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

                    //## Methods ##//
                        /**
                         * Clear all buckets
                         */
                        void clear();
                        /**
                         * Swap the hash table with another hash table
                         * @param table the other hash table
                         */
                        void swap(HashTable& table);

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

                public :    // Static
                    static constexpr float DEFAULT_MAX_LOAD_FACTOR = 0.9f;
            };
        }
    }

    #include "NRE_HashTable.tpp"
