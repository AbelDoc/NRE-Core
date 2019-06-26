
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
             HashTable<Key, T, Hash, KeyEqual>::BucketEntry::BucketEntry() : distanceToNext(EMPTY_BUCKET_DISTANCE) {
             }

             template <class Key, class T, class Hash, class KeyEqual>
             HashTable<Key, T, Hash, KeyEqual>::BucketEntry::BucketEntry(BucketEntry const& bucket) : distanceToNext(EMPTY_BUCKET_DISTANCE) {
                 if (!bucket.isEmpty()) {
                     new (&data) Pair<Key, T>(bucket.data);
                     distanceToNext = bucket.distanceToNext;
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             HashTable<Key, T, Hash, KeyEqual>::BucketEntry::BucketEntry(BucketEntry && bucket) : distanceToNext(EMPTY_BUCKET_DISTANCE) {
                 if (!bucket.isEmpty()) {
                     new (&data) Pair<Key, T>(std::move(bucket.data));
                     distanceToNext = bucket.distanceToNext;
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             HashTable<Key, T, Hash, KeyEqual>::BucketEntry::~BucketEntry() {
                 clear();
             }

             template <class Key, class T, class Hash, class KeyEqual>
             bool HashTable<Key, T, Hash, KeyEqual>::BucketEntry::isEmpty() const {
                 return distanceToNext == EMPTY_BUCKET_DISTANCE;
             }

             template <class Key, class T, class Hash, class KeyEqual>
             void HashTable<Key, T, Hash, KeyEqual>::BucketEntry::clear() const {
                 if (!isEmpty()) {
                     data.~Pair<Key, T>();
                     distanceToNext = EMPTY_BUCKET_DISTANCE;
                 }
             }

             template <class Key, class T, class Hash, class KeyEqual>
             void HashTable<Key, T, Hash, KeyEqual>::BucketEntry::swap(BucketEntry& bucket) const {
                using std::swap;
                swap(data, bucket.data);
                swap(distanceToNext, bucket.distanceToNext);
             }

             template <class Key, class T, class Hash, class KeyEqual>
             HashTable<Key, T, Hash, KeyEqual>::BucketEntry& HashTable<Key, T, Hash, KeyEqual>::BucketEntry::operator=(BucketEntry const& bucket) {
                if (this != &bucket) {
                    clear();

                    if (!bucket.isEmpty()) {
                        new (&data) Pair<Key, T>(bucket.data);
                    }

                    distanceToNext = bucket.distanceToNext;
                }
             }


         }
     }
