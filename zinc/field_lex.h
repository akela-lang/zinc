#ifndef ZINC_FIELD_LEX_H
#define ZINC_FIELD_LEX_H

#include "error.h"
#include "input_string.h"
#include "input.h"

enum FieldState {
    FieldStateStart,
    FieldStateSign,
    FieldStateInteger,
    FieldStatePoint,
    FieldStateFraction,
    FieldStateFloatE,
    FieldStateSignE,
    FieldStateExponent,
    FieldStateString,
};

struct FieldLexData {
    struct error_list* el;
    enum FieldState state;
    NextCharInterface NextChar;
    RepeatCharInterface RepeatChar;
    SeekInterface Seek;
    void* data;
};

#endif