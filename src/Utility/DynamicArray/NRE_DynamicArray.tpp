
    /**
     * @file NRE_DynamicArray.tpp
     * @brief Implementation of Utility's API's Container : DynamicArray
     * @author Louis ABEL
     * @date 05/02/2020
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Utility {

             template <class T, std::size_t Size>
             inline DynamicArray<T, Size>::DynamicArray() : length(0) {
             }

             template <class T, std::size_t Size>
             inline DynamicArray<T, Size>::DynamicArray(std::size_t count, T const& value) : length(0) {
                 assign(count, value);
             }

             template <class T, std::size_t Size>
             inline DynamicArray<T, Size>::DynamicArray(std::size_t count) : length(0) {
                 assign(count, T());
             }

             template <class T, std::size_t Size>
             template <class InputIterator>
             inline DynamicArray<T, Size>::DynamicArray(InputIterator begin, InputIterator end) : length(0) {
                 assign(begin, end);
             }

             template <class T, std::size_t Size>
             inline DynamicArray<T, Size>::DynamicArray(std::initializer_list<T> init) : DynamicArray(init.begin(), init.end()) {
             }

             template <class T, std::size_t Size>
             inline DynamicArray<T, Size>::DynamicArray(DynamicArray const& arr) : length(arr.length) {
                 copy(arr);
             }

             template <class T, std::size_t Size>
             inline DynamicArray<T, Size>::DynamicArray(DynamicArray && arr) : length(arr.length) {
                 move(arr);
                 arr.length = 0;
             }

             template <class T, std::size_t Size>
             inline DynamicArray<T, Size>::~DynamicArray() {
                 clear();
             }

             template <class T, std::size_t Size>
             inline T& DynamicArray<T, Size>::get(std::size_t index) {
                 if (index >= length) {
                     throw std::out_of_range("Accessing NRE::Utility::DynamicArray element : " + std::to_string(index) + " while dynamic array length is " + std::to_string(length) + ".");
                 }
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline T const& DynamicArray<T, Size>::get(std::size_t index) const {
                 if (index >= length) {
                     throw std::out_of_range("Accessing NRE::Utility::DynamicArray element : " + std::to_string(index) + " while dynamic array length is " + std::to_string(length) + ".");
                 }
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline T* DynamicArray<T, Size>::getData() {
                 return data;
             }

             template <class T, std::size_t Size>
             inline const T* DynamicArray<T, Size>::getData() const {
                 return data;
             }

             template <class T, std::size_t Size>
             inline T& DynamicArray<T, Size>::getFront() {
                 return data[0];
             }

             template <class T, std::size_t Size>
             inline T const& DynamicArray<T, Size>::getFront() const {
                 return data[0];
             }

             template <class T, std::size_t Size>
             inline T& DynamicArray<T, Size>::getLast() {
                 return data[length - 1];
             }

             template <class T, std::size_t Size>
             inline T const& DynamicArray<T, Size>::getLast() const {
                 return data[length - 1];
             }

             template <class T, std::size_t Size>
             inline std::size_t DynamicArray<T, Size>::getSize() const {
                 return length;
             }

             template <class T, std::size_t Size>
             inline constexpr std::size_t DynamicArray<T, Size>::getMaxSize() const {
                 return std::numeric_limits<std::size_t>::max();
             }

             template <class T, std::size_t Size>
             inline std::size_t DynamicArray<T, Size>::getCapacity() const {
                 return Size;
             }

             template <class T, std::size_t Size>
             inline bool DynamicArray<T, Size>::isEmpty() const {
                 return length == 0;
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::Iterator DynamicArray<T, Size>::begin() {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ConstIterator DynamicArray<T, Size>::begin() const {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ConstIterator DynamicArray<T, Size>::cbegin() const {
                 return begin();
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::Iterator DynamicArray<T, Size>::end() {
                 return data + length;
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ConstIterator DynamicArray<T, Size>::end() const {
                 return data + length;
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ConstIterator DynamicArray<T, Size>::cend() const {
                 return end();
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ReverseIterator DynamicArray<T, Size>::rbegin() {
                 return ReverseIterator(data + length);
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ConstReverseIterator DynamicArray<T, Size>::rbegin() const {
                 return ConstReverseIterator(data + length);
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ConstReverseIterator DynamicArray<T, Size>::crbegin() const {
                 return rbegin();
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ReverseIterator DynamicArray<T, Size>::rend() {
                 return ReverseIterator(data);
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ConstReverseIterator DynamicArray<T, Size>::rend() const {
                 return ConstReverseIterator(data);
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::ConstReverseIterator DynamicArray<T, Size>::crend() const {
                 return rend();
             }

             template <class T, std::size_t Size>
             inline void DynamicArray<T, Size>::assign(std::size_t count, T const& value) {
                 clear();
                 if (Size < count) {
                     throw std::out_of_range("Assigning more element than NRE::Utility::DynamicArray can handle.");
                 }
                 for (std::size_t i = 0; i < count; i++) {
                     new(&data[i]) T (value);
                 }
                 length = count;
             }

             template <class T, std::size_t Size>
             template <class InputIterator>
             inline void DynamicArray<T, Size>::assign(InputIterator begin, InputIterator end) {
                 clear();
                 std::size_t size = std::distance(begin, end);
                 if (Size < size) {
                     throw std::out_of_range("Assigning more element than NRE::Utility::DynamicArray can handle.");
                 }
                 std::size_t current = 0;
                 for ( ; begin != end; begin++) {
                     new(&data[current]) T (*(begin));
                     current++;
                 }
                 length = current;
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::Iterator DynamicArray<T, Size>::insert(ConstIterator start, T const& value) {
                 return emplace(start, value);
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::Iterator DynamicArray<T, Size>::insert(ConstIterator start, std::size_t count, T const& value) {
                 std::size_t index = start - ConstIterator(data);
                 if (Size < length + count) {
                     throw std::out_of_range("Inserting more element than NRE::Utility::DynamicArray can handle.");
                 }
                 if (index < length) {
                     shift(index, count);
                 }
                 for (std::size_t it = index; it != index + count; it++) {
                     new(&data[it]) T (value);
                 }
                 length += count;
                 return Iterator(data + index);
             }

             template <class T, std::size_t Size>
             template <class InputIterator>
             inline typename DynamicArray<T, Size>::Iterator DynamicArray<T, Size>::insert(ConstIterator start, InputIterator begin, InputIterator end) {
                 std::size_t count = std::distance(begin, end);
                 std::size_t index = start - ConstIterator(data);
                 if (Size < length + count) {
                     throw std::out_of_range("Inserting more element than NRE::Utility::DynamicArray can handle.");
                 }
                 if (index < length) {
                     shift(index, count);
                 }
                 for ( ; begin != end; begin++) {
                     new(&data[index]) T (*begin);
                     index++;
                 }
                 length += count;
                 return Iterator(data + index);
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::Iterator DynamicArray<T, Size>::insert(ConstIterator start, std::initializer_list<T> list) {
                 return insert(start, list.begin(), list.end());
             }

             template <class T, std::size_t Size>
             template <class ... Args>
             inline typename DynamicArray<T, Size>::Iterator DynamicArray<T, Size>::emplace(ConstIterator start, Args && ... args) {
                 std::size_t index = start - ConstIterator(data);
                 if (Size < length + 1) {
                     throw std::out_of_range("Inserting more element than NRE::Utility::DynamicArray can handle.");
                 }
                 if (index < length) {
                     shift(index, 1);
                 }
                 new(&data[index]) T (std::forward<Args>(args)...);
                 length++;
                 return Iterator(data + index);
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::Iterator DynamicArray<T, Size>::erase(ConstIterator pos) {
                 std::size_t index = pos - ConstIterator(data);
                 if (index > length - 1) {
                     throw std::out_of_range("Erasing after NRE::Utility::DynamicArray last element.");
                 }
                 (*pos).~T();
                 shiftBack(index, 1);
                 length--;
                 return Iterator(data + index);
             }

             template <class T, std::size_t Size>
             inline typename DynamicArray<T, Size>::Iterator DynamicArray<T, Size>::erase(ConstIterator begin, ConstIterator end) {
                 std::size_t count = std::distance(begin, end);
                 std::size_t index = begin - ConstIterator(data);
                 if (index > length - count) {
                     throw std::out_of_range("Erasing after NRE::Utility::DynamicArray last element.");
                 }
                 for (auto it = begin; it != end; it++) {
                     (*it).~T();
                 }
                 shiftBack(index, count);
                 length -= count;
                 return Iterator(data + index + count);
             }

             template <class T, std::size_t Size>
             inline void DynamicArray<T, Size>::pushBack(T const& value) {
                 emplaceBack(value);
             }

             template <class T, std::size_t Size>
             inline void DynamicArray<T, Size>::pushBack(T && value) {
                 emplaceBack(std::move(value));
             }

             template <class T, std::size_t Size>
             template <class ... Args>
             inline void DynamicArray<T, Size>::emplaceBack(Args && ... args) {
                 if (Size < length + 1) {
                     throw std::out_of_range("Inserting more element than NRE::Utility::DynamicArray can handle.");
                 }
                 new(&data[length]) T (std::forward<Args>(args)...);
                 length++;
             }


             template <class T, std::size_t Size>
             inline void DynamicArray<T, Size>::resize(std::size_t count) {
                 resize(count, T());
             }

             template <class T, std::size_t Size>
             inline void DynamicArray<T, Size>::resize(std::size_t count, T const& value) {
                 if (count != length) {
                     if (count < length) {
                         for (std::size_t index = count; index != length; index++) {
                             data[index].~T();
                         }
                         length = count;
                     } else {
                         if (Size < count) {
                             throw std::out_of_range("Resizing past NRE::Utility::DynamicArray fixed capacity.");
                         }
                         for (std::size_t index = length; index < count; index++) {
                             new(&data[index]) T (value);
                         }
                         length = count;
                     }
                 }
             }

             template <class T, std::size_t Size>
             inline void DynamicArray<T, Size>::swap(DynamicArray& arr) {
                 using std::swap;
                 swap(length, arr.length);
                 swap(data, arr.data);
             }

             template <class T, std::size_t Size>
             inline T& DynamicArray<T, Size>::operator[](std::size_t index) {
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline T const& DynamicArray<T, Size>::operator[](std::size_t index) const {
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline DynamicArray<T, Size>& DynamicArray<T, Size>::operator =(DynamicArray const& arr) {
                 if (this != &arr) {
                     assign(arr.begin(), arr.end());
                 }
                 return *this;
             }

             template <class T, std::size_t Size>
             inline DynamicArray<T, Size>& DynamicArray<T, Size>::operator =(DynamicArray && arr) {
                 if (this != &arr) {
                     move(arr);
                     length = arr.length;
                     arr.length = 0;
                 }
                 return *this;
             }

             template <class T, std::size_t Size>
             inline bool DynamicArray<T, Size>::operator !=(DynamicArray const& arr) const {
                 return !(*this == arr);
             }

             template <class T, std::size_t Size>
             inline String DynamicArray<T, Size>::toString() const {
                 if (isEmpty()) {
                     String res;
                     res << '[' << ']';
                     return res;
                 } else {
                     String res;
                     res << '[' << data[0];
                     res.reserve((res.getSize() + 2) * length);
                     for (std::size_t index = 1; index < length; index++) {
                         res << ',' << ' ' << data[index];
                     }
                     res << ']';
                     return res;
                 }
             }

         }
     }
