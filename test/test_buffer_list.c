#include "zinc/buffer_list.h"
#include "zinc/unit_test.h"
#include "zinc/memory.h"

void test_buffer_list1()
{
    test_name(__func__ );

    struct buffer_node* bn0 = NULL;
    malloc_safe((void**)&bn0, sizeof(struct buffer_node));
    buffer_node_init(bn0);
    buffer_init(&bn0->value);
    buffer_copy_str(&bn0->value, "one");

    struct buffer_node* bn1 = NULL;
    malloc_safe((void**)&bn1, sizeof(struct buffer_node));
    buffer_node_init(bn1);
    buffer_init(&bn1->value);
    buffer_copy_str(&bn1->value, "two");

    struct buffer_list bl;
    buffer_list_init(&bl);

    expect_null(bl.head, "head 0");
    expect_null(bl.tail, "tail 0");

    buffer_list_add(&bl, bn0);
    expect_ptr_equal(bl.head, bn0, "head 1");
    expect_ptr_equal(bl.tail, bn0, "tail 1");
    expect_null(bn0->next, "next 1");
    expect_null(bn0->prev, "next 1");

    buffer_list_add(&bl, bn1);
    expect_ptr_equal(bl.head, bn0, "head 2");
    expect_ptr_equal(bl.tail, bn1, "tail 2");
    expect_ptr_equal(bn0->next, bn1, "next bn0 2");
    expect_ptr_equal(bn0->prev, NULL, "prev bn0 2");
    expect_ptr_equal(bn1->next, NULL, "next bn1 2");
    expect_ptr_equal(bn1->prev, bn0, "prev bn1 2");

    buffer_list_destroy(&bl);
}

void test_buffer_list()
{
    test_buffer_list1();
}