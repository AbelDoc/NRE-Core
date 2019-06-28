
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
        assertEquals(this, table.toString(), String("{(A, 1), (B, 2), (C, 3)}"));
    }
