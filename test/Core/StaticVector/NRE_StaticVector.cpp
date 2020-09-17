
    /**
     * @file NRE_StaticVector.cpp
     * @brief Test of Core's API's Container : StaticVector
     * @author Louis ABEL
     * @date 05/02/2020
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Core.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Core;
    using namespace NRE::Tester;

    TEST(StaticVector, CtrFillValue) {
        StaticVector<int> vec(static_cast <std::size_t> (10), 1);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(0), 1);
    }

    TEST(StaticVector, CtrFill) {
        StaticVector<int> vec(static_cast <std::size_t> (10));
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(0), 0);
    }

    TEST(StaticVector, CtrInput) {
        std::vector<int> vector({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
        StaticVector<int> vec(vector.begin(), vector.end());
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(0), 0);
        assertEquals(this, vec.get(9), 9);
    }

    TEST(StaticVector, CtrList) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(4), 4);
    }

    TEST(StaticVector, Copy) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        StaticVector<int> copy(vec);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, copy.get(4), 4);
    }

    TEST(StaticVector, Move) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        StaticVector<int> move(std::move(vec));
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, move.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, move.get(4), 4);
    }

    TEST(StaticVector, Get) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.get(4), 4);
    }

    TEST(StaticVector, Data) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getData(), &vec.get(0));
        assertNotNull(this, vec.getData());
    }

    TEST(StaticVector, Front) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getFront(), 0);
    }

    TEST(StaticVector, Last) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getLast(), 4);
    }

    TEST(StaticVector, Size) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
    }

    TEST(StaticVector, MaxSize) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getMaxSize(), std::numeric_limits<std::size_t>::max());
    }

    TEST(StaticVector, Capacity) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertGreaterOrEquals(this, vec.getCapacity(), static_cast <std::size_t> (5));
    }

    TEST(StaticVector, NotEmpty) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertFalse(this, vec.isEmpty());
    }

    TEST(StaticVector, Empty) {
        StaticVector<int> vec;
        assertTrue(this, vec.isEmpty());
    }

    TEST(StaticVector, Begin) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, *(vec.begin()), 0);
    }

    TEST(StaticVector, End) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, *(vec.end() - 1), 4);
    }

    TEST(StaticVector, ReverseBegin) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, *(vec.rbegin()), 4);
    }

    TEST(StaticVector, ReverseEnd) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, *(vec.rend() - 1), 0);
    }

    TEST(StaticVector, AssignValue) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.get(4), 4);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        vec.assign(static_cast <std::size_t> (10), 100);
        assertEquals(this, vec.get(4), 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
    }

    TEST(StaticVector, AssignInput) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.get(4), 4);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        std::vector<int> toAssign({100, 100, 100, 100, 100, 100, 100, 100, 100, 100});
        vec.assign(toAssign.begin(), toAssign.end());
        assertEquals(this, vec.get(4), 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
    }

    TEST(StaticVector, Clear) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        vec.clear();
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (0));
    }

    TEST(StaticVector, InsertValue) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.insert(vec.begin() + 1, 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(StaticVector, InsertCountValue) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.insert(vec.begin() + 1, static_cast <std::size_t> (10), 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (15));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(StaticVector, InsertInput) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        std::vector<int> toInsert({100, 200, 300});
        vec.insert(vec.begin() + 1, toInsert.begin(), toInsert.end());
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(StaticVector, InsertList) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.insert(vec.begin() + 1, {100, 200, 300});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(StaticVector, Emplace) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.emplace(vec.begin() + 1, 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(StaticVector, Erase) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.erase(vec.begin() + 1);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, vec.get(1), 2);
    }

    TEST(StaticVector, EraseRange) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.erase(vec.begin() + 1, vec.end());
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (1));
        assertEquals(this, vec.get(0), 0);
    }

    TEST(StaticVector, PushBack) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.pushBack(100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(5), 100);
    }

    TEST(StaticVector, EmplaceBack) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.emplaceBack(100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(5), 100);
    }

    TEST(StaticVector, PopBack) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        vec.popBack();
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, vec.get(vec.getSize() - 1), 3);
    }

    TEST(StaticVector, Resize) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        vec.resize(10);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(vec.getSize() - 1), 0);
        assertEquals(this, vec.toString(), String("[0, 1, 2, 3, 4, 0, 0, 0, 0, 0]"));
        vec.resize(3);
        assertEquals(this, vec.toString(), String("[0, 1, 2]"));
    }

    TEST(StaticVector, ResizeValue) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        vec.resize(10, 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(vec.getSize() - 1), 100);
    }

    TEST(StaticVector, Swap) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        StaticVector<int> toSwap({10, 20, 30, 40, 50, 60});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        assertEquals(this, toSwap.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, toSwap.get(toSwap.getSize() - 1), 60);
        vec.swap(toSwap);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(vec.getSize() - 1), 60);
        assertEquals(this, toSwap.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, toSwap.get(toSwap.getSize() - 1), 4);
    }

    TEST(StaticVector, Access) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec[0], 0);
    }

    TEST(StaticVector, AssignCopy) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        StaticVector<int> toCopy({10, 20, 30, 40, 50, 60});
        vec = toCopy;
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(vec.getSize() - 1), 60);
    }

    TEST(StaticVector, AssignMove) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        StaticVector<int> toMove({10, 20, 30, 40, 50, 60});
        vec = std::move(toMove);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(vec.getSize() - 1), 60);
    }

    TEST(StaticVector, Equals) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        StaticVector<int> other({0, 1, 2, 3, 4});
        assertEquals(this, vec, other);
    }

    TEST(StaticVector, NotEquals) {
        StaticVector<int> vec({0, 1, 2, 3, 4});
        StaticVector<int> other({0, 1, 2, 3, 4, 5});
        StaticVector<int> otherVec({0, 1, 2, 3, 40});
        assertNotEquals(this, vec, other);
        assertNotEquals(this, vec, otherVec);
    }
