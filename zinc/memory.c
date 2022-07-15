#include <stdlib.h>
#include "memory.h"
#include "result.h"

/* dynamic-output buf */
enum result malloc_safe(void** buf, size_t size)
{
    /* allocate buf */
    *buf = malloc(size);
    if (*buf == NULL) {
        return set_error("Out of memory");
    }
    return result_ok;
}

/* dynamic-output buf */
enum result realloc_safe(void** buf, size_t size)
{
    void* new_buf;
    /* allocate buf */
    new_buf = realloc(*buf, size);
    if (new_buf == NULL) {
        return set_error("Out of memory");
    }
    *buf = new_buf;
    return result_ok;
}
