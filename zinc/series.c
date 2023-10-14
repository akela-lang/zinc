#include "series.h"
#include "memory.h"
#include "field.h"

void SeriesInit(struct Series* s)
{
    VectorInit(&s->name, sizeof(char));
    s->type = FieldTypeNone;
    VectorInit(&s->field, sizeof(struct Field));
    VectorInit(&s->value, sizeof(char));
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
    for (int i = 0; i < s->field.count; i++) {
        FieldDestroy(VECTOR_PTR(&s->field, i));
    }
    VectorDestroy(&s->field);
    VectorDestroy(&s->value);
}
