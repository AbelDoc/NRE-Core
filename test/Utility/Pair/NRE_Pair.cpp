
    /**
     * @file NRE_Pair.cpp
     * @brief Test of Utility's API's Object : Pair
     * @author Louis ABEL
     * @date 23/06/2019
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Utility.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Utility;
    using namespace NRE::Tester;

    TEST(Pair, Ctr) {
        Pair<int, int> p;
        assertEquals(this, p.first, 0);
        assertEquals(this, p.second, 0);
    }

    TEST(Pair, CtrParam) {
        Pair<int, int> p(10, 20);
        assertEquals(this, p.first, 10);
        assertEquals(this, p.second, 20);
    }

    TEST(Pair, CtrMoveParam) {
        Pair<std::string, std::string> p(std::string("First"), std::string("Second"));
        assertEquals(this, p.first, std::string("First"));
        assertEquals(this, p.second, std::string("Second"));
    }

    TEST(Pair, Copy) {
        Pair<int, int> p(10, 20);
        Pair<int, int> copy(p);
        assertEquals(this, copy.first, 10);
        assertEquals(this, copy.second, 20);
    }

    TEST(Pair, CopyType) {
        Pair<int, int> p(0, 10);
        Pair<std::size_t, std::size_t> copy(p);
        assertEquals(this, copy.first, static_cast <std::size_t> (0));
        assertEquals(this, copy.second, static_cast <std::size_t> (10));
    }

    TEST(Pair, Move) {
        Pair<int, int> p(10, 20);
        Pair<int, int> move(std::move(p));
        assertEquals(this, move.first, 10);
        assertEquals(this, move.second, 20);
    }

    TEST(Pair, MoveType) {
        Pair<int, int> p(10, 20);
        Pair<std::size_t, std::size_t> move(std::move(p));
        assertEquals(this, move.first, static_cast <std::size_t> (10));
        assertEquals(this, move.second, static_cast <std::size_t> (20));
    }

    TEST(Pair, Swap) {
        Pair<int, int> p(10, 20);
        Pair<int, int> other(30, 40);
        p.swap(other);
        assertEquals(this, p.first, 30);
        assertEquals(this, p.second, 40);
        assertEquals(this, other.first, 10);
        assertEquals(this, other.second, 20);
    }

    TEST(Pair, Assign) {
        Pair<int, int> p(10, 20);
        Pair<int, int> toAssign(30, 40);
        p = toAssign;
        assertEquals(this, p.first, 30);
        assertEquals(this, p.second, 40);
    }

    TEST(Pair, AssignType) {
        Pair<std::size_t, std::size_t> p(10, 20);
        Pair<int, int> toAssign(30, 40);
        p = toAssign;
        assertEquals(this, p.first, static_cast <std::size_t> (30));
        assertEquals(this, p.second, static_cast <std::size_t> (40));
    }

    TEST(Pair, AssignMove) {
        Pair<int, int> p(10, 20);
        Pair<int, int> toAssign(30, 40);
        p = std::move(toAssign);
        assertEquals(this, p.first, 30);
        assertEquals(this, p.second, 40);
    }

    TEST(Pair, AssignMoveType) {
        Pair<std::size_t, std::size_t> p(10, 20);
        Pair<int, int> toAssign(30, 40);
        p = std::move(toAssign);
        assertEquals(this, p.first, static_cast <std::size_t> (30));
        assertEquals(this, p.second, static_cast <std::size_t> (40));
    }

    TEST(Pair, Equals) {
        Pair<int, int> p(10, 20);
        Pair<int, int> other(10, 20);
        assertEquals(this, p, other);
    }

    TEST(Pair, NotEquals) {
        Pair<int, int> p(10, 20);
        Pair<int, int> other(30, 40);
        assertNotEquals(this, p, other);
    }

    TEST(Pair, Inferior) {
        Pair<int, int> p(10, 20);
        Pair<int, int> other1(0, 20);
        Pair<int, int> other2(10, 30);
        Pair<int, int> other3(10, 10);
        Pair<int, int> other4(20, 20);
        assertLesser(this, p, other2);
        assertLesser(this, p, other4);
        assertLesser(this, other1, p);
        assertLesser(this, other3, p);
    }

    TEST(Pair, InferiorOrEquals) {
        Pair<int, int> p(10, 20);
        Pair<int, int> other1(0, 20);
        Pair<int, int> other2(10, 30);
        Pair<int, int> other3(10, 10);
        Pair<int, int> other4(20, 20);
        Pair<int, int> other5(10, 20);
        assertLesserOrEquals(this, p, other2);
        assertLesserOrEquals(this, p, other4);
        assertLesserOrEquals(this, p, other5);
        assertLesserOrEquals(this, other1, p);
        assertLesserOrEquals(this, other3, p);
    }

    TEST(Pair, Greater) {
        Pair<int, int> p(10, 20);
        Pair<int, int> other1(0, 20);
        Pair<int, int> other2(10, 30);
        Pair<int, int> other3(10, 10);
        Pair<int, int> other4(20, 20);
        assertGreater(this, other4, p);
        assertGreater(this, other2, p);
        assertGreater(this, p, other1);
        assertGreater(this, p, other3);
    }

    TEST(Pair, GreaterOrEquals) {
        Pair<int, int> p(10, 20);
        Pair<int, int> other1(0, 20);
        Pair<int, int> other2(10, 30);
        Pair<int, int> other3(10, 10);
        Pair<int, int> other4(20, 20);
        Pair<int, int> other5(10, 20);
        assertGreaterOrEquals(this, other4, p);
        assertGreaterOrEquals(this, other2, p);
        assertGreaterOrEquals(this, p, other5);
        assertGreaterOrEquals(this, p, other1);
        assertGreaterOrEquals(this, p, other3);
    }
