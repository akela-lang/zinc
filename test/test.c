#include "zinc/assert.h"
#include "test_buffer.h"
#include "test_result.h"
#include "test_memory.h"

/* static-output */
int main()
{
	test_result();
	test_memory();
	test_buffer();
	print_results();
	return 0;
}
