#ifndef ZINC_SERIES_H
#define ZINC_SERIES_H

#include "vector.h"
#include "field.h"

struct Series {
    struct Vector name;
    enum FieldType type;
    struct Vector types;
    struct Vector raw;
    struct Vector value;
    struct Series* next;
    struct Series* prev;
};

void SeriesInit(struct Series* s);
void SeriesCreate(struct Series** s);
void SeriesDestroy(struct Series* s);
void SeriesRefreshValues(struct Series* s);

#endif