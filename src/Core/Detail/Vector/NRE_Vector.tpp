
    /**
     * @file NRE_Vector.tpp
     * @brief Implementation of Core's API's Container : Vector
     * @author Louis ABEL
     * @date 16/05/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Core {
             namespace Detail {

                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>::Vector(AllocatorType const& alloc) : AllocatorType(alloc), length(0), capacity(BASE_ALLOCATION_SIZE), data(AllocatorTraits::allocate(*this, capacity)) {
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>::Vector(SizeType count, ConstReference value, AllocatorType const& alloc) : AllocatorType(alloc), length(count), capacity(count), data(AllocatorTraits::allocate(*this, capacity)) {
                     assign(count, value);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>::Vector(SizeType count, AllocatorType const& alloc) : Vector(count, ValueType(), alloc) {
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 template <Concept::InputIterator It, Concept::SentinelFor<It> S>
                 inline Vector<T, Alloc>::Vector(It begin, S end, AllocatorType const& alloc) : AllocatorType(alloc), length(Core::distance(begin, end)), capacity(length), data(AllocatorTraits::allocate(*this, length)) {
                    Core::uninitializedCopy(begin, end, this->begin());
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 template <Concept::InputRange R>
                 inline Vector<T, Alloc>::Vector(R && range, AllocatorType const& alloc) : Vector(Core::begin(range), Core::end(range), alloc) {
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>::Vector(std::initializer_list<T> init, AllocatorType const& alloc) : Vector(Core::begin(init), Core::end(init), alloc) {
                 }
        
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>::Vector(Vector const& vec) : Vector(vec, static_cast <AllocatorType const&> (vec)) {
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>::Vector(Vector const& vec, AllocatorType const& alloc) : AllocatorType(alloc), length(vec.length), capacity(vec.capacity), data(AllocatorTraits::allocate(*this, vec.capacity)) {
                     Core::uninitializedCopy(begin, end, this->begin());
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>::Vector(Vector && vec) : Vector(std::move(vec), static_cast <AllocatorType const&> (vec)) {
                 }
        
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>::Vector(Vector && vec, AllocatorType const& alloc) : AllocatorType(alloc), length(vec.length), capacity(vec.capacity), data(std::move(vec.data)) {
                     vec.length = 0;
                     vec.capacity = 0;
                     vec.data = nullptr;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>::~Vector() {
                     clear();
                     AllocatorTraits::deallocate(*this, data, capacity);
                     data = nullptr;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Reference Vector<T, Alloc>::get(SizeType index) {
                     if (index >= length) {
                         throw std::out_of_range("Accessing NRE::Core::Vector element : " + std::to_string(index) + " while vector length is " + std::to_string(length) + ".");
                     }
                     return data[index];
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstReference Vector<T, Alloc>::get(SizeType index) const {
                     if (index >= length) {
                         throw std::out_of_range("Accessing NRE::Core::Vector element : " + std::to_string(index) + " while vector length is " + std::to_string(length) + ".");
                     }
                     return data[index];
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Pointer Vector<T, Alloc>::getData() {
                     return data;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstPointer Vector<T, Alloc>::getData() const {
                     return data;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstPointer Vector<T, Alloc>::getCData() const {
                     return data;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Reference Vector<T, Alloc>::getFront() {
                     return data[0];
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstReference Vector<T, Alloc>::getFront() const {
                     return data[0];
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Reference Vector<T, Alloc>::getLast() {
                     return data[length - 1];
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstReference Vector<T, Alloc>::getLast() const {
                     return data[length - 1];
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::SizeType Vector<T, Alloc>::getSize() const {
                     return length;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 constexpr typename Vector<T, Alloc>::SizeType Vector<T, Alloc>::getMaxSize() const {
                     return std::numeric_limits<SizeType>::max();
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::SizeType Vector<T, Alloc>::getCapacity() const {
                     return capacity;
                 }
        
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::AllocatorType Vector<T, Alloc>::getAllocator() const {
                     return AllocatorType(*this);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline bool Vector<T, Alloc>::isEmpty() const {
                     return length == 0;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::begin() {
                     return data;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstIterator Vector<T, Alloc>::begin() const {
                     return data;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstIterator Vector<T, Alloc>::cbegin() const {
                     return begin();
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::end() {
                     return data + length;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstIterator Vector<T, Alloc>::end() const {
                     return data + length;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstIterator Vector<T, Alloc>::cend() const {
                     return end();
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ReverseIterator Vector<T, Alloc>::rbegin() {
                     return ReverseIterator(data + length);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstReverseIterator Vector<T, Alloc>::rbegin() const {
                     return ConstReverseIterator(data + length);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstReverseIterator Vector<T, Alloc>::crbegin() const {
                     return rbegin();
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ReverseIterator Vector<T, Alloc>::rend() {
                     return ReverseIterator(data);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstReverseIterator Vector<T, Alloc>::rend() const {
                     return ConstReverseIterator(data);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstReverseIterator Vector<T, Alloc>::crend() const {
                     return rend();
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::assign(SizeType count, ConstReference value) {
                     clear();
                     if (capacity < count) {
                         reserveWithGrowFactor(count);
                     }
                     for (SizeType i = 0; i < count; i++) {
                         AllocatorTraits::construct(*this, &data[i], value);
                     }
                     length = count;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 template <Concept::InputRange R>
                 inline void Vector<T, Alloc>::assign(R && range) {
                     assign(Core::begin(range), Core::end(range));
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::reserve(SizeType size) {
                     if (capacity < size) {
                         reallocate(size);
                     }
                 }
                 
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::clear() noexcept {
                     Memory::destroy(*this);
                     length = 0;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::insert(ConstIterator start, ConstReference value) {
                     return emplace(start, value);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::insert(ConstIterator start, SizeType count, ConstReference value) {
                     SizeType index = Core::distance(ConstIterator(data), start);
                     if (capacity < length + count) {
                         reserveWithGrowFactor(length + count);
                     }
                     if (index < length) {
                         Core::shiftRight(data + index, data + length + count, count);
                     }
                     for (SizeType it = index; it != index + count; ++it) {
                         AllocatorTraits::construct(*this, &data[it], value);
                     }
                     length += count;
                     return Iterator(data + index);
                 }
                 
                 template <class T, Concept::Allocator Alloc>
                 template <Concept::InputRange R>
                 inline typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::insert(ConstIterator start, R && range) {
                     return insert(start, Core::begin(range), Core::end(range));
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::insert(ConstIterator start, std::initializer_list<T> list) {
                     return insert(start, Core::begin(list), Core::end(list));
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 template <class ... Args>
                 inline typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::emplace(ConstIterator start, Args && ... args) {
                     SizeType index = Core::distance(ConstIterator(data), start);
                     if (capacity < length + 1) {
                         reallocate();
                     }
                     if (index < length) {
                         Core::shiftRight(data + index, data + length + 1, 1);
                     }
                     AllocatorTraits::construct(*this, &data[index], std::forward<Args>(args)...);
                     ++length;
                     return Iterator(data + index);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::erase(ConstIterator pos) {
                     SizeType index = Core::distance(ConstIterator(data), pos);
                     if (index > length - 1) {
                         throw std::out_of_range("Erasing after NRE::Core::Vector last element.");
                     }
                     AllocatorTraits::destroy(*this, Core::addressOf(data[index]));
                     Core::shiftLeft(data + index, data + length + 1, 1);
                     --length;
                     return Iterator(data + index);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 template <Concept::SentinelFor<ConstIterator> S>
                 inline typename Vector<T, Alloc>::Iterator Vector<T, Alloc>::erase(ConstIterator begin, S end) {
                     SizeType count = Core::distance(begin, end);
                     SizeType index = Core::distance(ConstIterator(data), begin);
                     if (index > length - count) {
                         throw std::out_of_range("Erasing after NRE::Core::Vector last element.");
                     }
                     Memory::destroy(data + index, data + index + count);
                     Core::shiftLeft(data + index, data + length + count, count);
                     length -= count;
                     return Iterator(data + index + count);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::pushBack(ConstReference value) {
                     emplaceBack(value);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::pushBack(T && value) {
                     emplaceBack(std::move(value));
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 template <class ... Args>
                 inline void Vector<T, Alloc>::emplaceBack(Args && ... args) {
                     if (capacity < length + 1) {
                         reallocate();
                     }
                     AllocatorTraits::construct(*this, &data[length], std::forward<Args>(args)...);
                     length++;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::popBack() {
                     AllocatorTraits ::destroy(*this, Core::prev(end()));
                     --length;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::resize(SizeType count) {
                     resize(count, T());
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::resize(SizeType count, ConstReference value) {
                     if (count != length) {
                         if (count < length) {
                             for (SizeType index = count; index != length; ++index) {
                                 AllocatorTraits::destroy(*this, &data[index]);
                             }
                             length = count;
                         } else {
                             if (capacity < count) {
                                 reallocate(count);
                             }
                             for (SizeType index = length; index < count; index++) {
                                 AllocatorTraits::construct(*this, &data[index], value);
                             }
                             length = count;
                         }
                     }
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::swap(Vector& vec) {
                     using std::swap;
                     swap(static_cast <AllocatorType&> (*this), static_cast <AllocatorType&> (vec));
                     swap(length, vec.length);
                     swap(capacity, vec.capacity);
                     swap(data, vec.data);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::shrinkToFit() {
                     reallocate(length);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::Reference Vector<T, Alloc>::operator[](SizeType index) {
                     return data[index];
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline typename Vector<T, Alloc>::ConstReference Vector<T, Alloc>::operator[](SizeType index) const {
                     return data[index];
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>& Vector<T, Alloc>::operator =(Vector const& vec) {
                     if (this != &vec) {
                         AllocatorType::operator=(static_cast <AllocatorType const&> (vec));
                         assign(vec);
                     }
                     return *this;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline Vector<T, Alloc>& Vector<T, Alloc>::operator =(Vector && vec) {
                     if (this != &vec) {
                         swap(vec);
                     }
                     return *this;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline bool Vector<T, Alloc>::operator !=(Vector const& vec) const {
                     return !(*this == vec);
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline String Vector<T, Alloc>::toString() const {
                     if (isEmpty()) {
                         String res;
                         res << '[' << ']';
                         return res;
                     } else {
                         String res;
                         res << '[' << data[0];
                         res.reserve((res.getSize() + 2) * length);
                         for (SizeType index = 1; index < length; ++index) {
                             res << ',' << ' ' << data[index];
                         }
                         res << ']';
                         return res;
                     }
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::reallocate() {
                     reallocate((capacity < BASE_ALLOCATION_SIZE) ? (BASE_ALLOCATION_SIZE)
                                                                  : (static_cast <SizeType> (static_cast <float> (capacity) * GROW_FACTOR)));
                 }
                 
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::reallocate(SizeType newSize) {
                     SizeType tmp = capacity;
                     capacity = newSize;
                     Pointer newData = AllocatorTraits::allocate(*this, capacity);
                     Core::uninitializedMoveN(data, length, newData);
                     AllocatorTraits::deallocate(*this, data, tmp);
                     data = newData;
                 }
    
                 template <class T, Concept::Allocator Alloc>
                 inline void Vector<T, Alloc>::reserveWithGrowFactor(SizeType size) {
                     SizeType newSize = (capacity < BASE_ALLOCATION_SIZE) ? (BASE_ALLOCATION_SIZE)
                                                                          : (static_cast <SizeType> (static_cast <float> (capacity) * GROW_FACTOR));
                     while (newSize < size) {
                         newSize = static_cast <SizeType> (static_cast <float> (newSize) * GROW_FACTOR);
                     }
                     reallocate(newSize);
                 }
    
             }
         }
     }
