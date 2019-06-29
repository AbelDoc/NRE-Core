
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
        assertGreaterOrEquals(this, table.getSize(), static_cast <std::size_t> (0));
        table.insert({{"A", 1}, {"B", 2}, {"C", 3}});
        assertGreaterOrEquals(this, table.getSize(), static_cast <std::size_t> (3));
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
