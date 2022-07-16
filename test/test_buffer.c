#include <string.h>
#include <stdlib.h>
#include "zinc/assert.h"
#include "zinc/buffer.h"

/* static-output */
void test_buffer_init()
{
	test_name(__func__);

	struct buffer bf;
	buffer_init(&bf);
	expect_int_equal(bf.size, 0, "size");
	expect_int_equal(bf.buf_size, 0, "buf_size");
	expect_null(bf.buf, "buf");
}

/* static-output */
/* dynamic-temp bf{} */
void test_buffer_add_char()
{
	test_name(__func__);

	struct buffer bf;
	buffer_init(&bf);

	/* allocate bf{} */
	buffer_add_char(&bf, 'x');
	buffer_add_char(&bf, 'y');
	buffer_add_char(&bf, 'z');

	expect_str(&bf, "xyz", "str");

	/* destroy bf{} */
	buffer_destroy(&bf);
}

/* static-output */
/* dynamic-temp bf{} */
void test_buffer_clear()
{
	test_name(__func__);

	struct buffer bf;
	buffer_init(&bf);

	/* allocate bf{} */
	buffer_add_char(&bf, 'x');
	buffer_add_char(&bf, 'y');
	buffer_add_char(&bf, 'z');

	expect_str(&bf, "xyz", "str");
	buffer_clear(&bf);
	expect_str(&bf, "", "clear");

	/* destroy bf{} */
	buffer_destroy(&bf);
}

/* static-output */
/* dynamic-temp bf{} bf2{} */
void test_buffer_copy()
{
	test_name(__func__);

	struct buffer bf;
	struct buffer bf2;

	buffer_init(&bf);

	/* allocate bf{} */
	buffer_add_char(&bf, 'x');
	buffer_add_char(&bf, 'y');
	buffer_add_char(&bf, 'z');

	expect_str(&bf, "xyz", "str");

	buffer_init(&bf2);

	/* allocate bf2{} */
	buffer_copy(&bf, &bf2);

	expect_str(&bf2, "xyz", "copy");

	/* destroy bf{} bf2{} */
	buffer_destroy(&bf);
	buffer_destroy(&bf2);
}

/* static-output */
/* dynamic-temp bf{} a */
void test_buffer_buffer2array()
{
	test_name(__func__);

	enum result r;
	struct buffer bf;
	char* a;

	buffer_init(&bf);

	/* allocate bf{} */
	buffer_add_char(&bf, 'x');
	buffer_add_char(&bf, 'y');
	buffer_add_char(&bf, 'z');

	expect_str(&bf, "xyz", "str");

	/* allocate a */
	r = buffer2array(&bf, &a);
	assert_ok(r, "a");

	expect_true(strcmp(a, "xyz") == 0, "array");

	/* destroy bf{} a */
	buffer_destroy(&bf);
	free(a);
}

/* static-output */
/* dynamic-temp bf{} */
void test_buffer_array2buffer()
{
	test_name(__func__);

	char a[] = "xyz";
	struct buffer bf;
	enum result r;

	buffer_init(&bf);

	/* allocate bf{} */
	r = array2buffer(a, &bf);
	assert_ok(r, "bf");

	expect_str(&bf, "xyz", "str");


	/* destroy bf{} */
	buffer_destroy(&bf);
}

/* static-output */
/* dynamic-temp bf{} x{} */
void test_buffer_next_char()
{
	test_name(__func__);

	enum result r;
	struct buffer bf;
	buffer_init(&bf);

	/* allocate bf{} */
	buffer_add_char(&bf, 'x');
	buffer_add_char(&bf, 'y');
	buffer_add_char(&bf, 'z');

	struct buffer x;
	buffer_init(&x);
	size_t pos = 0;

	/* allocate x{} */
	r = next_char(&bf, &pos, &x);
	assert_ok(r, "next_char");

	expect_str(&x, "x", "x");

	/* allocate x{} */
	r = next_char(&bf, &pos, &x);
	assert_ok(r, "y");

	expect_str(&x, "y", "y");

	/* allocate x{} */
	r = next_char(&bf, &pos, &x);
	assert_ok(r, "z");

	expect_str(&x, "z", "z");

	/* destroy bf{} x{} */
	buffer_destroy(&bf);
	buffer_destroy(&x);
}

