
    /**
     * @file NRE_HashTable.cpp
     * @brief Test of Utility's API's Object : HashTable
     * @author Louis ABEL
     * @date 28/06/2019
     * @copyright CC-BY-NC-SA
     */

    #include "../../../src/Header/NRE_Utility.hpp"
    #include <Header/NRE_Tester.hpp>

    using namespace NRE::Utility;
    using namespace NRE::Tester;

    TEST(HashTable, Ctr) {
        HashTable<std::string, int> table;
        assertEquals(this, table.getSize(), static_cast <std::size_t> (0));
        assertEquals(this, table.toString(), String("{}"));
    }

    TEST(HashTable, CtrInput) {
        std::vector<Pair<std::string, int>> input({{"A", 1}, {"B", 2}, {"C", 3}});
        HashTable<std::string, int> table(input.begin(), input.end());
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(HashTable, CtrList) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(HashTable, CtrCopy) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        HashTable<std::string, int> copy(table);
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (3));
        String str(copy.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(HashTable, CtrMove) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        HashTable<std::string, int> copy(std::move(table));
        assertEquals(this, copy.getSize(), static_cast <std::size_t> (3));
        String str(copy.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(HashTable, Get) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.get("A"), 1);
    }

    TEST(HashTable, BucketCount) {
        HashTable<std::string, int> table(10);
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (10));
        HashTable<std::string, int> table2;
        assertGreaterOrEquals(this, table2.getBucketCount(), static_cast <std::size_t> (0));
        table2.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertGreaterOrEquals(this, table2.getBucketCount(), static_cast <std::size_t> (3));
    }

    TEST(HashTable, MaxBucketCount) {
        HashTable<std::string, int> table;
        assertEquals(this, table.getMaxBucketCount(), std::numeric_limits<std::size_t>::max());
    }

    TEST(HashTable, Size) {
        HashTable<std::string, int> table;
        assertEquals(this, table.getSize(), static_cast <std::size_t> (0));
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
    }

    TEST(HashTable, MaxLoadFactor) {
        HashTable<std::string, int> table;
        assertLesserOrEquals(this, table.getMaxLoadFactor(), 0.901f);
        table.setMaxLoadFactor(0.5f);
        assertLesserOrEquals(this, table.getMaxLoadFactor(), 0.501f);
    }

    TEST(HashTable, LoadFactor) {
        HashTable<std::string, int> table(6);
        assertLesserOrEquals(this, table.getLoadFactor(), 0.001f);
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertLesserOrEquals(this, table.getLoadFactor(), 0.501f);
    }

    TEST(HashTable, MaxSize) {
        HashTable<std::string, int> table;
        assertEquals(this, table.getMaxSize(), std::numeric_limits<std::size_t>::max());
    }

    TEST(HashTable, Empty) {
        HashTable<std::string, int> table;
        assertTrue(this, table.isEmpty());
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertFalse(this, table.isEmpty());
    }

    TEST(HashTable, Count) {
        HashTable<std::string, int> table;
        assertEquals(this, table.getCount("A"), static_cast <std::size_t> (0));
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getCount("A"), static_cast <std::size_t> (1));
    }

    TEST(HashTable, BeginBucket) {
        HashTable<std::string, int> table({{"A", 1}});
        assertEquals(this, *(table.begin(table.getBucket("A"))), {"A", 1});
    }

    TEST(HashTable, Begin) {
        HashTable<std::string, int> table({{"A", 1}});
        assertEquals(this, *(table.begin()), {"A", 1});
    }

    TEST(HashTable, Insert) {
        HashTable<std::string, int> table;
        table.insert({"A", 1});
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(HashTable, InsertInput) {
        std::vector<Pair<std::string, int>> input({{"A", 1}});
        HashTable<std::string, int> table;
        table.insert(input.begin(), input.end());
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(HashTable, InsertList) {
        HashTable<std::string, int> table;
        table.insert({{"A", 1}});
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(HashTable, InsertHint) {
        HashTable<std::string, int> table;
        table.insertHint(table.cbegin(), {"A", 1});
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(HashTable, Emplace) {
        HashTable<std::string, int> table;
        table.emplace("A", 1);
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(HashTable, EmplaceHint) {
        HashTable<std::string, int> table;
        table.emplaceHint(table.cbegin(), "A", 1);
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(HashTable, Clear) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        table.clear();
        table.emplace("A", 1);
        assertEquals(this, table.toString(), String("{(A, 1)}"));
    }

    TEST(HashTable, Swap) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        HashTable<std::string, int> swap;
        assertEquals(this, table.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, swap.getSize(), static_cast <std::size_t> (0));
        swap.swap(table);
        assertEquals(this, swap.getSize(), static_cast <std::size_t> (3));
        assertEquals(this, table.getSize(), static_cast <std::size_t> (0));
    }

    TEST(HashTable, Reserve) {
        HashTable<std::string, int> table;
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (0));
        table.reserve(10);
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (10));
    }

    TEST(HashTable, Rehash) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (3));
        table.rehash(100);
        assertGreaterOrEquals(this, table.getBucketCount(), static_cast <std::size_t> (100));
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(HashTable, EqualRange) {
        HashTable<std::string, int> table({{"A", 1}});
        auto pIt = table.equalRange("A");
        assertTrue(this, table.begin() == pIt.first);
        assertTrue(this, table.end() == pIt.second);
        pIt = table.equalRange("B");
        assertTrue(this, table.end() == pIt.first);
        assertTrue(this, table.end() == pIt.second);
    }

    TEST(HashTable, Find) {
        HashTable<std::string, int> table({{"A", 1}});
        assertTrue(this, table.find("A") == table.begin());
        assertTrue(this, table.find("B") == table.end());
    }

    TEST(HashTable, Erase) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
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

    TEST(HashTable, EraseRange) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        String str(table.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
        table.erase(table.cbegin(), table.cend());
        assertEquals(this, table.toString(), String("{}"));
    }

    TEST(HashTable, EraseKey) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        assertEquals(this, table.erase("A"), static_cast <std::size_t> (1));
        assertEquals(this, table.erase("A"), static_cast <std::size_t> (0));
        assertEquals(this, table.erase("D"), static_cast <std::size_t> (0));
    }

    TEST(HashTable, Assign) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        HashTable<std::string, int> assign;
        assign = table;
        String str(assign.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(HashTable, AssignMove) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
        HashTable<std::string, int> assign;
        assign = std::move(table);
        String str(assign.toString());
        assertTrue(str.contains("(A, 1)"));
        assertTrue(str.contains("(B, 2)"));
        assertTrue(str.contains("(C, 3)"));
    }

    TEST(HashTable, Access) {
        HashTable<std::string, int> table({{"A", 1}, {"B", 2}, {"C", 3}});
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
