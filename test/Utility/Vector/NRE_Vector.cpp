
    /**
     * @file NRE_Vector.cpp
     * @brief Test of Utility's API's Container : Vector
     * @author Louis ABEL
     * @date 19/06/2019
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Utility.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Utility;
    using namespace NRE::Tester;

    TEST(Vector, CtrFillValue) {
        Vector<int> vec(static_cast <std::size_t> (10), 1);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(0), 1);
    }

    TEST(Vector, CtrFill) {
        Vector<int> vec(static_cast <std::size_t> (10));
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(0), 0);
    }

    TEST(Vector, CtrInput) {
        std::vector<int> vector({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
        Vector<int> vec(vector.begin(), vector.end());
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(0), 0);
        assertEquals(this, vec.get(9), 9);
    }

    TEST(Vector, CtrList) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(4), 4);
    }

    TEST(Vector, Copy) {
        Vector<int> vec({0, 1, 2, 3, 4});
        Vector<int> copy(vec);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, copy.get(4), 4);
    }

    TEST(Vector, Move) {
        Vector<int> vec({0, 1, 2, 3, 4});
        Vector<int> move(std::move(vec));
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, move.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, move.get(4), 4);
    }

    TEST(Vector, Get) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.get(4), 4);
    }

    TEST(Vector, Data) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getData(), &vec.get(0));
        assertNotNull(this, vec.getData());
    }

    TEST(Vector, Front) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getFront(), 0);
    }

    TEST(Vector, Last) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getLast(), 4);
    }

    TEST(Vector, Size) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
    }

    TEST(Vector, MaxSize) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getMaxSize(), std::numeric_limits<std::size_t>::max());
    }

    TEST(Vector, Capacity) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertGreaterOrEquals(this, vec.getCapacity(), static_cast <std::size_t> (5));
    }

    TEST(Vector, NotEmpty) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertFalse(this, vec.isEmpty());
    }

    TEST(Vector, Empty) {
        Vector<int> vec;
        assertTrue(this, vec.isEmpty());
    }

    TEST(Vector, Begin) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, *(vec.begin()), 0);
    }

    TEST(Vector, End) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, *(vec.end() - 1), 4);
    }

    TEST(Vector, ReverseBegin) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, *(vec.rbegin()), 4);
    }

    TEST(Vector, ReverseEnd) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, *(vec.rend() - 1), 0);
    }

    TEST(Vector, AssignValue) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.get(4), 4);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        vec.assign(static_cast <std::size_t> (10), 100);
        assertEquals(this, vec.get(4), 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
    }

    TEST(Vector, AssignInput) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.get(4), 4);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        std::vector<int> toAssign({100, 100, 100, 100, 100, 100, 100, 100, 100, 100});
        vec.assign(toAssign.begin(), toAssign.end());
        assertEquals(this, vec.get(4), 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
    }

    TEST(Vector, Reserve) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertGreaterOrEquals(this, vec.getCapacity(), static_cast <std::size_t> (5));
        vec.reserve(100);
        assertEquals(this, vec.getCapacity(), static_cast <std::size_t> (100));
    }

    TEST(Vector, Clear) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        vec.clear();
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (0));
    }

    TEST(Vector, InsertValue) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.insert(vec.begin() + 1, 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(Vector, InsertCountValue) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.insert(vec.begin() + 1, static_cast <std::size_t> (10), 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (15));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(Vector, InsertInput) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        std::vector<int> toInsert({100, 200, 300});
        vec.insert(vec.begin() + 1, toInsert.begin(), toInsert.end());
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(Vector, InsertList) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.insert(vec.begin() + 1, {100, 200, 300});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(Vector, Emplace) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.emplace(vec.begin() + 1, 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(1), 100);
    }

    TEST(Vector, Erase) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.erase(vec.begin() + 1);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, vec.get(1), 2);
    }

    TEST(Vector, EraseRange) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.erase(vec.begin() + 1, vec.end());
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (1));
        assertEquals(this, vec.get(0), 0);
    }

    TEST(Vector, PushBack) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.pushBack(100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(5), 100);
    }

    TEST(Vector, EmplaceBack) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(1), 1);
        vec.emplaceBack(100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(5), 100);
    }

    TEST(Vector, PopBack) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        vec.popBack();
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, vec.get(vec.getSize() - 1), 3);
    }

    TEST(Vector, Resize) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        vec.resize(10);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(vec.getSize() - 1), 0);
    }

    TEST(Vector, ResizeValue) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        vec.resize(10, 100);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, vec.get(vec.getSize() - 1), 100);
    }

    TEST(Vector, Swap) {
        Vector<int> vec({0, 1, 2, 3, 4});
        Vector<int> toSwap({10, 20, 30, 40, 50, 60});
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

    TEST(Vector, Access) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec[0], 0);
    }

    TEST(Vector, AssignCopy) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        Vector<int> toCopy({10, 20, 30, 40, 50, 60});
        vec = toCopy;
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(vec.getSize() - 1), 60);
    }

    TEST(Vector, AssignMove) {
        Vector<int> vec({0, 1, 2, 3, 4});
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, vec.get(vec.getSize() - 1), 4);
        Vector<int> toMove({10, 20, 30, 40, 50, 60});
        vec = std::move(toMove);
        assertEquals(this, vec.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, vec.get(vec.getSize() - 1), 60);
        assertEquals(this, toMove.getSize(), static_cast <std::size_t> (0));
    }

    TEST(Vector, Equals) {
        Vector<int> vec({0, 1, 2, 3, 4});
        Vector<int> other({0, 1, 2, 3, 4});
        assertEquals(this, vec, other);
    }

    TEST(Vector, NotEquals) {
        Vector<int> vec({0, 1, 2, 3, 4});
        Vector<int> other({0, 1, 2, 3, 4, 5});
        Vector<int> otherVec({0, 1, 2, 3, 40});
        assertNotEquals(this, vec, other);
        assertNotEquals(this, vec, otherVec);
    }
