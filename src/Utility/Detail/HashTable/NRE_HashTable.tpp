
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
                namespace HashTableInner {
    
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
                     inline typename BucketEntry<ValueType, StoreHash>::DistanceType BucketEntry<ValueType, StoreHash>::getDistanceToNext() const {
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
        
                     template <class T, class Category, class Bucket>
                     inline ForwardIterator<T, Category, Bucket>::ForwardIterator(Bucket* bucket) : current(bucket) {
                     }
        
                     template <class T, class Category, class Bucket>
                     inline ForwardIterator<T, Category, Bucket>::ForwardIterator(const Bucket* bucket) : current(const_cast <Bucket*> (bucket)) {
                     }
    
                     template <class T, class Category, class Bucket>
                     inline Bucket* ForwardIterator<T, Category, Bucket>::getCurrent() {
                         return current;
                     }
        
                     template <class T, class Category, class Bucket>
                     inline typename ForwardIterator<T, Category, Bucket>::Reference ForwardIterator<T, Category, Bucket>::dereference() const {
                         return current->getData();
                     }
        
                     template <class T, class Category, class Bucket>
                     inline void ForwardIterator<T, Category, Bucket>::increment() {
                         while (true) {
                             if (current->isLastBucket()) {
                                 ++current;
                                 break;
                             }
            
                             ++current;
                             if (!current->isEmpty()) {
                                 break;
                             }
                         }
                     }
        
                     template <class T, class Category, class Bucket>
                     inline bool ForwardIterator<T, Category, Bucket>::equal(ForwardIterator const& it) const {
                         return current == it.current;
                     }
        
                     template <class T, class Category, class Bucket>
                     inline LocalForwardIterator<T, Category, Bucket>::LocalForwardIterator(Bucket* bucket) : current(bucket) {
                     }
        
                     template <class T, class Category, class Bucket>
                     inline LocalForwardIterator<T, Category, Bucket>::LocalForwardIterator(const Bucket* bucket) : current(const_cast <Bucket*> (bucket)) {
                     }
        
                     template <class T, class Category, class Bucket>
                     inline typename LocalForwardIterator<T, Category, Bucket>::Reference LocalForwardIterator<T, Category, Bucket>::dereference() const {
                         return current->getData();
                     }
        
                     template <class T, class Category, class Bucket>
                     inline void LocalForwardIterator<T, Category, Bucket>::increment() {
                         current = nullptr;
                     }
        
                     template <class T, class Category, class Bucket>
                     inline bool LocalForwardIterator<T, Category, Bucket>::equal(LocalForwardIterator const& it) const {
                         return current == it.current;
                     }
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(SizeType bucketCount, Hash const& hasher, KeyEqual const& equal, Allocator const& alloc) : Hash(hasher), KeyEqual(equal), data(alloc), nbElements(0), maxLoadFactor(DEFAULT_MAX_LOAD_FACTOR), growAtNextInsert(false) {
                     data.resize(roundUpToPowerOfTwo(bucketCount));
                     data.getLast().setAsLastBucket();
                     mask = data.getSize() - 1;
                     setMaxLoadFactor(maxLoadFactor);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 template <class InputIterator>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(InputIterator begin, InputIterator end, SizeType bucketCount, Hash const& hasher, KeyEqual const& equal, Allocator const& alloc) : HashTable(bucketCount, hasher, equal, alloc) {
                     insert(begin, end);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(std::initializer_list<ValueType> list, SizeType bucketCount, Hash const& hasher, KeyEqual const& equal, Allocator const& alloc) : HashTable(bucketCount, hasher, equal, alloc) {
                     insert(list);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(HashTable const& table) : HashTable(table, table.getAllocator()) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(HashTable const& table, Allocator const& alloc) : Hash(table), KeyEqual(table), data(table.data, alloc), nbElements(table.nbElements), mask(table.mask), loadThresHold(table.loadThresHold), maxLoadFactor(table.maxLoadFactor), growAtNextInsert(table.growAtNextInsert) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(HashTable && table) : HashTable(std::move(table), table.getAllocator()) {
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::HashTable(HashTable && table, Allocator const& alloc) : Hash(std::move(static_cast <Hash&> (table))), KeyEqual(std::move(static_cast <KeyEqual&> (table))), data(std::move(table.data), alloc), nbElements(table.nbElements), mask(table.mask), loadThresHold(table.loadThresHold), maxLoadFactor(table.maxLoadFactor), growAtNextInsert(table.growAtNextInsert) {
                     table.data.clear();
                     table.nbElements = 0;
                     table.loadThresHold = 0;
                     table.growAtNextInsert = false;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::MappedType& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::get(KeyType const& k) {
                     auto it = find(k);
                     if (it == end()) {
                         throw std::out_of_range("Accessing non existing element in NRE::Utility::HashTable.");
                     }
                     return it->second;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::MappedType const& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::get(KeyType const& k) const {
                     auto it = find(k);
                     if (it == end()) {
                         throw std::out_of_range("Accessing non existing element in NRE::Utility::HashTable.");
                     }
                     return it->second;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getBucketCount() const {
                     return data.getSize();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 constexpr typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getMaxBucketCount() const {
                     return data.getMaxSize();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getSize() const {
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
                     return Allocator(data.getAllocator());
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 constexpr typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getMaxSize() const {
                     return std::numeric_limits<SizeType>::max();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline bool HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::isEmpty() const {
                     return nbElements == 0;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getCount(KeyType const& k) const {
                     if (find(k) != end()) {
                         return 1;
                     } else {
                         return 0;
                     }
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getBucket(KeyType const& k) const {
                     return bucketFromHash(hashKey(k));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::setMaxLoadFactor(float factor) {
                     if (factor < 0.0f || factor > 1.0f) {
                         throw std::out_of_range("NRE::Utility::HashTable max load factor must be between 0.0 and 1.0.");
                     }
                     maxLoadFactor = factor;
                     loadThresHold = static_cast <SizeType> (static_cast <float> (getBucketCount()) * maxLoadFactor);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin() {
                     SizeType index = 0;
                     while (index < getBucketCount() && data[index].isEmpty()) {
                         ++index;
                     }
        
                     return Iterator(data.getData() + index);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin() const {
                     SizeType index = 0;
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
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin(SizeType index) {
                     return LocalIterator(&data[index]);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::begin(SizeType index) const {
                     return ConstLocalIterator(&data[index]);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cbegin(SizeType index) const {
                     return begin();
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::LocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end(SizeType index) {
                     return LocalIterator(nullptr);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::end(SizeType index) const {
                     return ConstLocalIterator(nullptr);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstLocalIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::cend(SizeType index) const {
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
                     SizeType count = std::distance(begin, end);
                     SizeType free = loadThresHold - getSize();
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
                     KeyType const& key = toInsert.first;
        
                     SizeType hashValue = hashKey(key);
                     SizeType index = bucketFromHash(hashValue);
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
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::reserve(SizeType count) {
                     rehash(static_cast <SizeType> (std::ceil(static_cast <float> (count) / getMaxLoadFactor())));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::rehash(SizeType count) {
                     count = std::max(count, static_cast <SizeType> (std::ceil(static_cast <float> (getSize()) / getMaxLoadFactor())));
                     HashTable newTable(count, static_cast <Hash&> (*this), static_cast <KeyEqual&> (*this));
        
                     bool useStoredHash = USE_STORED_HASH_ON_REHASH(newTable.getBucketCount());
        
                     for (auto& bucket : data) {
                         if (!bucket.isEmpty()) {
                             SizeType hashValue = (useStoredHash) ? (static_cast <SizeType> (bucket.getTruncatedHash())) : (newTable.hashKey(bucket.getData().first));
                             newTable.insertOnRehash(newTable.bucketFromHash(hashValue), 0, TruncatedHash(hashValue), std::move(bucket.getData()));
                         }
                     }
        
                     newTable.nbElements = nbElements;
                     newTable.swap(*this);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Pair<typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator, typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator> HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::equalRange(KeyType const& k) {
                     Iterator it = find(k);
                     return Pair<Iterator, Iterator>(it, (it == end()) ? (it) : (std::next(it)));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline Pair<typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator, typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator> HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::equalRange(KeyType const& k) const {
                     ConstIterator it = find(k);
                     return Pair<ConstIterator, ConstIterator>(it, (it == end()) ? (it) : (std::next(it)));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::find(KeyType const& k) {
                     return Iterator(const_cast <const HashTable&>(*this).find(k).getCurrent());
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::find(KeyType const& k) const {
                     SizeType hashValue = hashKey(k);
                     SizeType index = bucketFromHash(hashValue);
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
                     return erase(ConstIterator(pos.getCurrent()));
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(ConstIterator pos) {
                     pos.getCurrent()->clear();
                     nbElements--;
        
                     SizeType previousIndex = static_cast <SizeType> (pos.getCurrent() - data.getData());
                     SizeType index = next(previousIndex);
        
                     while (data[index].getDistanceToNext() > 0) {
                         DistanceType newDistance = static_cast <DistanceType>(data[index].getDistanceToNext() - 1);
                         data[previousIndex].setData(newDistance, data[index].getTruncatedHash(), std::move(data[index].getData()));
                         data[index].clear();
            
                         previousIndex = index;
                         index = next(index);
                     }
        
                     if (pos.getCurrent()->isEmpty()) {
                         ++pos;
                     }
                     return Iterator(pos.getCurrent());
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::Iterator HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(ConstIterator begin, ConstIterator end) {
                     if (begin == end) {
                         return Iterator(begin.getCurrent());
                     }
        
                     Iterator beginIt(begin.getCurrent());
                     Iterator endIt(end.getCurrent());
                     for (auto it = beginIt.getCurrent(); it != endIt.getCurrent(); ++it) {
                         if (!it->isEmpty()) {
                             it->clear();
                             nbElements--;
                         }
                     }
        
                     if (endIt == this->end()) {
                         return this->end();
                     }
        
                     SizeType closerIndex = static_cast <SizeType> (beginIt.getCurrent() - data.getData());
                     SizeType moveCloserIndex = static_cast <SizeType> (endIt.getCurrent() - data.getData());
        
                     SizeType returnIndex = moveCloserIndex - std::min(moveCloserIndex - closerIndex, static_cast <SizeType> (data[moveCloserIndex].getDistanceToNext()));
        
                     while (moveCloserIndex < getBucketCount() && data[moveCloserIndex].getDistanceToNext() > 0) {
                         closerIndex = moveCloserIndex - std::min(moveCloserIndex - closerIndex, static_cast <SizeType> (data[moveCloserIndex].getDistanceToNext()));
                         DistanceType newDistance = static_cast <DistanceType> (data[moveCloserIndex].getDistanceToNext() - (moveCloserIndex - closerIndex));
            
                         data[closerIndex].setData(newDistance, data[moveCloserIndex].getTruncatedHash(), std::move(data[moveCloserIndex].getData()));
                         data[moveCloserIndex].clear();
            
                         ++closerIndex;
                         ++moveCloserIndex;
                     }
        
                     return Iterator(data.getData() + returnIndex);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::erase(KeyType const& k) {
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
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::MappedType& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator [](KeyType const& k) {
                     return (insert(ValueType(k, T())).first)->second;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::MappedType& HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::operator [](KeyType && k) {
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
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::hashKey(KeyType const& k) const {
                     return Hash::operator ()(k);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline bool HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::compareKey(KeyType const& k1, KeyType const& k2) const {
                     return KeyEqual::operator ()(k1, k2);
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::next(SizeType index) const {
                     return (index + 1) & mask;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::bucketFromHash(SizeType hashValue) const {
                     return hashValue & mask;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::roundUpToPowerOfTwo(SizeType count) const {
                     if (count == 0) {
                         return 1;
                     }
        
                     if ((count & (count - 1)) == 0) {
                         return count;
                     }
        
                     --count;
                     for (SizeType i = 1; i < sizeof(SizeType) * CHAR_BIT; i *= 2) {
                         count |= count >> i;
                     }
                     return count + 1;
                 }
    
                 template <class Key, class T, class Allocator, bool StoreHash, class Hash, class KeyEqual>
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insertValue(SizeType index, DistanceType distanceToNext, TruncatedHash h, ValueType& pair) {
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
                 inline void HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::insertOnRehash(SizeType index, DistanceType distanceToNext, TruncatedHash h, ValueType&& pair) {
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
                 inline typename HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::SizeType HashTable<Key, T, Allocator, StoreHash, Hash, KeyEqual>::getNewSize() const {
                     return data.getSize() * 2;
                 }
    
             }
         }
     }
