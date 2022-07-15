#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdio.h>
#include "api.h"

#define BUFFER_CHUNK 64

struct buffer {
    size_t size;
    size_t buf_size;
    char* buf;
};

ZINC_API void buffer_init(struct buffer* bf);

/* dynamic-destroy bf */
ZINC_API void buffer_destroy(struct buffer* bf);

ZINC_API enum result buffer_add_char(struct buffer* bf, char c);
ZINC_API void buffer_reset(struct buffer* bf);
ZINC_API void buffer_clear(struct buffer* bf);

/* dynamic-output b */
ZINC_API enum result buffer_copy(struct buffer* a, struct buffer* b);

ZINC_API enum result buffer_copy_str(struct buffer* a, char* b);

/* dynamic-output array */
ZINC_API enum result buffer2array(struct buffer* bf, char** array);

/* dynamic-output bf */
ZINC_API enum result array2buffer(char* a, struct buffer* bf);

ZINC_API enum result next_char(struct buffer* bf, size_t* pos, struct buffer* bf2);
ZINC_API int buffer_compare(struct buffer* a, struct buffer* b);
ZINC_API int buffer_str_compare(struct buffer* a, char* b);
ZINC_API enum result buffer_uslice(struct buffer* src, struct buffer* dest, size_t start, size_t end);

#endif
