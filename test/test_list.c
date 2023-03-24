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

    struct list_node* ln0 = l.head;
    assert_ptr(ln0, "ptr ln0");
    expect_ptr_equal(ln0->item, n0, "n0");
    expect_int_equal(*n0, 0, "0");

    struct list_node* ln1 = ln0->next;
    assert_ptr(ln1, "ptr ln1");
    expect_ptr_equal(ln1->item, n1, "n1");
    expect_int_equal(*n1, 1, "1");

    struct list_node* ln2 = ln1->next;
    assert_ptr(ln2, "ptr ln2");
    expect_ptr_equal(ln2->item, n2, "n2");
    expect_int_equal(*n2, 2, "2");

    list_destroy(&l, (list_node_destroy)destroy_int);
}


void test_list()
{
    test_list_1();
}