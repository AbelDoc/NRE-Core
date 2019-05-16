
    /**
     * @file NRE_Array.tpp
     * @brief Implementation of Utility's API's Container : Array
     * @author Louis ABEL
     * @date 16/05/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Utility {

             template <class T, std::size_t Size>
             template <class ... Args>
             inline Array<T, Size>::Array(Args && ... args) : data{static_cast <T> (std::forward<Args>(args))...} {
             }

             template <class T, std::size_t Size>
             inline Array<T, Size>::Array(Array const& arr) {
                 copy(arr);
             }

             template <class T, std::size_t Size>
             inline Array<T, Size>::Array(Array && arr) {
                 move(arr);
             }

             template <class T, std::size_t Size>
             inline T& Array<T, Size>::get(std::size_t index) {
                 if (index >= Size) {
                     throw std::out_of_range("Accessing NRE::Utility::Array element : " + std::to_string(index) + " while array has " + std::to_string(Size) + " maximum capacity.");
                 }
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline T const& Array<T, Size>::get(std::size_t index) const {
                 if (index >= Size) {
                     throw std::out_of_range("Accessing NRE::Utility::Array element : " + std::to_string(index) + " while array has " + std::to_string(Size) + " maximum capacity.");
                 }
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline T* Array<T, Size>::getData() {
                 return data;
             }

             template <class T, std::size_t Size>
             inline const T* Array<T, Size>::getData() const {
                 return data;
             }

             template <class T, std::size_t Size>
             inline T& Array<T, Size>::getFront() {
                 return data[0];
             }

             template <class T, std::size_t Size>
             inline T const& Array<T, Size>::getFront() const {
                 return data[0];
             }

             template <class T, std::size_t Size>
             inline T& Array<T, Size>::getLast() {
                 return data[Size - 1];
             }

             template <class T, std::size_t Size>
             inline T const& Array<T, Size>::getLast() const {
                 return data[Size - 1];
             }

             template <class T, std::size_t Size>
             inline constexpr bool Array<T, Size>::isEmpty() const {
                 return Size == 0;
             }

             template <class T, std::size_t Size>
             inline constexpr std::size_t Array<T, Size>::getSize() const {
                 return Size;
             }

             template <class T, std::size_t Size>
             inline constexpr std::size_t Array<T, Size>::getMaxSize() const {
                 return Size;
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
             inline typename Array<T, Size>::Iterator Array<T, Size>::end() {
                 return data + Size;
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstIterator Array<T, Size>::end() const {
                 return data + Size;
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
             inline typename Array<T, Size>::ReverseIterator Array<T, Size>::rend() {
                 return ReverseIterator(data);
             }

             template <class T, std::size_t Size>
             inline typename Array<T, Size>::ConstReverseIterator Array<T, Size>::rend() const {
                 return ConstReverseIterator(data);
             }

             template <class T, std::size_t Size>
             inline void Array<T, Size>::fill(T const& value) {
                 for (std::size_t i = 0; i < Size; i++) {
                     data[i] = value;
                 }
             }

             template <class T, std::size_t Size>
             inline void Array<T, Size>::swap(Array& arr) noexcept {
                 using namespace std;
                 swap(data, arr.data);
             }

             template <class T, std::size_t Size>
             inline T& Array<T, Size>::operator[](std::size_t index) {
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline T const& Array<T, Size>::operator[](std::size_t index) const {
                 return data[index];
             }

             template <class T, std::size_t Size>
             inline Array<T, Size>& Array<T, Size>::operator =(Array const& arr) {
                 copy(arr);
                 return *this;
             }

             template <class T, std::size_t Size>
             inline Array<T, Size>& Array<T, Size>::operator =(Array && arr) {
                 move(arr);
                 return *this;
             }

             template <class T, std::size_t Size>
             inline bool Array<T, Size>::operator !=(Array const& arr) const {
                 return !(*this == arr);
             }

         }
     }
