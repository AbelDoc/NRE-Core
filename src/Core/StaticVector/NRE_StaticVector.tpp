
    /**
     * @file NRE_StaticVector.tpp
     * @brief Implementation of Core's API's Container : StaticVector
     * @author Louis ABEL
     * @date 05/02/2020
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Core {

             template <class T, std::size_t Size>
             inline StaticVector<T, Size>::StaticVector() : length(0) {
             }

             template <class T, std::size_t Size>
             inline StaticVector<T, Size>::StaticVector(SizeType count, ConstReference value) : length(0) {
                 assign(count, value);
             }

             template <class T, std::size_t Size>
             inline StaticVector<T, Size>::StaticVector(SizeType count) : length(0) {
                 assign(count, ValueType());
             }

             template <class T, std::size_t Size>
             template <class InputIterator>
             inline StaticVector<T, Size>::StaticVector(InputIterator begin, InputIterator end) : length(0) {
                 assign(begin, end);
             }

             template <class T, std::size_t Size>
             inline StaticVector<T, Size>::StaticVector(std::initializer_list<T> init) : StaticVector(init.begin(), init.end()) {
             }

             template <class T, std::size_t Size>
             inline StaticVector<T, Size>::StaticVector(StaticVector const& vec) {
                 copy(vec);
             }

             template <class T, std::size_t Size>
             inline StaticVector<T, Size>::StaticVector(StaticVector && vec) {
                 move(std::move(vec));
             }

             template <class T, std::size_t Size>
             inline StaticVector<T, Size>::~StaticVector() {
                 clear();
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Reference StaticVector<T, Size>::get(SizeType index) {
                 if (index >= length) {
                     throw std::out_of_range("Accessing NRE::Core::StaticVector element : " + std::to_string(index) + " while dynamic array length is " + std::to_string(length) + ".");
                 }
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstReference StaticVector<T, Size>::get(SizeType index) const {
                 if (index >= length) {
                     throw std::out_of_range("Accessing NRE::Core::StaticVector element : " + std::to_string(index) + " while dynamic array length is " + std::to_string(length) + ".");
                 }
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Pointer StaticVector<T, Size>::getData() {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstPointer StaticVector<T, Size>::getData() const {
                 return data;
             }
    
             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstPointer StaticVector<T, Size>::getCData() const {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Reference StaticVector<T, Size>::getFront() {
                 return data[0];
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstReference StaticVector<T, Size>::getFront() const {
                 return data[0];
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Reference StaticVector<T, Size>::getLast() {
                 return data[length - 1];
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstReference StaticVector<T, Size>::getLast() const {
                 return data[length - 1];
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::SizeType StaticVector<T, Size>::getSize() const {
                 return length;
             }

             template <class T, std::size_t Size>
             constexpr typename StaticVector<T, Size>::SizeType StaticVector<T, Size>::getMaxSize() const {
                 return std::numeric_limits<SizeType>::max();
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::SizeType StaticVector<T, Size>::getCapacity() const {
                 return Size;
             }

             template <class T, std::size_t Size>
             inline bool StaticVector<T, Size>::isEmpty() const {
                 return length == 0;
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Iterator StaticVector<T, Size>::begin() {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstIterator StaticVector<T, Size>::begin() const {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstIterator StaticVector<T, Size>::cbegin() const {
                 return begin();
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Iterator StaticVector<T, Size>::end() {
                 return data + length;
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstIterator StaticVector<T, Size>::end() const {
                 return data + length;
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstIterator StaticVector<T, Size>::cend() const {
                 return end();
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ReverseIterator StaticVector<T, Size>::rbegin() {
                 return ReverseIterator(data + length);
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstReverseIterator StaticVector<T, Size>::rbegin() const {
                 return ConstReverseIterator(data + length);
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstReverseIterator StaticVector<T, Size>::crbegin() const {
                 return rbegin();
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ReverseIterator StaticVector<T, Size>::rend() {
                 return ReverseIterator(data);
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstReverseIterator StaticVector<T, Size>::rend() const {
                 return ConstReverseIterator(data);
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstReverseIterator StaticVector<T, Size>::crend() const {
                 return rend();
             }

             template <class T, std::size_t Size>
             inline void StaticVector<T, Size>::assign(SizeType count, ConstReference value) {
                 clear();
                 if (Size < count) {
                     throw std::out_of_range("Assigning more element than NRE::Core::StaticVector can handle.");
                 }
                 for (SizeType i = 0; i < count; i++) {
                     data[i] = value;
                 }
                 length = count;
             }

             template <class T, std::size_t Size>
             template <class InputIterator>
             inline void StaticVector<T, Size>::assign(InputIterator begin, InputIterator end) {
                 clear();
                 SizeType size = std::distance(begin, end);
                 if (Size < size) {
                     throw std::out_of_range("Assigning more element than NRE::Core::StaticVector can handle.");
                 }
                 SizeType current = 0;
                 for ( ; begin != end; begin++) {
                     data[current] = *begin;
                     current++;
                 }
                 length = current;
             }
             
             template <class T, std::size_t Size>
             inline void StaticVector<T, Size>::clear() noexcept {
                 length = 0;
             }
             
             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Iterator StaticVector<T, Size>::insert(ConstIterator start, ConstReference value) {
                 return emplace(start, value);
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Iterator StaticVector<T, Size>::insert(ConstIterator start, SizeType count, ConstReference value) {
                 SizeType index = start - ConstIterator(data);
                 if (Size < length + count) {
                     throw std::out_of_range("Inserting more element than NRE::Core::StaticVector can handle.");
                 }
                 if (index < length) {
                     shift(index, count);
                 }
                 for (SizeType it = index; it != index + count; it++) {
                     data[it] = value;
                 }
                 length += count;
                 return Iterator(data + index);
             }

             template <class T, std::size_t Size>
             template <class InputIterator>
             inline typename StaticVector<T, Size>::Iterator StaticVector<T, Size>::insert(ConstIterator start, InputIterator begin, InputIterator end) {
                 SizeType count = std::distance(begin, end);
                 SizeType index = start - ConstIterator(data);
                 if (Size < length + count) {
                     throw std::out_of_range("Inserting more element than NRE::Core::StaticVector can handle.");
                 }
                 if (index < length) {
                     shift(index, count);
                 }
                 for ( ; begin != end; begin++) {
                     data[index] = *begin;
                     index++;
                 }
                 length += count;
                 return Iterator(data + index);
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Iterator StaticVector<T, Size>::insert(ConstIterator start, std::initializer_list<T> list) {
                 return insert(start, list.begin(), list.end());
             }

             template <class T, std::size_t Size>
             template <class ... Args>
             inline typename StaticVector<T, Size>::Iterator StaticVector<T, Size>::emplace(ConstIterator start, Args && ... args) {
                 SizeType index = start - ConstIterator(data);
                 if (Size < length + 1) {
                     throw std::out_of_range("Inserting more element than NRE::Core::StaticVector can handle.");
                 }
                 if (index < length) {
                     shift(index, 1);
                 }
                 data[index] = ValueType (std::forward<Args>(args)...);
                 length++;
                 return Iterator(data + index);
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Iterator StaticVector<T, Size>::erase(ConstIterator pos) {
                 SizeType index = pos - ConstIterator(data);
                 if (index > length - 1) {
                     throw std::out_of_range("Erasing after NRE::Core::StaticVector last element.");
                 }
                 shiftBack(index, 1);
                 length--;
                 return Iterator(data + index);
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Iterator StaticVector<T, Size>::erase(ConstIterator begin, ConstIterator end) {
                 SizeType count = std::distance(begin, end);
                 SizeType index = begin - ConstIterator(data);
                 if (index > length - count) {
                     throw std::out_of_range("Erasing after NRE::Core::StaticVector last element.");
                 }
                 shiftBack(index, count);
                 length -= count;
                 return Iterator(data + index + count);
             }

             template <class T, std::size_t Size>
             inline void StaticVector<T, Size>::pushBack(ConstReference value) {
                 emplaceBack(value);
             }

             template <class T, std::size_t Size>
             inline void StaticVector<T, Size>::pushBack(ValueType && value) {
                 emplaceBack(std::move(value));
             }

             template <class T, std::size_t Size>
             template <class ... Args>
             inline void StaticVector<T, Size>::emplaceBack(Args && ... args) {
                 if (Size < length + 1) {
                     throw std::out_of_range("Inserting more element than NRE::Core::StaticVector can handle.");
                 }
                 data[length] = ValueType(std::forward<Args>(args)...);
                 length++;
             }
             
             template <class T, std::size_t Size>
             inline void StaticVector<T, Size>::popBack() {
                 length--;
             }

             template <class T, std::size_t Size>
             inline void StaticVector<T, Size>::resize(SizeType count) {
                 resize(count, ValueType());
             }

             template <class T, std::size_t Size>
             inline void StaticVector<T, Size>::resize(SizeType count, ConstReference value) {
                 if (count != length) {
                     if (count < length) {
                         length = count;
                     } else {
                         if (Size < count) {
                             throw std::out_of_range("Resizing past NRE::Core::StaticVector fixed capacity.");
                         }
                         for (SizeType index = length; index < count; index++) {
                             data[index] = value;
                         }
                         length = count;
                     }
                 }
             }

             template <class T, std::size_t Size>
             inline void StaticVector<T, Size>::swap(StaticVector& vec) {
                 using std::swap;
                 swap(length, vec.length);
                 swap(data, vec.data);
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::Reference StaticVector<T, Size>::operator[](SizeType index) {
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline typename StaticVector<T, Size>::ConstReference StaticVector<T, Size>::operator[](SizeType index) const {
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline StaticVector<T, Size>& StaticVector<T, Size>::operator =(StaticVector const& vec) {
                 if (this != &vec) {
                     copy(vec);
                 }
                 return *this;
             }

             template <class T, std::size_t Size>
             inline StaticVector<T, Size>& StaticVector<T, Size>::operator =(StaticVector && vec) {
                 if (this != &vec) {
                     swap(vec);
                 }
                 return *this;
             }

             template <class T, std::size_t Size>
             inline bool StaticVector<T, Size>::operator !=(StaticVector const& vec) const {
                 return !(*this == vec);
             }

             template <class T, std::size_t Size>
             inline String StaticVector<T, Size>::toString() const {
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

         }
     }
