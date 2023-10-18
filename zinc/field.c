#include "field.h"
#include <assert.h>

void FieldInit(struct Field* field)
{
    field->type = FieldTypeNone;
    VectorInit(&field->raw, sizeof(char));
}

void FieldDestroy(struct Field* field)
{
    VectorDestroy(&field->raw);
}

bool FieldIsNumber(enum FieldType type)
{
    if (type == FieldTypeIntUnsigned)
        return true;
    if (type == FieldTypeInt)
        return true;
    if (type == FieldTypeFloat)
        return true;
    return false;
}

bool FieldPromotion(enum FieldType f1, enum FieldType f2)
{
    assert(f1 != FieldTypeNone);
    assert(f2 != FieldTypeNone);

    if (f1 == f2)
        return f1;

    if (f1 == FieldTypeEmpty)
        return f2;
    if (f2 == FieldTypeEmpty)
        return f1;

    if (FieldIsNumber(f1) && FieldIsNumber(f2)) {
        if (f1 > f2)
            return f1;
        else
            return f2;
    }

    return FieldTypeString;
}