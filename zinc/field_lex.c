#include "field.h"
#include <stdbool.h>

#include "field_lex.h"

void FieldLexDataInit(struct FieldLexData* lex_data)
{
    lex_data->el = NULL;
    lex_data->state = FieldStateStart;
    lex_data->NextChar = NULL;
    lex_data->RepeatChar = NULL;
    lex_data->Seek = NULL;
    lex_data->data = NULL;
}

void FieldLex(enum FieldType* type)
{

}
