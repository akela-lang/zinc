#ifndef ZINC_SERIES_H
#define ZINC_SERIES_H

#include "vector.h"
#include "field.h"

struct Series {
    struct Vector name;
    enum FieldType type;
    struct Vector field;
    struct Vector value;
    struct Series* next;
    struct Series* prev;
};

#endif