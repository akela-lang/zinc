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
void DataFrameAdd(struct DataFrame* df, Series* s)
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
    Series* s = df->head;
    while (s) {
        Series* temp = s;
        s = s->next;
        SeriesDestroy(temp);
        free(temp);
    }
}

Series* DataFrameSeriesByIndex(struct DataFrame* df, size_t index)
{
    size_t i = 0;
    Series* s = df->head;
    while (s) {
        if (i == index) {
            return s;
        }
        s = s->next;
        i++;
    }
    return NULL;
}

size_t DataFrameColumnCount(struct DataFrame* df)
{
    size_t count = 0;
    Series* s = df->head;
    while(s) {
        count++;
        s = s->next;
    }
    return count;
}

size_t DataFrameRowCount(struct DataFrame* df)
{
    Series* s = df->head;
    return s->value.count;
}