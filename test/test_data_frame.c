#include "zinc/unit_test.h"
#include "zinc/data_frame.h"

void TestDataFrame1()
{
    test_name(__func__);

    struct Vector* v0 = NULL;
    VectorCreate(&v0, sizeof(double));

    struct Vector* v1 = NULL;
    VectorCreate(&v1, sizeof(double));

    struct Series* sn0 = NULL;
    SeriesCreate(&sn0);

    struct Series* sn1 = NULL;
    SeriesCreate(&sn1);

    struct DataFrame* sl = NULL;
    DataFrameCreate(&sl);

    sn0->vector = v0;
    DataFrameAdd(sl, sn0);

    sn1->vector = v1;
    DataFrameAdd(sl, sn1);

    assert_ptr(v0, "ptr ds0");
    assert_ptr(sn0, "ptr sn0");
    assert_ptr(v1, "ptr ds1");
    assert_ptr(sn1, "ptr sn1");
    assert_ptr(sl, "ptr sl");

    expect_ptr_equal(sl->head, sn0, "head");
    expect_ptr_equal(sn0->prev, NULL, "sn0 prev");
    expect_ptr_equal(sn0->next, sn1, "sn0 next");
    expect_ptr_equal(sn1->prev, sn0, "sn1 prev");
    expect_ptr_equal(sn1->next, NULL, "sn1 next");
    expect_ptr_equal(sl->tail, sn1, "tail");

    DataFrameDestroy(sl);
}

void TestDataFrame()
{
    TestDataFrame1();
}