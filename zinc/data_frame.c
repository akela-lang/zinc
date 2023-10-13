#include "data_frame.h"
#include "memory.h"
#include "buffer.h"

void SeriesInit(struct Series* sn)
{
    buffer_init(&sn->name);
    sn->vector = NULL;
    sn->next = NULL;
    sn->prev = NULL;
}

void SeriesCreate(struct Series** sn)
{
    malloc_safe((void**)sn, sizeof(struct Series));
    SeriesInit(*sn);
}

void SeriesDestroy(struct Series* sn)
{
    buffer_destroy(&sn->name);
    if (sn->vector) {
        VectorDestroy(sn->vector);
    }
    free(sn);
}

void DataFrameInit(struct DataFrame* sl)
{
    sl->head = NULL;
    sl->tail = NULL;
}

void DataFrameCreate(struct DataFrame** sl)
{
    malloc_safe((void**)sl, sizeof(struct DataFrame));
    DataFrameInit(*sl);
}

/**
 * Append Vector node to end of list.
 * @param sl Vector list
 * @param sn Vector node
 */
void DataFrameAdd(struct DataFrame* sl, struct Series* sn)
{
    if (sl->head == NULL) {
        sl->head = sn;
        sl->tail = sn;
    } else {
        sn->prev = sl->tail;
        sl->tail->next = sn;
        sl->tail = sn;
    }
}

void DataFrameDestroy(struct DataFrame* sl)
{
    struct Series* sn = sl->head;
    while (sn) {
        struct Series* temp = sn;
        sn = sn->next;
        SeriesDestroy(temp);
    }
    free(sl);
}