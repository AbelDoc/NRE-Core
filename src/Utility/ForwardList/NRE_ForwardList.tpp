
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
             inline ForwardList<T>::NodeBase::NodeBase(NodeBase* node) : next(node) {
             }

             template <class T>
             inline ForwardList<T>::Node::Node(T const& value, NodeBase* node) : NodeBase(node), data(value) {
             }

             template <class T>
             inline ForwardList<T>::Node::Node(T && value, NodeBase* node) : NodeBase(node), data(value) {
             }

             template <class T>
             template <class K>
             inline ForwardList<T>::ForwardIterator<K>::ForwardIterator(NodeBase* node) : current(node) {
             }

             template <class T>
             template <class K>
             inline ForwardList<T>::ForwardIterator<K>::ForwardIterator(const NodeBase* node) : current(const_cast <NodeBase*> (node)) {
             }

             template <class T>
             template <class K>
             inline K& ForwardList<T>::ForwardIterator<K>::operator*() const {
                 return static_cast <Node*>(current)->data;
             }

             template <class T>
             template <class K>
             inline K& ForwardList<T>::ForwardIterator<K>::operator->() const {
                 return static_cast <Node*>(current)->data;
             }

             template <class T>
             template <class K>
             inline typename ForwardList<T>::template ForwardIterator<K>& ForwardList<T>::ForwardIterator<K>::operator++() {
                 current = current->next;
                 return *this;
             }

             template <class T>
             template <class K>
             inline typename ForwardList<T>::template ForwardIterator<K> ForwardList<T>::ForwardIterator<K>::operator++(int) {
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
             inline bool ForwardList<T>::ForwardIterator<K>::operator!=(ForwardIterator const& it) const {
                 return current != it.current;
             }

             template <class T>
             inline ForwardList<T>::ForwardList() : front(nullptr), length(0) {
             }

             template <class T>
             inline ForwardList<T>::ForwardList(std::size_t count, T const& value) : front(nullptr), length(0) {
                 assign(count, value);
             }

             template <class T>
             template <class InputIterator>
             inline ForwardList<T>::ForwardList(InputIterator begin, InputIterator end) : front(nullptr), length(0) {
                 assign(begin, end);
             }

             template <class T>
             inline ForwardList<T>::ForwardList(std::initializer_list<T> list) : front(nullptr), length(0) {
                 assign(list.begin(), list.end());
             }

             template <class T>
             inline ForwardList<T>::ForwardList(ForwardList const& list) : ForwardList(list.begin(), list.end()) {
             }

             template <class T>
             inline ForwardList<T>::ForwardList(ForwardList && list) : front(list.front), length(list.length) {
                 list.front = nullptr;
                 list.length = 0;
             }

             template <class T>
             inline ForwardList<T>::~ForwardList() {
                 clear();
             }

             template <class T>
             inline T& ForwardList<T>::getFront() {
                 return static_cast <Node*>(front.next)->data;
             }

             template <class T>
             inline T const& ForwardList<T>::getFront() const {
                 return static_cast <Node*>(front.next)->data;
             }

             template <class T>
             inline constexpr std::size_t ForwardList<T>::getMaxSize() const {
                 return std::numeric_limits<std::size_t>::max();
             }

             template <class T>
             inline std::size_t ForwardList<T>::getSize() const {
                 return length;
             }

             template <class T>
             inline bool ForwardList<T>::isEmpty() const {
                 return front.next == nullptr;
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::beforeBegin() {
                 return Iterator(&front);
             }

             template <class T>
             inline typename ForwardList<T>::ConstIterator ForwardList<T>::beforeBegin() const {
                 return ConstIterator(&front);
             }

             template <class T>
             inline typename ForwardList<T>::ConstIterator ForwardList<T>::cbeforeBegin() const {
                 return beforeBegin();
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::begin() {
                 return Iterator(front.next);
             }

             template <class T>
             inline typename ForwardList<T>::ConstIterator ForwardList<T>::begin() const {
                 return ConstIterator(front.next);
             }

             template <class T>
             inline typename ForwardList<T>::ConstIterator ForwardList<T>::cbegin() const {
                 return begin();
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::end() {
                 return Iterator(static_cast <NodeBase*> (nullptr));
             }

             template <class T>
             inline typename ForwardList<T>::ConstIterator ForwardList<T>::end() const {
                 return ConstIterator(static_cast <const NodeBase*> (nullptr));
             }

             template <class T>
             inline typename ForwardList<T>::ConstIterator ForwardList<T>::cend() const {
                 return end();
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
                 reverse();
             }

             template <class T>
             inline void ForwardList<T>::clear() {
                 while (!isEmpty()) {
                     Node* tmp = static_cast <Node*>(front.next->next);
                     delete front.next;
                     front.next = tmp;
                 }
                 length = 0;
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
                 Iterator it = Iterator(pos.current);
                 for ( ; begin != end; begin++) {
                     it = insertAfter(ConstIterator(it.current), *begin);
                 }
                 return it;
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::insertAfter(ConstIterator pos, std::initializer_list<T> list) {
                 return insertAfter(pos, list.begin(), list.end());
             }

             template <class T>
             template <class ... Args>
             inline typename ForwardList<T>::Iterator ForwardList<T>::emplaceAfter(ConstIterator pos, Args  && ... args) {
                Node* inserted = new Node(T(std::forward<Args>(args)...), pos.current->next);
                pos.current->next = inserted;
                length++;
                return Iterator(inserted);
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::eraseAfter(ConstIterator pos) {
                 if (pos.current == &front) {
                     popFront();
                     return begin();
                 } else {
                     if (pos.current && pos.current->next) {
                         Node* tmp = static_cast <Node*>(pos.current->next->next);
                         delete pos.current->next;
                         pos.current->next = tmp;
                         length--;
                         return Iterator(tmp);
                     } else {
                         return end();
                     }
                 }
             }

             template <class T>
             inline typename ForwardList<T>::Iterator ForwardList<T>::eraseAfter(ConstIterator begin, ConstIterator end) {
                 if (begin.current == &front) {
                     for (std::ptrdiff_t index = 0; index < std::distance(begin, end); index++) {
                         popFront();
                     }
                     return this->begin();
                 } else {
                     while (begin.current && begin.current->next && begin.current->next != end.current) {
                         Node* tmp = static_cast <Node*>(begin.current->next->next);
                         delete begin.current->next;
                         begin.current->next = tmp;
                         length--;
                     }
                     return Iterator(end.current);
                 }
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
                 front.next = new Node(T(std::forward<Args>(args)...), front.next);
                 length++;
             }

             template <class T>
             inline void ForwardList<T>::popFront() {
                 if (!isEmpty()) {
                     Node* tmp = static_cast <Node*>(front.next->next);
                     delete front.next;
                     front.next = tmp;
                     length--;
                 }
             }

             template <class T>
             inline void ForwardList<T>::resize(std::size_t count) {
                 resize(count, T());
             }

             template <class T>
             inline void ForwardList<T>::resize(std::size_t count, T const& value) {
                 if (count != length) {
                     if (count < length) {
                         eraseAfter(std::next(cbeforeBegin(), count), cend());
                     } else {
                         insertAfter(std::next(cbeforeBegin(), length), count - length, value);
                     }
                 }
             }

             template <class T>
             inline void ForwardList<T>::swap(ForwardList& list) {
                 using namespace std;
                 swap(front, list.front);
                 swap(length, list.front);
             }

             template <class T>
             inline void ForwardList<T>::merge(ForwardList& list) {
                 std::less<ForwardList<T>> comp;
                 merge(list, comp);
             }

             template <class T>
             inline void ForwardList<T>::merge(ForwardList && list) {
                 std::less<ForwardList<T>> comp;
                 merge(std::move(list), comp);
             }

             template <class T>
             template <class Comparator>
             inline void ForwardList<T>::merge(ForwardList& list, Comparator comp) {
                 if (this != &list) {
                     Iterator it = begin();
                     Iterator listIt = list.begin();
                     if (comp(*it, *listIt)) {
                         front = static_cast <Node*> (listIt.current);
                         listIt++;
                     } else {
                         front = static_cast <Node*> (it.current);
                         it++;
                     }
                     Node*& current = front;
                     while (it != end() && listIt != list.end()) {
                         if (comp(*it, *listIt)) {
                             current->next = listIt.current;
                             if (listIt != list.end()) {
                                 listIt++;
                             }
                         } else {
                             current->next = it.current;
                             if (it != end()) {
                                 it++;
                             }
                         }
                         current = static_cast <Node*> (current->next);
                     }

                     length += list.length;
                     list.front = nullptr;
                     list.length = 0;
                 }
             }

             template <class T>
             template <class Comparator>
             inline void ForwardList<T>::merge(ForwardList && list, Comparator comp) {
                 merge(std::move(list), comp);
             }

             template <class T>
             inline void ForwardList<T>::spliceAfter(ConstIterator pos, ForwardList& list) {
                 spliceAfter(pos, list, list.beforeBegin(), list.end());
             }

             template <class T>
             inline void ForwardList<T>::spliceAfter(ConstIterator pos, ForwardList && list) {
                 spliceAfter(pos, std::move(list), list.beforeBegin(), list.end());
             }

             template <class T>
             inline void ForwardList<T>::spliceAfter(ConstIterator pos, ForwardList& list, ConstIterator it) {
                 Node*& tmp = static_cast <Node*> (pos.current->next);
                 Node*& itTmp = static_cast <Node*> (it.current->next->next);
                 pos.current->next = it.current->next;
                 pos.current->next->next = tmp;
                 it.current->next = itTmp;

                 list.length--;
                 length++;
             }

             template <class T>
             inline void ForwardList<T>::spliceAfter(ConstIterator pos, ForwardList && list, ConstIterator it) {
                 spliceAfter(pos, std::move(list), it);
             }

             template <class T>
             inline void ForwardList<T>::spliceAfter(ConstIterator pos, ForwardList& list, ConstIterator begin, ConstIterator end) {
                 Node*& tmp = static_cast <Node*> (pos.current->next);
                 Node*& itTmp = static_cast <Node*> (begin.current->next->next);
                 while (itTmp->next != end.current) {
                     itTmp = static_cast <Node*> (itTmp->next);
                 }
                 pos.current->next = begin.current->next;
                 pos.current->next->next = tmp;
                 begin.current->next = itTmp;

                 std::size_t size = std::distance(begin, end);
                 list.length -= size;
                 length += size;
             }

             template <class T>
             inline void ForwardList<T>::spliceAfter(ConstIterator pos, ForwardList && list, ConstIterator begin, ConstIterator end) {
                 spliceAfter(pos, std::move(list), begin, end);
             }

             template <class T>
             inline void ForwardList<T>::remove(T const& value) {
                 removeIf([&](T const& current) {
                     return current == value;
                 });
             }

             template <class T>
             template <class UnaryPredicate>
             inline void ForwardList<T>::removeIf(UnaryPredicate p) {
                 ConstIterator it = beforeBegin();
                 while (it.current->next != end()) {
                     if (p(*(it.current->next))) {
                         it = eraseAfter(it);
                     } else {
                         ++it;
                     }
                 }
             }

             template <class T>
             inline void ForwardList<T>::reverse() {
                 NodeBase*& current = front.next;
                 NodeBase* prev = nullptr;
                 NodeBase* next = nullptr;
                 while (current != nullptr) {
                     next = current->next;
                     current->next = prev;
                     prev = current;
                     current = next;
                 }
                 front.next = prev;
             }

             template <class T>
             inline void ForwardList<T>::unique() {
                 ConstIterator it = begin();
                 ConstIterator next = it++;
                 while (next != end()) {
                    if (it.current == next.current) {
                        it = eraseAfter(it);
                    } else {
                        ++it;
                    }
                    next = it++;
                 }
             }

             template <class T>
             inline ForwardList<T>& ForwardList<T>::operator=(ForwardList const& list) {
                 if (this != &list) {
                     ForwardList copy(list);
                     swap(copy);
                 }
                 return *this;
             }

             template <class T>
             inline ForwardList<T>& ForwardList<T>::operator=(ForwardList && list) {
                 if (this != &list) {
                     ForwardList move(std::move(list));
                     swap(move);
                 }
                 return *this;
             }

             template <class T>
             inline bool ForwardList<T>::operator==(ForwardList const& list) const {
                 if (length != list.length) {
                     return false;
                 }
                 Node* node = front;
                 Node* listNode = list.front;
                 std::size_t current = 0;
                 bool res = true;
                 while (current < length && res) {
                     if (*node != *listNode) {
                         res = false;
                     }
                     node = static_cast <Node*> (node->next);
                     listNode = static_cast <Node*> (listNode->next);
                     current++;
                 }
             }

             template <class T>
             inline bool ForwardList<T>::operator!=(ForwardList const& list) const {
                 return !(*this == list);
             }

             template <class T>
             inline String ForwardList<T>::toString() const {
                 if (isEmpty()) {
                     String res;
                     res.reserve(2);
                     res << '(' << ')';
                     return res;
                 } else {
                     String res;
                     Node* current = static_cast <Node*> (front.next);
                     res << '(' << current->data;
                     res.reserve((res.getSize() + 2) * length);
                     current = static_cast <Node*> (current->next);
                     while(current != nullptr) {
                         res << ',' << ' ' << current->data;
                         current = static_cast <Node*> (current->next);
                     }
                     res << ')';
                     return res;
                 }
             }

             template <class T>
             std::ostream& operator <<(std::ostream& stream, ForwardList<T> const& o) {
                 return stream << o.toString();
             }

        }
    }
