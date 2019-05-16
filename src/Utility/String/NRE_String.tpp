
    /**
     * @file NRE_String.tpp
     * @brief Implementation of Utility's API's Container : String
     * @author Louis ABEL
     * @date 16/05/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace Utility {

             template <class T>
             inline BasicString<T>::BasicString() : length(0), capacity(1), data(static_cast <T*> (::operator new (2 * sizeof(T)))) {
                 addNullTerminated();
             }

             template <class T>
             inline BasicString<T>::BasicString(std::size_t count, T value) : length(count), capacity(count), data(static_cast <T*> (::operator new ((count + 1) * sizeof(T)))) {
                 assign(count, value);
             }

             template <class T>
             inline BasicString<T>::BasicString(std::size_t pos, std::size_t count, BasicString const& str) : length(count), capacity(count), data(static_cast <T*> (::operator new ((count + 1) * sizeof(T)))) {
                 assign(pos, count, str);
             }

             template <class T>
             inline BasicString<T>::BasicString(std::size_t count, const T* str) : length(count), capacity(count), data(static_cast <T*> (::operator new ((count + 1) * sizeof(T)))) {
                 assign(count, str);
             }

             template <class T>
             inline BasicString<T>::BasicString(const T* str) {
                 std::size_t count = 0;
                 while (str[count] != '\0') {
                     count++;
                 }
                 capacity = count;
                 data = static_cast <T*> (::operator new ((count + 1) * sizeof(T)));
                 assign(count, str);
             }

             template <class T>
             template <class InputIterator>
             inline BasicString<T>::BasicString(InputIterator begin, InputIterator end) : length(std::distance(begin, end)), capacity(length), data(static_cast <T*> (::operator new ((length + 1) * sizeof(T)))) {
                 assign(begin, end);
             }

             template <class T>
             inline BasicString<T>::BasicString(std::initializer_list<T> init) : length(init.size()), capacity(length), data(static_cast <T*> (::operator new ((length + 1) * sizeof(T)))) {
                 assign(init);
             }

             template <class T>
             inline BasicString<T>::BasicString(BasicString const& str) : length(str.length), capacity(str.capacity), data(static_cast <T*> (::operator new ((capacity + 1) * sizeof(T)))) {
                 assign(str);
             }

             template <class T>
             inline BasicString<T>::BasicString(BasicString && str) {
                 assign(str);
             }

             template <class T>
             inline BasicString<T>::~BasicString() {
                 ::operator delete(data);
             }

             template <class T>
             inline T& BasicString<T>::get(std::size_t index) {
                 if (index >= length) {
                     throw std::out_of_range("Accessing NRE::Utility::String element : " + std::to_string(index) + " while string length is " + std::to_string(length) + ".");
                 }
                 return data[index];
             }

             template <class T>
             inline T const& BasicString<T>::get(std::size_t index) const {
                 if (index >= length) {
                     throw std::out_of_range("Accessing NRE::Utility::String element : " + std::to_string(index) + " while string length is " + std::to_string(length) + ".");
                 }
                 return data[index];
             }

             template <class T>
             inline const T* BasicString<T>::getData() const {
                 return data;
             }

             template <class T>
             inline const T* BasicString<T>::getCData() const {
                 return data;
             }

             template <class T>
             inline T& BasicString<T>::getFront() {
                 return data[0];
             }

             template <class T>
             inline T const& BasicString<T>::getFront() const {
                 return data[0];
             }

             template <class T>
             inline T& BasicString<T>::getLast() {
                 return data[length - 1];
             }

             template <class T>
             inline T const& BasicString<T>::getLast() const {
                 return data[length - 1];
             }

             template <class T>
             inline std::size_t BasicString<T>::getSize() const {
                 return length;
             }

             template <class T>
             inline constexpr std::size_t BasicString<T>::getMaxSize() const {
                 return std::numeric_limits<std::size_t>::max();
             }

             template <class T>
             inline std::size_t BasicString<T>::getCapacity() const {
                 return capacity;
             }

             template <class T>
             inline constexpr bool BasicString<T>::isEmpty() const {
                 return length == 0;
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::begin() {
                 return data;
             }

             template <class T>
             inline typename BasicString<T>::ConstIterator BasicString<T>::begin() const {
                 return data;
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::end() {
                 return data + length;
             }

             template <class T>
             inline typename BasicString<T>::ConstIterator BasicString<T>::end() const {
                 return data + length;
             }

             template <class T>
             inline typename BasicString<T>::ReverseIterator BasicString<T>::rbegin() {
                 return ReverseIterator(data + length);
             }

             template <class T>
             inline typename BasicString<T>::ConstReverseIterator BasicString<T>::rbegin() const {
                 return ConstReverseIterator(data + length);
             }

             template <class T>
             inline typename BasicString<T>::ReverseIterator BasicString<T>::rend() {
                 return ReverseIterator(data);
             }

             template <class T>
             inline typename BasicString<T>::ConstReverseIterator BasicString<T>::rend() const {
                 return ConstReverseIterator(data);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(std::size_t count, T value) {
                 if (capacity < count) {
                     reserveWithGrowFactor(count);
                 }
                 for (std::size_t i = 0; i < count; i++) {
                     data[i] = *(new(&data[i]) T (value));
                 }
                 length = count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(BasicString const& str) {
                 return assign(str.length, str.data);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(std::size_t pos, std::size_t count, BasicString const& str) {
                 return assign(count, str.data + pos);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(BasicString && str) {
                 length = str.length;
                 capacity = str.capacity;
                 data = std::move(str.data);

                 str.length = 0;
                 str.capacity = 0;
                 str.data = nullptr;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(std::size_t count, const T* str) {
                 if (capacity < count) {
                     reserveWithGrowFactor(count);
                 }
                 std::memcpy(data, str, (count + 1) * sizeof(T));
                 length = count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(const T* str) {
                 std::size_t count = 0;
                 while (str[count] != 0) {
                     count++;
                 }
                 return assign(count, str);
             }

             template <class T>
             template <class InputIterator>
             inline BasicString<T>& BasicString<T>::assign(InputIterator begin, InputIterator end) {
                 std::size_t count = std::distance(begin, end);
                 if (capacity < count) {
                     reserveWithGrowFactor(count);
                 }
                 std::size_t current = 0;
                 for ( ; begin != end; begin++) {
                     data[current] = *(new(&data[current]) T (*(begin)));
                     current++;
                 }
                 length = count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(std::initializer_list<T> init) {
                 std::size_t count = init.size();
                 if (capacity < count) {
                     reserveWithGrowFactor(count);
                 }
                 std::size_t current = 0;
                 for (auto it = init.begin(); it != init.end(); it++) {
                     data[current] = *(new(&data[current]) T (std::move(*it)));
                     current++;
                 }
                 length = count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(BasicString const& str) {
                 if (str.data != data) {
                     length = str.length;
                     capacity = str.capacity;
                     data = static_cast <T*> (::operator new((capacity + 1) * sizeof(T)));
                     assign(str);
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(BasicString && str) {
                 if (str.data != data) {
                     assign(str);
                 }
                 return *this;
             }

             template <class T>
             inline void BasicString<T>::reallocate() {
                 reallocate((capacity == 1) ? (BASE_ALLOCATION_SIZE)
                                            : (static_cast <std::size_t> (static_cast <float> (capacity) * GROW_FACTOR)));
             }

             template <class T>
             inline void BasicString<T>::reallocate(std::size_t newSize) {
                 capacity = newSize;
                 T* newData = static_cast <T*> (::operator new((capacity + 1) * sizeof(T)));

                 std::memmove(newData, data, length * sizeof(T));
                 ::operator delete(data);
                 data = newData;
             }

             template <class T>
             inline void BasicString<T>::reserveWithGrowFactor(std::size_t size) {
                 std::size_t newSize = (capacity == 1) ? (BASE_ALLOCATION_SIZE)
                                                       : (static_cast <std::size_t> (static_cast <float> (capacity) * GROW_FACTOR));
                 while (newSize < size) {
                     newSize = static_cast <std::size_t> (static_cast <float> (newSize) * GROW_FACTOR);
                 }
                 reallocate(newSize);
             }

             template <class T>
             inline void BasicString<T>::addNullTerminated() {
                 data[length] = '\0';
             }

         }
     }
