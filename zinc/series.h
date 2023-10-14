#ifndef ZINC_SERIES_H
#define ZINC_SERIES_H

#include "vector.h"

enum SeriesType {
    SeriesTypeNone,
    SeriesTypeEmpty,
    SeriesTypeString,
    SeriesTypeInt,
    SeriesTypeFloat,
    SeriesTypeBool,
};

struct Field {
    enum SeriesType type;
    struct Vector raw;
};

struct Series {
    struct Vector name;
    enum SeriesType type;
    struct Vector field;
    struct Vector value;
    struct Series* next;
    struct Series* prev;
};

#endif