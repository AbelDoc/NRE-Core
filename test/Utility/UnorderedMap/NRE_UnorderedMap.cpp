
    /**
     * @file NRE_UnorderedMap.cpp
     * @brief Test of Utility's API's Container : UnorderedMap
     * @author Louis ABEL
     * @date 01/07/2019
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Utility.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Utility;
    using namespace NRE::Tester;

    TEST(UnorderedMap, Ctr) {
        UnorderedMap<std::string, int> table;
        assertEquals(this, table.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, table.toString(), String("{}"));
    }

    TEST(UnorderedMap, CtrInput) {
        std::vector<Pair<std::string, int>> input({{"A", 1}, {"B", 2}, {"C", 3}});
        UnorderedMap<std::string, int> table(input.begin(), input.end());
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, CtrList) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, CtrCopy) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        UnorderedMap<std::string, int> copy(table);
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (3));
        String str(copy.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, CtrMove) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        UnorderedMap<std::string, int> copy(std::move(table));
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (3));
        String str(copy.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, Get) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.get("A"), 1);
    }

    TEST(UnorderedMap, BucketCount) {
        UnorderedMap<std::string, int> table(10);
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (10));
        UnorderedMap<std::string, int> table2;
        assertGreaterOrEquals(this, table2.getBucketCount(), static_cast <std::size_t> (0));
        table2.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertGreaterOrEquals(this, table2.getBucketCount(), static_cast <std::size_t> (3));
    }

    TEST(UnorderedMap, MaxBucketCount) {
        UnorderedMap<std::string, int> table;
        assertEquals(this, table.getMaxBucketCount(), std::numeric_limits<std::size_t>::max());
    }

    TEST(UnorderedMap, Size) {
        UnorderedMap<std::string, int> table;
        assertEquals(this, table.getSize(), static_cast <std::size_t> (0));
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
    }

    TEST(UnorderedMap, MaxLoadFactor) {
        UnorderedMap<std::string, int> table;
        assertLesserOrEquals(this, table.getMaxLoadFactor(), 0.901f);
        table.setMaxLoadFactor(0.5f);
        assertLesserOrEquals(this, table.getMaxLoadFactor(), 0.501f);
    }

    TEST(UnorderedMap, LoadFactor) {
        UnorderedMap<std::string, int> table(6);
        assertLesserOrEquals(this, table.getLoadFactor(), 0.001f);
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertLesserOrEquals(this, table.getLoadFactor(), 0.501f);
    }

    TEST(UnorderedMap, MaxSize) {
        UnorderedMap<std::string, int> table;
        assertEquals(this, table.getMaxSize(), std::numeric_limits<std::size_t>::max());
    }

    TEST(UnorderedMap, Empty) {
        UnorderedMap<std::string, int> table;
        assertTrue(this, table.isEmpty());
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertFalse(this, table.isEmpty());
    }

    TEST(UnorderedMap, Count) {
        UnorderedMap<std::string, int> table;
        assertEquals(this, table.getCount("A"), static_cast <std::size_t> (0));
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getCount("A"), static_cast <std::size_t> (1));
    }

    TEST(UnorderedMap, BeginBucket) {
        UnorderedMap<std::string, int> table({{"A", 1}});
        assertEquals(this, *(table.begin(table.getBucket("A"))), {"A", 1});
    }

    TEST(UnorderedMap, Begin) {
        UnorderedMap<std::string, int> table({{"A", 1}});
        assertEquals(this, *(table.begin()), {"A", 1});
    }

    TEST(UnorderedMap, Insert) {
        UnorderedMap<std::string, int> table;
        table.insert({"A", 1});
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, InsertInput) {
        std::vector<Pair<std::string, int>> input({{"A", 1}});
        UnorderedMap<std::string, int> table;
        table.insert(input.begin(), input.end());
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, InsertList) {
        UnorderedMap<std::string, int> table;
        table.insert({{"A", 1}});
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, InsertHint) {
        UnorderedMap<std::string, int> table;
        table.insertHint(table.cbegin(), {"A", 1});
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, Emplace) {
        UnorderedMap<std::string, int> table;
        table.emplace("A", 1);
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, EmplaceHint) {
        UnorderedMap<std::string, int> table;
        table.emplaceHint(table.cbegin(), "A", 1);
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, Clear) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        table.clear();
        table.emplace("A", 1);
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, Swap) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        UnorderedMap<std::string, int> swap;
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, swap.getSize(), static_cast <std::size_t> (0));
        swap.swap(table);
        assertEquals(this, swap.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, table.getSize(), static_cast <std::size_t> (0));
    }

    TEST(UnorderedMap, Reserve) {
        UnorderedMap<std::string, int> table;
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (0));
        table.reserve(10);
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (10));
    }

    TEST(UnorderedMap, Rehash) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (3));
        table.rehash(100);
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (100));
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, EqualRange) {
        UnorderedMap<std::string, int> table({{"A", 1}});
        auto pIt = table.equalRange("A");
        assertTrue(this, table.begin() == pIt.first);
        assertTrue(this, table.end() == pIt.second);
        pIt = table.equalRange("B");
        assertTrue(this, table.end() == pIt.first);
        assertTrue(this, table.end() == pIt.second);
    }

    TEST(UnorderedMap, Find) {
        UnorderedMap<std::string, int> table({{"A", 1}});
        assertTrue(this, table.find("A") == table.begin());
        assertTrue(this, table.find("B") == table.end());
    }

    TEST(UnorderedMap, Erase) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
        table.erase(table.find("A"));
        String str2(table.toString());
        assertFalse(str2.contains("(A, 1)"));
        assertTrue(str2.contains("(B, 2)"));
        assertTrue(str2.contains("(C, 3)"));
    }

    TEST(UnorderedMap, EraseRange) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
        table.erase(table.cbegin(), table.cend());
        assertEquals(this, table.toString(), String("{}"));
    }

    TEST(UnorderedMap, EraseKey) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.erase("A"), static_cast <std::size_t> (1));
        assertEquals(this, table.erase("A"), static_cast <std::size_t> (0));
        assertEquals(this, table.erase("D"), static_cast <std::size_t> (0));
    }

    TEST(UnorderedMap, Assign) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        UnorderedMap<std::string, int> assign;
        assign = table;
        String str(assign.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, AssignMove) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        UnorderedMap<std::string, int> assign;
        assign = std::move(table);
        String str(assign.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, Access) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table["A"], 1);
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
        assertFalse(str.contains("(D, 4)"));
        table["D"] = 4;
        assertEquals(this, table["D"], 4);
        String str2(table.toString());
        assertTrue(str2.contains("(A, 1)"));
        assertTrue(str2.contains("(B, 2)"));
        assertTrue(str2.contains("(C, 3)"));
        assertTrue(str2.contains("(D, 4)"));
    }

    TEST(UnorderedMap, Equals) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        UnorderedMap<std::string, int> other({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table, other);
    }

    TEST(UnorderedMap, NotEquals) {
        UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        UnorderedMap<std::string, int> other({{"A", 1}, {"B", 3}, {"C", 3}});
        assertNotEquals(this, table, other);
    }
