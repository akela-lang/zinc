#ifndef ZINC_INPUT_CHAR_STRING_H
#define ZINC_INPUT_CHAR_STRING_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"
#include "vector.h"
#include "input_char.h"

struct InputCharString {
    struct location loc;
    struct location prev_loc;
    bool repeat_char;
    size_t pos;
    struct Vector* text;
    InputCharNextInterface Next;
    InputCharRepeatInterface Repeat;
    InputCharSeekInterface Seek;
    InputCharGetAllInterface GetAll;
    InputCharVTable* input_vtable;
};

extern InputCharVTable InputStringVTable;

void InputCharStringInit(struct InputCharString* input_string, struct Vector* text);
void InputCharStringCreate(struct InputCharString** input_string, struct Vector* text);
bool InputCharStringNext(struct InputCharString* data, char* c, struct location* loc);
void InputCharStringRepeat(struct InputCharString* data);
void InputCharStringSeek(struct InputCharString* data, size_t pos);
void InputCharStringGetAll(struct InputCharString* data, struct Vector** text);

#endif