/* static-output */
/* dynamic bf{} bf2{} */
test_buffer_buffer_compare()
{
	test_name(__func__);

	struct buffer bf;
	buffer_init(&bf);

	/* allocate bf{} */
	buffer_add_char(&bf, 'x');
	buffer_add_char(&bf, 'y');
	buffer_add_char(&bf, 'z');

	struct buffer bf2;
	buffer_init(&bf2);

	/* allocate bf2{} */
	buffer_add_char(&bf2, 'x');
	buffer_add_char(&bf2, 'y');
	buffer_add_char(&bf2, 'z');

	expect_true(buffer_compare(&bf, &bf2), "equal");

	buffer_clear(&bf2);

	/* allocate bf2{} */
	buffer_add_char(&bf2, 'x');
	buffer_add_char(&bf2, 'y');
	buffer_add_char(&bf2, '1');

	expect_true(buffer_compare(&bf, &bf2) == 0, "not equal");

	/* destroy bf{} bf2{} */
	buffer_destroy(&bf);
	buffer_destroy(&bf2);
}

/* static-output */
/* dynamic-temp bf{} */
test_buffer_str_compare()
{
	test_name(__func__);

	struct buffer bf;
	buffer_init(&bf);

	/* allocate bf{} */
	buffer_add_char(&bf, 'x');
	buffer_add_char(&bf, 'y');
	buffer_add_char(&bf, 'z');

	expect_true(buffer_str_compare(&bf, "xyz") == 1, "equal");
	expect_true(buffer_str_compare(&bf, "xy1") == 0, "not equal");

	/* destroy bf{} */
	buffer_destroy(&bf);
}

/* static-output */
/* dynamic-temp bf{} bf2{} */
void test_buffer_uslice()
{
	test_name(__func__);

	struct buffer bf;
	struct buffer bf2;
	enum result r;

	buffer_init(&bf);

	/* allocate bf{} */
	buffer_add_char(&bf, 'a');
	buffer_add_char(&bf, 'b');
	buffer_add_char(&bf, 'c');
	buffer_add_char(&bf, 'd');
	buffer_add_char(&bf, 'e');
	buffer_add_char(&bf, 'f');

	buffer_init(&bf2);

	/* allocate bf2{} */
	r = buffer_uslice(&bf, &bf2, 2, 5);
	assert_ok(r, "buffer_uslice");

	assert_ptr(bf2.buf, "ptr buf2.buf");
	expect_int_equal(bf2.size, 3, "3 bf2.size");
	expect_str(&bf2, "cde", "cde bf2");

	/* destory bf{} bf2{} */
	buffer_destroy(&bf);
	buffer_destroy(&bf2);
}

/* static-output */
/* dynamic bf{} bf2{} */
void test_buffer_uslice2()
{
	test_name(__func__);

	struct buffer bf;
	struct buffer bf2;
	enum result r;

	buffer_init(&bf);

	/* allocate bf{} */
	buffer_add_char(&bf, 'a');
	buffer_add_char(&bf, 'b');
	buffer_add_char(&bf, 'c');
	buffer_add_char(&bf, 'd');
	buffer_add_char(&bf, 'e');
	buffer_add_char(&bf, 'f');

	buffer_init(&bf2);

	/* allocate bf2{} */
	r = buffer_uslice(&bf, &bf2, 2, 1000);
	assert_ok(r, "buffer_uslice");

	assert_ptr(bf2.buf, "ptr buf2.buf");
	expect_int_equal(bf2.size, 4, "4 bf2.size");
	expect_str(&bf2, "cdef", "cdef bf2");

	/* destroy bf{} bf2{} */
	buffer_destroy(&bf);
	buffer_destroy(&bf2);
}

/* static-output */
void test_buffer()
{
	test_buffer_init();
	test_buffer_add_char();
	test_buffer_clear();
	test_buffer_copy();
	test_buffer_buffer2array();
	test_buffer_array2buffer();
	test_buffer_next_char();
	test_buffer_buffer_compare();
	test_buffer_str_compare();
	test_buffer_uslice();
	test_buffer_uslice2();
}
