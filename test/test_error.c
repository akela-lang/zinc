#include "zinc/error.h"
#include "zinc/error_unit_test.h"
#include <stdlib.h>
#include "zinc/memory.h"
#include "zinc/unit_test.h"

void test_error_list()
{
    test_name(__func__);

    struct error* e = NULL;
    malloc_safe((void**)&e, sizeof(struct error));
    error_init(e);

    struct error_list el;
    error_list_init(&el);
    error_list_add(&el, e);

    struct error* e0 = el.head;
    assert_ptr(e0, "ptr e0");
    expect_true(el.head == e, "head");
    expect_true(el.tail == e, "tail");

    error_list_destroy(&el);
}

void test_error()
{
    test_error_list();
}