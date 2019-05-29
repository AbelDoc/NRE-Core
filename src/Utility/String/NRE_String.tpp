
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
                     data[i] = value;
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
                 while (str[count] != '\0') {
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
                     data[current++] = *begin;
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
                     data[current++] = std::move(*it);
                 }
                 length = count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline void BasicString<T>::reserve(std::size_t size) {
                 if (capacity < size) {
                     reallocate(size);
                 }
             }

             template <class T>
             inline void BasicString<T>::clear() {
                 length = 0;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(std::size_t start, std::size_t count, T value) {
                 if (start > length) {
                     throw std::out_of_range("Inserting after NRE::Utility::String last element.");
                 }
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 if (start == length) {
                     for (std::size_t it = start; it != start + count; it++) {
                         data[it] = value;
                     }
                     length += count;
                     addNullTerminated();
                 } else {
                     shift(start, count);
                     for (std::size_t it = start; it != start + count; it++) {
                         data[it] = value;
                     }
                     length += count;
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(std::size_t start, const T* str) {
                 std::size_t count = 0;
                 while (str[count] != '\0') {
                     count++;
                 }
                 insert(start, count, str);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(std::size_t start,  std::size_t count, const T* str) {
                 if (start > length) {
                     throw std::out_of_range("Inserting after NRE::Utility::String last element.");
                 }
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 if (start == length) {
                     std::memcpy(data + start, str, count * sizeof(T));
                     length += count;
                     addNullTerminated();
                 } else {
                     shift(start, count);
                     std::memcpy(data + start, str, count * sizeof(T));
                     length += count;
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(std::size_t start, BasicString const& str) {
                 return insert(start, str.size(), str.data);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(std::size_t start, BasicString const& str, std::size_t index, std::size_t count) {
                 return insert(start, count, str.substr(index, count));
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::insert(ConstIterator start, T value) {
                 std::size_t index = start - ConstIterator(data);
                 if (capacity < length + 1) {
                     reallocate();
                 }
                 if (index == length) {
                     data[index] = value;
                     length++;
                     addNullTerminated();
                 } else {
                     shift(index, 1);
                     length++;
                     data[index] = value;
                 }
                 return Iterator(data + index + 1);
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::insert(ConstIterator start, std::size_t count, T value) {
                 std::size_t index = start - ConstIterator(data);
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 if (index == length) {
                     for (std::size_t it = index; it != index + count; it++) {
                         data[it] = value;
                     }
                     length += count;
                     addNullTerminated();
                 } else {
                     shift(index, count);
                     for (std::size_t it = index; it != index + count; it++) {
                         data[it] = value;
                     }
                     length += count;
                 }
                 return Iterator(data + index + count);
             }

             template <class T>
             template <class InputIterator>
             inline typename BasicString<T>::Iterator BasicString<T>::insert(ConstIterator start, InputIterator begin, InputIterator end) {
                 std::size_t count = std::distance(begin, end);
                 std::size_t index = start - ConstIterator(data);
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 if (index == length) {
                     std::size_t current = index;
                     for ( ; begin != end; begin++) {
                         data[current] = *begin;
                         current++;
                     }
                     length += count;
                     addNullTerminated();
                 } else {
                     shift(index, count);
                     std::size_t current = index;
                     for ( ; begin != end; begin++) {
                         data[current] = *begin;
                         current++;
                     }
                     length += count;
                 }
                 return Iterator(data + index + count);
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::insert(ConstIterator start, std::initializer_list<T> list) {
                 std::size_t index = start - ConstIterator(data);
                 std::size_t count = list.size();
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 if (index == length) {
                     std::size_t current = index;
                     for (auto it = list.begin(); it != list.end(); it++) {
                         data[current++] = std::move(*it);
                     }
                     length += count;
                     addNullTerminated();
                 } else {
                     shift(index, count);
                     std::size_t current = index;
                     for (auto it = list.begin(); it != list.end(); it++) {
                         data[current++] = std::move(*it);
                     }
                     length += count;
                 }
                 return Iterator(data + index + count);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::erase(std::size_t index, std::size_t count) {
                 shiftBack(index, count);
                 length -= count;
                 return *this;
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::erase(ConstIterator pos) {
                 std::size_t index = pos - ConstIterator(data);
                 shiftBack(index, 1);
                 length--;
                 return Iterator(data + index);
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::erase(ConstIterator begin, ConstIterator end) {
                 std::size_t count = std::distance(begin, end);
                 std::size_t index = begin - ConstIterator(data);
                 shiftBack(index, count);
                 length -= count;
                 return Iterator(data + index + count);
             }

             template <class T>
             inline void BasicString<T>::pushBack(T value) {
                 if (capacity < length + 1) {
                     reallocate();
                 }
                 data[length] = value;
                 length++;
                 addNullTerminated();
             }

             template <class T>
             inline void BasicString<T>::popBack() {
                 length--;
                 addNullTerminated();
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(std::size_t count, T value) {
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 for (std::size_t index = length; index < length + count; index++) {
                     data[index] = value;
                 }
                 length += count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(BasicString const& str) {
                 return append(str.data, str.size());
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(BasicString const& str, std::size_t index, std::size_t count) {
                 return append(str.data + index, count);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(const T* str, std::size_t count) {
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 std::memcpy(data + length, str, count * sizeof(T));
                 length += count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(const T* str) {
                 std::size_t count = 0;
                 while (str[count] != '\0') {
                     count++;
                 }
                 return append(str, count);
             }

             template <class T>
             template <class InputIterator>
             inline BasicString<T>& BasicString<T>::append(InputIterator begin, InputIterator end) {
                 std::size_t count = std::distance(begin, end);
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 std::size_t current = length;
                 for ( ; begin != end; begin++) {
                     data[current++] = *begin;
                 }
                 length += count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(std::initializer_list<T> list) {
                 std::size_t count = list.size();
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 std::size_t current = length;
                 for (auto it = list.begin(); it != list.end(); it++) {
                     data[current++] = std::move(*it);
                 }
                 length += count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline int BasicString<T>::compare(BasicString const& str) const {
                 return compare(0, length, str.data, 0, str.length);
             }

             template <class T>
             inline int BasicString<T>::compare(std::size_t tPos, std::size_t tCount, BasicString const& str) const {
                 return compare(tPos, tCount, str.data, 0, str.length);
             }

             template <class T>
             inline int BasicString<T>::compare(std::size_t tPos, std::size_t tCount, BasicString const& str, std::size_t sPos, std::size_t sCount) const {
                 return compare(tPos, tCount, str.data, sPos, sCount);
             }

             template <class T>
             inline int BasicString<T>::compare(const T* str) const {
                 return compare(0, length, str);
             }

             template <class T>
             inline int BasicString<T>::compare(std::size_t tPos, std::size_t tCount, const T* str) const {
                 std::size_t count = 0;
                 while (str[count] != '\0') {
                     count++;
                 }
                 return compare(tPos, tCount, str, 0, count);
             }

             template <class T>
             inline int BasicString<T>::compare(std::size_t tPos, std::size_t tCount, const T* str, std::size_t sPos, std::size_t sCount) const {
                 if (tCount != sCount) {
                     if (tCount < sCount) {
                         return -1;
                     } else {
                         return 1;
                     }
                 }
                 return std::memcmp(data + tPos, str + sPos, tCount);
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
             inline BasicString<T>& BasicString<T>::operator+=(BasicString const& str) {
                 return append(str);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator+=(T value) {
                 return append(value);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator+=(const T* str) {
                 return append(str);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator+=(std::initializer_list<T> list) {
                 return append(list);
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

             template <class T>
             inline void BasicString<T>::shift(std::size_t start, std::size_t count) {
                 std::memmove(data + start + count, data + start, (length - start) * sizeof(T));
             }

             template <class T>
             inline void BasicString<T>::shiftBack(std::size_t start, std::size_t count) {
                 std::memmove(data + start, data + start + count, (length - start) * sizeof(T));
             }

         }
     }
