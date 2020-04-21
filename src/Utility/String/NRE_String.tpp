
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
             inline BasicString<T>::BasicString() : length(0), capacity(0), data(static_cast <Pointer> (::operator new ((capacity + 1) * sizeof(ValueType)))) {
                 addNullTerminated();
             }

             template <class T>
             inline BasicString<T>::BasicString(SizeType count, ValueType value) : length(count), capacity(count), data(static_cast <Pointer> (::operator new ((capacity + 1) * sizeof(ValueType)))) {
                 assign(count, value);
             }

             template <class T>
             inline BasicString<T>::BasicString(SizeType pos, SizeType count, BasicString const& str) : length(count), capacity(count), data(static_cast <Pointer> (::operator new ((capacity + 1) * sizeof(ValueType)))) {
                 assign(pos, count, str);
             }

             template <class T>
             inline BasicString<T>::BasicString(SizeType count, ConstPointer str) : length(count), capacity(count), data(static_cast <Pointer> (::operator new ((capacity + 1) * sizeof(ValueType)))) {
                 assign(count, str);
             }

             template <class T>
             inline BasicString<T>::BasicString(ConstPointer str) {
                 capacity = std::strlen(str);
                 data = static_cast <Pointer> (::operator new ((capacity + 1) * sizeof(ValueType)));
                 assign(capacity, str);
             }

             template <class T>
             template <class InputIterator>
             inline BasicString<T>::BasicString(InputIterator begin, InputIterator end) : length(std::distance(begin, end)), capacity(length), data(static_cast <Pointer> (::operator new ((length + 1) * sizeof(ValueType)))) {
                 assign(begin, end);
             }

             template <class T>
             inline BasicString<T>::BasicString(std::initializer_list<T> init) : BasicString(init.begin(), init.end()) {
             }

             template <class T>
             inline BasicString<T>::BasicString(BasicString const& str) : length(str.length), capacity(str.capacity), data(static_cast <Pointer> (::operator new ((capacity + 1) * sizeof(ValueType)))) {
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
             inline typename BasicString<T>::Reference BasicString<T>::get(SizeType index) {
                 if (index >= length) {
                     throw std::out_of_range("Accessing NRE::Utility::String element : " + std::to_string(index) + " while string length is " + std::to_string(length) + ".");
                 }
                 return data[index];
             }

             template <class T>
             inline typename BasicString<T>::ConstReference BasicString<T>::get(SizeType index) const {
                 if (index >= length) {
                     throw std::out_of_range("Accessing NRE::Utility::String element : " + std::to_string(index) + " while string length is " + std::to_string(length) + ".");
                 }
                 return data[index];
             }

             template <class T>
             inline typename BasicString<T>::ConstPointer BasicString<T>::getData() const {
                 return data;
             }

             template <class T>
             inline typename BasicString<T>::ConstPointer BasicString<T>::getCData() const {
                 return data;
             }

             template <class T>
             inline typename BasicString<T>::Reference BasicString<T>::getFront() {
                 return data[0];
             }

             template <class T>
             inline typename BasicString<T>::ConstReference BasicString<T>::getFront() const {
                 return data[0];
             }

             template <class T>
             inline typename BasicString<T>::Reference BasicString<T>::getLast() {
                 return data[length - 1];
             }

             template <class T>
             inline typename BasicString<T>::ConstReference BasicString<T>::getLast() const {
                 return data[length - 1];
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::getSize() const {
                 return length;
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::getLength() const {
                 return length;
             }

             template <class T>
             constexpr typename BasicString<T>::SizeType BasicString<T>::getMaxSize() const {
                 return std::numeric_limits<SizeType>::max();
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::getCapacity() const {
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
             inline BasicString<T>& BasicString<T>::assign(SizeType count, ValueType value) {
                 length = 0;
                 return append(count, value);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(BasicString const& str) {
                 return assign(str.length, str.data);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(SizeType pos, SizeType count, BasicString const& str) {
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
             inline BasicString<T>& BasicString<T>::assign(SizeType count, ConstPointer str) {
                 length = 0;
                 return append(str, count);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::assign(ConstPointer str) {
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
             inline void BasicString<T>::reserve(SizeType size) {
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
             inline void BasicString<T>::reverse(SizeType pos, SizeType count) {
                 SizeType start = pos;
                 SizeType end = pos + count - 1;
                 while (start < end) {
                     ValueType value = data[start];
                     data[start] = data[end];
                     data[end] = value;
                     start++;
                     end--;
                 }
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(SizeType start, SizeType count, ValueType value) {
                 if (start > length) {
                     throw std::out_of_range("Inserting after NRE::Utility::String last element.");
                 }
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 if (start == length) {
                     for (SizeType it = start; it != start + count; it++) {
                         data[it] = value;
                     }
                     length += count;
                     addNullTerminated();
                 } else {
                     shift(start, count);
                     for (SizeType it = start; it != start + count; it++) {
                         data[it] = value;
                     }
                     length += count;
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(SizeType start, ConstPointer str) {
                 return insert(start, std::strlen(str), str);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(SizeType start,  SizeType count, ConstPointer str) {
                 if (start > length) {
                     throw std::out_of_range("Inserting after NRE::Utility::String last element.");
                 }
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 if (start == length) {
                     std::memcpy(data + start, str, count * sizeof(ValueType));
                     length += count;
                     addNullTerminated();
                 } else {
                     shift(start, count);
                     std::memcpy(data + start, str, count * sizeof(ValueType));
                     length += count;
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(SizeType start, BasicString const& str) {
                 return insert(start, str.getSize(), str.data);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::insert(SizeType start, BasicString const& str, SizeType index, SizeType count) {
                 return insert(start, str.substr(index, count));
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::insert(ConstIterator start, ValueType value) {
                 SizeType index = start - ConstIterator(data);
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
             inline typename BasicString<T>::Iterator BasicString<T>::insert(ConstIterator start, SizeType count, ValueType value) {
                 SizeType index = start - ConstIterator(data);
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 if (index == length) {
                     for (SizeType it = index; it != index + count; it++) {
                         data[it] = value;
                     }
                     length += count;
                     addNullTerminated();
                 } else {
                     shift(index, count);
                     for (SizeType it = index; it != index + count; it++) {
                         data[it] = value;
                     }
                     length += count;
                 }
                 return Iterator(data + index + count);
             }

             template <class T>
             template <class InputIterator>
             inline typename BasicString<T>::Iterator BasicString<T>::insert(ConstIterator start, InputIterator begin, InputIterator end) {
                 SizeType count = std::distance(begin, end);
                 SizeType index = start - ConstIterator(data);
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 if (index == length) {
                     SizeType current = index;
                     for ( ; begin != end; begin++) {
                         data[current] = *begin;
                         current++;
                     }
                     length += count;
                     addNullTerminated();
                 } else {
                     shift(index, count);
                     SizeType current = index;
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
             inline BasicString<T>& BasicString<T>::erase(SizeType index, SizeType count) {
                 if (index > length - count) {
                     throw std::out_of_range("Erasing after NRE::Utility::String last element.");
                 }
                 if (index == length - count) {
                     length -= count;
                     addNullTerminated();
                 } else {
                     shiftBack(index, count);
                     length -= count;
                 }
                 return *this;
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::erase(ConstIterator pos) {
                 SizeType index = pos - ConstIterator(data);
                 erase(index, 1);
                 return Iterator(data + index);
             }

             template <class T>
             inline typename BasicString<T>::Iterator BasicString<T>::erase(ConstIterator begin, ConstIterator end) {
                 SizeType count = std::distance(begin, end);
                 SizeType index = begin - ConstIterator(data);
                 erase(index, count);
                 return Iterator(data + index + count);
             }

             template <class T>
             inline void BasicString<T>::pushBack(ValueType value) {
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
             inline BasicString<T>& BasicString<T>::append(bool value) {
                 if (value) {
                     append("true");
                 } else {
                     append("false");
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(ValueType value) {
                 return append(1, value);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(short int value) {
                 char str[7];
                 std::sprintf(str, "%i", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(int value) {
                 char str[12];
                 std::sprintf(str, "%i", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(long int value) {
                 char str[21];
                 std::sprintf(str, "%li", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(long long int value) {
                 char str[21];
                 std::sprintf(str, "%lli", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(unsigned short int value) {
                 char str[6];
                 std::sprintf(str, "%u", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(unsigned int value) {
                 char str[11];
                 std::sprintf(str, "%u", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(unsigned long int value) {
                 char str[11];
                 std::sprintf(str, "%lu", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(unsigned long long int value) {
                 char str[21];
                 std::sprintf(str, "%llu", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(float value) {
                 char str[20];
                 std::sprintf(str, "%f", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(double value) {
                 char str[30];
                 std::sprintf(str, "%f", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(long double value) {
                 char str[30];
                 std::sprintf(str, "%Lf", value);
                 append(static_cast <ConstPointer> (&str[0]));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(SizeType count, ValueType value) {
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 for (SizeType index = length; index < length + count; index++) {
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
             inline BasicString<T>& BasicString<T>::append(BasicString const& str, SizeType index, SizeType count) {
                 return append(str.data + index, count);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(ConstPointer str, SizeType count) {
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 std::memcpy(data + length, str, count * sizeof(ValueType));
                 length += count;
                 addNullTerminated();
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(ConstPointer str) {
                 SizeType count = std::strlen(str);
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 std::memcpy(data + length, str, (count + 1) * sizeof(ValueType));
                 length += count;
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::append(std::string const& str) {
                 return append(str.c_str(), str.size());
             }

             template <class T>
             template <class InputIterator>
             inline BasicString<T>& BasicString<T>::append(InputIterator begin, InputIterator end) {
                 SizeType count = std::distance(begin, end);
                 if (capacity < length + count) {
                     reserveWithGrowFactor(length + count);
                 }
                 SizeType current = length;
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
             inline int BasicString<T>::compare(SizeType tPos, SizeType tCount, BasicString const& str) const {
                 return compare(tPos, tCount, str.data, 0, str.length);
             }

             template <class T>
             inline int BasicString<T>::compare(SizeType tPos, SizeType tCount, BasicString const& str, SizeType sPos, SizeType sCount) const {
                 return compare(tPos, tCount, str.data, sPos, sCount);
             }

             template <class T>
             inline int BasicString<T>::compare(ConstPointer str) const {
                 return compare(0, length, str);
             }

             template <class T>
             inline int BasicString<T>::compare(SizeType tPos, SizeType tCount, ConstPointer str) const {
                 return compare(tPos, tCount, str, 0, std::strlen(str));
             }

             template <class T>
             inline int BasicString<T>::compare(SizeType tPos, SizeType tCount, ConstPointer str, SizeType sPos, SizeType sCount) const {
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
             inline bool BasicString<T>::startsWith(ValueType value) const {
                 return length >= 1 && data[0] == value;
             }

             template <class T>
             inline bool BasicString<T>::startsWith(ConstPointer str) const {
                 SizeType size = std::strlen(str);
                 return length >= size && compare(0, size, str, 0, size) == 0;
             }

             template <class T>
             inline bool BasicString<T>::endsWith(BasicString const& str) const {
                 return length >= str.getSize() && compare(length - 1 - str.getSize(), str.getSize(), str) == 0;
             }

             template <class T>
             inline bool BasicString<T>::endsWith(ValueType value) const {
                 return length >= 1 && data[length - 1] == value;
             }

             template <class T>
             inline bool BasicString<T>::endsWith(ConstPointer str) const {
                 SizeType size = std::strlen(str);
                 return length >= size && compare(length - 1 - size, size, str, 0, size) == 0;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(SizeType pos, SizeType count, BasicString const& str) {
                 return replace(pos, count, str, 0, str.getSize());
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, BasicString const& str) {
                 SizeType index = start - ConstIterator(data);
                 return replace(index, std::distance(start, end), str, 0, str.getSize());
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(SizeType tPos, SizeType tCount, BasicString const& str, SizeType sPos, SizeType sCount) {
                 return replace(tPos, tCount, str.data + sPos, sCount);
             }

             template <class T>
             template <class InputIterator>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator tStart, ConstIterator tEnd, BasicString const& str, InputIterator sStart, InputIterator sEnd) {
                 SizeType index = tStart - ConstIterator(data);
                 return replace(index, std::distance(tStart, tEnd), str, sStart - InputIterator(str.data), std::distance(sStart, sEnd));
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(SizeType pos, SizeType tCount, ConstPointer str, SizeType sCount) {
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
                 std::memcpy(data + pos, str, sCount * sizeof(ValueType));
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, ConstPointer str, SizeType sCount) {
                 SizeType index = start - ConstIterator(data);
                 return replace(index, std::distance(start, end), str, sCount);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(SizeType pos, SizeType count, ConstPointer str) {
                 return replace(pos, count, str, std::strlen(str));
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, ConstPointer str) {
                 return replace(start, end, str, std::strlen(str));
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(SizeType pos, SizeType tCount, ValueType value, SizeType sCount) {
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
                 for (SizeType current = pos; current < pos + sCount; current++) {
                     data[current] = value;
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, ValueType value, SizeType sCount) {
                 return replace(start - ConstIterator(data), std::distance(start, end), value, sCount);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::replace(ConstIterator start, ConstIterator end, std::initializer_list<T> list) {
                 SizeType pos = start - ConstIterator(data);
                 SizeType tCount = std::distance(start, end);
                 SizeType sCount = list.size();
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
                 for (SizeType current = pos; current < pos + sCount; current++) {
                     data[current] = *(it);
                     it++;
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T> BasicString<T>::substr(SizeType pos, SizeType count) const {
                 BasicString sub;
                 sub.reserve(count);

                 std::memcpy(sub.data, data + pos, count * sizeof(ValueType));
                 sub.length = count;
                 sub.addNullTerminated();
                 return sub;
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::copy(Pointer str, SizeType pos, SizeType count) const {
                 SizeType copied = std::min(count, length);
                 std::memcpy(str, data + pos, copied);
                 return copied;
             }

             template <class T>
             inline void BasicString<T>::resize(SizeType count) {
                 resize(count, ValueType());
             }

             template <class T>
             inline void BasicString<T>::resize(SizeType count, ValueType value) {
                 if (count != length) {
                     if (count < length) {
                         length = count;
                     } else {
                         if (capacity < count) {
                             reallocate(count);
                         }
                         for (SizeType index = length; index != count; index++) {
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
             inline bool BasicString<T>::contains(ConstPointer str) const {
                 return find(str) != NOT_FOUND;
             }

             template <class T>
             inline bool BasicString<T>::contains(BasicString const& str) const {
                 return find(str) != NOT_FOUND;
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::find(BasicString const& str, SizeType pos) const {
                 return find(str.length, str.data, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::find(SizeType count, ConstPointer str, SizeType pos) const {
                 SizeType res = NOT_FOUND;
                 SizeType current = pos;
                 SizeType needle = 0;

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
             inline typename BasicString<T>::SizeType BasicString<T>::find(ConstPointer str, SizeType pos) const {
                 return find(std::strlen(str), str, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::find(ValueType value, SizeType pos) const {
                 return find(1, &value, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::rfind(BasicString const& str, SizeType pos) const {
                 return rfind(str.length, str.data, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::rfind(SizeType count, ConstPointer str, SizeType pos) const {
                 SizeType res = NOT_FOUND;
                 SizeType current = pos;
                 SizeType needle = count - 1;

                 while (res == NOT_FOUND && current != static_cast <SizeType> (-1)) {
                     if (data[current] == str[needle]) {
                         needle--;
                         if (needle == static_cast <SizeType> (-1)) {
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
             inline typename BasicString<T>::SizeType BasicString<T>::rfind(ConstPointer str, SizeType pos) const {
                 return rfind(std::strlen(str), str, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::rfind(ValueType value, SizeType pos) const {
                 return rfind(1, &value, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findFirstOf(BasicString const& str, SizeType pos) const {
                 return findFirstOf(str.length, str.data, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findFirstOf(SizeType count, ConstPointer str, SizeType pos) const {
                 SizeType res = NOT_FOUND;
                 SizeType current = pos;

                 while (res == NOT_FOUND && current < length) {
                     SizeType needle = 0;
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
             inline typename BasicString<T>::SizeType BasicString<T>::findFirstOf(ConstPointer str, SizeType pos) const {
                 return findFirstOf(std::strlen(str), str, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findFirstOf(ValueType value, SizeType pos) const {
                 return findFirstOf(1, &value, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findFirstNotOf(BasicString const& str, SizeType pos) const {
                 return findFirstNotOf(str.length, str.data, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findFirstNotOf(SizeType count, ConstPointer str, SizeType pos) const {
                 SizeType res = NOT_FOUND;
                 SizeType current = pos;

                 while (res == NOT_FOUND && current < length) {
                     SizeType needle = 0;
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
             inline typename BasicString<T>::SizeType BasicString<T>::findFirstNotOf(ConstPointer str, SizeType pos) const {
                 return findFirstNotOf(std::strlen(str), str, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findFirstNotOf(ValueType value, SizeType pos) const {
                 return findFirstNotOf(1, &value, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findLastOf(BasicString const& str, SizeType pos) const {
                 return findLastOf(str.length, str.data, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findLastOf(SizeType count, ConstPointer str, SizeType pos) const {
                 SizeType res = NOT_FOUND;
                 SizeType current = pos;

                 while (res == NOT_FOUND && current != static_cast <SizeType> (-1)) {
                     SizeType needle = 0;
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
             inline typename BasicString<T>::SizeType BasicString<T>::findLastOf(ConstPointer str, SizeType pos) const {
                 return findLastOf(std::strlen(str), str, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findLastOf(ValueType value, SizeType pos) const {
                 return findLastOf(1, &value, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findLastNotOf(BasicString const& str, SizeType pos) const {
                 return findLastNotOf(str.length, str.data, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findLastNotOf(SizeType count, ConstPointer str, SizeType pos) const {
                 SizeType res = NOT_FOUND;
                 SizeType current = pos;

                 while (res == NOT_FOUND && current != static_cast <SizeType> (-1)) {
                     SizeType needle = 0;
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
             inline typename BasicString<T>::SizeType BasicString<T>::findLastNotOf(ConstPointer str, SizeType pos) const {
                 return findLastNotOf(std::strlen(str), str, pos);
             }

             template <class T>
             inline typename BasicString<T>::SizeType BasicString<T>::findLastNotOf(ValueType value, SizeType pos) const {
                 return findLastNotOf(1, &value, pos);
             }

             template <class T>
             inline typename BasicString<T>::Reference BasicString<T>::operator[](SizeType index) {
                 return data[index];
             }

             template <class T>
             inline typename BasicString<T>::ConstReference BasicString<T>::operator[](SizeType index) const {
                 return data[index];
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(BasicString const& str) {
                 if (this != &str) {
                     assign(str);
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(BasicString && str) {
                 if (this != &str) {
                     assign(std::move(str));
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(ConstPointer str) {
                 if (str != data) {
                     assign(str);
                 }
                 return *this;
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator =(ValueType value) {
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
             inline BasicString<T>& BasicString<T>::operator+=(ValueType value) {
                 return append(value);
             }

             template <class T>
             inline BasicString<T>& BasicString<T>::operator+=(ConstPointer str) {
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
                 return std::memcmp(data, str.data, length * sizeof(ValueType)) == 0;
             }

             template <class T>
             inline bool BasicString<T>::operator!=(BasicString const& str) const {
                 return !(*this == str);
             }

             template <class T>
             inline bool BasicString<T>::operator<(BasicString const& str) const {
                 return std::memcmp(data, str.data, length * sizeof(ValueType)) < 0;
             }

             template <class T>
             inline bool BasicString<T>::operator<=(BasicString const& str) const {
                 return std::memcmp(data, str.data, length * sizeof(ValueType)) <= 0;
             }

             template <class T>
             inline bool BasicString<T>::operator>(BasicString const& str) const {
                 return std::memcmp(data, str.data, length * sizeof(ValueType)) > 0;
             }

             template <class T>
             inline bool BasicString<T>::operator>=(BasicString const& str) const {
                 return std::memcmp(data, str.data, length * sizeof(ValueType)) >= 0;
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
                 reallocate((capacity <= BASE_ALLOCATION_SIZE / 2) ? (BASE_ALLOCATION_SIZE) : (static_cast <SizeType> (static_cast <float> (capacity) * GROW_FACTOR)));
             }

             template <class T>
             inline void BasicString<T>::reallocate(SizeType newSize) {
                 capacity = newSize;
                 Pointer newData = static_cast <Pointer> (::operator new((capacity + 1) * sizeof(ValueType)));

                 std::memmove(newData, data, length * sizeof(ValueType));
                 ::operator delete(data);
                 data = newData;
             }

             template <class T>
             inline void BasicString<T>::reserveWithGrowFactor(SizeType size) {
                 SizeType newSize = (capacity <= BASE_ALLOCATION_SIZE / 2) ? (BASE_ALLOCATION_SIZE) : (static_cast <SizeType> (static_cast <float> (capacity) * GROW_FACTOR));
                 while (newSize < size) {
                     newSize = static_cast <SizeType> (static_cast <float> (newSize) * GROW_FACTOR);
                 }
                 reallocate(newSize);
             }

             template <class T>
             inline void BasicString<T>::addNullTerminated() {
                 data[length] = '\0';
             }

             template <class T>
             inline void BasicString<T>::shift(SizeType start, SizeType count) {
                 std::memmove(data + start + count, data + start, (length - start) * sizeof(ValueType));
             }

             template <class T>
             inline void BasicString<T>::shiftBack(SizeType start, SizeType count) {
                 std::memmove(data + start, data + start + count, (length + 1 - start) * sizeof(ValueType));
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

     namespace {
         inline std::size_t unalignedLoad(const char* p) {
             std::size_t result;
             __builtin_memcpy(&result, p, sizeof(result));
             return result;
         }

         #if __SIZEOF_SIZE_T__  == 8
            inline std::size_t loadBytes(const char* p, int n) {
                std::size_t result = 0;
                --n;
                do {
                    result = (result << 8) + static_cast <unsigned char> (p[n]);
                } while (--n >= 0);

                return result;
            }

            inline std::size_t shiftMix(std::size_t v) {
                return v ^ (v >> 47);
            }
         #endif
     }

     namespace std {

         #if __SIZEOF_SIZE_T__  == 4
             inline size_t hash<NRE::Utility::String>::operator()(NRE::Utility::String const& str) const {
                 constexpr size_t seed = static_cast <size_t> (0xc70f6907UL);
                 constexpr size_t m    = 0x5bd1e995;
                 size_t len = str.getSize();

                 size_t result = seed ^ len;
                 const char* buf = str.getCData();

                 // Mix 4 bytes at a time into the hash.
                 while (len >= 4) {
                  	 size_t k = unalignedLoad(buf);
                 	 k *= m;
                 	 k ^= k >> 24;
                	 k *= m;
                	 result *= m;
                	 result ^= k;
        	         buf += 4;
                	 len -= 4;
                 }

                 // Handle the last few bytes of the input array.
                 switch (len) {
                     case 3: {
                         result ^= static_cast<unsigned char>(buf[2]) << 16;
                         [[fallthrough]];
                     }
                     case 2: {
                         result ^= static_cast<unsigned char>(buf[1]) << 8;
                         [[fallthrough]];
                     }
                     case 1: {
                    	 result ^= static_cast<unsigned char>(buf[0]);
                     }
                     result *= m;
                 };

                 // Do a few final mixes of the hash.
                 result ^= result >> 13;
                 result *= m;
                 result ^= result >> 15;

                 return result;
             }
        #elif __SIZEOF_SIZE_T__ == 8
            inline size_t hash<NRE::Utility::String>::operator()(NRE::Utility::String const& str) const {
                constexpr size_t seed = static_cast <size_t> (0xc70f6907UL);
                constexpr size_t mul = (( static_cast <size_t> (0xc6a4a793UL)) << 32UL) + static_cast <size_t> (0x5bd1e995UL);
                size_t len = str.getSize();

                const char* const buf = str.getCData();

                // Remove the bytes not divisible by the sizeof(size_t).  This
                // allows the main loop to process the data as 64-bit integers.
                const int len_aligned = static_cast <int> (len & ~0x7);
                const char* const end = buf + len_aligned;

                size_t result = seed ^ (len * mul);

                for (const char* p = buf; p != end; p += 8) {
                    const size_t data = shiftMix(unalignedLoad(p) * mul) * mul;
                    result ^= data;
                    result *= mul;
                }

                if ((len & 0x7) != 0) {
                    const size_t data = loadBytes(end, len & 0x7);
                    result ^= data;
                    result *= mul;
                }

                result = shiftMix(result) * mul;
                result = shiftMix(result);
                return result;
            }
        #else
            inline size_t hash<NRE::Utility::String>::operator()(NRE::Utility::String const& str) const {
                constexpr size_t seed = static_cast <size_t> (0xc70f6907UL);
                size_t result = seed;
                const char* cptr = str.getCData();
                for (; len; --len) {
                    result = (result * 131) + *cptr++;
                }
                return result;
            }
        #endif
     }
