#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
#include "result.h"

/* dynamic-output return */
void *malloc_safe(size_t size)
{
    void* buf;
    
    /* allocate buf */
    buf = malloc(size);
    if (buf == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    return buf;
}

/* dynamic-output buf */
void realloc_safe(void** buf, size_t size)
{
    void* new_buf;
    /* allocate new_buf */
    new_buf = realloc(*buf, size);
    if (new_buf == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    *buf = new_buf;
}
