
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
             inline ForwardList<T>::ForwardIterator<K>::ForwardIterator(K* node, bool before) : current(node), beforeBegin(before) {
             }

             template <class T>
             template <class K>
             inline T& ForwardList<T>::ForwardIterator<K>::operator*() const {
                 return current->data;
             }

             template <class T>
             template <class K>
             inline T& ForwardList<T>::ForwardIterator<K>::operator->() const {
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
                 for (auto it = list.begin(); it != list.end(); it++) {
                     pushFront(*it);
                 }
             }

             template <class T>
             inline ForwardList<T>::ForwardList(ForwardList const& list) {
                 clear();
             }

             template <class T>
             inline ForwardList<T>::ForwardList(ForwardList && list) : front(list.front) {
                 list.front = nullptr;
             }

             template <class T>
             inline ForwardList<T>::~ForwardList() {
                 Node* tmp, current = front;
                 while (current != nullptr) {
                     tmp = current->next;
                     delete current;
                     current = tmp;
                 }
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
                 Node* current = list.front;
                 while (current != nullptr) {
                     pushFront(current->data);
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
                 Iterator res = pos;
                 for (auto it = list.begin(); it != list.end(); it++){
                     res = insertAfter(res, *it);
                 }
                 return res;
             }

             template <class T>
             inline ForwardList<T>& ForwardList<T>::operator=(ForwardList const& list) {
                 Node* current = list.front;
                 while (current != nullptr) {
                     pushFront(current->data);
                 }
                 return *this;
             }

             template <class T>
             inline ForwardList<T>& ForwardList<T>::operator(ForwardList && list) {
                 front = list.front;
                 list.front = nullptr;
                 return *this;
             }

        }
    }
