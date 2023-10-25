#ifndef SERIES_LIST_H
#define SERIES_LIST_H

#include "vector.h"
#include "series.h"

struct DataFrame {
    Series* head;
    Series* tail;
};

void SeriesInit(Series* sn);
void SeriesCreate(Series** s);
void SeriesDestroy(Series* sn);
void DataFrameInit(struct DataFrame* sl);
void DataFrameCreate(struct DataFrame** sl);
void DataFrameAdd(struct DataFrame* df, Series* s);
void DataFrameDestroy(struct DataFrame* df);
Series* DataFrameSeriesByIndex(struct DataFrame* df, size_t index);
size_t DataFrameColumnCount(struct DataFrame* df);
size_t DataFrameRowCount(struct DataFrame* df);

#endif