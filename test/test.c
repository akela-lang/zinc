#include "zinc/unit_test.h"
#include "test_buffer.h"
#include "test_result.h"
#include "test_memory.h"
#include "test_unit_test.h"
#include "test_utf8.h"
#include "test_hash.h"
#include "test_os_unix.h"

/* static-output */
int main()
{
	test_result();
	test_memory();
	test_assert();
	test_utf8();
	test_buffer();
	test_hash();
    test_os_unix();
	print_results();
	return 0;
}
