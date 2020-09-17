
    /**
     * @file NRE_Array.tpp
     * @brief Implementation of Core's API's Container : Array
     * @author Louis ABEL
     * @date 16/05/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Core {

             template <class T, std::size_t Size>
             inline Array<T, Size>::Array(std::initializer_list<T> list) {
                 SizeType index = 0;
                 for (auto it = list.begin(); it != list.end(); it++) {
                     data[index++] = *it;
                 }
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::Reference Array<T, Size>::get(SizeType index) {
                 if (index >= Size) {
                     throw std::out_of_range("Accessing NRE::Core::Array element : " + std::to_string(index) + " while array has " + std::to_string(Size) + " maximum capacity.");
                 }
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstReference Array<T, Size>::get(SizeType index) const {
                 if (index >= Size) {
                     throw std::out_of_range("Accessing NRE::Core::Array element : " + std::to_string(index) + " while array has " + std::to_string(Size) + " maximum capacity.");
                 }
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::Pointer Array<T, Size>::getData() {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstPointer Array<T, Size>::getData() const {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::Reference Array<T, Size>::getFront() {
                 return data[0];
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstReference Array<T, Size>::getFront() const {
                 return data[0];
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::Reference Array<T, Size>::getLast() {
                 return data[Size - 1];
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstReference Array<T, Size>::getLast() const {
                 return data[Size - 1];
             }

             template <class T, std::size_t Size>
             constexpr bool Array<T, Size>::isEmpty() const {
                 return false;
             }

             template <class T, std::size_t Size>
             constexpr typename Array<T, Size>::SizeType Array<T, Size>::getSize() const {
                 return Size;
             }

             template <class T, std::size_t Size>
             constexpr typename Array<T, Size>::SizeType Array<T, Size>::getMaxSize() const {
                 return std::numeric_limits<SizeType>::max();
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::Iterator Array<T, Size>::begin() {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstIterator Array<T, Size>::begin() const {
                 return data;
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstIterator Array<T, Size>::cbegin() const {
                 return begin();
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::Iterator Array<T, Size>::end() {
                 return data + Size;
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstIterator Array<T, Size>::end() const {
                 return data + Size;
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstIterator Array<T, Size>::cend() const {
                 return end();
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ReverseIterator Array<T, Size>::rbegin() {
                 return ReverseIterator(data + Size);
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstReverseIterator Array<T, Size>::rbegin() const {
                 return ConstReverseIterator(data + Size);
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstReverseIterator Array<T, Size>::crbegin() const {
                 return rbegin();
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ReverseIterator Array<T, Size>::rend() {
                 return ReverseIterator(data);
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstReverseIterator Array<T, Size>::rend() const {
                 return ConstReverseIterator(data);
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstReverseIterator Array<T, Size>::crend() const {
                 return rend();
             }

             template <class T, std::size_t Size>
             inline void Array<T, Size>::fill(ConstReference value) {
                 for (SizeType i = 0; i < Size; i++) {
                     data[i] = value;
                 }
             }

             template <class T, std::size_t Size>
             inline void Array<T, Size>::swap(Array& arr) noexcept {
                 using std::swap;
                 swap(data, arr.data);
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::Reference Array<T, Size>::operator[](SizeType index) {
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstReference Array<T, Size>::operator[](SizeType index) const {
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline bool Array<T, Size>::operator !=(Array const& arr) const {
                 return !(*this == arr);
             }

             template <class T, std::size_t Size>
             inline String Array<T, Size>::toString() const {
                 String res;
                 res.reserve(5 * Size);
                 res << '[' << data[0];
                 for (SizeType index = 1; index < Size; index++) {
                     res << ',' << ' ' << data[index];
                 }
                 res << ']';
                 return res;
             }
         }
     }
