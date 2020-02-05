
    /**
     * @file NRE_DynamicArray.cpp
     * @brief Test of Utility's API's Container : DynamicArray
     * @author Louis ABEL
     * @date 05/02/2020
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Utility.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Utility;
    using namespace NRE::Tester;

    TEST(DynamicArray, CtrFillValue) {
        DynamicArray<int> arr(static_cast <std::size_t> (10), 1);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, arr.get(0), 1);
    }

    TEST(DynamicArray, CtrFill) {
        DynamicArray<int> arr(static_cast <std::size_t> (10));
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, arr.get(0), 0);
    }

    TEST(DynamicArray, CtrInput) {
        std::vector<int> vector({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
        DynamicArray<int> arr(vector.begin(), vector.end());
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, arr.get(0), 0);
        assertEquals(this, arr.get(9), 9);
    }

    TEST(DynamicArray, CtrList) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(4), 4);
    }

    TEST(DynamicArray, Copy) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        DynamicArray<int> copy(arr);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, copy.get(4), 4);
    }

    TEST(DynamicArray, Move) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        DynamicArray<int> move(std::move(arr));
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, move.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, move.get(4), 4);
    }

    TEST(DynamicArray, Get) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.get(4), 4);
    }

    TEST(DynamicArray, Data) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getData(), &arr.get(0));
        assertNotNull(this, arr.getData());
    }

    TEST(DynamicArray, Front) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getFront(), 0);
    }

    TEST(DynamicArray, Last) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getLast(), 4);
    }

    TEST(DynamicArray, Size) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
    }

    TEST(DynamicArray, MaxSize) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getMaxSize(), std::numeric_limits<std::size_t>::max());
    }

    TEST(DynamicArray, Capacity) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertGreaterOrEquals(this, arr.getCapacity(), static_cast <std::size_t> (5));
    }

    TEST(DynamicArray, NotEmpty) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertFalse(this, arr.isEmpty());
    }

    TEST(DynamicArray, Empty) {
        DynamicArray<int> arr;
        assertTrue(this, arr.isEmpty());
    }

    TEST(DynamicArray, Begin) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, *(arr.begin()), 0);
    }

    TEST(DynamicArray, End) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, *(arr.end() - 1), 4);
    }

    TEST(DynamicArray, ReverseBegin) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, *(arr.rbegin()), 4);
    }

    TEST(DynamicArray, ReverseEnd) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, *(arr.rend() - 1), 0);
    }

    TEST(DynamicArray, AssignValue) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.get(4), 4);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        arr.assign(static_cast <std::size_t> (10), 100);
        assertEquals(this, arr.get(4), 100);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (10));
    }

    TEST(DynamicArray, AssignInput) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.get(4), 4);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        std::vector<int> toAssign({100, 100, 100, 100, 100, 100, 100, 100, 100, 100});
        arr.assign(toAssign.begin(), toAssign.end());
        assertEquals(this, arr.get(4), 100);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (10));
    }

    TEST(DynamicArray, Clear) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        arr.clear();
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (0));
    }

    TEST(DynamicArray, InsertValue) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(1), 1);
        arr.insert(arr.begin() + 1, 100);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, arr.get(1), 100);
    }

    TEST(DynamicArray, InsertCountValue) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(1), 1);
        arr.insert(arr.begin() + 1, static_cast <std::size_t> (10), 100);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (15));
        assertEquals(this, arr.get(1), 100);
    }

    TEST(DynamicArray, InsertInput) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(1), 1);
        std::vector<int> toInsert({100, 200, 300});
        arr.insert(arr.begin() + 1, toInsert.begin(), toInsert.end());
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, arr.get(1), 100);
    }

    TEST(DynamicArray, InsertList) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(1), 1);
        arr.insert(arr.begin() + 1, {100, 200, 300});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, arr.get(1), 100);
    }

    TEST(DynamicArray, Emplace) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(1), 1);
        arr.emplace(arr.begin() + 1, 100);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, arr.get(1), 100);
    }

    TEST(DynamicArray, Erase) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(1), 1);
        arr.erase(arr.begin() + 1);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, arr.get(1), 2);
    }

    TEST(DynamicArray, EraseRange) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(1), 1);
        arr.erase(arr.begin() + 1, arr.end());
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (1));
        assertEquals(this, arr.get(0), 0);
    }

    TEST(DynamicArray, PushBack) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(1), 1);
        arr.pushBack(100);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, arr.get(5), 100);
    }

    TEST(DynamicArray, EmplaceBack) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(1), 1);
        arr.emplaceBack(100);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, arr.get(5), 100);
    }

    TEST(DynamicArray, PopBack) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(arr.getSize() - 1), 4);
        arr.popBack();
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, arr.get(arr.getSize() - 1), 3);
    }

    TEST(DynamicArray, Resize) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(arr.getSize() - 1), 4);
        arr.resize(10);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, arr.get(arr.getSize() - 1), 0);
        assertEquals(this, arr.toString(), String("[0, 1, 2, 3, 4, 0, 0, 0, 0, 0]"));
        arr.resize(3);
        assertEquals(this, arr.toString(), String("[0, 1, 2]"));
    }

    TEST(DynamicArray, ResizeValue) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(arr.getSize() - 1), 4);
        arr.resize(10, 100);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, arr.get(arr.getSize() - 1), 100);
    }

    TEST(DynamicArray, Swap) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        DynamicArray<int> toSwap({10, 20, 30, 40, 50, 60});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(arr.getSize() - 1), 4);
        assertEquals(this, toSwap.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, toSwap.get(toSwap.getSize() - 1), 60);
        arr.swap(toSwap);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, arr.get(arr.getSize() - 1), 60);
        assertEquals(this, toSwap.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, toSwap.get(toSwap.getSize() - 1), 4);
    }

    TEST(DynamicArray, Access) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr[0], 0);
    }

    TEST(DynamicArray, AssignCopy) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(arr.getSize() - 1), 4);
        DynamicArray<int> toCopy({10, 20, 30, 40, 50, 60});
        arr = toCopy;
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, arr.get(arr.getSize() - 1), 60);
    }

    TEST(DynamicArray, AssignMove) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, arr.get(arr.getSize() - 1), 4);
        DynamicArray<int> toMove({10, 20, 30, 40, 50, 60});
        arr = std::move(toMove);
        assertEquals(this, arr.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, arr.get(arr.getSize() - 1), 60);
    }

    TEST(DynamicArray, Equals) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        DynamicArray<int> other({0, 1, 2, 3, 4});
        assertEquals(this, arr, other);
    }

    TEST(DynamicArray, NotEquals) {
        DynamicArray<int> arr({0, 1, 2, 3, 4});
        DynamicArray<int> other({0, 1, 2, 3, 4, 5});
        DynamicArray<int> otherArr({0, 1, 2, 3, 40});
        assertNotEquals(this, arr, other);
        assertNotEquals(this, arr, otherArr);
    }
