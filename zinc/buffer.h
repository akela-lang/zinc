#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdio.h>
#include "api.h"
#include "result.h"

#define BUFFER_CHUNK 64

struct buffer {
    size_t size;
    size_t buf_size;
    char* buf;
};

/* static-output */
/* initialize-output bf{} */
ZINC_API void buffer_init(struct buffer* bf);

/* dynamic-destroy bf{} */
ZINC_API void buffer_destroy(struct buffer* bf);

/* dynamic-output bf{} */
ZINC_API void buffer_add_char(struct buffer* bf, char c);

ZINC_API void buffer_finish(struct buffer* bf);

/* dynamic-destroy bf{} */
ZINC_API void buffer_reset(struct buffer* bf);

/* static-output */
ZINC_API void buffer_clear(struct buffer* bf);

/* dynamic-output b{} */
ZINC_API void buffer_copy(struct buffer* a, struct buffer* b);

/* dynamic-output a{} */
ZINC_API void buffer_copy_str(struct buffer* a, const char* b);

/* dynamic-output a */
ZINC_API void buffer2array(struct buffer* bf, char** a);

/* dynamic-output bf{} */
ZINC_API void array2buffer(const char* a, struct buffer* bf);

/* dynamic-output bf2{} */
ZINC_API enum result next_char(struct buffer* bf, size_t* pos, struct buffer* bf2);

/* static-output */
ZINC_API int buffer_compare(struct buffer* a, struct buffer* b);

/* static-output */
ZINC_API int buffer_compare_str(struct buffer* a, const char* b);

/* dynamic-output dest{} */
ZINC_API enum result buffer_uslice(struct buffer* src, struct buffer* dest, size_t start, size_t end);

ZINC_API void buffer_add_format(struct buffer *bf, const char* fmt, ...);

#endif
