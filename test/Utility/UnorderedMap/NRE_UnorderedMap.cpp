
    /**
     * @file NRE_UnorderedMap.cpp
     * @brief Test of Utility's API's Container : UnorderedMap
     * @author Louis ABEL
     * @date 01/07/2019
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Utility.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE;
    using namespace NRE::Utility;
    using namespace NRE::Tester;

    TEST(UnorderedMap, Ctr) {
        Utility::UnorderedMap<std::string, int> table;
        assertEquals(this, table.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, table.toString(), String("{}"));
    }

    TEST(UnorderedMap, CtrInput) {
        std::vector<Pair<std::string, int>> input({{"A", 1}, {"B", 2}, {"C", 3}});
        Utility::UnorderedMap<std::string, int> table(input.begin(), input.end());
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, CtrList) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, CtrCopy) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        Utility::UnorderedMap<std::string, int> copy(table);
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (3));
        String str(copy.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, CtrMove) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        Utility::UnorderedMap<std::string, int> copy(std::move(table));
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (3));
        String str(copy.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, Get) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.get("A"), 1);
    }

    TEST(UnorderedMap, BucketCount) {
        Utility::UnorderedMap<std::string, int> table(10);
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (10));
        Utility::UnorderedMap<std::string, int> table2;
        assertGreaterOrEquals(this, table2.getBucketCount(), static_cast <std::size_t> (0));
        table2.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertGreaterOrEquals(this, table2.getBucketCount(), static_cast <std::size_t> (3));
    }

    TEST(UnorderedMap, MaxBucketCount) {
        Utility::UnorderedMap<std::string, int> table;
        assertEquals(this, table.getMaxBucketCount(), std::numeric_limits<std::size_t>::max());
    }

    TEST(UnorderedMap, Size) {
        Utility::UnorderedMap<std::string, int> table;
        assertEquals(this, table.getSize(), static_cast <std::size_t> (0));
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
    }

    TEST(UnorderedMap, MaxLoadFactor) {
        Utility::UnorderedMap<std::string, int> table;
        assertLesserOrEquals(this, table.getMaxLoadFactor(), 0.901f);
        table.setMaxLoadFactor(0.5f);
        assertLesserOrEquals(this, table.getMaxLoadFactor(), 0.501f);
    }

    TEST(UnorderedMap, LoadFactor) {
        Utility::UnorderedMap<std::string, int> table(6);
        assertLesserOrEquals(this, table.getLoadFactor(), 0.001f);
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertLesserOrEquals(this, table.getLoadFactor(), 0.501f);
    }

    TEST(UnorderedMap, MaxSize) {
        Utility::UnorderedMap<std::string, int> table;
        assertEquals(this, table.getMaxSize(), std::numeric_limits<std::size_t>::max());
    }

    TEST(UnorderedMap, Empty) {
        Utility::UnorderedMap<std::string, int> table;
        assertTrue(this, table.isEmpty());
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertFalse(this, table.isEmpty());
    }

    TEST(UnorderedMap, Count) {
        Utility::UnorderedMap<std::string, int> table;
        assertEquals(this, table.getCount("A"), static_cast <std::size_t> (0));
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getCount("A"), static_cast <std::size_t> (1));
    }

    TEST(UnorderedMap, BeginBucket) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}});
        assertEquals(this, *(table.begin(table.getBucket("A"))), {"A", 1});
    }

    TEST(UnorderedMap, Begin) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}});
        assertEquals(this, *(table.begin()), {"A", 1});
    }

    TEST(UnorderedMap, Insert) {
        Utility::UnorderedMap<std::string, int> table;
        table.insert({"A", 1});
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, InsertInput) {
        std::vector<Pair<std::string, int>> input({{"A", 1}});
        Utility::UnorderedMap<std::string, int> table;
        table.insert(input.begin(), input.end());
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, InsertList) {
        Utility::UnorderedMap<std::string, int> table;
        table.insert({{"A", 1}});
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, InsertHint) {
        Utility::UnorderedMap<std::string, int> table;
        table.insertHint(table.cbegin(), {"A", 1});
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, Emplace) {
        Utility::UnorderedMap<std::string, int> table;
        table.emplace("A", 1);
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, EmplaceHint) {
        Utility::UnorderedMap<std::string, int> table;
        table.emplaceHint(table.cbegin(), "A", 1);
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, Clear) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        table.clear();
        table.emplace("A", 1);
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(UnorderedMap, Swap) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        Utility::UnorderedMap<std::string, int> swap;
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, swap.getSize(), static_cast <std::size_t> (0));
        swap.swap(table);
        assertEquals(this, swap.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, table.getSize(), static_cast <std::size_t> (0));
    }

    TEST(UnorderedMap, Reserve) {
        Utility::UnorderedMap<std::string, int> table;
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (0));
        table.reserve(10);
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (10));
    }

    TEST(UnorderedMap, Rehash) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (3));
        table.rehash(100);
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (100));
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, EqualRange) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}});
        auto pIt = table.equalRange("A");
        assertTrue(this, table.begin() == pIt.first);
        assertTrue(this, table.end() == pIt.second);
        pIt = table.equalRange("B");
        assertTrue(this, table.end() == pIt.first);
        assertTrue(this, table.end() == pIt.second);
    }

    TEST(UnorderedMap, Find) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}});
        assertTrue(this, table.find("A") == table.begin());
        assertTrue(this, table.find("B") == table.end());
    }

    TEST(UnorderedMap, Erase) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
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
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
        table.erase(table.cbegin(), table.cend());
        assertEquals(this, table.toString(), String("{}"));
    }

    TEST(UnorderedMap, EraseKey) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.erase("A"), static_cast <std::size_t> (1));
        assertEquals(this, table.erase("A"), static_cast <std::size_t> (0));
        assertEquals(this, table.erase("D"), static_cast <std::size_t> (0));
    }

    TEST(UnorderedMap, Assign) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        Utility::UnorderedMap<std::string, int> assign;
        assign = table;
        String str(assign.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, AssignMove) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        Utility::UnorderedMap<std::string, int> assign;
        assign = std::move(table);
        String str(assign.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(UnorderedMap, Access) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
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
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        Utility::UnorderedMap<std::string, int> other({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table, other);
    }

    TEST(UnorderedMap, NotEquals) {
        Utility::UnorderedMap<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        Utility::UnorderedMap<std::string, int> other({{"A", 1}, {"B", 3}, {"C", 3}});
        assertNotEquals(this, table, other);
    }
