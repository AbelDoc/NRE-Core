
    /**
     * @file NRE_Vector.tpp
     * @brief Implementation of Utility's API's Container : Vector
     * @author Louis ABEL
     * @date 16/05/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Utility {
             namespace Detail {

                 template <class T, class Allocator>
                 inline Vector<T, Allocator>::Vector(Allocator const& alloc) :  Allocator(alloc), length(0), capacity(BASE_ALLOCATION_SIZE), data(this->allocate(capacity)) {
                 }
    
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>::Vector(SizeType count, T const& value, Allocator const& alloc) : Allocator(alloc), length(count), capacity(count), data(this->allocate(capacity)) {
                     assign(count, value);
                 }
    
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>::Vector(SizeType count, Allocator const& alloc) : Allocator(alloc), length(count), capacity(count), data(this->construct(this->allocate(count))) {
                 }
    
                 template <class T, class Allocator>
                 template <class InputIterator>
                 inline Vector<T, Allocator>::Vector(InputIterator begin, InputIterator end, Allocator const& alloc) : Allocator(alloc), length(std::distance(begin, end)), capacity(length), data(this->allocate(length)) {
                     assign(begin, end);
                 }
    
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>::Vector(std::initializer_list<T> init, Allocator const& alloc) : Vector(init.begin(), init.end(), alloc) {
                 }
        
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>::Vector(Vector const& vec) : Vector(vec, static_cast <Allocator const&> (vec)) {
                 }
    
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>::Vector(Vector const& vec, Allocator const& alloc) : Allocator(alloc), length(vec.length), capacity(vec.capacity), data(this->allocate(vec.capacity)) {
                     copy(vec);
                 }
    
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>::Vector(Vector && vec) : Vector(std::move(vec), static_cast <Allocator const&> (vec)) {
                 }
        
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>::Vector(Vector && vec, Allocator const& alloc) : Allocator(alloc), length(vec.length), capacity(vec.capacity), data(std::move(vec.data)) {
                     vec.length = 0;
                     vec.capacity = 0;
                     vec.data = nullptr;
                 }
    
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>::~Vector() {
                     clear();
                     this->deallocate(data, capacity);
                 }
    
                 template <class T, class Allocator>
                 inline T& Vector<T, Allocator>::get(SizeType index) {
                     if (index >= length) {
                         throw std::out_of_range("Accessing NRE::Utility::Vector element : " + std::to_string(index) + " while vector length is " + std::to_string(length) + ".");
                     }
                     return data[index];
                 }
    
                 template <class T, class Allocator>
                 inline T const& Vector<T, Allocator>::get(SizeType index) const {
                     if (index >= length) {
                         throw std::out_of_range("Accessing NRE::Utility::Vector element : " + std::to_string(index) + " while vector length is " + std::to_string(length) + ".");
                     }
                     return data[index];
                 }
    
                 template <class T, class Allocator>
                 inline T* Vector<T, Allocator>::getData() {
                     return data;
                 }
    
                 template <class T, class Allocator>
                 inline const T* Vector<T, Allocator>::getData() const {
                     return data;
                 }
    
                 template <class T, class Allocator>
                 inline T& Vector<T, Allocator>::getFront() {
                     return data[0];
                 }
    
                 template <class T, class Allocator>
                 inline T const& Vector<T, Allocator>::getFront() const {
                     return data[0];
                 }
    
                 template <class T, class Allocator>
                 inline T& Vector<T, Allocator>::getLast() {
                     return data[length - 1];
                 }
    
                 template <class T, class Allocator>
                 inline T const& Vector<T, Allocator>::getLast() const {
                     return data[length - 1];
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::SizeType Vector<T, Allocator>::getSize() const {
                     return length;
                 }
    
                 template <class T, class Allocator>
                 constexpr typename Vector<T, Allocator>::SizeType Vector<T, Allocator>::getMaxSize() const {
                     return std::numeric_limits<SizeType>::max();
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::SizeType Vector<T, Allocator>::getCapacity() const {
                     return capacity;
                 }
        
                 template <class T, class Allocator>
                 inline Allocator const& Vector<T, Allocator>::getAllocator() const {
                     return *this;
                 }
    
                 template <class T, class Allocator>
                 inline bool Vector<T, Allocator>::isEmpty() const {
                     return length == 0;
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::begin() {
                     return data;
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::begin() const {
                     return data;
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::cbegin() const {
                     return begin();
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::end() {
                     return data + length;
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::end() const {
                     return data + length;
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ConstIterator Vector<T, Allocator>::cend() const {
                     return end();
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::rbegin() {
                     return ReverseIterator(data + length);
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::rbegin() const {
                     return ConstReverseIterator(data + length);
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::crbegin() const {
                     return rbegin();
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ReverseIterator Vector<T, Allocator>::rend() {
                     return ReverseIterator(data);
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::rend() const {
                     return ConstReverseIterator(data);
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::ConstReverseIterator Vector<T, Allocator>::crend() const {
                     return rend();
                 }
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::assign(SizeType count, T const& value) {
                     clear();
                     if (capacity < count) {
                         reserveWithGrowFactor(count);
                     }
                     for (SizeType i = 0; i < count; i++) {
                         this->construct(&data[i], value);
                     }
                     length = count;
                 }
    
                 template <class T, class Allocator>
                 template <class InputIterator>
                 inline void Vector<T, Allocator>::assign(InputIterator begin, InputIterator end) {
                     clear();
                     SizeType size = std::distance(begin, end);
                     if (capacity < size) {
                         reserveWithGrowFactor(size);
                     }
                     SizeType current = 0;
                     for ( ; begin != end; begin++) {
                         this->construct(&data[current], *begin);
                         current++;
                     }
                     length = current;
                 }
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::reserve(SizeType size) {
                     if (capacity < size) {
                         reallocate(size);
                     }
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::insert(ConstIterator start, T const& value) {
                     return emplace(start, value);
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::insert(ConstIterator start, SizeType count, T const& value) {
                     SizeType index = start - ConstIterator(data);
                     if (capacity < length + count) {
                         reserveWithGrowFactor(length + count);
                     }
                     if (index < length) {
                         shift(index, count);
                     }
                     for (SizeType it = index; it != index + count; it++) {
                         this->construct(&data[it], value);
                     }
                     length += count;
                     return Iterator(data + index);
                 }
    
                 template <class T, class Allocator>
                 template <class InputIterator>
                 inline typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::insert(ConstIterator start, InputIterator begin, InputIterator end) {
                     SizeType count = std::distance(begin, end);
                     SizeType index = start - ConstIterator(data);
                     if (capacity < length + count) {
                         reserveWithGrowFactor(length + count);
                     }
                     if (index < length) {
                         shift(index, count);
                     }
                     for ( ; begin != end; begin++) {
                         this->construct(&data[index], *begin);
                         index++;
                     }
                     length += count;
                     return Iterator(data + index);
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::insert(ConstIterator start, std::initializer_list<T> list) {
                     return insert(start, list.begin(), list.end());
                 }
    
                 template <class T, class Allocator>
                 template <class ... Args>
                 inline typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::emplace(ConstIterator start, Args && ... args) {
                     SizeType index = start - ConstIterator(data);
                     if (capacity < length + 1) {
                         reallocate();
                     }
                     if (index < length) {
                         shift(index, 1);
                     }
                     this->construct(&data[index], std::forward<Args>(args)...);
                     length++;
                     return Iterator(data + index);
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::erase(ConstIterator pos) {
                     SizeType index = pos - ConstIterator(data);
                     if (index > length - 1) {
                         throw std::out_of_range("Erasing after NRE::Utility::Vector last element.");
                     }
                     this->destroy(pos);
                     shiftBack(index, 1);
                     length--;
                     return Iterator(data + index);
                 }
    
                 template <class T, class Allocator>
                 inline typename Vector<T, Allocator>::Iterator Vector<T, Allocator>::erase(ConstIterator begin, ConstIterator end) {
                     SizeType count = std::distance(begin, end);
                     SizeType index = begin - ConstIterator(data);
                     if (index > length - count) {
                         throw std::out_of_range("Erasing after NRE::Utility::Vector last element.");
                     }
                     for (auto it = begin; it != end; it++) {
                         this->destroy(it);
                     }
                     shiftBack(index, count);
                     length -= count;
                     return Iterator(data + index + count);
                 }
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::pushBack(T const& value) {
                     emplaceBack(value);
                 }
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::pushBack(T && value) {
                     emplaceBack(std::move(value));
                 }
    
                 template <class T, class Allocator>
                 template <class ... Args>
                 inline void Vector<T, Allocator>::emplaceBack(Args && ... args) {
                     if (capacity < length + 1) {
                         reallocate();
                     }
                     this->construct(&data[length], std::forward<Args>(args)...);
                     length++;
                 }
    
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::resize(SizeType count) {
                     resize(count, T());
                 }
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::resize(SizeType count, T const& value) {
                     if (count != length) {
                         if (count < length) {
                             for (SizeType index = count; index != length; index++) {
                                 this->destroy(&data[index]);
                             }
                             length = count;
                         } else {
                             if (capacity < count) {
                                 reallocate(count);
                             }
                             for (SizeType index = length; index < count; index++) {
                                 this->construct(&data[index], value);
                             }
                             length = count;
                         }
                     }
                 }
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::swap(Vector& vec) {
                     using std::swap;
                     swap(static_cast <Allocator&> (*this), static_cast <Allocator&> (vec));
                     swap(length, vec.length);
                     swap(capacity, vec.capacity);
                     swap(data, vec.data);
                 }
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::shrinkToFit() {
                     reallocate(length);
                 }
    
                 template <class T, class Allocator>
                 inline T& Vector<T, Allocator>::operator[](SizeType index) {
                     return data[index];
                 }
    
                 template <class T, class Allocator>
                 inline T const& Vector<T, Allocator>::operator[](SizeType index) const {
                     return data[index];
                 }
    
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>& Vector<T, Allocator>::operator =(Vector const& vec) {
                     if (this != &vec) {
                         Allocator::operator=(static_cast <Allocator const&> (vec));
                         assign(vec.begin(), vec.end());
                     }
                     return *this;
                 }
    
                 template <class T, class Allocator>
                 inline Vector<T, Allocator>& Vector<T, Allocator>::operator =(Vector && vec) {
                     if (this != &vec) {
                         swap(vec);
                     }
                     return *this;
                 }
    
                 template <class T, class Allocator>
                 inline bool Vector<T, Allocator>::operator !=(Vector const& vec) const {
                     return !(*this == vec);
                 }
    
                 template <class T, class Allocator>
                 inline String Vector<T, Allocator>::toString() const {
                     if (isEmpty()) {
                         String res;
                         res << '[' << ']';
                         return res;
                     } else {
                         String res;
                         res << '[' << data[0];
                         res.reserve((res.getSize() + 2) * length);
                         for (SizeType index = 1; index < length; index++) {
                             res << ',' << ' ' << data[index];
                         }
                         res << ']';
                         return res;
                     }
                 }
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::reallocate() {
                     reallocate((capacity < BASE_ALLOCATION_SIZE) ? (BASE_ALLOCATION_SIZE)
                                                                  : (static_cast <SizeType> (static_cast <float> (capacity) * GROW_FACTOR)));
                 }
    
                 template <class T, class Allocator>
                 inline void Vector<T, Allocator>::reserveWithGrowFactor(SizeType size) {
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
