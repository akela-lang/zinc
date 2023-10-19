#ifndef ZINC_FIELD_LEX_H
#define ZINC_FIELD_LEX_H

#include "error.h"
#include "input_string.h"
#include "input.h"
#include "field.h"

struct FieldLexData {
    bool has_digit;
    bool has_sign;
    NextCharInterface NextChar;
    RepeatCharInterface RepeatChar;
    SeekInterface Seek;
    GetAllInterface GetAll;
    void* data;
};

void FieldLexDataInit(struct FieldLexData* lex_data);
void FieldLexDataCreate(struct FieldLexData** lex_data);
void FieldLex(struct FieldLexData* lex_data, enum FieldType* type);
void FieldGetType(struct Vector* text, enum FieldType* type);

#endif