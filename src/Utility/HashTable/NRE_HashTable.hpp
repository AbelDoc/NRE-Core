
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
                            Pair<Key, T> data;              /**< The bucket entry data */
                            std::ptrdiff_t distanceToNext;  /**< The ideal distance to the next bucket */

                        public :    // Methods
                            //## Constructor ##//
                                /**
                                 * Construct an empty bucket
                                 */
                                BucketEntry();

                            //## Copy Constructor ##//
                                /**
                                 * Copy bucket into this
                                 * @param bucket the bucket entry to copy
                                 */
                                BucketEntry(BucketEntry const& bucket)

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
                            static const std::ptrdiff_t EMPTY_BUCKET_DISTANCE = -1; /**< The distance used to mark a bucket as empty

                    };

                private :    // Fields
                    Vector<BucketEntry> data;   /**< The hash table data */
                    std::size_t nbElements;     /**< The number in the table */

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
            };
        }
    }

    #include "NRE_HashTable.tpp"
