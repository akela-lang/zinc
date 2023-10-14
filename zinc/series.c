#include "series.h"
#include "memory.h"

void FieldInit(struct Field* field)
{
    field->type = SeriesTypeNone;
    VectorInit(&field->raw, sizeof(char));
}

void FieldDestroy(struct Field* field)
{
    VectorDestroy(&field->raw);
}

void SeriesInit(struct Series* s)
{
    VectorInit(&s->name, sizeof(char));
    s->type = SeriesTypeNone;
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
