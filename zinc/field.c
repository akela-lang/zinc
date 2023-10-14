#include "field.h"

void FieldInit(struct Field* field)
{
    field->type = FieldTypeNone;
    VectorInit(&field->raw, sizeof(char));
}

void FieldDestroy(struct Field* field)
{
    VectorDestroy(&field->raw);
}