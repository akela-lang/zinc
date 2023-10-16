#ifndef ZINC_FIELD_H
#define ZINC_FIELD_H

enum FieldType {
    FieldTypeNone,
    FieldTypeEmpty,
    FieldTypeString,
    FieldTypeInt,
    FieldTypeIntUnsigned,
    FieldTypeFloat,
    FieldTypeBool,
};

#include "vector.h"

struct Field {
    enum FieldType type;
    struct Vector raw;
};

void FieldInit(struct Field* field);
void FieldDestroy(struct Field* field);

#endif