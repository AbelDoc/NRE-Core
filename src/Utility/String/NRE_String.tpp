
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
             inline BasicString<T>::BasicString() : length(0), capacity(1), data(static_cast <T*> (::operator new (sizeof(T)))) {
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
                 capacity = std::strlen(str) + 1;
                 data = static_cast <T*> (::operator new ((capacity) * sizeof(T)));
                 assign(capacity, str);
             }

             template <class T>
             template <class InputIterator>
             inline BasicString<T>::BasicString(InputIterator begin, InputIterator end) : length(std::distance(begin, end)), capacity(length), data(static_cast <T*> (::operator new ((length + 1) * sizeof(T)))) {
                 assign(begin, end);
             }

             template <class T>
             inline BasicString<T>::BasicString(std::initializer_list<T> init) : BasicString(init.begin(), init.end()) {
             }

             template <class T>
             inline BasicString<T>::BasicString(BasicString const& str) : length(str.length), capacity(str.capacity), data(static_cast <T*> (::operator new ((capacity + 1) * sizeof(T)))) {
                 assign(str);
             }

             template <class T>
             inline BasicString<T>::BasicString(BasicString && str) {
                 assign(std::move(str));
             }

             template <class T>
             inline BasicString<T>::~BasicString() {
                 ::operator delete(data);
                 data = nullptr;
                 length = 0;
                 capacity = 0;
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
             inline std::size_t BasicString<T>::getLength() const {
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
             inline bool BasicString<T>::isEmpty() const {
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
             inline typename BasicString<T>::ConstIterator BasicString<T>::cbegin() const {
                 return begin();
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
             inline typename BasicString<T>::ConstIterator BasicString<T>::cend() const {
                 return end();
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
             inline typename BasicString<T>::ConstReverseIterator BasicString<T>::crbegin() const {
                 return rbegin();
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
             inline typename BasicString<T>::ConstReverseIterator BasicString<T>::crend() const {
                 return rend();
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(std::size_t count, T value) {
                 length = 0;
                 return append(count, value);
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
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(std::size_t count, const T* str) {
                 length = 0;
                 return append(str, count);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(const T* str) {
                 length = 0;
                 return append(str);
             }

             template <class T>
             template <class InputIterator>
             inline BasicString<T>& BasicString<T>::assign(InputIterator begin, InputIterator end) {
                 length = 0;
                 return append(begin, end);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(std::initializer_list<T> init) {
                 return assign(init.begin(), init.end());
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
                 addNullTerminated();
             }

             template <class T>
             inline void BasicString<T>::reverse() {
                 reverse(0, length);
             }

             template <class T>
             inline void BasicString<T>::reverse(std::size_t pos, std::size_t count) {
                 std::size_t start = pos;
                 std::size_t end = pos + count - 1;
                 while (start < end) {
                     T value = data[start];
                     data[start] = data[end];
                     data[end] = value;
                     start++;
                     end--;
                 }
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
                 return insert(start, std::strlen(str), str);
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
                 return insert(start, str.getSize(), str.data);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(std::size_t start, BasicString const& str, std::size_t index, std::size_t count) {
                 return insert(start, str.substr(index, count));
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
                 return insert(start, list.begin(), list.end());
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::erase(std::size_t index, std::size_t count) {
                 if (index > length - 1) {
                     throw std::out_of_range("Erasing after NRE::Utility::String last element.");
                 }
                 shiftBack(index, count);
                 length -= count;
                 return *this;
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::erase(ConstIterator pos) {
                 std::size_t index = pos - ConstIterator(data);
                 if (index > length - 1) {
                     throw std::out_of_range("Erasing after NRE::Utility::String last element.");
                 }
                 shiftBack(index, 1);
                 length--;
                 return Iterator(data + index);
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::erase(ConstIterator begin, ConstIterator end) {
                 std::size_t count = std::distance(begin, end);
                 std::size_t index = begin - ConstIterator(data);
                 if (index > length - count) {
                     throw std::out_of_range("Erasing after NRE::Utility::String last element.");
                 }
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
             template <class K>
             inline BasicString<T>& BasicString<T>::append(K const& o) {
                 return append(o.toString());
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(bool value) {
                 if (value) {
                     append("true");
                 } else {
                     append("false");
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(T value) {
                 return append(1, value);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(short int value) {
                 char str[7];
                 std::sprintf(str, "%i", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(int value) {
                 char str[12];
                 std::sprintf(str, "%i", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(long int value) {
                 char str[21];
                 std::sprintf(str, "%li", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(long long int value) {
                 char str[21];
                 std::sprintf(str, "%lli", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(unsigned short int value) {
                 char str[6];
                 std::sprintf(str, "%u", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(unsigned int value) {
                 char str[11];
                 std::sprintf(str, "%u", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(unsigned long int value) {
                 char str[11];
                 std::sprintf(str, "%lu", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(unsigned long long int value) {
                 char str[21];
                 std::sprintf(str, "%llu", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(float value) {
                 char str[20];
                 std::sprintf(str, "%f", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(double value) {
                 char str[30];
                 std::sprintf(str, "%f", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(long double value) {
                 char str[30];
                 std::sprintf(str, "%Lf", value);
                 append(static_cast <const T*> (&str[0]));
                 return *this;
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
                 return append(str.data, str.getSize());
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
                 std::size_t count = std::strlen(str);
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 std::memcpy(data + length, str, (count + 1) * sizeof(T));
                 length += count;
                 return *this;
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
                 return append(list.begin(), list.end());
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
                 return compare(tPos, tCount, str, 0, std::strlen(str));
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
             inline bool BasicString<T>::startsWith(BasicString const& str) const {
                 return length >= str.getSize() && compare(0, str.getSize(), str) == 0;
             }

             template <class T>
             inline bool BasicString<T>::startsWith(T value) const {
                 return length >= 1 && data[0] == value;
             }

             template <class T>
             inline bool BasicString<T>::startsWith(const T* str) const {
                 std::size_t size = std::strlen(str);
                 return length >= size && compare(0, size, str, 0, size) == 0;
             }

             template <class T>
             inline bool BasicString<T>::endsWith(BasicString const& str) const {
                 return length >= str.getSize() && compare(length - 1 - str.getSize(), str.getSize(), str) == 0;
             }

             template <class T>
             inline bool BasicString<T>::endsWith(T value) const {
                 return length >= 1 && data[length - 1] == value;
             }

             template <class T>
             inline bool BasicString<T>::endsWith(const T* str) const {
                 std::size_t size = std::strlen(str);
                 return length >= size && compare(length - 1 - size, size, str, 0, size) == 0;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(std::size_t pos, std::size_t count, BasicString const& str) {
                 return replace(pos, count, str, 0, str.getSize());
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, BasicString const& str) {
                 std::size_t index = start - ConstIterator(data);
                 return replace(index, std::distance(start, end), str, 0, str.getSize());
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(std::size_t tPos, std::size_t tCount, BasicString const& str, std::size_t sPos, std::size_t sCount) {
                 return replace(tPos, tCount, str.data + sPos, sCount);
             }

             template <class T>
             template <class InputIterator>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator tStart, ConstIterator tEnd, BasicString const& str, InputIterator sStart, InputIterator sEnd) {
                 std::size_t index = tStart - ConstIterator(data);
                 return replace(index, std::distance(tStart, tEnd), str, sStart - InputIterator(str.data), std::distance(sStart, sEnd));
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(std::size_t pos, std::size_t tCount, const T* str, std::size_t sCount) {
                 if (tCount < sCount) {
                     if (capacity < length + (sCount - tCount)) {
                         reserveWithGrowFactor(length + (sCount - tCount));
                     }
                     shift(pos + tCount, sCount - tCount);
                     length += (sCount - tCount);
                     addNullTerminated();
                 } else {
                     shiftBack(pos + sCount, tCount - sCount);
                     length -= (tCount - sCount);
                 }
                 std::memcpy(data + pos, str, sCount * sizeof(T));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, const T* str, std::size_t sCount) {
                 std::size_t index = start - ConstIterator(data);
                 return replace(index, std::distance(start, end), str, sCount);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(std::size_t pos, std::size_t count, const T* str) {
                 return replace(pos, count, str, std::strlen(str));
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, const T* str) {
                 return replace(start, end, str, std::strlen(str));
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(std::size_t pos, std::size_t tCount, T value, std::size_t sCount) {
                 if (tCount < sCount) {
                     if (capacity < length + (sCount - tCount)) {
                         reserveWithGrowFactor(length + (sCount - tCount));
                     }
                     shift(pos + tCount, sCount - tCount);
                     length += (sCount - tCount);
                     addNullTerminated();
                 } else {
                     shiftBack(pos + sCount, tCount - sCount);
                     length -= (tCount - sCount);
                 }
                 for (std::size_t current = pos; current < pos + sCount; current++) {
                     data[current] = value;
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, T value, std::size_t sCount) {
                 return replace(start - ConstIterator(data), std::distance(start, end), value, sCount);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, std::initializer_list<T> list) {
                 std::size_t pos = start - ConstIterator(data);
                 std::size_t tCount = std::distance(start, end);
                 std::size_t sCount = list.size();
                 if (tCount < sCount) {
                     if (capacity < length + (sCount - tCount)) {
                         reserveWithGrowFactor(length + (sCount - tCount));
                     }
                     shift(pos + tCount, sCount - tCount);
                     length += (sCount - tCount);
                     addNullTerminated();
                 } else {
                     shiftBack(pos + sCount, tCount - sCount);
                     length -= (tCount - sCount);
                 }
                 auto it = list.begin();
                 for (std::size_t current = pos; current < pos + sCount; current++) {
                     data[current] = *(it);
                     it++;
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T> BasicString<T>::substr(std::size_t pos, std::size_t count) const {
                 BasicString sub;
                 sub.reserve(count);

                 std::memcpy(sub.data, data + pos, count * sizeof(T));
                 sub.length = count;
                 sub.addNullTerminated();
                 return sub;
             }

             template <class T>
             inline std::size_t BasicString<T>::copy(T* str, std::size_t pos, std::size_t count) const {
                 std::size_t copied = std::min(count, length);
                 std::memcpy(str, data + pos, copied);
                 return copied;
             }

             template <class T>
             inline void BasicString<T>::resize(std::size_t count) {
                 resize(count, T());
             }

             template <class T>
             inline void BasicString<T>::resize(std::size_t count, T value) {
                 if (count != length) {
                     if (count < length) {
                         length = count;
                     } else {
                         if (capacity < count) {
                             reallocate(count);
                         }
                         for (std::size_t index = length; index != count; index++) {
                             data[index] = value;
                         }
                         length = count;
                     }
                     addNullTerminated();
                 }
             }

             template <class T>
             inline void BasicString<T>::swap(BasicString& str) {
                 using std::swap;
                 swap(length, str.length);
                 swap(capacity, str.capacity);
                 swap(data, str.data);
             }

             template <class T>
             inline void BasicString<T>::shrinkToFit() {
                 reallocate(length);
             }

             template <class T>
             inline std::size_t BasicString<T>::find(BasicString const& str, std::size_t pos) const {
                 return find(str.length, str.data, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::find(std::size_t count, const T* str, std::size_t pos) const {
                 std::size_t res = NOT_FOUND;
                 std::size_t current = pos;
                 std::size_t needle = 0;

                 while (res == NOT_FOUND && current < length) {
                     if (data[current] == str[needle]) {
                         needle++;
                         if (needle == count) {
                             res = current - (count - 1);
                         }
                     } else {
                         current -= needle;
                         needle = 0;
                     }
                     current++;
                 }
                 return res;
             }

             template <class T>
             inline std::size_t BasicString<T>::find(const T* str, std::size_t pos) const {
                 return find(std::strlen(str), str, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::find(T value, std::size_t pos) const {
                 return find(1, &value, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::rfind(BasicString const& str, std::size_t pos) const {
                 return rfind(str.length, str.data, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::rfind(std::size_t count, const T* str, std::size_t pos) const {
                 std::size_t res = NOT_FOUND;
                 std::size_t current = pos;
                 std::size_t needle = count - 1;

                 while (res == NOT_FOUND && current != static_cast <std::size_t> (-1)) {
                     if (data[current] == str[needle]) {
                         needle--;
                         if (needle == static_cast <std::size_t> (-1)) {
                             res = current;
                         }
                     } else {
                         current += count - needle - 1;
                         needle = count - 1;
                     }
                     current--;
                 }
                 return res;
             }

             template <class T>
             inline std::size_t BasicString<T>::rfind(const T* str, std::size_t pos) const {
                 return rfind(std::strlen(str), str, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::rfind(T value, std::size_t pos) const {
                 return rfind(1, &value, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findFirstOf(BasicString const& str, std::size_t pos) const {
                 return findFirstOf(str.length, str.data, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findFirstOf(std::size_t count, const T* str, std::size_t pos) const {
                 std::size_t res = NOT_FOUND;
                 std::size_t current = pos;

                 while (res == NOT_FOUND && current < length) {
                     std::size_t needle = 0;
                     while (res == NOT_FOUND && needle < count) {
                         if (data[current] == str[needle]) {
                             res = current;
                         }
                         needle++;
                     }
                     current++;
                 }
                 return res;
             }

             template <class T>
             inline std::size_t BasicString<T>::findFirstOf(const T* str, std::size_t pos) const {
                 return findFirstOf(std::strlen(str), str, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findFirstOf(T value, std::size_t pos) const {
                 return findFirstOf(1, &value, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findFirstNotOf(BasicString const& str, std::size_t pos) const {
                 return findFirstNotOf(str.length, str.data, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findFirstNotOf(std::size_t count, const T* str, std::size_t pos) const {
                 std::size_t res = NOT_FOUND;
                 std::size_t current = pos;

                 while (res == NOT_FOUND && current < length) {
                     std::size_t needle = 0;
                     bool match = false;
                     while (!match && needle < count) {
                         if (data[current] == str[needle]) {
                             match = true;
                         }
                         needle++;
                     }
                     if (!match) {
                         res = current;
                     }
                     current++;
                 }
                 return res;
             }

             template <class T>
             inline std::size_t BasicString<T>::findFirstNotOf(const T* str, std::size_t pos) const {
                 return findFirstNotOf(std::strlen(str), str, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findFirstNotOf(T value, std::size_t pos) const {
                 return findFirstNotOf(1, &value, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findLastOf(BasicString const& str, std::size_t pos) const {
                 return findLastOf(str.length, str.data, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findLastOf(std::size_t count, const T* str, std::size_t pos) const {
                 std::size_t res = NOT_FOUND;
                 std::size_t current = pos;

                 while (res == NOT_FOUND && current != static_cast <std::size_t> (-1)) {
                     std::size_t needle = 0;
                     while (res == NOT_FOUND && needle < count) {
                         if (data[current] == str[needle]) {
                             res = current;
                         }
                         needle++;
                     }
                     current--;
                 }
                 return res;
             }

             template <class T>
             inline std::size_t BasicString<T>::findLastOf(const T* str, std::size_t pos) const {
                 return findLastOf(std::strlen(str), str, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findLastOf(T value, std::size_t pos) const {
                 return findLastOf(1, &value, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findLastNotOf(BasicString const& str, std::size_t pos) const {
                 return findLastNotOf(str.length, str.data, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findLastNotOf(std::size_t count, const T* str, std::size_t pos) const {
                 std::size_t res = NOT_FOUND;
                 std::size_t current = pos;

                 while (res == NOT_FOUND && current != static_cast <std::size_t> (-1)) {
                     std::size_t needle = 0;
                     bool match = false;
                     while (!match && needle < count) {
                         if (data[current] == str[needle]) {
                             match = true;
                         }
                         needle++;
                     }
                     if (!match) {
                         res = current;
                     }
                     current--;
                 }
                 return res;
             }

             template <class T>
             inline std::size_t BasicString<T>::findLastNotOf(const T* str, std::size_t pos) const {
                 return findLastNotOf(std::strlen(str), str, pos);
             }

             template <class T>
             inline std::size_t BasicString<T>::findLastNotOf(T value, std::size_t pos) const {
                 return findLastNotOf(1, &value, pos);
             }

             template <class T>
             inline T& BasicString<T>::operator[](std::size_t index) {
                 return data[index];
             }

             template <class T>
             inline T const& BasicString<T>::operator[](std::size_t index) const {
                 return data[index];
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(BasicString const& str) {
                 if (str.data != data) {
                     assign(str);
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(BasicString && str) {
                 if (str.data != data) {
                     assign(std::move(str));
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(const T* str) {
                 if (str != data) {
                     assign(str);
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(T value) {
                 return assign(1, value);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(std::initializer_list<T> list) {
                 return assign(list);
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
             inline bool BasicString<T>::operator==(BasicString const& str) const {
                 if (length != str.length) {
                     return false;
                 }
                 return std::memcmp(data, str.data, length * sizeof(T)) == 0;
             }

             template <class T>
             inline bool BasicString<T>::operator!=(BasicString const& str) const {
                 return !(*this == str);
             }

             template <class T>
             inline bool BasicString<T>::operator<(BasicString const& str) const {
                 return std::memcmp(data, str.data, length * sizeof(T)) < 0;
             }

             template <class T>
             inline bool BasicString<T>::operator<=(BasicString const& str) const {
                 return std::memcmp(data, str.data, length * sizeof(T)) <= 0;
             }

             template <class T>
             inline bool BasicString<T>::operator>(BasicString const& str) const {
                 return std::memcmp(data, str.data, length * sizeof(T)) > 0;
             }

             template <class T>
             inline bool BasicString<T>::operator>=(BasicString const& str) const {
                 return std::memcmp(data, str.data, length * sizeof(T)) >= 0;
             }

             template <class T>
             inline BasicString<T> const& BasicString<T>::toString() const {
                 return *this;
             }

             template <class T>
             template <class K>
             inline BasicString<T>& BasicString<T>::operator<<(K const& o) {
                 return append(o);
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
                 std::memmove(data + start, data + start + count, (length + 1 - start) * sizeof(T));
             }

             template <class T>
             std::ostream& operator <<(std::ostream& stream, BasicString<T> const& o) {
                 return stream.write(o.getData(), o.getSize());
             }

             template <class T>
             std::istream& operator >>(std::istream& stream, BasicString<T>& o) {
                 if (!stream.eof()) {
                     T current = static_cast <T> (stream.get());
                     bool endRead = stream.eof() || std::isspace(current, stream.getloc());
                     while (!endRead) {
                         o.append(1, current);
                         current = static_cast <T> (stream.get());
                         endRead = stream.eof() || std::isspace(current, stream.getloc());
                     }
                 }
                 return stream;
             }

             template <class T>
             inline BasicString<T> operator+(BasicString<T> const& lhs, BasicString<T> const& rhs) {
                 return BasicString<T>(lhs).append(rhs);
             }

             template <class T>
             inline BasicString<T> operator+(const T* lhs, BasicString<T> const& rhs) {
                 return BasicString<T>(lhs).append(rhs);
             }

             template <class T>
             inline BasicString<T> operator+(T lhs, BasicString<T> const& rhs) {
                 return BasicString<T>(1, lhs).append(rhs);
             }

             template <class T>
             inline BasicString<T> operator+(BasicString<T> const& lhs, const T* rhs) {
                return BasicString<T>(lhs).append(rhs);
             }

             template <class T>
             inline BasicString<T> operator+(BasicString<T> const& lhs, T rhs) {
                 return BasicString<T>(lhs).append(1, rhs);
             }

             template <class T>
             inline BasicString<T> operator+(BasicString<T> && lhs, BasicString<T> const& rhs) {
                 return std::move(lhs.append(rhs));
             }

             template <class T>
             inline BasicString<T> operator+(BasicString<T> const& lhs, BasicString<T> && rhs) {
                 return std::move(rhs.insert(0, lhs));
             }

             template <class T>
             inline BasicString<T> operator+(BasicString<T> && lhs, BasicString<T> && rhs) {
                 return std::move(lhs.append(rhs));
             }

             template <class T>
             inline BasicString<T> operator+(const T* lhs, BasicString<T> && rhs) {
                 return std::move(rhs.insert(0, lhs));
             }

             template <class T>
             inline BasicString<T> operator+(T lhs, BasicString<T> && rhs) {
                 return std::move(rhs.insert(static_cast <std::size_t> (0), static_cast <std::size_t> (1), lhs));
             }

             template <class T>
             inline BasicString<T> operator+(BasicString<T> && lhs, const T* rhs) {
                 return std::move(lhs.append(rhs));
             }

             template <class T>
             inline BasicString<T> operator+(BasicString<T> && lhs, T rhs) {
                 return std::move(lhs.append(1, rhs));
             }

         }
     }