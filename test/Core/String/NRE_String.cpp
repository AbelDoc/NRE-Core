
    /**
     * @file NRE_String.cpp
     * @brief Test of Core's API's Container : String
     * @author Louis ABEL
     * @date 20/06/2019
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Core.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Core;
    using namespace NRE::Tester;

    TEST(String, DefaultCtr) {
        String str;
        assertEquals(this, str.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, str, String(""));
    }

    TEST(String, CtrFill) {
        String str(10, 'a');
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("aaaaaaaaaa"));
    }

    TEST(String, CtrStrRange) {
        String ctr("abcdefg");
        String str(0, 7, ctr);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (7));
        assertEquals(this, str, String("abcdefg"));
        String str2(3, 4, ctr);
        assertEquals(this, str2.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, str2, String("defg"));
    }

    TEST(String, CtrStrStart) {
        String str(10, "abcdefghijklmnop");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
    }

    TEST(String, CtrStr) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
    }

    TEST(String, CtrInput) {
        std::string input("abcdefghij");
        String str(input.begin(), input.end());
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
    }

    TEST(String, CtrList) {
        String str({'a', 'b', 'c', 'd', 'e'});
        assertEquals(this, str.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, str, String("abcde"));
    }

    TEST(String, CopyCtr) {
        String str("abcdefghij");
        String copy(str);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, copy, String("abcdefghij"));
    }

    TEST(String, Move) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        String move(std::move(str));
        assertEquals(this, str.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, move.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, move, String("abcdefghij"));
    }

    TEST(String, Get) {
        String str("abcdefghij");
        assertEquals(this, str.get(9), 'j');
    }

    TEST(String, Data) {
        String str("abcdefghij");
        assertNotNull(this, static_cast <const void*> (str.getData()));
        assertEquals(this, str.getData(), static_cast <const char*> (&str.get(0)));
    }

    TEST(String, Front) {
        String str("abcdefghij");
        assertEquals(this, str.getFront(), 'a');
    }

    TEST(String, Last) {
        String str("abcdefghij");
        assertEquals(this, str.getLast(), 'j');
    }

    TEST(String, Size) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
    }

    TEST(String, Length) {
        String str("abcdefghij");
        assertEquals(this, str.getLength(), static_cast <std::size_t> (10));
    }

    TEST(String, MaxSize) {
        String str("abcdefghij");
        assertEquals(this, str.getMaxSize(), std::numeric_limits<std::size_t>::max());
    }

    TEST(String, Capacity) {
        String str;
        assertGreaterOrEquals(this, str.getCapacity(), static_cast <std::size_t> (0));
        str = "abcdefghij";
        assertGreaterOrEquals(this, str.getCapacity(), static_cast <std::size_t> (10));
    }

    TEST(String, Empty) {
        String str;
        assertTrue(this, str.isEmpty());
    }

    TEST(String, NotEmpty) {
        String str("abcdefghij");
        assertFalse(this, str.isEmpty());
    }

    TEST(String, Begin) {
        String str("abcdefghij");
        assertEquals(this, *(str.begin()), 'a');
    }

    TEST(String, End) {
        String str("abcdefghij");
        assertEquals(this, *(str.end() - 1), 'j');
    }

    TEST(String, ReverseBegin) {
        String str("abcdefghij");
        assertEquals(this, *(str.rbegin()), 'j');
    }

    TEST(String, ReverseEnd) {
        String str("abcdefghij");
        assertEquals(this, *(str.rend() - 1), 'a');
    }

    TEST(String, AssignFill) {
        String str;
        assertEquals(this, str.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, str, String(""));
        str.assign(10, 'a');
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("aaaaaaaaaa"));
        str.assign(2, 'b');
        assertEquals(this, str.getSize(), static_cast <std::size_t> (2));
        assertEquals(this, str, String("bb"));
    }

    TEST(String, AssignCopy) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        String assign("bb");
        str.assign(assign);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (2));
        assertEquals(this, str, String("bb"));
    }

    TEST(String, AssignStrRange) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        String assign("aaaabbbb");
        str.assign(0, 8, assign);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, str, String("aaaabbbb"));
        str.assign(2, 4, assign);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, str, String("aabb"));
    }

    TEST(String, AssignMove) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        String assign("aaaabbbb");
        assertEquals(this, assign.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, assign, String("aaaabbbb"));
        str.assign(std::move(assign));
        assertEquals(this, assign.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, str.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, AssignStrStart) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        str.assign(4, "aabbbbb");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, str, String("aabb"));
    }

    TEST(String, AssignStr) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        str.assign("aabbbbb");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (7));
        assertEquals(this, str, String("aabbbbb"));
    }

    TEST(String, AssignInput) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        std::string input("aaaabbbb");
        str.assign(input.begin(), input.end());
        assertEquals(this, str.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, AssignList) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        str.assign({'z', 'x', 'y'});
        assertEquals(this, str.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, str, String("zxy"));
    }

    TEST(String, Reserve) {
        String str;
        assertGreaterOrEquals(this, str.getCapacity(), static_cast <std::size_t> (0));
        str.reserve(100);
        assertEquals(this, str.getCapacity(), static_cast <std::size_t> (100));
    }

    TEST(String, Clear) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        str.clear();
        assertEquals(this, str.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, str, String(""));
    }

    TEST(String, Reverse) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        str.reverse();
        assertEquals(this, str, String("jihgfedcba"));
    }

    TEST(String, ReversePart) {
        String str("abcdefghij");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("abcdefghij"));
        str.reverse(0, 4);
        assertEquals(this, str, String("dcbaefghij"));
        str.reverse(6, 4);
        assertEquals(this, str, String("dcbaefjihg"));
    }

    TEST(String, InsertCopyVal) {
        String str("aaaa");
        str.insert(static_cast <std::size_t> (0), 2, 'b');
        assertEquals(this, str, String("bbaaaa"));
        str.insert(static_cast <std::size_t> (6), 2, 'b');
        assertEquals(this, str, String("bbaaaabb"));
        str.insert(static_cast <std::size_t> (4), 2, 'b');
        assertEquals(this, str, String("bbaabbaabb"));
    }

    TEST(String, InsertStr) {
        String str("aaaa");
        str.insert(0, "bb");
        assertEquals(this, str, String("bbaaaa"));
        str.insert(6, "bb");
        assertEquals(this, str, String("bbaaaabb"));
        str.insert(4, "bb");
        assertEquals(this, str, String("bbaabbaabb"));
    }

    TEST(String, InsertCopy) {
        String str("aaaa");
        str.insert(0, String("bb"));
        assertEquals(this, str, String("bbaaaa"));
        str.insert(6, String("bb"));
        assertEquals(this, str, String("bbaaaabb"));
        str.insert(4, String("bb"));
        assertEquals(this, str, String("bbaabbaabb"));
    }

    TEST(String, InsertCopyRange) {
        String str("aaaa");
        str.insert(0, String("bbaabb"), 0, 2);
        assertEquals(this, str, String("bbaaaa"));
        str.insert(6, String("bbaabb"), 4, 2);
        assertEquals(this, str, String("bbaaaabb"));
        str.insert(4, String("bbaabb"), 2, 2);
        assertEquals(this, str, String("bbaaaaaabb"));
    }

    TEST(String, InsertItValue) {
        String str("aaaa");
        str.insert(str.begin(), 'b');
        assertEquals(this, str, String("baaaa"));
        str.insert(str.end(), 'b');
        assertEquals(this, str, String("baaaab"));
        str.insert(str.begin() + 3, 'b');
        assertEquals(this, str, String("baabaab"));
    }

    TEST(String, InsertItFill) {
        String str("aaaa");
        str.insert(str.begin(), 2, 'b');
        assertEquals(this, str, String("bbaaaa"));
        str.insert(str.end(), 2, 'b');
        assertEquals(this, str, String("bbaaaabb"));
        str.insert(str.begin() + 4, 2, 'b');
        assertEquals(this, str, String("bbaabbaabb"));
    }

    TEST(String, InsertInput) {
        String str("aaaa");
        std::string input("bb");
        str.insert(str.begin(), input.begin(), input.end());
        assertEquals(this, str, String("bbaaaa"));
        str.insert(str.end(), input.begin(), input.end());
        assertEquals(this, str, String("bbaaaabb"));
        str.insert(str.begin() + 4, input.begin(), input.end());
        assertEquals(this, str, String("bbaabbaabb"));
    }

    TEST(String, InsertList) {
        String str("aaaa");
        str.insert(str.begin(), {'b', 'b'});
        assertEquals(this, str, String("bbaaaa"));
        str.insert(str.end(), {'b', 'b'});
        assertEquals(this, str, String("bbaaaabb"));
        str.insert(str.begin() + 4, {'b', 'b'});
        assertEquals(this, str, String("bbaabbaabb"));
    }

    TEST(String, EraseCount) {
        String str("aaaabb");
        str.erase(0, 2);
        assertEquals(this, str, String("aabb"));
        str.erase(2, 2);
        assertEquals(this, str, String("aa"));
    }

    TEST(String, Erase) {
        String str("aaaabb");
        str.erase(str.begin());
        assertEquals(this, str, String("aaabb"));
        str.erase(str.end() - 1);
        assertEquals(this, str, String("aaab"));
    }

    TEST(String, EraseRange) {
        String str("aaaabb");
        str.erase(str.begin(), str.begin() + 4);
        assertEquals(this, str, String("bb"));
        str.erase(str.begin(), str.end());
        assertEquals(this, str, String(""));
    }

    TEST(String, PushBack) {
        String str("aaaa");
        str.pushBack('b');
        assertEquals(this, str, String("aaaab"));
    }

    TEST(String, PopBack) {
        String str("aaaab");
        str.popBack();
        assertEquals(this, str, String("aaaa"));
    }

    TEST(String, AppendObject) {
        String str;
        Vector<int> vec({1, 2, 3});
        str.append(vec);
        assertEquals(this, str, String("[1, 2, 3]"));
    }

    TEST(String, AppendTrue) {
        String str;
        str.append(true);
        assertEquals(this, str, String("true"));
    }

    TEST(String, AppendFalse) {
        String str;
        str.append(false);
        assertEquals(this, str, String("false"));
    }

    TEST(String, AppendChar) {
        String str;
        str.append('a');
        assertEquals(this, str, String("a"));
    }

    TEST(String, AppendShortInt) {
        String str;
        short int value = 123;
        str.append(value);
        assertEquals(this, str, String("123"));
    }

    TEST(String, AppendInt) {
        String str;
        int value = 123;
        str.append(value);
        assertEquals(this, str, String("123"));
    }

    TEST(String, AppendLongInt) {
        String str;
        long int value = 123;
        str.append(value);
        assertEquals(this, str, String("123"));
    }

    TEST(String, AppendLongLongInt) {
        String str;
        long long int value = 123;
        str.append(value);
        assertEquals(this, str, String("123"));
    }

    TEST(String, AppendNegativeLongLongInt) {
        String str;
        long long int value = -123;
        str.append(value);
        assertEquals(this, str, String("-123"));
    }

    TEST(String, AppendUnsignedShortInt) {
        String str;
        unsigned short int value = 123;
        str.append(value);
        assertEquals(this, str, String("123"));
    }

    TEST(String, AppendUnsignedInt) {
        String str;
        unsigned int value = 123;
        str.append(value);
        assertEquals(this, str, String("123"));
    }

    TEST(String, AppendUnsignedLongInt) {
        String str;
        unsigned long int value = 123;
        str.append(value);
        assertEquals(this, str, String("123"));
    }

    TEST(String, AppendUnsignedLongLongInt) {
        String str;
        unsigned long long int value = 123;
        str.append(value);
        assertEquals(this, str, String("123"));
    }

    TEST(String, AppendFloat) {
        String str;
        float value = 123.456f;
        str.append(value);
        assertEquals(this, str.substr(0, 7), String("123.456"));
    }

    TEST(String, AppendDouble) {
        String str;
        double value = 123.456;
        str.append(value);
        assertEquals(this, str.substr(0, 7), String("123.456"));
    }

    TEST(String, AppendLongDouble) {
        String str;
        long double value = 123.456;
        str.append(value);
        assertEquals(this, str.substr(0, 7), String("123.456"));
    }

    TEST(String, AppendNegativeLongDouble) {
        String str;
        long double value = -123.456;
        str.append(value);
        assertEquals(this, str.substr(0, 8), String("-123.456"));
    }

    TEST(String, AppendCount) {
        String str;
        str.append(10, 'a');
        assertEquals(this, str, String("aaaaaaaaaa"));
    }

    TEST(String, AppendCopy) {
        String str;
        String append("aaaabbbb");
        str.append(append);
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, AppendCopyRange) {
        String str;
        String append("aaaabbbb");
        str.append(append, 0, 4);
        assertEquals(this, str, String("aaaa"));
        str.append(append, 3, 2);
        assertEquals(this, str, String("aaaaab"));
    }

    TEST(String, AppendStrStart) {
        String str;
        str.append("aaaabbbb", 6);
        assertEquals(this, str, String("aaaabb"));
    }

    TEST(String, AppendStr) {
        String str;
        String append("aaaabbbb");
        str.append(append.getData());
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, AppendInput) {
        String str;
        std::string append("aaaabbbb");
        str.append(append.begin(), append.end());
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, AppendList) {
        String str;
        str.append({'a', 'b', 'c'});
        assertEquals(this, str, String("abc"));
    }

    TEST(String, Compare) {
        String str("aaa");
        String str1("bbb");
        String str2("ccc");
        assertGreater(this, str1.compare(str), 0);
        assertLesser(this, str1.compare(str2), 0);
        assertEquals(this, str1.compare(str1), 0);
    }

    TEST(String, CompareStr) {
        String str("bbb");
        assertGreater(this, str.compare("aaa"), 0);
        assertLesser(this, str.compare("ccc"), 0);
        assertEquals(this, str.compare("bbb"), 0);
    }

    TEST(String, StartWith) {
        String str("aaaabbbb");
        assertTrue(this, str.startsWith("aa"));
        assertFalse(this, str.startsWith("aabbbb"));
    }

    TEST(String, StartWithChar) {
        String str("aaaabbbb");
        assertTrue(this, str.startsWith('a'));
        assertFalse(this, str.startsWith('b'));
    }

    TEST(String, EndsWith) {
        String str("aaaabbbb");
        assertTrue(this, str.endsWith("bb"));
        assertFalse(this, str.endsWith("aaaabb"));
    }

    TEST(String, EndsWithChar) {
        String str("aaaabbbb");
        assertTrue(this, str.endsWith('b'));
        assertFalse(this, str.endsWith('a'));
    }

    TEST(String, ReplacePartByCopy) {
        String str("aaaabbbb");
        str.replace(0, 4, String("cc"));
        assertEquals(this, str, String("ccbbbb"));
        str.replace(0, 2, String("aaaa"));
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplaceRangeByCopy) {
        String str("aaaabbbb");
        str.replace(str.begin(), str.begin() + 4, String("cc"));
        assertEquals(this, str, String("ccbbbb"));
        str.replace(str.begin(), str.begin() + 2, String("aaaa"));
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplacePartByCopyPart) {
        String str("aaaabbbb");
        str.replace(0, 4, String("ccdd"), 0, 2);
        assertEquals(this, str, String("ccbbbb"));
        str.replace(0, 2, String("aaaaddaaaa"), 6, 4);
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplaceRangeByCopyRange) {
        String str("aaaabbbb");
        String replace1("ccdd");
        str.replace(str.begin(), str.begin() + 4, replace1, replace1.begin(), replace1.begin() + 2);
        assertEquals(this, str, String("ccbbbb"));
        String replace2("aaaaddaaaa");
        str.replace(str.begin(), str.begin() + 2, replace2, replace2.begin() + 6, replace2.begin() + 10);
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplacePartByStrStart) {
        String str("aaaabbbb");
        str.replace(0, 4, "ccdddd", 2);
        assertEquals(this, str, String("ccbbbb"));
        str.replace(0, 2, "aaaaddddaaaa", 4);
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplaceRangeByStrStart) {
        String str("aaaabbbb");
        str.replace(str.begin(), str.begin() + 4, "ccdddd", 2);
        assertEquals(this, str, String("ccbbbb"));
        str.replace(str.begin(), str.begin() + 2, "aaaaddddaaaa", 4);
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplacePartByStr) {
        String str("aaaabbbb");
        str.replace(0, 4, "cc");
        assertEquals(this, str, String("ccbbbb"));
        str.replace(0, 2, "aaaa");
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplaceRangeByStr) {
        String str("aaaabbbb");
        str.replace(str.begin(), str.begin() + 4, "cc");
        assertEquals(this, str, String("ccbbbb"));
        str.replace(str.begin(), str.begin() + 2, "aaaa");
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplacePartByCount) {
        String str("aaaabbbb");
        str.replace(0, 4, 'c', 2);
        assertEquals(this, str, String("ccbbbb"));
        str.replace(0, 2, 'a', 4);
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplaceRangeByCount) {
        String str("aaaabbbb");
        str.replace(str.begin(), str.begin() + 4, 'c', 2);
        assertEquals(this, str, String("ccbbbb"));
        str.replace(str.begin(), str.begin() + 2, 'a', 4);
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, ReplaceRangeByList) {
        String str("aaaabbbb");
        str.replace(str.begin(), str.begin() + 4, {'c', 'c'});
        assertEquals(this, str, String("ccbbbb"));
        str.replace(str.begin(), str.begin() + 2, {'a', 'a', 'a', 'a'});
        assertEquals(this, str, String("aaaabbbb"));
    }

    TEST(String, SubStr) {
        String str("aaaabbbb");
        assertEquals(this, str.substr(2, 4), String("aabb"));
    }

    TEST(String, Copy) {
        String str("aaaabbbb");
        char copy[4];
        str.copy(copy, 2, 4);
    }

    TEST(String, Resize) {
        String str("aaaabbbb");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (8));
        str.resize(10);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String(10, "aaaabbbb\0\0"));
    }

    TEST(String, ResizeValue) {
        String str("aaaabbbb");
        assertEquals(this, str.getSize(), static_cast <std::size_t> (8));
        str.resize(10, 'c');
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str, String("aaaabbbbcc"));
        str.resize(3);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, str, String("aaa"));
    }

    TEST(String, Swap) {
        String str("aaaabbbb");
        String swap("ccdd");
        str.swap(swap);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, swap.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, str, String("ccdd"));
        assertEquals(this, swap, String("aaaabbbb"));
    }

    TEST(String, ShrinkToFit) {
        String str(static_cast <std::size_t> (100), 'a');
        assertEquals(this, str.getSize(), static_cast <std::size_t> (100));
        assertEquals(this, str.get(str.getSize() - 1), 'a');
        str.resize(10);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertGreaterOrEquals(this, str.getCapacity(), static_cast <std::size_t> (100));
        assertEquals(this, str.get(str.getSize() - 1), 'a');
        str.shrinkToFit();
        assertEquals(this, str.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, str.getCapacity(), static_cast <std::size_t> (10));
        assertEquals(this, str.get(str.getSize() - 1), 'a');
    }

    TEST(String, Contains) {
        String str("aaaabbbb");
        assertTrue(this, str.contains("aaaa"));
        assertFalse(this, str.contains("aaaaa"));
        assertTrue(this, str.contains("ab"));
        assertFalse(this, str.contains("bab"));
    }

    TEST(String, Find) {
        String str("aaaabbbb");
        assertEquals(this, str.find(String("ab")), static_cast <std::size_t> (3));
        assertEquals(this, str.find(String("ab"), 4), String::NOT_FOUND);
    }

    TEST(String, FindStrPart) {
        String str("aaaabbbb");
        assertEquals(this, str.find(2, "abcdef"), static_cast <std::size_t> (3));
        assertEquals(this, str.find(2, "abcdef", 4), String::NOT_FOUND);
    }

    TEST(String, FindStr) {
        String str("aaaabbbb");
        assertEquals(this, str.find("ab"), static_cast <std::size_t> (3));
        assertEquals(this, str.find("ab", 4), String::NOT_FOUND);
    }

    TEST(String, FindChar) {
        String str("aaaabbbb");
        assertEquals(this, str.find("b"), static_cast <std::size_t> (4));
        assertEquals(this, str.find("a", 5), String::NOT_FOUND);
    }

    TEST(String, ReverseFind) {
        String str("aaaabbbbaaaa");
        assertEquals(this, str.rfind(String("aa"), str.getSize() - 1), static_cast <std::size_t> (10));
        assertEquals(this, str.rfind(String("bb"), 4), String::NOT_FOUND);
    }

    TEST(String, ReverseFindStrPart) {
        String str("aaaabbbbaaaa");
        assertEquals(this, str.rfind(2, "aabb", str.getSize() - 1), static_cast <std::size_t> (10));
        assertEquals(this, str.rfind(2, "bbaa", 4), String::NOT_FOUND);
    }

    TEST(String, ReverseFindStr) {
        String str("aaaabbbbaaaa");
        assertEquals(this, str.rfind("aa", str.getSize() - 1), static_cast <std::size_t> (10));
        assertEquals(this, str.rfind("bb", 4), String::NOT_FOUND);
    }

    TEST(String, ReverseFindChar) {
        String str("aaaabbbbaaaa");
        assertEquals(this, str.rfind('a', str.getSize() - 1), static_cast <std::size_t> (11));
        assertEquals(this, str.rfind('b', 3), String::NOT_FOUND);
    }

    TEST(String, FindFirstOf) {
        String str("aaaaabcdef");
        assertEquals(this, str.findFirstOf(String("dfe")), static_cast <std::size_t> (7));
        assertEquals(this, str.findFirstOf(String("efd")), static_cast <std::size_t> (7));
        assertEquals(this, str.findFirstOf(String("g")), String::NOT_FOUND);
    }

    TEST(String, FindFirstOfStrPart) {
        String str("aaaaabcdef");
        assertEquals(this, str.findFirstOf(3, "dfea"), static_cast <std::size_t> (7));
        assertEquals(this, str.findFirstOf(3, "efda"), static_cast <std::size_t> (7));
        assertEquals(this, str.findFirstOf(1, "gabcedf"), String::NOT_FOUND);
    }

    TEST(String, FindFirstOfStr) {
        String str("aaaaabcdef");
        assertEquals(this, str.findFirstOf("dfe"), static_cast <std::size_t> (7));
        assertEquals(this, str.findFirstOf("efd"), static_cast <std::size_t> (7));
        assertEquals(this, str.findFirstOf("g"), String::NOT_FOUND);
    }

    TEST(String, FindFirstOfChar) {
        String str("aaaaabcdef");
        assertEquals(this, str.findFirstOf('d'), static_cast <std::size_t> (7));
        assertEquals(this, str.findFirstOf('a'), static_cast <std::size_t> (0));
        assertEquals(this, str.findFirstOf('g'), String::NOT_FOUND);
    }

    TEST(String, FindFirstNotOf) {
        String str("aabbccddeeff");
        assertEquals(this, str.findFirstNotOf(String("abcdf")), static_cast <std::size_t> (8));
        assertEquals(this, str.findFirstNotOf(String("aaaaabcfdbac")), static_cast <std::size_t> (8));
        assertEquals(this, str.findFirstNotOf(String("abcdef")), String::NOT_FOUND);
    }

    TEST(String, FindFirstNotOfStrPart) {
        String str("aabbccddeeff");
        assertEquals(this, str.findFirstNotOf(5, "abcdfe"), static_cast <std::size_t> (8));
        assertEquals(this, str.findFirstNotOf(12, "aaaaabcfdbace"), static_cast <std::size_t> (8));
        assertEquals(this, str.findFirstNotOf(6, "abcdef"), String::NOT_FOUND);
    }

    TEST(String, FindFirstNotOfStr) {
        String str("aabbccddeeff");
        assertEquals(this, str.findFirstNotOf("abcdf"), static_cast <std::size_t> (8));
        assertEquals(this, str.findFirstNotOf("aaaaabcfdbac"), static_cast <std::size_t> (8));
        assertEquals(this, str.findFirstNotOf("abcdef"), String::NOT_FOUND);
    }

    TEST(String, FindFirstNotOfChar) {
        String str("aabbccddeeff");
        assertEquals(this, str.findFirstNotOf('a'), static_cast <std::size_t> (2));
        assertEquals(this, str.findFirstNotOf('b'), static_cast <std::size_t> (0));
    }

    TEST(String, FindLastOf) {
        String str("aaaaabcdef");
        assertEquals(this, str.findLastOf(String("dfe"), str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastOf(String("efd"), str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastOf(String("g"), str.getSize() - 1), String::NOT_FOUND);
    }

    TEST(String, FindLastOfStrPart) {
        String str("aaaaabcdefg");
        assertEquals(this, str.findLastOf(3, "dfeg", str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastOf(3, "efdg", str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastOf(1, "h", str.getSize() - 1), String::NOT_FOUND);
    }

    TEST(String, FindLastOfStr) {
        String str("aaaaabcdef");
        assertEquals(this, str.findLastOf("dfe", str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastOf("efd", str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastOf("g", str.getSize() - 1), String::NOT_FOUND);
    }

    TEST(String, FindLastOfChar) {
        String str("aaaaabcdef");
        assertEquals(this, str.findLastOf('e', str.getSize() - 1), static_cast <std::size_t> (8));
        assertEquals(this, str.findLastOf('a', str.getSize() - 1), static_cast <std::size_t> (4));
        assertEquals(this, str.findLastOf('g', str.getSize() - 1), String::NOT_FOUND);
    }

    TEST(String, FindLastNotOf) {
        String str("aabbccddeeff");
        assertEquals(this, str.findLastNotOf(String("abcdf"), str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastNotOf(String("aaaaabcfdbac"), str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastNotOf(String("abcdef"), str.getSize() - 1), String::NOT_FOUND);
    }

    TEST(String, FindLastNotOfStrPart) {
        String str("aabbccddeeff");
        assertEquals(this, str.findLastNotOf(5, "abcdfe", str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastNotOf(12, "aaaaabcfdbace", str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastNotOf(6, "abcdef", str.getSize() - 1), String::NOT_FOUND);
    }

    TEST(String, FindLastNotOfStr) {
        String str("aabbccddeeff");
        assertEquals(this, str.findLastNotOf("abcdf", str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastNotOf("aaaaabcfdbac", str.getSize() - 1), static_cast <std::size_t> (9));
        assertEquals(this, str.findLastNotOf("abcdef", str.getSize() - 1), String::NOT_FOUND);
    }

    TEST(String, FindLastNotOfChar) {
        String str("aabbccddeeff");
        assertEquals(this, str.findLastNotOf('a', str.getSize() - 1), static_cast <std::size_t> (11));
        assertEquals(this, str.findLastNotOf('f', str.getSize() - 1), static_cast <std::size_t> (9));
    }

    TEST(String, Access) {
        String str("aabbcdef");
        assertEquals(this, str[0], 'a');
        assertEquals(this, str[7], 'f');
    }

    TEST(String, AssignOpCopy) {
        String str;
        assertEquals(this, str, String(""));
        String copy("abcdef");
        str = copy;
        assertEquals(this, str, String("abcdef"));
    }

    TEST(String, AssignOpMove) {
        String str;
        assertEquals(this, str, String(""));
        String move("abcdef");
        assertEquals(this, move.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, str.getSize(), static_cast <std::size_t> (0));
        str = std::move(move);
        assertEquals(this, str.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, move.getSize(), static_cast <std::size_t> (0));
    }

    TEST(String, AssignOpStr) {
        String str;
        assertEquals(this, str, String(""));
        str = "abcdef";
        assertEquals(this, str, String("abcdef"));
    }

    TEST(String, AssignOpChar) {
        String str("abcdef");
        assertEquals(this, str, String("abcdef"));
        str = 'g';
        assertEquals(this, str, String("g"));
    }

    TEST(String, AssignOpList) {
        String str("abcdef");
        assertEquals(this, str, String("abcdef"));
        str = {'a', 'b', 'c'};
        assertEquals(this, str, String("abc"));
    }

    TEST(String, ConcatShortCopy) {
        String str("abcdef");
        assertEquals(this, str, String("abcdef"));
        str += str;
        assertEquals(this, str, String("abcdefabcdef"));
    }

    TEST(String, ConcatShortChar) {
        String str("abcdef");
        assertEquals(this, str, String("abcdef"));
        str += 'g';
        assertEquals(this, str, String("abcdefg"));
    }

    TEST(String, ConcatShortStr) {
        String str("abcdef");
        assertEquals(this, str, String("abcdef"));
        str += "abcdef";
        assertEquals(this, str, String("abcdefabcdef"));
    }

    TEST(String, ConcatShortList) {
        String str("abcdef");
        assertEquals(this, str, String("abcdef"));
        str += {'a', 'b', 'c', 'd', 'e', 'f'};
        assertEquals(this, str, String("abcdefabcdef"));
    }

    TEST(String, Equals) {
        String str("abcdef");
        String other("abcdef");
        assertEquals(this, str, other);
    }

    TEST(String, NotEquals) {
        String str("abcdef");
        String other("azerty");
        assertNotEquals(this, str, other);
    }

    TEST(String, Inferior) {
        String str("aaa");
        String other("bbb");
        assertLesser(this, str, other);
    }

    TEST(String, InferiorOrEquals) {
        String str("aa");
        String other("aa");
        String other2("aaa");
        assertLesserOrEquals(this, str, other);
        assertLesserOrEquals(this, str, other2);
    }

    TEST(String, Superior) {
        String str("bbb");
        String other("aaa");
        assertGreater(this, str, other);
    }

    TEST(String, SuperiorOrEquals) {
        String str("aaa");
        String other("aaaa");
        String other2("aaa");
        assertGreaterOrEquals(this, str, other);
        assertGreaterOrEquals(this, str, other2);
    }

    TEST(String, ConcatCopyCopy) {
        String str("aa");
        String other("bb");
        assertEquals(this, str + other, String("aabb"));
    }

    TEST(String, ConcatStrCopy) {
        String other("bb");
        assertEquals(this, "aa" + other, String("aabb"));
    }

    TEST(String, ConcatCharCopy) {
        String other("bb");
        assertEquals(this, 'a' + other, String("abb"));
    }

    TEST(String, ConcatCopyStr) {
        String str("aa");
        assertEquals(this, str + "bb", String("aabb"));
    }

    TEST(String, ConcatCopyChar) {
        String str("aa");
        assertEquals(this, str + 'b', String("aab"));
    }

    TEST(String, ConcatMoveCopy) {
        String str("aa");
        String other("bb");
        assertEquals(this, std::move(str) + other, String("aabb"));
    }

    TEST(String, ConcatCopyMove) {
        String str("aa");
        String other("bb");
        assertEquals(this, str + std::move(other), String("aabb"));
    }

    TEST(String, ConcatMoveMove) {
        String str("aa");
        String other("bb");
        assertEquals(this, std::move(str) + std::move(other), String("aabb"));
    }

    TEST(String, ConcatStrMove) {
        String other("bb");
        assertEquals(this, "aa" + std::move(other), String("aabb"));
    }

    TEST(String, ConcatCharMove) {
        String other("bb");
        assertEquals(this, 'a' + std::move(other), String("abb"));
    }

    TEST(String, ConcatMoveStr) {
        String str("aa");
        assertEquals(this, std::move(str) + "bb", String("aabb"));
    }

    TEST(String, ConcatMoveChar) {
        String str("aa");
        assertEquals(this, std::move(str) + 'b', String("aab"));
    }

    TEST(String, Hash) {
        std::hash<String> hashUtil;
        std::hash<std::string> hashStl;
        assertEquals(this, hashUtil(String("Hello")), hashStl(std::string("Hello")));
    }
