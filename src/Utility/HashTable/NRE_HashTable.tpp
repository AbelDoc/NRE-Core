
    /**
     * @file NRE_HashTable.tpp
     * @brief Implementation of Utility's API's Object : HashTable
     * @author Louis ABEL
     * @date 26/06/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Utility {

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::BucketEntry::BucketEntry() : distanceToNext(EMPTY_BUCKET_DISTANCE), last(false) {
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::BucketEntry::BucketEntry(BucketEntry const& bucket) : distanceToNext(EMPTY_BUCKET_DISTANCE), last(bucket.last) {
                 if (!bucket.isEmpty()) {
                     new (&data) Pair<Key, T>(bucket.data);
                     distanceToNext = bucket.distanceToNext;
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::BucketEntry::BucketEntry(BucketEntry && bucket) : distanceToNext(EMPTY_BUCKET_DISTANCE), last(bucket.last) {
                 if (!bucket.isEmpty()) {
                     new (&data) Pair<Key, T>(std::move(bucket.data));
                     distanceToNext = bucket.distanceToNext;
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::BucketEntry::~BucketEntry() {
                 clear();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline bool HashTable<Key, T, Hash, KeyEqual>::BucketEntry::isEmpty() const {
                 return distanceToNext == EMPTY_BUCKET_DISTANCE;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline bool HashTable<Key, T, Hash, KeyEqual>::BucketEntry::isLastBucket() const {
                 return last;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::ptrdiff_t HashTable<Key, T, Hash, KeyEqual>::BucketEntry::getDistanceToNext() const {
                 return distanceToNext;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline Key const& HashTable<Key, T, Hash, KeyEqual>::BucketEntry::getKey() const {
                 return data.first;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline Pair<Key, T>& HashTable<Key, T, Hash, KeyEqual>::BucketEntry::getData() {
                 return data;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline Pair<Key, T> const& HashTable<Key, T, Hash, KeyEqual>::BucketEntry::getData() const {
                 return data;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::BucketEntry::setAsLastBucket() {
                 last = true;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::BucketEntry::setData(std::ptrdiff_t distance, Pair<Key, T> && newData) {
                 new (&data) Pair<Key, T>(std::move(newData));
                 distanceToNext = distance;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::BucketEntry::clear() {
                 if (!isEmpty()) {
                     data.~Pair<Key, T>();
                     distanceToNext = EMPTY_BUCKET_DISTANCE;
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::BucketEntry::swap(BucketEntry& bucket) {
                using std::swap;
                swap(distanceToNext, bucket.distanceToNext);
                swap(last, bucket.last);
                swap(data, bucket.data);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::BucketEntry::swapWithData(std::ptrdiff_t& distance, Pair<Key, T> && newData) {
                using std::swap;
                swap(distanceToNext, distance);
                swap(data, newData);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::BucketEntry& HashTable<Key, T, Hash, KeyEqual>::BucketEntry::operator=(BucketEntry const& bucket) {
                if (this != &bucket) {
                    clear();

                    if (!bucket.isEmpty()) {
                        new (&data) Pair<Key, T>(bucket.data);
                    }

                    distanceToNext = bucket.distanceToNext;
                    last = bucket.last;
                }
                return *this;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::BucketEntry& HashTable<Key, T, Hash, KeyEqual>::BucketEntry::operator=(BucketEntry && bucket) {
                if (this != &bucket) {
                    clear();

                    if (!bucket.isEmpty()) {
                        new (&data) Pair<Key, T>(std::move(bucket.data));
                    }

                    distanceToNext = bucket.distanceToNext;
                    last = bucket.last;
                }
                return *this;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class K>
             inline HashTable<Key, T, Hash, KeyEqual>::ForwardIterator<K>::ForwardIterator(BucketEntry* bucket) : current(bucket) {
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class K>
             inline HashTable<Key, T, Hash, KeyEqual>::ForwardIterator<K>::ForwardIterator(const BucketEntry* bucket) : current(const_cast <BucketEntry*> (bucket)) {
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class K>
             inline K& HashTable<Key, T, Hash, KeyEqual>::ForwardIterator<K>::operator*() const {
                 return current->getData();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class K>
             inline K* HashTable<Key, T, Hash, KeyEqual>::ForwardIterator<K>::operator->() const {
                 return &current->getData();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class K>
             inline typename HashTable<Key, T, Hash, KeyEqual>::template ForwardIterator<K>& HashTable<Key, T, Hash, KeyEqual>::ForwardIterator<K>::operator++() {
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

             template <class Key, class T, class Hash, class KeyEqual>
             template <class K>
             inline typename HashTable<Key, T, Hash, KeyEqual>::template ForwardIterator<K> HashTable<Key, T, Hash, KeyEqual>::ForwardIterator<K>::operator++(int) {
                 ForwardIterator it(current);
                 ++(*this);
                 return it;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class K>
             inline bool HashTable<Key, T, Hash, KeyEqual>::ForwardIterator<K>::operator==(ForwardIterator const& it) const {
                 return current == it.current;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class K>
             inline bool HashTable<Key, T, Hash, KeyEqual>::ForwardIterator<K>::operator!=(ForwardIterator const& it) const {
                 return current != it.current;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(std::size_t bucketCount, Hash const& hasher, KeyEqual const& equal) : Hash(hasher), KeyEqual(equal), nbElements(0), maxLoadFactor(DEFAULT_MAX_LOAD_FACTOR) {
                 data.resize(roundUpToPowerOfTwo(bucketCount));
                 data.getLast().setAsLastBucket();
                 mask = data.getSize() - 1;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class InputIterator>
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(InputIterator begin, InputIterator end, std::size_t bucketCount, Hash const& hasher, KeyEqual const& equal) : HashTable(bucketCount, hasher, equal) {
                 insert(begin, end);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(std::initializer_list<Pair<Key, T>> list, std::size_t bucketCount, Hash const& hasher, KeyEqual const& equal) : HashTable(bucketCount, hasher, equal) {
                 insert(list);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(HashTable const& table) : Hash(table), KeyEqual(table), data(table.data), nbElements(table.nbElements), mask(table.mask), maxLoadFactor(table.maxLoadFactor) {
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(HashTable && table) : Hash(std::move(static_cast <Hash&> (table))), KeyEqual(std::move(static_cast <KeyEqual&> (table))), data(std::move(table.data)), nbElements(table.nbElements), mask(table.mask), maxLoadFactor(table.maxLoadFactor) {
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline T& HashTable<Key, T, Hash, KeyEqual>::get(Key const& k) {
                 auto it = find(k);
                 if (it == end()) {
                     throw std::out_of_range("Accessing non existing element in NRE::Utility::HashTable.");
                 }
                 return it->second;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline T const& HashTable<Key, T, Hash, KeyEqual>::get(Key const& k) const {
                 auto it = find(k);
                 if (it == end()) {
                     throw std::out_of_range("Accessing non existing element in NRE::Utility::HashTable.");
                 }
                 return it->second;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::size_t HashTable<Key, T, Hash, KeyEqual>::getBucketCount() const {
                 return data.getSize();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline constexpr std::size_t HashTable<Key, T, Hash, KeyEqual>::getMaxBucketCount() const {
                 return data.getMaxSize();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::size_t HashTable<Key, T, Hash, KeyEqual>::getSize() const {
                 return nbElements;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline float HashTable<Key, T, Hash, KeyEqual>::getMaxLoadFactor() const {
                 return maxLoadFactor;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline float HashTable<Key, T, Hash, KeyEqual>::getLoadFactor() const {
                 return static_cast <float> (getSize()) / static_cast <float> (getBucketCount());
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline constexpr std::size_t HashTable<Key, T, Hash, KeyEqual>::getMaxSize() const {
                 return std::numeric_limits<std::size_t>::max();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline bool HashTable<Key, T, Hash, KeyEqual>::isEmpty() const {
                 return nbElements == 0;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::size_t HashTable<Key, T, Hash, KeyEqual>::getCount(Key const& k) const {
                 if (find(k) != end()) {
                     return 1;
                 } else {
                     return 0;
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::setMaxLoadFactor(float factor) {
                 if (factor < 0.0f || factor > 1.0f) {
                     throw std::out_of_range("NRE::Utility::HashTable max load factor must be between 0.0 and 1.0.");
                 }
                 maxLoadFactor = factor;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::Iterator HashTable<Key, T, Hash, KeyEqual>::begin() {
                 std::size_t index = 0;
                 while (index < getBucketCount() && data[index].isEmpty()) {
                     ++index;
                 }

                 return Iterator(data.getData() + index);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Hash, KeyEqual>::begin() const {
                 std::size_t index = 0;
                 while (index < getBucketCount() && data[index].isEmpty()) {
                     ++index;
                 }

                 return ConstIterator(data.getData() + index);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Hash, KeyEqual>::cbegin() const {
                 return begin();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::Iterator HashTable<Key, T, Hash, KeyEqual>::end() {
                 return Iterator(data.getData() + data.getSize());
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Hash, KeyEqual>::end() const {
                 return ConstIterator(data.getData() + data.getSize());
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Hash, KeyEqual>::cend() const {
                 return end();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline Pair<typename HashTable<Key, T, Hash, KeyEqual>::Iterator, bool> HashTable<Key, T, Hash, KeyEqual>::insert(Pair<Key, T> const& value) {
                 return emplace(value);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class P>
             inline Pair<typename HashTable<Key, T, Hash, KeyEqual>::Iterator, bool> HashTable<Key, T, Hash, KeyEqual>::insert(P && value) {
                 return emplace(std::forward<P>(value));
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class InputIterator>
             inline void HashTable<Key, T, Hash, KeyEqual>::insert(InputIterator begin, InputIterator end) {
                 std::size_t count = std::distance(begin, end);
                 std::size_t free = getBucketCount() - getSize();
                 if (free < count) {
                     reserve(getSize() + count);
                 }
                 for ( ; begin != end; ++begin) {
                     insert(*begin);
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::insert(std::initializer_list<Pair<Key, T>> list) {
                 insert(list.begin(), list.end());
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::Iterator HashTable<Key, T, Hash, KeyEqual>::insertHint(ConstIterator hint, Pair<Key, T> const& value) {
                 return insert(value).first;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class P>
             inline typename HashTable<Key, T, Hash, KeyEqual>::Iterator HashTable<Key, T, Hash, KeyEqual>::insertHint(ConstIterator hint, P && value) {
                 return insert(std::forward<P>(value)).first;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class ... Args>
             inline Pair<typename HashTable<Key, T, Hash, KeyEqual>::Iterator, bool> HashTable<Key, T, Hash, KeyEqual>::emplace(Args && ... args) {
                 Pair<Key, T> toInsert(std::forward<Args>(args)...);
                 Key& key = toInsert.first;

                 std::size_t hashValue = hashKey(key);
                 std::size_t index = bucketFromHash(hashValue);
                 std::ptrdiff_t distanceToNext = 0;

                 while (distanceToNext <= data[index].getDistanceToNext()) {
                     if (compareKey(data[index].getKey(), key)) {
                         return Pair<Iterator, bool>(data.getData() + index, false);
                     }

                     index = next(index);
                     ++distanceToNext;
                 }

                 if (data[index].isEmpty()) {
                     data[index].setData(distanceToNext, std::move(toInsert));
                 } else {
                     insertValue(index, distanceToNext, std::move(toInsert));
                 }
                 ++nbElements;

                 return Pair<Iterator, bool>(Iterator(data.getData() + index), true);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class ... Args>
             inline typename HashTable<Key, T, Hash, KeyEqual>::Iterator HashTable<Key, T, Hash, KeyEqual>::emplaceHint(ConstIterator hint, Args && ... args) {
                 return emplace(std::forward<Args>(args)...);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::clear() {
                 for (BucketEntry& bucket : data) {
                     bucket.clear();
                 }

                 nbElements = 0;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::swap(HashTable& table) {
                 using std::swap;

                 swap(static_cast <Hash&> (*this), static_cast <Hash&> (table));
                 swap(static_cast <KeyEqual&> (*this), static_cast <KeyEqual&> (table));
                 swap(data, table.data);
                 swap(nbElements, table.nbElements);
                 swap(mask, table.mask);
                 swap(maxLoadFactor, table.maxLoadFactor);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::reserve(std::size_t count) {
                 rehash(static_cast <std::size_t> (std::ceil(static_cast <float> (count) / getMaxLoadFactor())));
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::rehash(std::size_t count) {
                 count = std::max(count, static_cast <std::size_t> (std::ceil(static_cast <float> (getSize()) / getMaxLoadFactor())));
                 HashTable newTable(count, static_cast <Hash&> (*this), static_cast <KeyEqual&> (*this));

                 for (auto& bucket : data) {
                     if (!bucket.isEmpty()) {
                         std::size_t hashValue = newTable.hashKey(bucket.getKey());
                         newTable.insertOnRehash(newTable.bucketFromHash(hashValue), 0, std::move(bucket.getData()));
                     }
                 }

                 newTable.nbElements = nbElements;
                 newTable.swap(*this);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline Pair<typename HashTable<Key, T, Hash, KeyEqual>::Iterator, typename HashTable<Key, T, Hash, KeyEqual>::Iterator> HashTable<Key, T, Hash, KeyEqual>::equalRange(Key const& k) {
                 Iterator it = find(k);
                 return Pair<Key, T>(it, (it == end()) ? (it) : (std::next(it)));
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline Pair<typename HashTable<Key, T, Hash, KeyEqual>::ConstIterator, typename HashTable<Key, T, Hash, KeyEqual>::ConstIterator> HashTable<Key, T, Hash, KeyEqual>::equalRange(Key const& k) const {
                 ConstIterator it = find(k);
                 return Pair<Key, T>(it, (it == end()) ? (it) : (std::next(it)));
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::Iterator HashTable<Key, T, Hash, KeyEqual>::find(Key const& k) {
                 std::size_t hashValue = hashKey(k);
                 std::size_t index = bucketFromHash(hashValue);
                 std::ptrdiff_t distanceToNext = 0;

                 while (distanceToNext <= data[index].getDistanceToNext()) {
                     if (compareKey(data[index].getKey(), k)) {
                         return Iterator(data.getData() + index);
                     }

                     index = next(index);
                     ++distanceToNext;
                 }

                 return end();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::ConstIterator HashTable<Key, T, Hash, KeyEqual>::find(Key const& k) const {
                 return ConstIterator(find(k).current);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::Iterator HashTable<Key, T, Hash, KeyEqual>::erase(ConstIterator pos) {
                pos.current->clear();
                nbElements--;

                std::size_t previousIndex = static_cast <std::size_t> (pos.current - data.getData());
                std::size_t index = next(previousIndex);

                while (data[index].getDistanceToNext() > 0) {
                    std::ptrdiff_t newDistance = static_cast <std::ptrdiff_t>(data[index].getDistanceToNext() - 1);
                    data[previousIndex].setData(newDistance, std::move(data[index].getData()));
                    data[index].clear();

                    previousIndex = index;
                    index = next(index);
                }

                if (pos.current->isEmpty()) {
                    ++pos;
                }
                return pos;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline typename HashTable<Key, T, Hash, KeyEqual>::Iterator HashTable<Key, T, Hash, KeyEqual>::erase(ConstIterator begin, ConstIterator end) {
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

                 if (endIt == end()) {
                     return end();
                 }

                 std::size_t closerIndex = static_cast <std::size_t> (beginIt.current - data.getData());
                 std::size_t moveCloserIndex = static_cast <std::size_t> (endIt.current - data.getData());

                 std::size_t returnIndex = moveCloserIndex - std::min(moveCloserIndex - closerIndex, static_cast <std::size_t> (data[moveCloserIndex].getDistanceToNext()));

                 while (moveCloserIndex < getBucketCount() && data[moveCloserIndex].getDistanceToNext() > 0) {
                     closerIndex = moveCloserIndex  - std::min(moveCloserIndex - closerIndex, static_cast <std::size_t> (data[moveCloserIndex].getDistanceToNext()));
                     std::ptrdiff_t newDistance = static_cast <std::ptrdiff_t> (data[moveCloserIndex].getDistanceToNext() - (moveCloserIndex - closerIndex));

                     data[closerIndex].setData(newDistance, std::move(data[moveCloserIndex].getData()));
                     data[moveCloserIndex].clear();

                     ++closerIndex;
                     ++moveCloserIndex;
                 }

                 return Iterator(data.getData() + returnIndex);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::size_t HashTable<Key, T, Hash, KeyEqual>::erase(Key const& k) {
                 ConstIterator it = find(k);
                 if (it != cend()) {
                     erase(it);
                     return 1;
                 } else {
                     return 0;
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>& HashTable<Key, T, Hash, KeyEqual>::operator=(HashTable const& table) {
                 if (this != &table) {
                     Hash::operator=(table);
                     KeyEqual::operator=(table);

                     data = table.data;
                     nbElements = table.nbElements;
                     mask = table.mask;
                     maxLoadFactor = table.maxLoadFactor;
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>& HashTable<Key, T, Hash, KeyEqual>::operator=(HashTable && table) {
                 if (this != &table) {
                     swap(table);
                     table.clear();
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline T& HashTable<Key, T, Hash, KeyEqual>::operator[](Key const& k) {
                 return (insert(Pair<Key, T>(k, T())).first)->second;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline T& HashTable<Key, T, Hash, KeyEqual>::operator[](Key && k) {
                 return (insert(Pair<Key, T>(std::move(k), T())).first)->second;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline String HashTable<Key, T, Hash, KeyEqual>::toString() const {
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

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::size_t HashTable<Key, T, Hash, KeyEqual>::hashKey(Key const& k) const {
                 return Hash::operator()(k);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline bool HashTable<Key, T, Hash, KeyEqual>::compareKey(Key const& k1, Key const& k2) const {
                 return KeyEqual::operator()(k1, k2);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::size_t HashTable<Key, T, Hash, KeyEqual>::next(std::size_t index) const {
                 return (index + 1) & mask;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::size_t HashTable<Key, T, Hash, KeyEqual>::bucketFromHash(std::size_t hashValue) const {
                 return hashValue & mask;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::size_t HashTable<Key, T, Hash, KeyEqual>::roundUpToPowerOfTwo(std::size_t count) const {
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

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::insertValue(std::size_t index, std::ptrdiff_t distanceToNext, Pair<Key, T> && pair) {
                 data[index].swapWithData(distanceToNext, std::move(pair));
                 index = next(index);
                 ++distanceToNext;

                 while (!data[index].isEmpty()) {
                     if (distanceToNext > data[index].getDistanceToNext()) {
                         if (distanceToNext >= REHASH_HIGH_PROBE && getLoadFactor() >= REHASH_MIN_LOAD_FACTOR) {
                             rehash(getNewSize());
                         }
                         data[index].swapWithData(distanceToNext, std::move(pair));
                     }

                     index = next(index);
                     ++distanceToNext;
                 }

                 data[index].setData(distanceToNext, std::move(pair));
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline void HashTable<Key, T, Hash, KeyEqual>::insertOnRehash(std::size_t index, std::ptrdiff_t distanceToNext, Pair<Key, T> && pair) {
                 bool done = false;
                 while (!done) {
                     if (distanceToNext > data[index].getDistanceToNext()) {
                         if (data[index].isEmpty()) {
                             data[index].setData(distanceToNext, std::move(pair));
                             done = true;
                         } else {
                            data[index].swapWithData(distanceToNext, std::move(pair));
                         }
                     }

                     ++distanceToNext;
                     index = next(index);
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline std::size_t HashTable<Key, T, Hash, KeyEqual>::getNewSize() const {
                return data.getSize() * 2;
             }

         }
     }
