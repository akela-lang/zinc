#include "data_frame.h"
#include "memory.h"
#include "buffer.h"

void SeriesInit(struct Series* s)
{
    VectorInit(&s->name, sizeof(char));
    s->vector = NULL;
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
    if (s->vector) {
        VectorDestroy(s->vector);
    }
    free(s);
}

void DataFrameInit(struct DataFrame* df)
{
    df->head = NULL;
    df->tail = NULL;
}

void DataFrameCreate(struct DataFrame** df)
{
    malloc_safe((void**)df, sizeof(struct DataFrame));
    DataFrameInit(*df);
}

/**
 * Append Vector node to end of list.
 * @param df Vector list
 * @param s Vector node
 */
void DataFrameAdd(struct DataFrame* df, struct Series* s)
{
    if (df->head == NULL) {
        df->head = s;
        df->tail = s;
    } else {
        s->prev = df->tail;
        df->tail->next = s;
        df->tail = s;
    }
}

void DataFrameDestroy(struct DataFrame* df)
{
    struct Series* s = df->head;
    while (s) {
        struct Series* temp = s;
        s = s->next;
        SeriesDestroy(temp);
    }
    free(df);
}