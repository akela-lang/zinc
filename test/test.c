#include "zinc/assert.h"
#include "test_buffer.h"
#include "test_result.h"
#include "test_memory.h"
#include "test_assert.h"

/* static-output */
int main()
{
	test_result();
	test_memory();
	test_assert();
	test_buffer();
	print_results();
	return 0;
}
