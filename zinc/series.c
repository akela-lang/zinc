#include "series.h"
#include "memory.h"
#include "field.h"

void SeriesInit(struct Series* s)
{
    VectorInit(&s->name, sizeof(char));
    s->type = FieldTypeNone;
    VectorInit(&s->types, sizeof(enum FieldType));
    VectorInit(&s->raw, sizeof(struct Vector*));
    VectorInit(&s->value, 0);
    s->next = NULL;
    s->prev = NULL;
}

void SeriesCreate(struct Series** s)
{
    malloc_safe((void**)s, sizeof(struct Series));
    SeriesInit(*s);
}

void SeriesDestroy(struct Series* s)
{
    VectorDestroy(&s->name);
    VectorDestroy(&s->types);
    VectorDestroy(&s->raw);
    VectorDestroy(&s->value);
}
