#include "zinc/unit_test.h"
#include "zinc/list.h"
#include "zinc/memory.h"

void destroy_int(int* x)
{
    free(x);
}

void test_list_1()
{
    test_name(__func__);

    struct list l;
    list_init(&l);

    int* n0 = NULL;
    malloc_safe((void**)&n0, sizeof(int));
    *n0 = 0;
    list_add_item(&l, n0);

    int* n1 = NULL;
    malloc_safe((void**)&n1, sizeof(int));
    *n1 = 1;
    list_add_item(&l, n1);

    int* n2 = NULL;
    malloc_safe((void**)&n2, sizeof(int));
    *n2 = 2;
    list_add_item(&l, n2);

    int* x0 = list_get(&l, 0);
    assert_ptr(x0, "ptr x0");
    expect_ptr_equal(x0, n0, "x0");
    expect_int_equal(*x0, 0, "0");

    int* x1 = list_get(&l, 1);
    assert_ptr(x1, "ptr x1");
    expect_ptr_equal(x1, n1, "x1");
    expect_int_equal(*x1, 1, "1");

    int* x2 = list_get(&l, 2);
    assert_ptr(x2, "ptr x2");
    expect_ptr_equal(x2, n2, "x2");
    expect_int_equal(*x2, 2, "2");

    list_destroy(&l, (list_node_destroy)destroy_int);
}


void test_list()
{
    test_list_1();
}