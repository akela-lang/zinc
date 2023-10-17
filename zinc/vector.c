#include "vector.h"
#include "memory.h"
#include <assert.h>
#include <string.h>

void VectorInit(struct Vector* v, size_t value_size)
{
    v->buffer = NULL;
    v->value_size = value_size;
    v->count = 0;
    v->container_size = 0;
}

void VectorCreate(struct Vector** v, size_t value_size)
{
    malloc_safe((void**)v, sizeof(struct Vector));
    VectorInit(*v, value_size);
}

/**
 * Add space to Vector.
 * @param v Vector
 * @param count the count of elements
 */
void VectorExpand(struct Vector* v, size_t count)
{
    assert(v->value_size > 0);

    size_t copy_size = v->value_size * count;
    size_t current_size = v->value_size * v->count;
    if (current_size + copy_size > v->container_size) {
        size_t old_container_size = v->container_size;
        if (copy_size < SERIES_CHUNK_SIZE) {
            v->container_size = current_size + SERIES_CHUNK_SIZE;
        } else {
            v->container_size = current_size + copy_size;
        }
        if (old_container_size == 0) {
            malloc_safe(&v->buffer, v->container_size);
        } else {
            realloc_safe(&v->buffer, v->container_size);
        }
    }
}

/**
 * Add a number of values to the end of the Vector.
 * @param v the Vector
 * @param buffer the buffer holding the new values
 * @param count the number of new elements
 */
void VectorAdd(struct Vector* v, void* buffer, size_t count)
{
    VectorExpand(v, count);
    memcpy(VECTOR_PTR(v, v->count), buffer, v->value_size * count);
    v->count += count;
}

/**
 * Add a null byte. Only use if value_size is 1 byte.
 * @param v Vector
 */
void VectorAddNull(struct Vector* v)
{
    assert(v->value_size == sizeof(u_int8_t));
    u_int8_t value = 0x0;
    VectorAdd(v, &value, 1);
    v->count--;
}

void VectorDestroy(struct Vector* v)
{
    free(v->buffer);
}

bool VectorMatch(struct Vector* a, struct Vector* b)
{
    return match(
            a->buffer, a->count * a->value_size,
            b->buffer, b->count * b->value_size);
}

bool VectorMatchStr(struct Vector* a, const char b[])
{
    return match(
            a->buffer, a->count * a->value_size,
            (u_int8_t *)b, strlen(b));
}