#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "result.h"
#include "buffer.h"
#include "memory.h"
#include "utf8.h"

/* static-output */
/* initialize-output bf{} */
void buffer_init(struct buffer* bf)
{
    bf->buf = NULL;
    bf->buf_size = 0;
    bf->size = 0;
}

/* dynamic-destroy bf{} */
void buffer_destroy(struct buffer* bf)
{
    if (bf) {
        if (bf->buf) {
            /* destroy bf{buf} */
            free(bf->buf);
        }
    }
}

/* dynamic-output bf{} */
void buffer_add_char(struct buffer* bf, char c)
{
    enum result r = result_ok;

    if (bf->size + 1 > bf->buf_size) {
        if (bf->buf == NULL) {
            /* allocate buf{} */
            malloc_safe((void**)&bf->buf, BUFFER_CHUNK);
        } else {
            /* allocate buf{} */
            realloc_safe((void**)&bf->buf, bf->buf_size + BUFFER_CHUNK);
        }
        bf->buf_size += BUFFER_CHUNK;
    }
    bf->buf[bf->size++] = c;
}

void buffer_finish(struct buffer* bf)
{
    buffer_add_char(bf, '\0');
    bf->size--;
}

/* dynamic-destroy bf{} */
void buffer_reset(struct buffer* bf)
{
    if (bf != NULL) {
        if (bf->buf != NULL) {
            /* destroy bf{} */
            free(bf->buf);
            buffer_init(bf);
        }
    }
}

/* static-output */
void buffer_clear(struct buffer* bf)
{
    if (bf != NULL) {
        bf->size = 0;
    }
}

/* dynamic-output b{} */
void buffer_copy(struct buffer* a, struct buffer* b)
{
    for (int i = 0; i < a->size; i++) {
        /* allocate b{} */
        buffer_add_char(b, a->buf[i]);
    }
}

/* dynamic-output a{} */
void buffer_copy_str(struct buffer* a, const char* b)
{
    while (*b) {
        /* allocate a{} */
        buffer_add_char(a, *b);
        b++;
    }
}

/* dynamic-output a */
void buffer2array(struct buffer* bf, char** a)
{
    /* allocate a */
    malloc_safe((void**)a, bf->size + 1);
    for (int i = 0; i < bf->size; i++) {
        (*a)[i] = bf->buf[i];
    }
    (*a)[bf->size] = '\0';
}

/* bf must be initialized */
/* dynamic-output bf{} */
void array2buffer(const char* a, struct buffer* bf)
{
    const char* p = a;
    while (*p != '\0') {
        /* allocate b{} */
        buffer_add_char(bf, *p);
        p++;
    }
}

/* dynamic-output bf2{} */
enum result next_char(struct buffer* bf, size_t* pos, struct buffer* bf2)
{
    char c = bf->buf[(*pos)++];
    int count;
    enum result r = check_num_bytes(c, &count);
    if (r == result_error) {
        return r;
    }
    buffer_clear(bf2);

    /* allocate bf2{} */
    buffer_add_char(bf2, c);
    for (int i = 1; i < count; i++) {
        c = bf->buf[(*pos)++];
        r = check_extra_byte(c);
        if (r == result_error) {
            return r;
        }

        /* allocate bf2{} */
        buffer_add_char(bf2, c);
    }
    return result_ok;
}

/*
* if strings are equal, return 1
* otherwise, return 0
*/
/* static-output */
int buffer_compare(struct buffer* a, struct buffer* b)
{
    if (a->size != b->size) {
        return 0;
    }

    for (int i = 0; i < a->size; i++) {
        if (a->buf[i] != b->buf[i]) {
            return 0;
        }
    }
    return 1;
}

/*
* if strings are equal, return 1
* otherwise, return 0
*/
/* static-output */
int buffer_compare_str(struct buffer* a, const char* b)
{
    size_t size = strlen(b);
    if (a->size != size) {
        return 0;
    }

    for (int i = 0; i < a->size; i++) {
        if (a->buf[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

/* dynamic-output dest{} */
enum result buffer_uslice(struct buffer* src, struct buffer* dest, size_t start, size_t end)
{
    enum result r = result_ok;
    char c;
    int count;

    size_t i = 0;
    size_t index = 0;
    while (i < src->size && index < end) {
        c = src->buf[i++];
        r = check_num_bytes(c, &count);
        if (r == result_error) return r;

        if (index >= start && index < end) {
            /* allocate dest{} */
            buffer_add_char(dest, c);
        }


        for (int j = 1; j < count; j++) {
            c = src->buf[i++];
            r = check_extra_byte(c);
            if (r == result_error) return r;

            if (index >= start && index < end) {
                /* allocate dest{} */
                buffer_add_char(dest, c);
            }
        }

        index++;
    }

    return r;
}
