#ifndef ZINC_VECTOR_H
#define ZINC_VECTOR_H

#include <stdlib.h>

#define SERIES_CHUNK_SIZE 64

struct Vector {
    void* buffer;
    size_t value_size;
    size_t count;
    size_t container_size;
};

void VectorInit(struct Vector* v, size_t value_size);
void VectorCreate(struct Vector** v, size_t value_size);
void VectorExpand(struct Vector* v, size_t count);
void VectorAdd(struct Vector* v, void* buffer, size_t count);
void VectorAddNull(struct Vector* v);
void VectorDestroy(struct Vector* v);

#define VECTOR_PTR(s, index) ((s)->buffer + ((s)->value_size * (index)))
#define VECTOR_DOUBLE(s, index) (*(double*)((s)->buffer + ((s)->value_size * (index))))
#define VECTOR_CHAR(s, index) (*(char*)((s)->buffer + ((s)->value_size * (index))))
#define VECTOR_STRING(s) ((char*)(s)->buffer)

#endif