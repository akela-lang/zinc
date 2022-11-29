#include "zinc/unit_test.h"
#include "zinc/sort.h"

#define ARRAY_SIZE 10

void test_sort1()
{
    test_name(__func__);
    int in[ARRAY_SIZE] = {5, 2, 6, 8, 9, 4, 1, 3, 7, 0};
    qsort(in, 0, ARRAY_SIZE - 1);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        expect_int_equal(in[i], i, "in array");
    }
}


void test_sort()
{
    test_sort1();
}