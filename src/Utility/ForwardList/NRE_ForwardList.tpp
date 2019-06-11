
    /**
     * @file NRE_ForwardList.tpp
     * @brief Implementation of Utility's API's Container : ForwardList
     * @author Louis ABEL
     * @date 11/06/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Utility {

             template <class T>
             inline ForwardList<T>::Node::Node(T const& value, T* node) : data(value), next(node) {
             }

             template <class T>
             inline ForwardList<T>::Node::Node(T && value, T* node) : data(value), next(node) {
             }

             template <class T>
             template <class K>
             inline ForwardList<T>::ForwardIterator<K>::ForwardIterator(Node* node, bool before) : current(node), beforeBegin(before) {
             }

             template <class T>
             template <class K>
             inline K& ForwardList<T>::ForwardIterator<K>::operator*() const {
                 return current->data;
             }

             template <class T>
             template <class K>
             inline K& ForwardList<T>::ForwardIterator<K>::operator->() const {
                 return current->data;
             }

             template <class T>
             template <class K>
             inline typename ForwardList<T>::ForwardIterator<K>& ForwardList<T>::ForwardIterator<K>::operator++() {
                 if (beforeBegin) {
                     beforeBegin = false;
                 } else {
                     current = current->next;
                 }
                 return *this;
             }

             template <class T>
             template <class K>
             inline typename ForwardList<T>::ForwardIterator<K> ForwardList<T>::ForwardIterator<K>::operator++(int) {
                 ForwardIterator it(current);
                 current = current->next;
                 return it;
             }

             template <class T>
             template <class K>
             inline bool ForwardList<T>::ForwardIterator<K>::operator==(ForwardIterator const& it) const {
                 return current == it.current;
             }

             template <class T>
             template <class K>
             inline bool ForwardList<T>::ForwardIterator<K>::operator==(ForwardIterator const& it) const {
                 return current != it.current;
             }

             template <class T>
             inline ForwardList<T>::ForwardList() : front(nullptr) {
             }

             template <class T>
             inline ForwardList<T>::ForwardList(std::size_t count, T const& value) {
                 assign(count, value);
             }

             template <class T>
             template <class InputIterator>
             inline ForwardList<T>::ForwardList(InputIterator begin, InputIterator end) {
                 assign(begin, end);
             }

             template <class T>
             inline ForwardList<T>::ForwardList(std::initializer_list<T> list) {
                 assign(list.begin(), list.end());
             }

             template <class T>
             inline ForwardList<T>::ForwardList(ForwardList const& list) : ForwardList(list.begin(), list.end()) {
             }

             template <class T>
             inline ForwardList<T>::ForwardList(ForwardList && list) : front(list.front) {
                 list.front = nullptr;
             }

             template <class T>
             inline ForwardList<T>::~ForwardList() {
                 clear();
             }

             template <class T>
             inline T& ForwardList<T>::getFront() {
                 return front;
             }

             template <class T>
             inline T const& ForwardList<T>::getFront() const {
                 return front;
             }

             template <class T>
             inline constexpr std::size_t ForwardList<T>::getMaxSize() const {
                 return std::numeric_limits<std::size_t>::max();
             }

             template <class T>
             inline bool ForwardList<T>::isEmpty() const {
                 return front == nullptr;
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::beforeBegin() {
                 return Iterator(front, true);
             }

             template <class T>
             inline typename ForwardList<T>::ConstIterator ForwardList<T>::beforeBegin() const {
                 return ConstIterator(front, true);
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::begin() {
                 return Iterator(front);
             }

             template <class T>
             inline typename ForwardList<T>::ConstIterator ForwardList<T>::begin() const {
                 return ConstIterator(front);
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::end() {
                 return Iterator(nullptr);
             }

             template <class T>
             inline typename ForwardList<T>::ConstIterator ForwardList<T>::end() const {
                 return ConstIterator(nullptr);
             }

             template <class T>
             inline void ForwardList<T>::assign(std::size_t count, T const& value) {
                 clear();
                 for (std::size_t index = 0; index < count; index++) {
                     pushFront(value);
                 }
             }

             template <class T>
             template <class InputIterator>
             inline void ForwardList<T>::assign(InputIterator begin, InputIterator end) {
                 clear();
                 for ( ; begin != end; begin++) {
                     pushFront(*begin);
                 }
             }

             template <class T>
             inline void ForwardList<T>::clear() {
                 while (!isEmpty()) {
                     Node* tmp = front->next;
                     delete front;
                     front = tmp;
                 }
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::insertAfter(ConstIterator pos, T const& value) {
                 return emplaceAfter(pos, value);
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::insertAfter(ConstIterator pos, T && value) {
                 return emplaceAfter(pos, std::move(value));
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::insertAfter(ConstIterator pos, std::size_t count, T const& value) {
                 Iterator it;
                 for (std::size_t index = 0; index < count; index++) {
                     it = insertAfter(pos, value);
                 }
                 return it;
             }

             template <class T>
             template <class InputIterator>
             inline typename ForwardList<T>::Iterator ForwardList<T>::insertAfter(ConstIterator pos, InputIterator begin, InputIterator end) {
                 Iterator it = pos
                 for ( ; begin != end; end++) {
                     it = insertAfter(it, *begin);
                 }
                 return it;
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::insertAfter(ConstIterator pos, std::initializer_list<T> list) {
                 return insertAfter(pos, list.begin(), list.end());
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::emplaceAfter(ConstIterator pos, Args  && ... args) {
                 if (pos.beforeBegin) {
                    emplaceFront(std::forward<Args>(args)...);
                    return begin();
                } else {
                    Node* inserted = new Node(T(std::forward<Args>(args)...), pos.current->next);
                    pos.current->next = inserted;
                    return Iterator(inserted);
                }
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::eraseAfter(ConstIterator pos) {
                 if (pos.beforeBegin) {
                     popFront();
                     return begin();
                 } else {
                     if (pos.current && pos.current->next) {
                         Node* tmp = pos.current->next->next;
                         delete pos.current->next;
                         pos.current->next = tmp;
                         return Iterator(tmp);
                     } else {
                         return end();
                     }
                 }
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::eraseAfter(ConstIterator begin, ConstIterator end) {
                 if (begin.beforeBegin) {
                     for (std::size_t index = 0; index < std::distance(++begin, end); index++) {
                         popFront();
                     }
                 } else {
                     while (begin.current && (++begin) != end) {
                         Node* tmp = begin.current->next;
                         delete begin.current;
                         begin.current = tmp;
                     }
                 }
                 return Iterator(end.current, end.beforeBegin);
             }

             template <class T>
             inline void ForwardList<T>::pushFront(T const& value) {
                 emplaceFront(value);
             }

             template <class T>
             inline void ForwardList<T>::pushFront(T && value) {
                 emplaceFront(std::move(value));
             }

             template <class T>
             template <class ... Args>
             inline void ForwardList<T>::emplaceFront(Args && ... args) {
                 front = new Node(T(std::forward<Args>(args)...), front);
             }

             template <class T>
             inline void ForwardList<T>::popFront() {
                 if (!isEmpty()) {
                     Node* tmp = front->next;
                     delete front;
                     front = tmp;
                 }
             }

             template <class T>
             inline void ForwardList<T>::swap(ForwardList& list) {
                 using namespace std;
                 swap(front, list.front);
             }

             template <class T>
             inline ForwardList<T>& ForwardList<T>::operator=(ForwardList const& list) {
                 ForwardList copy(list);
                 swap(copy);
                 return *this;
             }

             template <class T>
             inline ForwardList<T>& ForwardList<T>::operator(ForwardList && list) {
                 ForwardList move(std::move(list));
                 swap(move);
                 return *this;
             }

        }
    }
