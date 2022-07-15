#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "result.h"
#include "buffer.h"
#include "memory.h"

/* static-output */
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
enum result buffer_add_char(struct buffer* bf, char c)
{
    if (bf == NULL) {
        return set_error("adding char to a string that is not allocated");
    }

    enum result r;

    if (bf->size + 1 > bf->buf_size) {
        if (bf->buf == NULL) {
            /* allocate buf{} */
            r = malloc_safe(&bf->buf, BUFFER_CHUNK);
        } else {
            /* allocate buf{} */
            r = malloc_safe(&bf->buf, bf->buf_size + BUFFER_CHUNK);
        }
        if (r == result_error) {
            return r;
        }
        bf->buf_size += BUFFER_CHUNK;
    }
    bf->buf[bf->size++] = c;

    return result_ok;
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
enum result buffer_copy(struct buffer* a, struct buffer* b)
{
    enum result r;
    for (int i = 0; i < a->size; i++) {
        /* allocate b{} */
        r = buffer_add_char(b, a->buf[i]);
        if (r == result_error) {
            return r;
        }
    }
    return result_ok;
}

/* dynamic-output a{} */
enum result buffer_copy_str(struct buffer* a, char* b)
{
    enum result r;
    while (*b) {
        /* allocate a{} */
        r = buffer_add_char(a, *b);
        if (r == result_error) return r;
        b++;
    }

    return result_ok;
}

/* dynamic-output a */
enum result buffer2array(struct buffer* bf, char** a)
{
    /* allocate a */
    enum result r = malloc_safe(a, bf->size + 1);
    if (r == result_error) {
        return r;
    }
    for (int i = 0; i < bf->size; i++) {
        (*a)[i] = bf->buf[i];
    }
    (*a)[bf->size] = '\0';
    return result_ok;
}

/* bf must be initialized */
/* dynamic-output bf{} */
enum result array2buffer(char* a, struct buffer* bf)
{
    enum result r;
    char* p = a;
    while (*p != '\0') {
        /* allocate b{} */
        r = buffer_add_char(bf, *p);
        if (r == result_error) {
            return r;
        }
        p++;
    }
    return result_ok;
}

/* dynamic-output bf2{} */
enum result next_char(struct buffer* bf, size_t* pos, struct buffer* bf2)
{
    char c = bf->buf[(*pos)++];
    int count;
    enum result r = num_bytes(c, &count);
    if (r == result_error) {
        return r;
    }
    buffer_clear(bf2);

    /* allocate bf2{} */
    r = buffer_add_char(bf2, c);
    if (r == result_error) {
        return r;
    }
    for (int i = 1; i < count; i++) {
        c = bf->buf[(*pos)++];
        r = check_extra_byte(c);
        if (r == result_error) {
            return r;
        }

        /* allocate bf2{} */
        r = buffer_add_char(bf2, c);
        if (r == result_error) {
            return r;
        }
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
int buffer_str_compare(struct buffer* a, char* b)
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
        r = num_bytes(c, &count);
        if (r == result_error) return r;

        if (index >= start && index < end) {
            /* allocate dest{} */
            r = buffer_add_char(dest, c);
            if (r == result_error) return r;
        }


        for (int j = 1; j < count; j++) {
            c = src->buf[i++];
            r = check_extra_byte(c);
            if (r == result_error) return r;

            if (index >= start && index < end) {
                /* allocate dest{} */
                r = buffer_add_char(dest, c);
                if (r == result_error) return r;
            }
        }

        index++;
    }

    return r;
}

/* static-output */
enum result num_bytes(unsigned char c, int* count)
{
    /* 1 byte: 0xxx xxxx */
    if ((c & 0x80) == 0x00) {
        *count = 1;
        return result_ok;
    }

    /* 2 byte: 110x xxxx */
    if ((c & 0xe0) == 0xc0) {
        *count = 2;
        return result_ok;
    }

    /* 3 byte: 1110 xxxx */
    if ((c & 0xf0) == 0xe0) {
        *count = 3;
        return result_ok;
    }

    /* 4 byte: 1111 0xxx */
    if ((c & 0xf8) == 0xf0) {
        *count = 3;
        return result_ok;
    }

    *count = 0;
    return set_error("Not utf8: could not detect number bytes in character");
}

/* static-output */
enum result check_extra_byte(char c)
{
    /* 10xx xxxx */
    if ((c & 0xc0) == 0x80) {
        return result_ok;
    }

    return set_error("Not utf8: extra byte in character not encoded as utf8");
}
