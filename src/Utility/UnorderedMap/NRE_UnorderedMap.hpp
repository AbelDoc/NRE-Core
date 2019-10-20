
    /**
     * @file NRE_UnorderedMap.hpp
     * @brief Declaration of Utility's API's Container : UnorderedMap
     * @author Louis ABEL
     * @date 01/07/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../Detail/HashTable/NRE_HashTable.hpp"

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
             * @class UnorderedMap
             * @brief An unordered map, associative unordered container
             */
            template <class Key, class T, bool StoreHash = false, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
            class UnorderedMap : public Stringable<UnorderedMap<Key, T, StoreHash, Hash, KeyEqual>> {
                public :    // Typedef
                    typedef Pair<Key, T> ValueType;
                    typedef typename Detail::HashTable<Key, T, StoreHash, Hash, KeyEqual>::Iterator             Iterator;
                    typedef typename Detail::HashTable<Key, T, StoreHash, Hash, KeyEqual>::ConstIterator        ConstIterator;
                    typedef typename Detail::HashTable<Key, T, StoreHash, Hash, KeyEqual>::LocalIterator        LocalIterator;
                    typedef typename Detail::HashTable<Key, T, StoreHash, Hash, KeyEqual>::ConstLocalIterator   ConstLocalIterator;

                private :   // Fields
                     Detail::HashTable<Key, T, StoreHash, Hash, KeyEqual> table; /**< The internal hash table */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct an empty map with a number of bucket
                         * @param bucketCount the base bucket count
                         * @param hasher      the hash function used in the map
                         * @param equal       the equal function used in the map
                         */
                        UnorderedMap(std::size_t bucketCount = Detail::HashTable<Key, T, StoreHash, Hash, KeyEqual>::DEFAULT_BUCKET_COUNT , Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual());
                        /**
                         * Construct a map with a number of bucket and filled with elements in the given range
                         * @param begin       the begin iterator
                         * @param end         the end iterator
                         * @param bucketCount the base bucket count
                         * @param hasher      the hash function used in the map
                         * @param equal       the equal function used in the map
                         */
                        template <class InputIterator>
                        UnorderedMap(InputIterator begin, InputIterator end, std::size_t bucketCount = Detail::HashTable<Key, T, StoreHash, Hash, KeyEqual>::DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual());
                        /**
                         * Construct a map with a number of bucket and filled with elements in the given list
                         * @param list        the list to fill the map with
                         * @param bucketCount the base bucket count
                         * @param hasher       the hash function used in the map
                         * @param equal       the equal function used in the map
                         */
                        UnorderedMap(std::initializer_list<ValueType> list, std::size_t bucketCount = Detail::HashTable<Key, T, StoreHash, Hash, KeyEqual>::DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual());

                    //## Copy Constructor ##//
                        /**
                         * Copy map into this
                         * @param map the map to copy
                         */
                        UnorderedMap(UnorderedMap const& map);

                    //## Move Constructor ##//
                        /**
                         * Move map into this
                         * @param map the map to move
                         */
                        UnorderedMap(UnorderedMap && map);

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
                         * @return the number of buckets in the map
                         */
                        std::size_t getBucketCount() const;
                        /**
                         * @return the maximum number of bucket in the map
                         */
                        constexpr std::size_t getMaxBucketCount() const;
                        /**
                         * @return the number of elements in the map
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
                         * @return the maximum map size
                         */
                        constexpr std::size_t getMaxSize() const;
                        /**
                         * @return if the map is empty
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
                         * Insert the given value in the map
                         * @param value the pair with the key and the corresponding element
                         * @return      a pair containing an iterator on the inserted element, and a boolean telling if the insertion has been done
                         */
                        Pair<Iterator, bool> insert(ValueType const& value);
                        /**
                         * Insert the given value in the map
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
                         * Insert the given value in the map using the hint as a suggestion for the search start
                         * @param  hint  the hint used for the search
                         * @param  value the value to insert
                         * @return       an iterator on the inserted element
                         */
                        Iterator insertHint(ConstIterator hint, ValueType const& value);
                        /**
                         * Insert the given value in the map using the hint as a suggestion for the search start
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
                         * Swap the map with another map
                         * @param map the other map
                         */
                        void swap(UnorderedMap& map);
                        /**
                         * Reserve at least count bucket in the map and rehash the map
                         * @param count the number of desired bucket
                         */
                        void reserve(std::size_t count);
                        /**
                         * Reserve at least coutn bucket in the map and rehash the map
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
                         * Copy map into this
                         * @param map the map to copy into this
                         * @return      the reference of himself
                         */
                        UnorderedMap& operator =(UnorderedMap const& map);
                        /**
                         * Move map into this
                         * @param map the map to move into this
                         * @return      the reference of himself
                         */
                        UnorderedMap& operator =(UnorderedMap && map);

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

                    //## Comparison Operator ##//
                        /**
                         * Equality test between this and map
                         * @param map the other map
                         * @return the test result
                         */
                        bool operator ==(UnorderedMap const& map) const;
                        /**
                         * Inequality test between this and map
                         * @param map the other map
                         * @return the test result
                         */
                        bool operator !=(UnorderedMap const& map) const;

                    //## Stream Operator ##//
                        /**
                         * Convert the object into a string representation
                         * @return the converted object
                         */
                        String toString() const;
            };

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return        the modified stream
             */
            template <class Key, class T, bool StoreHash, class Hash, class KeyEqual>
            std::ostream& operator <<(std::ostream& stream, UnorderedMap<Key, T, StoreHash, Hash, KeyEqual> const& o);
        }
    }

    #include "NRE_UnorderedMap.tpp"
