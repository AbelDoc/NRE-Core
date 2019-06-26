
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
             inline void HashTable<Key, T, Hash, KeyEqual>::BucketEntry::setAsLastBucket() {
                 last = true;
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
                 return current->data;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class K>
             inline K* HashTable<Key, T, Hash, KeyEqual>::ForwardIterator<K>::operator->() const {
                 return &current->data;
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
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(std::size_t bucketCount, Hash const& hash, KeyEqual const& equal) : Hash(hash), KeyEqual(equal), nbElements(0), maxLoadFactor() {
                 data.resize(bucketCount);
                 data.getBack().setAsLastBucket();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             template <class InputIterator>
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(InputIterator begin, InputIterator end, std::size_t bucketCount, Hash const& hash, KeyEqual const& equal) : HashTable(bucketCount, hash, equal) {
                 insert(begin, end);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(std::initializer_list<Pair<Key, T>> list, std::size_t bucketCount, Hash const& hash, KeyEqual const& equal) : HashTable(bucketCount, hash, equal) {
                 insert(list);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(HashTable const& table) : Hash(table), KeyEqual(table), data(table.data), nbElements(table.data), maxLoadFactor(table.maxLoadFactor) {
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>::HashTable(HashTable && table) : Hash(std::move(static_cast <Hash&> (table))), KeyEqual(std::move(static_cast <KeyEqual&> (table))), data(std::move(table.data)), nbElements(table.data), maxLoadFactor(table.maxLoadFactor) {
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
                 swap(maxLoadFactor, table.maxLoadFactor);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             inline HashTable<Key, T, Hash, KeyEqual>& HashTable<Key, T, Hash, KeyEqual>::operator=(HashTable const& table) {
                 if (this != &table) {
                     Hash::operator=(table);
                     KeyEqual::operator=(table);

                     data = table.data;
                     nbElements = table.nbElements;
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


         }
     }
