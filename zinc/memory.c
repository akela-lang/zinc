#include <stdlib.h>
#include <stdio.h>
#include "memory.h"
#include "result.h"

/* dynamic-output buf */
void malloc_safe(void** buf, size_t size)
{
    /* allocate buf */
    *buf = malloc(size);
    if (*buf == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
}

/* dynamic-output buf */
void realloc_safe(void** buf, size_t size)
{
    void* new_buf;
    /* allocate buf */
    new_buf = realloc(*buf, size);
    if (new_buf == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    *buf = new_buf;
}

void free_safe(void* p)
{
    free(p);
}