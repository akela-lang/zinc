#include <stdlib.h>
#include "zinc/result.h"
#include "zinc/memory.h"
#include "zinc/assert.h"

/* static-output */
/* dynamic-temp p */
void test_memory_malloc()
{
	test_name(__func__);

	char* p = NULL;

	/* allocate p*/
	p = malloc_safe(10);
	assert_ptr(p, "malloc_safe");

	for (int i = 0; i < 10; i++) {
		p[i] = 0;
	}

	/* destroy p */
	free(p);
}


/* static-output */
void test_memory()
{
	test_memory_malloc();
}
