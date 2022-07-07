#include "zinc/assert.h"
#include "zinc/result.h"

void test_result_set_error()
{
	test_name(__func__);

	enum result r;
	r = set_error("error x");
	assert_error(r, "set_error");
	expect_error_message("error x");
}

void test_result()
{
	test_result_set_error();
}
