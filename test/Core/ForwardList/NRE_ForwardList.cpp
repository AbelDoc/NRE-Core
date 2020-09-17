
    /**
     * @file NRE_ForwardList.cpp
     * @brief Test of Core's API's Container : ForwardList
     * @author Louis ABEL
     * @date 21/06/2019
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Core.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Core;
    using namespace NRE::Tester;

    TEST(ForwardList, Ctr) {
        ForwardList<int> list;
        assertTrue(this, list.isEmpty());
    }

    TEST(ForwardList, CtrCount) {
        ForwardList<int> list(10);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.getFront(), 0);
        assertEquals(this, list.toString(), String("(0, 0, 0, 0, 0, 0, 0, 0, 0, 0)"));
        ForwardList<int> list2(static_cast <std::size_t> (10), 100);
        assertEquals(this, list2.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list2.getFront(), 100);
        assertEquals(this, list2.toString(), String("(100, 100, 100, 100, 100, 100, 100, 100, 100, 100)"));
    }

    TEST(ForwardList, CtrInput) {
        Vector<int> vec({1, 2, 3, 4, 5});
        ForwardList<int> list(vec.begin(), vec.end());
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, CtrList) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, CtrCopy) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        ForwardList<int> copy(list);
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, copy.getFront(), 1);
        assertEquals(this, copy.toString(), String("(1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, CtrMove) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        ForwardList<int> move(std::move(list));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, move.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, move.getFront(), 1);
        assertEquals(this, move.toString(), String("(1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, Front) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, MaxSize) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getMaxSize(), std::numeric_limits<std::size_t>::max());
    }

    TEST(ForwardList, Size) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
    }

    TEST(ForwardList, Empty) {
        ForwardList<int> list;
        assertTrue(this, list.isEmpty());
    }

    TEST(ForwardList, NotEmpty) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertFalse(this, list.isEmpty());
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, BeforeBegin) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        auto it = list.beforeBegin();
        it++;
        assertEquals(this, *(it), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, Begin) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, *(list.begin()), 1);
    }

    TEST(ForwardList, AssignCount) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.assign(static_cast <std::size_t> (10), 5);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.getFront(), 5);
        assertEquals(this, list.toString(), String("(5, 5, 5, 5, 5, 5, 5, 5, 5, 5)"));
    }

    TEST(ForwardList, AssignInput) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        Vector<int> vec(static_cast <std::size_t> (10), 5);
        list.assign(vec.begin(), vec.end());
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.getFront(), 5);
        assertEquals(this, list.toString(), String("(5, 5, 5, 5, 5, 5, 5, 5, 5, 5)"));
    }

    TEST(ForwardList, Clear) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.clear();
        assertEquals(this, list.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, list.toString(), String("()"));
    }

    TEST(ForwardList, InsertAfterValue) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.insertAfter(++++list.cbegin(), 10);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 10, 4, 5)"));
    }

    TEST(ForwardList, InsertAfterMoveValue) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.insertAfter(++++list.cbegin(), std::move(10));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 10, 4, 5)"));
    }

    TEST(ForwardList, InsertAfterCount) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.insertAfter(++++list.cbegin(), static_cast <std::size_t> (3), 10);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 10, 10, 10, 4, 5)"));
    }

    TEST(ForwardList, InsertAfterInput) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        std::vector<int> vec({10, 10, 10});
        list.insertAfter(++++list.cbegin(), vec.begin(), vec.end());
        assertEquals(this, list.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 10, 10, 10, 4, 5)"));
    }

    TEST(ForwardList, InsertAfterList) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.insertAfter(++++list.cbegin(), {10, 10, 10});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 10, 10, 10, 4, 5)"));
    }

    TEST(ForwardList, EmplaceAfter) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.emplaceAfter(++++list.cbegin(), 10);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 10, 4, 5)"));
    }

    TEST(ForwardList, EraseAfter) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.eraseAfter(++++list.cbegin());
        assertEquals(this, list.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 5)"));
    }

    TEST(ForwardList, EraseAfterRange) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.eraseAfter(list.cbeforeBegin(), ++++++list.cbegin());
        assertEquals(this, list.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, list.getFront(), 3);
        assertEquals(this, list.toString(), String("(3, 4, 5)"));
    }

    TEST(ForwardList, PushFront) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.pushFront(6);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, list.getFront(), 6);
        assertEquals(this, list.toString(), String("(6, 1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, PushFrontMove) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.pushFront(std::move(6));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, list.getFront(), 6);
        assertEquals(this, list.toString(), String("(6, 1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, EmplaceFront) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.emplaceFront(6);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, list.getFront(), 6);
        assertEquals(this, list.toString(), String("(6, 1, 2, 3, 4, 5)"));
    }

    TEST(ForwardList, PopFront) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.popFront();
        assertEquals(this, list.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, list.getFront(), 2);
        assertEquals(this, list.toString(), String("(2, 3, 4, 5)"));
    }

    TEST(ForwardList, Resize) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.resize(10);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5, 0, 0, 0, 0, 0)"));
        list.resize(3);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3)"));
    }

    TEST(ForwardList, ResizeValue) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.resize(10, 100);
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5, 100, 100, 100, 100, 100)"));
    }

    TEST(ForwardList, Swap) {
        ForwardList<int> list({1, 2, 3, 4, 5});
        ForwardList<int> other({10, 20, 30, 40, 50, 60});
        assertEquals(this, list.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, list.getFront(), 1);
        assertEquals(this, list.toString(), String("(1, 2, 3, 4, 5)"));
        list.swap(other);
        assertEquals(this, other.getSize(), static_cast <std::size_t> (5));
        assertEquals(this, other.getFront(), 1);
        assertEquals(this, other.toString(), String("(1, 2, 3, 4, 5)"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, list.getFront(), 10);
        assertEquals(this, list.toString(), String("(10, 20, 30, 40, 50, 60)"));
    }

    TEST(ForwardList, Merge) {
        ForwardList<int> list({1, 3, 5, 7, 9});
        ForwardList<int> other({0, 2, 4, 6, 8});
        list.merge(other);
        assertEquals(this, other.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, other.toString(), String("()"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.toString(), String("(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)"));
    }

    TEST(ForwardList, MergeMove) {
        ForwardList<int> list({1, 3, 5, 7, 9});
        ForwardList<int> other({0, 2, 4, 6, 8});
        list.merge(std::move(other));
        assertEquals(this, other.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, other.toString(), String("()"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.toString(), String("(0, 1, 2, 3, 4, 5, 6, 7, 8, 9)"));
    }

    TEST(ForwardList, MergeCompare) {
        ForwardList<int> list({9, 7, 5, 3, 1});
        ForwardList<int> other({8, 6, 4, 2, 0});
        std::greater<int> comp;
        list.merge(other, comp);
        assertEquals(this, other.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, other.toString(), String("()"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.toString(), String("(9, 8, 7, 6, 5, 4, 3, 2, 1, 0)"));
    }

    TEST(ForwardList, MergeMoveCompare) {
        ForwardList<int> list({9, 7, 5, 3, 1});
        ForwardList<int> other({8, 6, 4, 2, 0});
        std::greater<int> comp;
        list.merge(std::move(other), comp);
        assertEquals(this, other.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, other.toString(), String("()"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.toString(), String("(9, 8, 7, 6, 5, 4, 3, 2, 1, 0)"));
    }

    TEST(ForwardList, SpliceAfter) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({100, 200, 300, 400, 500});
        list.spliceAfter(list.cbegin(), other);
        assertEquals(this, other.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, other.toString(), String("()"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.toString(), String("(0, 100, 200, 300, 400, 500, 1, 2, 3, 4)"));
    }

    TEST(ForwardList, SpliceAfterMove) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({100, 200, 300, 400, 500});
        list.spliceAfter(list.cbegin(), std::move(other));
        assertEquals(this, other.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, other.toString(), String("()"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (10));
        assertEquals(this, list.toString(), String("(0, 100, 200, 300, 400, 500, 1, 2, 3, 4)"));
    }

    TEST(ForwardList, SpliceAfterPos) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({100, 200, 300, 400, 500});
        list.spliceAfter(list.cbegin(), other, ++other.cbegin());
        assertEquals(this, other.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, other.toString(), String("(100, 200, 400, 500)"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, list.toString(), String("(0, 300, 1, 2, 3, 4)"));
    }

    TEST(ForwardList, SpliceAfterPosMove) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({100, 200, 300, 400, 500});
        list.spliceAfter(list.cbegin(), std::move(other), ++other.cbegin());
        assertEquals(this, other.getSize(), static_cast <std::size_t> (4));
        assertEquals(this, other.toString(), String("(100, 200, 400, 500)"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (6));
        assertEquals(this, list.toString(), String("(0, 300, 1, 2, 3, 4)"));
    }

    TEST(ForwardList, SpliceAfterRange) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({100, 200, 300, 400, 500});
        list.spliceAfter(list.cbegin(), other, other.cbegin(), std::next(other.cbegin(), 4));
        assertEquals(this, other.getSize(), static_cast <std::size_t> (2));
        assertEquals(this, other.toString(), String("(100, 500)"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, list.toString(), String("(0, 200, 300, 400, 1, 2, 3, 4)"));
    }

    TEST(ForwardList, SpliceAfterRangeMove) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({100, 200, 300, 400, 500});
        list.spliceAfter(list.cbegin(), std::move(other), other.cbegin(), std::next(other.cbegin(), 4));
        assertEquals(this, other.getSize(), static_cast <std::size_t> (2));
        assertEquals(this, other.toString(), String("(100, 500)"));
        assertEquals(this, list.getSize(), static_cast <std::size_t> (8));
        assertEquals(this, list.toString(), String("(0, 200, 300, 400, 1, 2, 3, 4)"));
    }

    TEST(ForwardList, Remove) {
        ForwardList<int> list({0, 1, 2, 1, 2, 5, 6, 3, 1, 1, 4});
        list.remove(1);
        assertEquals(this, list.toString(), String("(0, 2, 2, 5, 6, 3, 4)"));
        list.remove(2);
        assertEquals(this, list.toString(), String("(0, 5, 6, 3, 4)"));
    }

    TEST(ForwardList, RemoveIf) {
        ForwardList<int> list({0, 1, 2, 1, 2, 5, 6, 3, 1, 1, 4});
        list.removeIf([&](int current) {
            return current > 2;
        });
        assertEquals(this, list.toString(), String("(0, 1, 2, 1, 2, 1, 1)"));
        list.removeIf([&](int current) {
            return current % 2 == 0;
        });
        assertEquals(this, list.toString(), String("(1, 1, 1, 1)"));
    }

    TEST(ForwardList, Reverse) {
        ForwardList<int> list({0, 1, 2, 3, 4, 5});
        list.reverse();
        assertEquals(this, list.toString(), String("(5, 4, 3, 2, 1, 0)"));
    }

    TEST(ForwardList, Unique) {
        ForwardList<int> list({1, 1, 2, 3, 1, 1, 1, 1, 1, 2, 2});
        list.unique();
        assertEquals(this, list.toString(), String("(1, 2, 3, 1, 2)"));
    }

    TEST(ForwardList, AssignCopy) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({10, 20, 30, 40, 50, 60});
        assertEquals(this, list.toString(), String("(0, 1, 2, 3, 4)"));
        list = other;
        assertEquals(this, list.toString(), String("(10, 20, 30, 40, 50, 60)"));
        assertEquals(this, other.toString(), String("(10, 20, 30, 40, 50, 60)"));
    }

    TEST(ForwardList, AssignMove) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({10, 20, 30, 40, 50, 60});
        assertEquals(this, list.toString(), String("(0, 1, 2, 3, 4)"));
        list = std::move(other);
        assertEquals(this, list.toString(), String("(10, 20, 30, 40, 50, 60)"));
    }

    TEST(ForwardList, Equals) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({0, 1, 2, 3, 4});
        assertEquals(this, list, other);
    }

    TEST(ForwardList, NotEquals) {
        ForwardList<int> list({0, 1, 2, 3, 4});
        ForwardList<int> other({0, 1, 3, 3, 4});
        assertNotEquals(this, list, other);
    }
