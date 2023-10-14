#include "data_frame.h"
#include "memory.h"
#include "buffer.h"
#include <stdbool.h>
#include "string.h"
#include <ctype.h>
#include "series.h"

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
        free(temp);
    }
    free(df);
}