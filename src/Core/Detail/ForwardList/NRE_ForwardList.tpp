
    /**
     * @file NRE_ForwardList.tpp
     * @brief Implementation of Core's API's Container : ForwardList
     * @author Louis ABEL
     * @date 11/06/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Core {
             namespace Detail {
                 namespace ForwardListInner {
                     
                     inline NodeBase::NodeBase(NodeBase* node) : next(node) {
                     }
    
                     template <class T>
                     inline Node<T>::Node(T const& value, NodeBase* node) : NodeBase(node), data(value) {
                     }
    
                     template <class T>
                     inline Node<T>::Node(T && value, NodeBase* node) : NodeBase(node), data(value) {
                     }
    
                     template <class T, class Category>
                     inline ForwardIterator<T, Category>::ForwardIterator(NodeBase* node) : current(node) {
                     }
    
                     template <class T, class Category>
                     inline ForwardIterator<T, Category>::ForwardIterator(const NodeBase* node) : current(const_cast <NodeBase*> (node)) {
                     }
    
                     template <class T, class Category>
                     inline NodeBase* ForwardIterator<T, Category>::getCurrent() {
                         return current;
                     }
    
                     template <class T, class Category>
                     inline typename ForwardIterator<T, Category>::Reference ForwardIterator<T, Category>::dereference() const {
                         return static_cast <Node<T>*>(current)->data;
                     }
    
                     template <class T, class Category>
                     inline void ForwardIterator<T, Category>::increment() {
                         current = current->next;
                     }
    
                     template <class T, class Category>
                     inline bool ForwardIterator<T, Category>::equal(ForwardIterator const& it) const {
                         return current == it.current;
                     }
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>::ForwardList(Allocator const& alloc) : AllocatorType(alloc), front(nullptr), length(0) {
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>::ForwardList(SizeType count, ConstReference value, Allocator const& alloc) : AllocatorType(alloc), front(nullptr), length(0) {
                     assign(count, value);
                 }
    
                 template <class T, class Allocator>
                 template <class InputIterator>
                 inline ForwardList<T, Allocator>::ForwardList(InputIterator begin, InputIterator end, Allocator const& alloc) : AllocatorType(alloc), front(nullptr), length(0) {
                     assign(begin, end);
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>::ForwardList(std::initializer_list<T> list, Allocator const& alloc) : AllocatorType(alloc), front(nullptr), length(0) {
                     assign(list.begin(), list.end());
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>::ForwardList(ForwardList const& list) : ForwardList(list, static_cast <AllocatorType const&> (list)) {
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>::ForwardList(ForwardList const& list, Allocator const& alloc) : ForwardList(list.begin(), list.end(), alloc) {
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>::ForwardList(ForwardList && list) : ForwardList(std::move(list), static_cast <AllocatorType const&> (list)) {
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>::ForwardList(ForwardList && list, Allocator const& alloc) : AllocatorType(alloc), front(list.front), length(list.length) {
                     list.front = nullptr;
                     list.length = 0;
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>::~ForwardList() {
                     clear();
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Reference ForwardList<T, Allocator>::getFront() {
                     return static_cast <Node*>(front.next)->data;
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::ConstReference ForwardList<T, Allocator>::getFront() const {
                     return static_cast <Node*>(front.next)->data;
                 }
    
                 template <class T, class Allocator>
                 constexpr typename ForwardList<T, Allocator>::SizeType ForwardList<T, Allocator>::getMaxSize() const {
                     return std::numeric_limits<SizeType>::max();
                 }
    
                 template <class T, class Allocator>
                 inline Allocator ForwardList<T, Allocator>::getAllocator() const {
                     return Allocator(*this);
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::SizeType ForwardList<T, Allocator>::getSize() const {
                     return length;
                 }
    
                 template <class T, class Allocator>
                 inline bool ForwardList<T, Allocator>::isEmpty() const {
                     return front.next == nullptr;
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::beforeBegin() {
                     return Iterator(&front);
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::ConstIterator ForwardList<T, Allocator>::beforeBegin() const {
                     return ConstIterator(&front);
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::ConstIterator ForwardList<T, Allocator>::cbeforeBegin() const {
                     return beforeBegin();
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::begin() {
                     return Iterator(front.next);
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::ConstIterator ForwardList<T, Allocator>::begin() const {
                     return ConstIterator(front.next);
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::ConstIterator ForwardList<T, Allocator>::cbegin() const {
                     return begin();
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::end() {
                     return Iterator(static_cast <NodeBase*> (nullptr));
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::ConstIterator ForwardList<T, Allocator>::end() const {
                     return ConstIterator(static_cast <const NodeBase*> (nullptr));
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::ConstIterator ForwardList<T, Allocator>::cend() const {
                     return end();
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::assign(SizeType count, ConstReference value) {
                     clear();
                     for (SizeType index = 0; index < count; index++) {
                         pushFront(value);
                     }
                 }
    
                 template <class T, class Allocator>
                 template <class InputIterator>
                 inline void ForwardList<T, Allocator>::assign(InputIterator begin, InputIterator end) {
                     clear();
                     for ( ; begin != end; begin++) {
                         pushFront(*begin);
                     }
                     reverse();
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::clear() {
                     while (!isEmpty()) {
                         NodeBase* tmp = front.next->next;
                         this->deallocate(this->destroy(static_cast <Node*>(front.next)));
                         front.next = tmp;
                     }
                     length = 0;
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::insertAfter(ConstIterator pos, ConstReference value) {
                     return emplaceAfter(pos, value);
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::insertAfter(ConstIterator pos, T && value) {
                     return emplaceAfter(pos, std::move(value));
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::insertAfter(ConstIterator pos, SizeType count, ConstReference value) {
                     Iterator it;
                     for (SizeType index = 0; index < count; index++) {
                         it = insertAfter(pos, value);
                     }
                     return it;
                 }
    
                 template <class T, class Allocator>
                 template <class InputIterator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::insertAfter(ConstIterator pos, InputIterator begin, InputIterator end) {
                     Iterator it = Iterator(pos.getCurrent());
                     for ( ; begin != end; begin++) {
                         it = insertAfter(ConstIterator(it.getCurrent()), *begin);
                     }
                     return it;
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::insertAfter(ConstIterator pos, std::initializer_list<T> list) {
                     return insertAfter(pos, list.begin(), list.end());
                 }
    
                 template <class T, class Allocator>
                 template <class ... Args>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::emplaceAfter(ConstIterator pos, Args  && ... args) {
                    Node* inserted = this->construct(this->allocate(), T(std::forward<Args>(args)...), pos.getCurrent()->next);
                    pos.getCurrent()->next = inserted;
                    length++;
                    return Iterator(inserted);
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::eraseAfter(ConstIterator pos) {
                     if (pos.getCurrent() == &front) {
                         popFront();
                         return begin();
                     } else {
                         if (pos.getCurrent() && pos.getCurrent()->next) {
                             NodeBase* tmp = pos.getCurrent()->next->next;
                             this->deallocate(this->destroy(static_cast <Node*>(pos.getCurrent()->next)));
                             pos.getCurrent()->next = tmp;
                             length--;
                             return Iterator(tmp);
                         } else {
                             return end();
                         }
                     }
                 }
    
                 template <class T, class Allocator>
                 inline typename ForwardList<T, Allocator>::Iterator ForwardList<T, Allocator>::eraseAfter(ConstIterator begin, ConstIterator end) {
                     if (begin.getCurrent() == &front) {
                         for (std::ptrdiff_t index = 0; index < std::distance(begin, end); index++) {
                             popFront();
                         }
                         return this->begin();
                     } else {
                         while (begin.getCurrent() && begin.getCurrent()->next && begin.getCurrent()->next != end.getCurrent()) {
                             NodeBase* tmp = begin.getCurrent()->next->next;
                             this->deallocate(this->destroy(static_cast <Node*>(begin.getCurrent()->next)));
                             begin.getCurrent()->next = tmp;
                             length--;
                         }
                         return Iterator(end.getCurrent());
                     }
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::pushFront(ConstReference value) {
                     emplaceFront(value);
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::pushFront(T && value) {
                     emplaceFront(std::move(value));
                 }
    
                 template <class T, class Allocator>
                 template <class ... Args>
                 inline void ForwardList<T, Allocator>::emplaceFront(Args && ... args) {
                     front.next = this->construct(this->allocate(), T(std::forward<Args>(args)...), front.next);
                     length++;
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::popFront() {
                     if (!isEmpty()) {
                         NodeBase* tmp = front.next->next;
                         this->deallocate(this->destroy(static_cast <Node*>(front.next)));
                         front.next = tmp;
                         length--;
                     }
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::resize(SizeType count) {
                     resize(count, T());
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::resize(SizeType count, ConstReference value) {
                     if (count != length) {
                         if (count < length) {
                             eraseAfter(std::next(cbeforeBegin(), count), cend());
                         } else {
                             insertAfter(std::next(cbeforeBegin(), length), count - length, value);
                         }
                     }
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::swap(ForwardList& list) {
                     using std::swap;
                     swap(static_cast <AllocatorType&> (*this), static_cast <AllocatorType&> (list));
                     swap(front, list.front);
                     swap(length, list.length);
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::merge(ForwardList& list) {
                     std::less<T> comp;
                     merge(std::move(list), comp);
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::merge(ForwardList && list) {
                     std::less<T> comp;
                     merge(list, comp);
                 }
    
                 template <class T, class Allocator>
                 template <class Comparator>
                 inline void ForwardList<T, Allocator>::merge(ForwardList& list, Comparator comp) {
                     merge(std::move(list), comp);
                 }
    
                 template <class T, class Allocator>
                 template <class Comparator>
                 inline void ForwardList<T, Allocator>::merge(ForwardList && list, Comparator comp) {
                     if (this != &list) {
                         Iterator it = begin();
                         Iterator listIt = list.begin();
                         if (comp(*listIt, *it)) {
                             front.next = listIt.getCurrent();
                             listIt++;
                         } else {
                             front.next = it.getCurrent();
                             it++;
                         }
                         NodeBase* current = front.next;
                         while (it != end() || listIt != list.end()) {
                             if (comp(*listIt, *it)) {
                                 current->next = listIt.getCurrent();
                                 if (listIt != list.end()) {
                                     listIt++;
                                     if (listIt == list.end()) {
                                         while (it != end()) {
                                             current = current->next;
                                             current->next = it.getCurrent();
                                             it++;
                                         }
                                     }
                                 }
                             } else {
                                 current->next = it.getCurrent();
                                 if (it != end()) {
                                     it++;
                                     if (it == end()) {
                                         while (listIt != list.end()) {
                                            current = current->next;
                                            current->next = listIt.getCurrent();
                                            listIt++;
                                        }
                                    }
                                 }
                             }
                             current = current->next;
                         }
    
                         length += list.length;
                         list.front.next = nullptr;
                         list.length = 0;
                     }
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::spliceAfter(ConstIterator pos, ForwardList& list) {
                     spliceAfter(pos, std::move(list), list.cbeforeBegin(), list.cend());
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::spliceAfter(ConstIterator pos, ForwardList && list) {
                     spliceAfter(pos, list, list.cbeforeBegin(), list.cend());
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::spliceAfter(ConstIterator pos, ForwardList& list, ConstIterator it) {
                     spliceAfter(pos, std::move(list), it);
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::spliceAfter(ConstIterator pos, ForwardList && list, ConstIterator it) {
                     NodeBase* tmp = pos.getCurrent()->next;
                     NodeBase* itTmp = it.getCurrent()->next;
                     NodeBase* end = it.getCurrent()->next->next;
                     pos.getCurrent()->next = it.getCurrent()->next;
                     itTmp->next = tmp;
                     it.getCurrent()->next = end;
    
                     list.length--;
                     length++;
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::spliceAfter(ConstIterator pos, ForwardList& list, ConstIterator begin, ConstIterator end) {
                     spliceAfter(pos, std::move(list), begin, end);
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::spliceAfter(ConstIterator pos, ForwardList && list, ConstIterator begin, ConstIterator end) {
                     SizeType size = std::distance(begin, end) - 1;
    
                     NodeBase* tmp = pos.getCurrent()->next;
                     NodeBase* itTmp = begin.getCurrent()->next;
                     while (itTmp->next != end.getCurrent()) {
                         itTmp = itTmp->next;
                     }
                     pos.getCurrent()->next = begin.getCurrent()->next;
                     itTmp->next = tmp;
                     begin.getCurrent()->next = end.getCurrent();
    
                     list.length -= size;
                     length += size;
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::remove(ConstReference value) {
                     removeIf([&](ConstReference current) {
                         return current == value;
                     });
                 }
    
                 template <class T, class Allocator>
                 template <class UnaryPredicate>
                 inline void ForwardList<T, Allocator>::removeIf(UnaryPredicate p) {
                     ConstIterator it = cbeforeBegin();
                     while (it.getCurrent()->next != end().getCurrent()) {
                         if (p(static_cast <Node*> (it.getCurrent()->next)->data)) {
                             eraseAfter(it);
                         } else {
                             ++it;
                         }
                     }
                 }
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::reverse() {
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
    
                 template <class T, class Allocator>
                 inline void ForwardList<T, Allocator>::unique() {
                     ConstIterator it = cbegin();
                     ConstIterator next = std::next(it);
                     while (next != cend()) {
                        if (*it == *next) {
                            eraseAfter(it);
                        } else {
                            it = next;
                        }
                        next = std::next(it);
                     }
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>& ForwardList<T, Allocator>::operator=(ForwardList const& list) {
                     if (this != &list) {
                         AllocatorType::operator=(static_cast <AllocatorType const&> (list));
                         assign(list.begin(), list.end());
                     }
                     return *this;
                 }
    
                 template <class T, class Allocator>
                 inline ForwardList<T, Allocator>& ForwardList<T, Allocator>::operator=(ForwardList && list) {
                     if (this != &list) {
                         swap(list);
                     }
                     return *this;
                 }
    
                 template <class T, class Allocator>
                 inline bool ForwardList<T, Allocator>::operator==(ForwardList const& list) const {
                     if (length != list.length) {
                         return false;
                     }
                     Node* node = static_cast <Node*> (front.next);
                     Node* listNode = static_cast <Node*> (list.front.next);
                     SizeType current = 0;
                     bool res = true;
                     while (current < length && res) {
                         if (node->data != listNode->data) {
                             res = false;
                         }
                         node = static_cast <Node*> (node->next);
                         listNode = static_cast <Node*> (listNode->next);
                         current++;
                     }
                     return res;
                 }
    
                 template <class T, class Allocator>
                 inline bool ForwardList<T, Allocator>::operator!=(ForwardList const& list) const {
                     return !(*this == list);
                 }
    
                 template <class T, class Allocator>
                 inline String ForwardList<T, Allocator>::toString() const {
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

            }
        }
    }
