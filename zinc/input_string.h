#ifndef ZINC_INPUT_STRING_H
#define ZINC_INPUT_STRING_H

#include <stdbool.h>
#include <stdlib.h>
#include "error.h"
#include "vector.h"
#include "input.h"

struct InputString {
    struct location loc;
    struct location prev_loc;
    bool repeat_char;
    size_t pos;
    struct Vector* text;
    NextCharInterface NextChar;
    RepeatCharInterface RepeatChar;
    SeekInterface Seek;
    GetAllInterface GetAll;
    InputVTable* input_vtable;
};

extern InputVTable InputStringVTable;

void InputStringInit(struct InputString* input_string, struct Vector* text);
void InputStringCreate(struct InputString** input_string, struct Vector* text);
bool InputStringNextChar(struct InputString* data, char* c, struct location* loc);
void InputStringRepeatChar(struct InputString* data);
void InputStringSeek(struct InputString* data, size_t pos);
void InputStringGetAll(struct InputString* data, struct Vector** v);

#endif