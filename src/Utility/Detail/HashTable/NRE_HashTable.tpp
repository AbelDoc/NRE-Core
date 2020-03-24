
    /**
     * @file NRE_HashTable.tpp
     * @brief Implementation of Utility's API's Object : HashTable
     * @author Louis ABEL
     * @date 26/06/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Utility {
             namespace Detail {
    
                 template <class ValueType, bool StoreHash>
                 inline BucketEntry<ValueType, StoreHash>::BucketEntry() : BucketEntryHash<StoreHash>(), distanceToNext(EMPTY_BUCKET_DISTANCE), last(false) {
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline BucketEntry<ValueType, StoreHash>::BucketEntry(BucketEntry const& bucket) : BucketEntryHash<StoreHash>(bucket), distanceToNext(EMPTY_BUCKET_DISTANCE), last(bucket.last) {
                     if (!bucket.isEmpty()) {
                         ::new(&data) ValueType(bucket.getData());
                         distanceToNext = bucket.distanceToNext;
                     }
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline BucketEntry<ValueType, StoreHash>::BucketEntry(BucketEntry&& bucket) : BucketEntryHash<StoreHash>(bucket), distanceToNext(EMPTY_BUCKET_DISTANCE), last(bucket.last) {
                     if (!bucket.isEmpty()) {
                         ::new(&data) ValueType(std::move(bucket.getData()));
                         distanceToNext = bucket.distanceToNext;
                     }
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline BucketEntry<ValueType, StoreHash>::~BucketEntry() {
                     clear();
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline bool BucketEntry<ValueType, StoreHash>::isEmpty() const {
                     return distanceToNext == EMPTY_BUCKET_DISTANCE;
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline bool BucketEntry<ValueType, StoreHash>::isLastBucket() const {
                     return last;
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline typename BucketEntry<ValueType, StoreHash>::DistanceType
                 BucketEntry<ValueType, StoreHash>::getDistanceToNext() const {
                     return distanceToNext;
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline ValueType& BucketEntry<ValueType, StoreHash>::getData() {
                     return *reinterpret_cast <ValueType*> (&data);
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline ValueType const& BucketEntry<ValueType, StoreHash>::getData() const {
                     return *reinterpret_cast <const ValueType*> (&data);
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline void BucketEntry<ValueType, StoreHash>::setAsLastBucket() {
                     last = true;
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline void BucketEntry<ValueType, StoreHash>::setData(DistanceType distance, TruncatedHash h,ValueType&& newData) {
                     ::new(&data) ValueType(std::move(newData));
                     this->setHash(h);
                     distanceToNext = distance;
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline void BucketEntry<ValueType, StoreHash>::clear() {
                     if (!isEmpty()) {
                         getData().~ValueType();
                         distanceToNext = EMPTY_BUCKET_DISTANCE;
                     }
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline void BucketEntry<ValueType, StoreHash>::swapWithData(DistanceType& distance, TruncatedHash& h, ValueType& newData) {
                     using std::swap;
                     swap(distanceToNext, distance);
                     swap(getData(), newData);
        
                     (void) h;
                     if (StoreHash) {
                         auto tmp = this->getTruncatedHash();
                         this->setHash(h);
                         h = tmp;
                     }
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline BucketEntry<ValueType, StoreHash>& BucketEntry<ValueType, StoreHash>::operator =(BucketEntry const& bucket) {
                     if (this != &bucket) {
                         clear();
            
                         BucketEntryHash<StoreHash>::operator =(bucket);
                         if (!bucket.isEmpty()) {
                             ::new(&data) ValueType(bucket.getData());
                         }
            
                         distanceToNext = bucket.distanceToNext;
                         last = bucket.last;
                     }
                     return *this;
                 }
    
                 template <class ValueType, bool StoreHash>
                 inline BucketEntry<ValueType, StoreHash>& BucketEntry<ValueType, StoreHash>::operator =(BucketEntry&& bucket) {
                     if (this != &bucket) {
                         clear();
            
                         BucketEntryHash<StoreHash>::operator =(std::move(bucket));
                         if (!bucket.isEmpty()) {
                             ::new(&data) ValueType(std::move(bucket.getData()));
                         }
            
                         distanceToNext = bucket.distanceToNext;
                         last = bucket.last;
                     }
                     return *this;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ForwardIterator<K>::ForwardIterator(BucketEntry <ValueType, STORE_HASH>* bucket) : current(bucket) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ForwardIterator<K>::ForwardIterator(const BucketEntry <ValueType, STORE_HASH>* bucket) : current(const_cast <BucketEntry <ValueType, STORE_HASH>*> (bucket)) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline K& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ForwardIterator<K>::operator *() const {
                     return current->getData();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline K* HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ForwardIterator<K>::operator ->() const {
                     return &current->getData();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::template ForwardIterator<K>&
                 HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ForwardIterator<K>::operator ++() {
                     while (true) {
                         if (current->isLastBucket()) {
                             ++current;
                             return *this;
                         }
            
                         ++current;
                         if (!current->isEmpty()) {
                             return *this;
                         }
                     }
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::template ForwardIterator<K>
                 HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ForwardIterator<K>::operator ++(int) {
                     ForwardIterator it(current);
                     ++(*this);
                     return it;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline bool HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ForwardIterator<K>::operator ==(ForwardIterator const& it) const {
                     return current == it.current;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline bool HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ForwardIterator<K>::operator !=(ForwardIterator const& it) const {
                     return current != it.current;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalForwardIterator<K>::LocalForwardIterator(BucketEntry <ValueType, STORE_HASH>* bucket) : current(bucket) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalForwardIterator<K>::LocalForwardIterator(const BucketEntry <ValueType, STORE_HASH>* bucket) : current(const_cast <BucketEntry <ValueType, STORE_HASH>*> (bucket)) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline K& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalForwardIterator<K>::operator *() const {
                     return current->getData();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline K* HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalForwardIterator<K>::operator ->() const {
                     return &current->getData();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::template LocalForwardIterator<K>&
                 HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalForwardIterator<K>::operator ++() {
                     current = nullptr;
                     return *this;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::template LocalForwardIterator<K>
                 HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalForwardIterator<K>::operator ++(int) {
                     LocalForwardIterator it(current);
                     ++(*this);
                     return it;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline bool HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalForwardIterator<K>::operator ==(LocalForwardIterator const& it) const {
                     return current == it.current;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class K>
                 inline bool HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalForwardIterator<K>::operator !=(LocalForwardIterator const& it) const {
                     return current != it.current;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(std::size_t bucketCount, Hash const& hasher, KeyEqual const& equal, Allocator const& alloc) : Hash(hasher), KeyEqual(equal), data(alloc), nbElements(0), maxLoadFactor(DEFAULT_MAX_LOAD_FACTOR), growAtNextInsert(false) {
                     data.resize(roundUpToPowerOfTwo(bucketCount));
                     data.getLast().setAsLastBucket();
                     mask = data.getSize() - 1;
                     setMaxLoadFactor(maxLoadFactor);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class InputIterator>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(InputIterator begin, InputIterator end, std::size_t bucketCount, Hash const& hasher, KeyEqual const& equal, Allocator const& alloc) : HashTable(bucketCount, hasher, equal, alloc) {
                     insert(begin, end);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(std::initializer_list<ValueType> list, std::size_t bucketCount, Hash const& hasher, KeyEqual const& equal, Allocator const& alloc) : HashTable(bucketCount, hasher, equal, alloc) {
                     insert(list);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(HashTable const& table, Allocator const& alloc) : Hash(table), KeyEqual(table), data(table.data, alloc), nbElements(table.nbElements), mask(table.mask), loadThresHold(table.loadThresHold), maxLoadFactor(table.maxLoadFactor), growAtNextInsert(table.growAtNextInsert) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(HashTable&& table, Allocator const& alloc) : Hash(std::move(static_cast <Hash&> (table))), KeyEqual(std::move(static_cast <KeyEqual&> (table))), data(std::move(table.data), alloc), nbElements(table.nbElements), mask(table.mask), loadThresHold(table.loadThresHold), maxLoadFactor(table.maxLoadFactor), growAtNextInsert(table.growAtNextInsert) {
                     table.data.clear();
                     table.nbElements = 0;
                     table.loadThresHold = 0;
                     table.growAtNextInsert = false;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline T& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::get(Key const& k) {
                     auto it = find(k);
                     if (it == end()) {
                         throw std::out_of_range("Accessing non existing element in NRE::Utility::HashTable.");
                     }
                     return it->second;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline T const& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::get(Key const& k) const {
                     auto it = find(k);
                     if (it == end()) {
                         throw std::out_of_range("Accessing non existing element in NRE::Utility::HashTable.");
                     }
                     return it->second;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getBucketCount() const {
                     return data.getSize();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 constexpr std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getMaxBucketCount() const {
                     return data.getMaxSize();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getSize() const {
                     return nbElements;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline float HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getMaxLoadFactor() const {
                     return maxLoadFactor;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline float HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getLoadFactor() const {
                     return static_cast <float> (getSize()) / static_cast <float> (getBucketCount());
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Allocator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getAllocator() const {
                     return data.getAllocator();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 constexpr std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getMaxSize() const {
                     return std::numeric_limits<std::size_t>::max();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline bool HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::isEmpty() const {
                     return nbElements == 0;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getCount(Key const& k) const {
                     if (find(k) != end()) {
                         return 1;
                     } else {
                         return 0;
                     }
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getBucket(Key const& k) const {
                     return bucketFromHash(hashKey(k));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::setMaxLoadFactor(float factor) {
                     if (factor < 0.0f || factor > 1.0f) {
                         throw std::out_of_range("NRE::Utility::HashTable max load factor must be between 0.0 and 1.0.");
                     }
                     maxLoadFactor = factor;
                     loadThresHold = static_cast <std::size_t> (static_cast <float> (getBucketCount()) * maxLoadFactor);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin() {
                     std::size_t index = 0;
                     while (index < getBucketCount() && data[index].isEmpty()) {
                         ++index;
                     }
        
                     return Iterator(data.getData() + index);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin() const {
                     std::size_t index = 0;
                     while (index < getBucketCount() && data[index].isEmpty()) {
                         ++index;
                     }
        
                     return ConstIterator(data.getData() + index);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cbegin() const {
                     return begin();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end() {
                     return Iterator(data.getData() + data.getSize());
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end() const {
                     return ConstIterator(data.getData() + data.getSize());
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cend() const {
                     return end();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin(std::size_t index) {
                     return LocalIterator(&data[index]);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin(std::size_t index) const {
                     return ConstLocalIterator(&data[index]);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cbegin(std::size_t index) const {
                     return begin();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end(std::size_t index) {
                     return LocalIterator(nullptr);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end(std::size_t index) const {
                     return ConstLocalIterator(nullptr);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cend(std::size_t index) const {
                     return end();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Pair<typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator, bool> HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insert(ValueType const& value) {
                     return emplace(value);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class P>
                 inline Pair<typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator, bool> HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insert(P&& value) {
                     return emplace(std::forward<P>(value));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class InputIterator>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insert(InputIterator begin, InputIterator end) {
                     std::size_t count = std::distance(begin, end);
                     std::size_t free = loadThresHold - getSize();
                     if (count > 0 && free < count) {
                         reserve(getSize() + count);
                     }
                     for (; begin != end; ++begin) {
                         insert(*begin);
                     }
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insert(std::initializer_list<ValueType> list) {
                     insert(list.begin(), list.end());
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insertHint(ConstIterator, ValueType const& value) {
                     return insert(value).first;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class P>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insertHint(ConstIterator, P&& value) {
                     return insert(std::forward<P>(value)).first;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class ... Args>
                 inline Pair<typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator, bool> HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::emplace(Args&& ... args) {
                     ValueType toInsert(std::forward<Args>(args)...);
                     Key& key = toInsert.first;
        
                     std::size_t hashValue = hashKey(key);
                     std::size_t index = bucketFromHash(hashValue);
                     DistanceType distanceToNext = 0;
        
                     while (distanceToNext <= data[index].getDistanceToNext()) {
                         if ((!USE_STORED_HASH_ON_LOOKUP || data[index].bucketHashEquals(hashValue)) &&
                             compareKey(data[index].getData().first, key)) {
                             return Pair<Iterator, bool>(data.getData() + index, false);
                         }
            
                         index = next(index);
                         ++distanceToNext;
                     }
        
                     if (rehashOnExtremeLoad()) {
                         index = bucketFromHash(hashValue);
                         distanceToNext = 0;
            
                         while (distanceToNext <= data[index].getDistanceToNext()) {
                             index = next(index);
                             ++distanceToNext;
                         }
                     }
        
                     if (data[index].isEmpty()) {
                         data[index].setData(distanceToNext, TruncatedHash(hashValue), std::move(toInsert));
                     } else {
                         insertValue(index, distanceToNext, TruncatedHash(hashValue), toInsert);
                     }
                     ++nbElements;
        
                     return Pair<Iterator, bool>(Iterator(data.getData() + index), true);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class ... Args>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::emplaceHint(ConstIterator, Args&& ... args) {
                     return emplace(std::forward<Args>(args)...).first;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::clear() {
                     for (BucketEntry<ValueType, STORE_HASH>& bucket : data) {
                         bucket.clear();
                     }
        
                     nbElements = 0;
                     growAtNextInsert = false;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::swap(HashTable& table) {
                     using std::swap;
        
                     swap(static_cast <Hash&> (*this), static_cast <Hash&> (table));
                     swap(static_cast <KeyEqual&> (*this), static_cast <KeyEqual&> (table));
                     swap(data, table.data);
                     swap(nbElements, table.nbElements);
                     swap(mask, table.mask);
                     swap(loadThresHold, table.loadThresHold);
                     swap(maxLoadFactor, table.maxLoadFactor);
                     swap(growAtNextInsert, table.growAtNextInsert);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::reserve(std::size_t count) {
                     rehash(static_cast <std::size_t> (std::ceil(static_cast <float> (count) / getMaxLoadFactor())));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::rehash(std::size_t count) {
                     count = std::max(count, static_cast <std::size_t> (std::ceil(static_cast <float> (getSize()) / getMaxLoadFactor())));
                     HashTable newTable(count, static_cast <Hash&> (*this), static_cast <KeyEqual&> (*this));
        
                     bool useStoredHash = USE_STORED_HASH_ON_REHASH(newTable.getBucketCount());
        
                     for (auto& bucket : data) {
                         if (!bucket.isEmpty()) {
                             std::size_t hashValue = (useStoredHash) ? (static_cast <std::size_t> (bucket.getTruncatedHash())) : (newTable.hashKey(bucket.getData().first));
                             newTable.insertOnRehash(newTable.bucketFromHash(hashValue), 0, TruncatedHash(hashValue), std::move(bucket.getData()));
                         }
                     }
        
                     newTable.nbElements = nbElements;
                     newTable.swap(*this);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Pair<typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator, typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator> HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::equalRange(Key const& k) {
                     Iterator it = find(k);
                     return Pair<Iterator, Iterator>(it, (it == end()) ? (it) : (std::next(it)));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Pair<typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator, typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator> HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::equalRange(Key const& k) const {
                     ConstIterator it = find(k);
                     return Pair<ConstIterator, ConstIterator>(it, (it == end()) ? (it) : (std::next(it)));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::find(Key const& k) {
                     return Iterator(const_cast <const HashTable&>(*this).find(k).current);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::find(Key const& k) const {
                     std::size_t hashValue = hashKey(k);
                     std::size_t index = bucketFromHash(hashValue);
                     DistanceType distanceToNext = 0;
        
                     while (distanceToNext <= data[index].getDistanceToNext()) {
                         if ((!USE_STORED_HASH_ON_LOOKUP || data[index].bucketHashEquals(hashValue)) && compareKey(data[index].getData().first, k)) {
                             return ConstIterator(data.getData() + index);
                         }
            
                         index = next(index);
                         ++distanceToNext;
                     }
        
                     return end();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(Iterator pos) {
                     return erase(ConstIterator(pos.current));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(ConstIterator pos) {
                     pos.current->clear();
                     nbElements--;
        
                     std::size_t previousIndex = static_cast <std::size_t> (pos.current - data.getData());
                     std::size_t index = next(previousIndex);
        
                     while (data[index].getDistanceToNext() > 0) {
                         DistanceType newDistance = static_cast <DistanceType>(data[index].getDistanceToNext() - 1);
                         data[previousIndex].setData(newDistance, data[index].getTruncatedHash(), std::move(data[index].getData()));
                         data[index].clear();
            
                         previousIndex = index;
                         index = next(index);
                     }
        
                     if (pos.current->isEmpty()) {
                         ++pos;
                     }
                     return Iterator(pos.current);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(ConstIterator begin, ConstIterator end) {
                     if (begin == end) {
                         return Iterator(begin.current);
                     }
        
                     Iterator beginIt(begin.current);
                     Iterator endIt(end.current);
                     for (auto it = beginIt.current; it != endIt.current; ++it) {
                         if (!it->isEmpty()) {
                             it->clear();
                             nbElements--;
                         }
                     }
        
                     if (endIt == this->end()) {
                         return this->end();
                     }
        
                     std::size_t closerIndex = static_cast <std::size_t> (beginIt.current - data.getData());
                     std::size_t moveCloserIndex = static_cast <std::size_t> (endIt.current - data.getData());
        
                     std::size_t returnIndex = moveCloserIndex - std::min(moveCloserIndex - closerIndex, static_cast <std::size_t> (data[moveCloserIndex].getDistanceToNext()));
        
                     while (moveCloserIndex < getBucketCount() && data[moveCloserIndex].getDistanceToNext() > 0) {
                         closerIndex = moveCloserIndex - std::min(moveCloserIndex - closerIndex, static_cast <std::size_t> (data[moveCloserIndex].getDistanceToNext()));
                         DistanceType newDistance = static_cast <DistanceType> (data[moveCloserIndex].getDistanceToNext() - (moveCloserIndex - closerIndex));
            
                         data[closerIndex].setData(newDistance, data[moveCloserIndex].getTruncatedHash(), std::move(data[moveCloserIndex].getData()));
                         data[moveCloserIndex].clear();
            
                         ++closerIndex;
                         ++moveCloserIndex;
                     }
        
                     return Iterator(data.getData() + returnIndex);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(Key const& k) {
                     Iterator it = find(k);
                     if (it != end()) {
                         erase(it);
                         return 1;
                     } else {
                         return 0;
                     }
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Hash HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getHash() const {
                     return static_cast <Hash&> (*this);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline KeyEqual HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getKeyEqual() const {
                     return static_cast <KeyEqual&> (*this);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator =(HashTable const& table) {
                     if (this != &table) {
                         Hash::operator =(table);
                         KeyEqual::operator =(table);
            
                         data = table.data;
                         nbElements = table.nbElements;
                         mask = table.mask;
                         loadThresHold = table.loadThresHold;
                         maxLoadFactor = table.maxLoadFactor;
                         growAtNextInsert = table.growAtNextInsert;
                     }
                     return *this;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator =(HashTable&& table) {
                     if (this != &table) {
                         swap(table);
                         table.clear();
                     }
                     return *this;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline T& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator [](Key const& k) {
                     return (insert(ValueType(k, T())).first)->second;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline T& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator [](Key&& k) {
                     return (insert(ValueType(std::move(k), T())).first)->second;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline String HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::toString() const {
                     if (isEmpty()) {
                         return String("{}");
                     } else {
                         String res;
                         ConstIterator first = begin();
                         res << '{' << (*first);
                         res.reserve((res.getSize() + 2) * nbElements);
                         ++first;
                         while (first != end()) {
                             res << ',' << ' ' << (*first);
                             ++first;
                         }
                         res << '}';
                         return res;
                     }
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::hashKey(Key const& k) const {
                     return Hash::operator ()(k);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline bool HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::compareKey(Key const& k1, Key const& k2) const {
                     return KeyEqual::operator ()(k1, k2);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::next(std::size_t index) const {
                     return (index + 1) & mask;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::bucketFromHash(std::size_t hashValue) const {
                     return hashValue & mask;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::roundUpToPowerOfTwo(std::size_t count) const {
                     if (count == 0) {
                         return 1;
                     }
        
                     if ((count & (count - 1)) == 0) {
                         return count;
                     }
        
                     --count;
                     for (std::size_t i = 1; i < sizeof(std::size_t) * CHAR_BIT; i *= 2) {
                         count |= count >> i;
                     }
                     return count + 1;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insertValue(std::size_t index, DistanceType distanceToNext, TruncatedHash h, ValueType& pair) {
                     data[index].swapWithData(distanceToNext, h, pair);
                     index = next(index);
                     ++distanceToNext;
        
                     while (!data[index].isEmpty()) {
                         if (distanceToNext > data[index].getDistanceToNext()) {
                             if (distanceToNext >= REHASH_HIGH_PROBE && getLoadFactor() >= REHASH_MIN_LOAD_FACTOR) {
                                 growAtNextInsert = true;
                             }
                             data[index].swapWithData(distanceToNext, h, pair);
                         }
            
                         index = next(index);
                         ++distanceToNext;
                     }
        
                     data[index].setData(distanceToNext, h, std::move(pair));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insertOnRehash(std::size_t index, DistanceType distanceToNext, TruncatedHash h, ValueType&& pair) {
                     bool done = false;
                     while (!done) {
                         if (distanceToNext > data[index].getDistanceToNext()) {
                             if (data[index].isEmpty()) {
                                 data[index].setData(distanceToNext, h, std::move(pair));
                                 done = true;
                             } else {
                                 data[index].swapWithData(distanceToNext, h, pair);
                             }
                         }
            
                         ++distanceToNext;
                         index = next(index);
                     }
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline bool HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::rehashOnExtremeLoad() {
                     if (growAtNextInsert || getSize() >= loadThresHold) {
                         rehash(getNewSize());
                         growAtNextInsert = false;
                         return true;
                     }
                     return false;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline std::size_t HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getNewSize() const {
                     return data.getSize() * 2;
                 }
    
             }
         }
     }
