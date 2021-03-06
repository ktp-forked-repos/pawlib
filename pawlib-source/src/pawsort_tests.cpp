#include "pawlib/pawsort_tests.hpp"

namespace pawlib
{
    void TestSuite_Pawsort::load_tests()
    {
        register_test("P-tB3001",
            new TestPawSort(TestSort::ARRAY_SORTED), true,
            new TestStdSort(TestSort::ARRAY_SORTED));

        register_test("P-tB3002",
            new TestPawSort(TestSort::ARRAY_REVERSED), true,
            new TestStdSort(TestSort::ARRAY_REVERSED));

        register_test("P-tB3003",
            new TestPawSort(TestSort::ARRAY_NEARLY_2), true,
            new TestStdSort(TestSort::ARRAY_NEARLY_2));

        register_test("P-tB3004",
            new TestPawSort(TestSort::ARRAY_NEARLY_5), true,
            new TestStdSort(TestSort::ARRAY_NEARLY_5));

        register_test("P-tB3005",
            new TestPawSort(TestSort::ARRAY_FEW_UNIQUE), true,
            new TestStdSort(TestSort::ARRAY_FEW_UNIQUE));

        register_test("P-tB3006",
            new TestPawSort(TestSort::ARRAY_BLACK_SHEEP), true,
            new TestStdSort(TestSort::ARRAY_BLACK_SHEEP));

        register_test("P-tB3007",
            new TestPawSort(TestSort::ARRAY_DOUBLE_CLIMB), true,
            new TestStdSort(TestSort::ARRAY_DOUBLE_CLIMB));

        register_test("P-tB3008",
            new TestPawSort(TestSort::ARRAY_DOUBLE_DROP), true,
            new TestStdSort(TestSort::ARRAY_DOUBLE_DROP));

        register_test("P-tB3009",
            new TestPawSort(TestSort::ARRAY_STAIRS), true,
            new TestStdSort(TestSort::ARRAY_STAIRS));

        register_test("P-tB3010",
            new TestPawSort(TestSort::ARRAY_MOUNTAIN), true,
            new TestStdSort(TestSort::ARRAY_MOUNTAIN));

        register_test("P-tB3011",
            new TestPawSort(TestSort::ARRAY_DOUBLE_MOUNTAIN), true,
            new TestStdSort(TestSort::ARRAY_DOUBLE_MOUNTAIN));

        register_test("P-tB3012",
            new TestPawSort(TestSort::ARRAY_EVEREST), true,
            new TestStdSort(TestSort::ARRAY_EVEREST));

        register_test("P-tB3013",
            new TestPawSort(TestSort::ARRAY_CLIFF), true,
            new TestStdSort(TestSort::ARRAY_CLIFF));

        register_test("P-tB3014",
            new TestPawSort(TestSort::ARRAY_SPIKE), true,
            new TestStdSort(TestSort::ARRAY_SPIKE));

        register_test("P-tB3015",
            new TestPawSort(TestSort::ARRAY_CHICKEN), true,
            new TestStdSort(TestSort::ARRAY_CHICKEN));

        register_test("P-tB3016",
            new TestPawSort(TestSort::ARRAY_NIGHTMARE), true,
            new TestStdSort(TestSort::ARRAY_NIGHTMARE));
            
        register_test("P-tB3021",
            new TestInsertionSort(TestSort::ARRAY_SORTED), true);

        register_test("P-tB3022",
            new TestInsertionSort(TestSort::ARRAY_REVERSED), true);

        register_test("P-tB3023",
            new TestInsertionSort(TestSort::ARRAY_NEARLY_2), true);

        register_test("P-tB3024",
            new TestInsertionSort(TestSort::ARRAY_NEARLY_5), true);

        register_test("P-tB3025",
            new TestInsertionSort(TestSort::ARRAY_FEW_UNIQUE), true);

        register_test("P-tB3026",
            new TestInsertionSort(TestSort::ARRAY_BLACK_SHEEP), true);

        register_test("P-tB3027",
            new TestInsertionSort(TestSort::ARRAY_DOUBLE_CLIMB), true);

        register_test("P-tB3028",
            new TestInsertionSort(TestSort::ARRAY_DOUBLE_DROP), true);

        register_test("P-tB3029",
            new TestInsertionSort(TestSort::ARRAY_STAIRS), true);

        register_test("P-tB3030*",
            new TestInsertionSort(TestSort::ARRAY_MOUNTAIN), true);

        register_test("P-tB3031",
            new TestInsertionSort(TestSort::ARRAY_DOUBLE_MOUNTAIN), true);

        register_test("P-tB3032",
            new TestInsertionSort(TestSort::ARRAY_EVEREST), true);

        register_test("P-tB3033",
            new TestInsertionSort(TestSort::ARRAY_CLIFF), true);

        register_test("P-tB3034",
            new TestInsertionSort(TestSort::ARRAY_SPIKE), true);

        register_test("P-tB3035",
            new TestInsertionSort(TestSort::ARRAY_CHICKEN), true);

        register_test("P-tB3036",
            new TestInsertionSort(TestSort::ARRAY_NIGHTMARE), true);
    }
}