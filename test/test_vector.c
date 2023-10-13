#include "zinc/vector.h"
#include "zinc/data_frame.h"
#include "zinc/unit_test.h"

void test_vector_double()
{
    test_name(__func__);

    struct Vector* v = NULL;
    VectorCreate(&v, sizeof(double));

    double v0 = 5;
    double v1[4] = {1, 2, 3, 4};
    double v2 = 150;
    VectorAdd(v, &v0, 1);
    VectorAdd(v, v1, 4);
    VectorAdd(v, &v2, 1);
    expect_double_equal(VECTOR_DOUBLE(v, 0), v0, "v0");
    expect_double_equal(VECTOR_DOUBLE(v, 1), v1[0], "v1[0]");
    expect_double_equal(VECTOR_DOUBLE(v, 2), v1[1], "v1[1]");
    expect_double_equal(VECTOR_DOUBLE(v, 3), v1[2], "v1[2]");
    expect_double_equal(VECTOR_DOUBLE(v, 4), v1[3], "v1[3]");
    expect_double_equal(VECTOR_DOUBLE(v, 5), v2, "v2");

    VectorDestroy(v);
}

void test_vector_double_large()
{
    test_name(__func__);

    struct Vector* v = NULL;
    VectorCreate(&v, sizeof(double));

    double value[100];
    for (int i = 0; i < 100; i++) {
        value[i] = i;
    }
    VectorAdd(v, value, 100);

    for (int i = 0; i < 100; i++) {
        expect_double_equal(VECTOR_DOUBLE(v, i), value[i], "value[i]");
    }

    VectorDestroy(v);
}

void test_vector_list()
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

void test_vector()
{
    test_vector_double();
    test_vector_double_large();
    test_vector_list();
}
