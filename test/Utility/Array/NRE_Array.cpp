
    /**
     * @file NRE_Array.cpp
     * @brief Test of Utility's API's Container : Array
     * @author Louis ABEL
     * @date 19/06/2019
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Utility.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Utility;
    using namespace NRE::Tester;

    TEST(Array, Get) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array.get(0), 0);
    }

    TEST(Array, Copy) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array.get(0), 0);
        Array<int, 5> copy(array);
        assertEquals(this, copy.get(0), 0);
    }

    TEST(Array, Data) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array.getData(), &(array.get(0)));
        assertNotNull(this, array.getData());
    }

    TEST(Array, Front) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array.getFront(), 0);
    }

    TEST(Array, Last) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array.getLast(), 4);
    }

    TEST(Array, NotEmpty) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertFalse(this, array.isEmpty());
    }

    TEST(Array, Size) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array.getSize(), static_cast <std::size_t> (5));
    }

    TEST(Array, MaxSize) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array.getMaxSize(), std::numeric_limits<std::size_t>::max());
    }

    TEST(Array, Begin) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, *(array.begin()), 0);
    }

    TEST(Array, End) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, *(array.end() - 1), 4);
    }

    TEST(Array, ReverseBegin) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, *(array.rbegin()), 4);
    }

    TEST(Array, ReverseEnd) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, *(array.rend() - 1), 0);
    }

    TEST(Array, Fill) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array.get(0), 0);
        array.fill(100);
        assertEquals(this, array.get(0), 100);
    }

    TEST(Array, Swap) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        Array<int, 5> toSwap({100, 100, 100, 100, 100});
        assertEquals(this, array.get(0), 0);
        assertEquals(this, toSwap.get(0), 100);
        array.swap(toSwap);
        assertEquals(this, array.get(0), 100);
        assertEquals(this, toSwap.get(0), 0);
    }

    TEST(Array, Access) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array[0], 0);
    }

    TEST(Array, Assign) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        assertEquals(this, array.get(0), 0);
        Array<int, 5> toAssign({100, 100, 100, 100, 100});
        array = toAssign;
        assertEquals(this, array.get(0), 100);
    }

    TEST(Array, Equals) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        Array<int, 5> other({0, 1, 2, 3, 4});
        assertEquals(this, array, other);
    }

    TEST(Array, NotEquals) {
        Array<int, 5> array({0, 1, 2, 3, 4});
        Array<int, 5> other({100, 100, 100, 100, 100});
        assertNotEquals(this, array, other);
    }
