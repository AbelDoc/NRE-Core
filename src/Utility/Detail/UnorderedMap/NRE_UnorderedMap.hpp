
    /**
     * @file NRE_UnorderedMap.hpp
     * @brief Declaration of Utility's API's Container : UnorderedMap
     * @author Louis ABEL
     * @date 01/07/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../HashTable/NRE_HashTable.hpp"

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

                /**
                 * @class UnorderedMap
                 * @brief An unordered map, associative unordered container
                 */
                template <class Key, class T, class Allocator, bool StoreHash = false, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
                class UnorderedMap : public Stringable<UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>> {
                    public :     // Traits
                        /**< The table key type */
                        using KeyType               = Key;
                        /**< The table mapped type */
                        using MappedType            = T;
                        /**< The container's allocated type */
                        using ValueType             = Pair<KeyType, MappedType>;
                        /**< The container's allocator */
                        using AllocatorType         = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::AllocatorType;
                        /**< The object's size type */
                        using SizeType              = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType;
                        /**< The object's difference type */
                        using DifferenceType        = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::DifferenceType;
                        /**< The allocated type reference */
                        using Reference             = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Reference;
                        /**< The allocated type const reference */
                        using ConstReference        = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstReference;
                        /**< The allocated type pointer */
                        using Pointer               = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Pointer;
                        /**< The allocated type const pointer */
                        using ConstPointer          = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstPointer;
                        /**< Mutable random access iterator */
                        using Iterator              = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator;
                        /**< Immuable random access iterator */
                        using ConstIterator         = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator;
                        /**< Mutable random access iterator */
                        using LocalIterator         = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalIterator;
                        /**< Immuable random access iterator */
                        using ConstLocalIterator    = typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator;
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
                        /**< STL compatibility */
                        using iterator              = Iterator;
                        /**< STL compatibility */
                        using const_iterator        = ConstIterator;
                        /**< STL compatibility */
                        using local_iterator        = LocalIterator;
                        /**< STL compatibility */
                        using const_local_iterator  = ConstLocalIterator;
    
                    private :   // Fields
                         HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual> table; /**< The internal hash table */
    
                    public :    // Methods
                        //## Constructor ##//
                            /**
                             * Construct an empty map with a number of bucket
                             * @param bucketCount the base bucket count
                             * @param hasher      the hash function used in the map
                             * @param equal       the equal function used in the map
                             * @param alloc       the hashtable's memory allocator
                             */
                            UnorderedMap(SizeType bucketCount = HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual(), Allocator const& alloc = Allocator());
                            /**
                             * Construct a map with a number of bucket and filled with elements in the given range
                             * @param begin       the begin iterator
                             * @param end         the end iterator
                             * @param bucketCount the base bucket count
                             * @param hasher      the hash function used in the map
                             * @param equal       the equal function used in the map
                             * @param alloc       the hashtable's memory allocator
                             */
                            template <class InputIterator>
                            UnorderedMap(InputIterator begin, InputIterator end, SizeType bucketCount = HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual(), Allocator const& alloc = Allocator());
                            /**
                             * Construct a map with a number of bucket and filled with elements in the given list
                             * @param list        the list to fill the map with
                             * @param bucketCount the base bucket count
                             * @param hasher       the hash function used in the map
                             * @param equal       the equal function used in the map
                             * @param alloc       the hashtable's memory allocator
                             */
                            UnorderedMap(std::initializer_list<ValueType> list, SizeType bucketCount = HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::DEFAULT_BUCKET_COUNT, Hash const& hasher = Hash(), KeyEqual const& equal = KeyEqual(), Allocator const& alloc = Allocator());
    
                        //## Copy Constructor ##//
                            /**
                             * Copy map into this
                             * @param map   the map to copy
                             * @param alloc the hashtable's memory allocator
                             */
                            UnorderedMap(UnorderedMap const& map, Allocator const& alloc = Allocator());
    
                        //## Move Constructor ##//
                            /**
                             * Move map into this
                             * @param map   the map to move
                             * @param alloc the hashtable's memory allocator
                             */
                            UnorderedMap(UnorderedMap && map, Allocator const& alloc = Allocator());
    
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
                             * @return the number of buckets in the map
                             */
                            SizeType getBucketCount() const;
                            /**
                             * @return the maximum number of bucket in the map
                             */
                            constexpr SizeType getMaxBucketCount() const;
                            /**
                             * @return the number of elements in the map
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
                             * @return the maximum map size
                             */
                            constexpr SizeType getMaxSize() const;
                            /**
                             * @return the hashtable's memory allocator
                             */
                            Allocator getAllocator() const;
                            /**
                             * @return if the map is empty
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
                            void reserve(SizeType count);
                            /**
                             * Reserve at least coutn bucket in the map and rehash the map
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
                            MappedType& operator[](KeyType const& k);
                            /**
                             * Try to access the element designed by the given key, if not found insert a default one
                             * @param  k the key used for access
                             * @return   the found/inserted element
                             */
                            MappedType& operator[](KeyType && k);
    
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
                            [[nodiscard]] String toString() const;
                };
            }
        }
    }

    #include "NRE_UnorderedMap.tpp"
