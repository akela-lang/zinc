#ifndef ZINC_INPUT_CHAR_STRING_H
#define ZINC_INPUT_CHAR_STRING_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"
#include "vector.h"
#include "input_char.h"

typedef struct {
    struct location loc;
    struct location prev_loc;
    bool repeat_char;
    size_t pos;
    Vector* text;
    InputCharNextInterface Next;
    InputCharRepeatInterface Repeat;
    InputCharSeekInterface Seek;
    InputCharGetAllInterface GetAll;
    InputCharVTable* input_vtable;
} InputCharString;

extern InputCharVTable InputStringVTable;

void InputCharStringInit(InputCharString* input_string, Vector* text);
void InputCharStringCreate(InputCharString** input_string, Vector* text);
bool InputCharStringNext(InputCharString* data, char* c, struct location* loc);
void InputCharStringRepeat(InputCharString* data);
void InputCharStringSeek(InputCharString* data, size_t pos);
void InputCharStringGetAll(InputCharString* data, Vector** text);

#endif