
    /**
     * @file NRE_UnorderedMap.tpp
     * @brief Implementation of Utility's API's Container : UnorderedMap
     * @author Louis ABEL
     * @date 01/07/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Utility {
             namespace Detail {

                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::UnorderedMap(SizeType bucketCount, Hash const& hasher, KeyEqual const& equal, Allocator const& alloc) : table(bucketCount, hasher, equal, alloc) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class InputIterator>
                 inline UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::UnorderedMap(InputIterator begin, InputIterator end, SizeType bucketCount, Hash const& hasher, KeyEqual const& equal, Allocator const& alloc) : table(begin, end, bucketCount, hasher, equal, alloc) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::UnorderedMap(std::initializer_list<ValueType> list, SizeType bucketCount, Hash const& hasher, KeyEqual const& equal, Allocator const& alloc) : table(list, bucketCount, hasher, equal, alloc) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::UnorderedMap(UnorderedMap const& map, Allocator const& alloc) : table(map.table, alloc) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::UnorderedMap(UnorderedMap && map, Allocator const& alloc) : table(std::move(map.table), alloc) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::MappedType& UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::get(KeyType const& k) {
                     return table.get(k);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::MappedType const& UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::get(KeyType const& k) const {
                     return table.get(k);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getBucketCount() const {
                     return table.getBucketCount();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 constexpr typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getMaxBucketCount() const {
                     return table.getMaxBucketCount();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getSize() const {
                     return table.getSize();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline float UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getMaxLoadFactor() const {
                     return table.getMaxLoadFactor();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline float UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getLoadFactor() const {
                     return table.getLoadFactor();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 constexpr typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getMaxSize() const {
                     return table.getMaxSize();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Allocator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getAllocator() const {
                     return table.getAllocator();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline bool UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::isEmpty() const {
                     return table.isEmpty();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getCount(KeyType const& k) const {
                     return table.getCount(k);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getBucket(KeyType const& k) const {
                     return table.getBucket(k);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::setMaxLoadFactor(float factor) {
                     table.setMaxLoadFactor(factor);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin() {
                     return table.begin();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin() const {
                     return table.begin();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cbegin() const {
                     return table.cbegin();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end() {
                     return table.end();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end() const {
                     return table.end();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cend() const {
                     return table.cend();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin(SizeType index) {
                     return table.begin(index);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin(SizeType index) const {
                     return table.begin(index);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cbegin(SizeType index) const {
                     return table.cbegin(index);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end(SizeType index) {
                     return table.end(index);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end(SizeType index) const {
                     return table.end(index);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cend(SizeType index) const {
                     return table.cend(index);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Pair<typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator, bool> UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insert(ValueType const& value) {
                     return table.insert(value);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class P>
                 inline Pair<typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator, bool> UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insert(P && value) {
                     return table.insert(value);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class InputIterator>
                 inline void UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insert(InputIterator begin, InputIterator end) {
                     return table.insert(begin, end);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insert(std::initializer_list<ValueType> list) {
                     return table.insert(list);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insertHint(ConstIterator hint, ValueType const& value) {
                     return table.insertHint(hint, value);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class P>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insertHint(ConstIterator hint, P && value) {
                     return table.insertHint(hint, std::forward<P>(value));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class ... Args>
                 inline Pair<typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator, bool> UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::emplace(Args && ... args) {
                     return table.emplace(std::forward<Args>(args)...);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class ... Args>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::emplaceHint(ConstIterator hint, Args && ... args) {
                     return table.emplaceHint(hint, std::forward<Args>(args)...);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::clear() {
                     return table.clear();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::swap(UnorderedMap& map) {
                     using std::swap;
                     swap(table, map.table);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::reserve(SizeType count) {
                     table.reserve(count);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::rehash(SizeType count) {
                     table.rehash(count);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Pair<typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator, typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator> UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::equalRange(KeyType const& key) {
                     return table.equalRange(key);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Pair<typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator, typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator> UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::equalRange(KeyType const& key) const {
                     return table.equalRange(key);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::find(KeyType const& k) {
                     return table.find(k);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::find(KeyType const& k) const {
                     return table.find(k);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(Iterator pos) {
                     return table.erase(pos);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(ConstIterator pos) {
                     return table.erase(pos);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(ConstIterator begin, ConstIterator end) {
                     return table.erase(begin, end);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(KeyType const& k) {
                     return table.erase(k);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Hash UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getHash() const {
                     return table.getHash();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline KeyEqual UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getKeyEqual() const {
                     return table.getKeyEqual();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>& UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator=(UnorderedMap const& map) {
                     table = map.table;
                     return *this;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>& UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator=(UnorderedMap && map) {
                     table = std::move(map.table);
                     return *this;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::MappedType& UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator[](KeyType const& k) {
                     return table[k];
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::MappedType& UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator[](KeyType && k) {
                     return table[std::forward<Key>(k)];
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline String UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::toString() const {
                     return table.toString();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline bool UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator==(UnorderedMap const& map) const {
                     if (getSize() != map.getSize()) {
                         return false;
                     }
    
                     for (auto const& it : *this) {
                         auto mapIt = map.find(it.first);
                         if (mapIt == map.end() || it.second != mapIt->second) {
                             return false;
                         }
                     }
    
                     return true;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline bool UnorderedMap<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator!=(UnorderedMap const& map) const {
                     return !(*this == map);
                 }
            }
         }
     }
