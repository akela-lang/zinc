#ifndef SERIES_LIST_H
#define SERIES_LIST_H

#include "vector.h"

struct Series {
    struct Vector name;
    struct Vector* vector;
    struct Series* next;
    struct Series* prev;
};

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

#endif