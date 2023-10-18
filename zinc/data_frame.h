#ifndef SERIES_LIST_H
#define SERIES_LIST_H

#include "vector.h"
#include "series.h"

struct DataFrame {
    struct Series* head;
    struct Series* tail;
};

void SeriesInit(struct Series* sn);
void SeriesCreate(struct Series** s);
void SeriesDestroy(struct Series* sn);
void DataFrameInit(struct DataFrame* sl);
void DataFrameCreate(struct DataFrame** sl);
void DataFrameAdd(struct DataFrame* df, struct Series* s);
void DataFrameDestroy(struct DataFrame* df);
struct Series* DataFrameSeriesByIndex(struct DataFrame* df, size_t index);
size_t DataFrameColumnCount(struct DataFrame* df);
size_t DataFrameRowCount(struct DataFrame* df);

#endif