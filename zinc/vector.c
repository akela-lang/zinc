#include "vector.h"
#include "memory.h"
#include <assert.h>
#include <string.h>

void VectorInit(struct Vector* s, size_t value_size)
{
    s->buffer = NULL;
    s->value_size = value_size;
    s->count = 0;
    s->container_size = 0;
}

void VectorCreate(struct Vector** s, size_t value_size)
{
    malloc_safe((void**)s, sizeof(struct Vector));
    VectorInit(*s, value_size);
}

/**
 * Add space to Vector.
 * @param s Vector
 * @param count the count of elements
 */
void VectorExpand(struct Vector* s, size_t count)
{
    assert(s->value_size > 0);

    size_t copy_size = s->value_size * count;
    size_t current_size = s->value_size * s->count;
    if (current_size + copy_size > s->container_size) {
        size_t old_container_size = s->container_size;
        if (copy_size < SERIES_CHUNK_SIZE) {
            s->container_size = current_size + SERIES_CHUNK_SIZE;
        } else {
            s->container_size = current_size + copy_size;
        }
        if (old_container_size == 0) {
            malloc_safe(&s->buffer, s->container_size);
        } else {
            realloc_safe(&s->buffer, s->container_size);
        }
    }
}

/**
 * Add a number of values to the end of the Vector.
 * @param s the Vector
 * @param buffer the buffer holding the new values
 * @param count the number of new elements
 */
void VectorAdd(struct Vector* s, void* buffer, size_t count)
{
    VectorExpand(s, count);
    memcpy(VECTOR_PTR(s, s->count), buffer, s->value_size * count);
    s->count += count;
}

/**
 * Add a null byte. Only use if value_size is 1 byte.
 * @param s Vector
 */
void VectorAddNull(struct Vector* s)
{
    assert(s->value_size == sizeof(u_int8_t));
    u_int8_t value = 0x0;
    VectorAdd(s, &value, 1);
    s->count--;
}

void VectorDestroy(struct Vector* s)
{
    free(s->buffer);
}