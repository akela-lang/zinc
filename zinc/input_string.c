#include "input_string.h"
#include "memory.h"
#include <stddef.h>

InputVTable InputStringVTable = {
        .next_char_offset = offsetof(struct InputString, NextChar),
        .repeat_char_offset = offsetof(struct InputString, RepeatChar),
        .seek_offset = offsetof(struct InputString, Seek),
        .get_all_offset = offsetof(struct InputString, GetAll),
};

void InputStringInit(struct InputString* input_string, struct Vector* text)
{
    location_init(&input_string->loc);
    location_init(&input_string->prev_loc);
    input_string->repeat_char = false;
    input_string->pos = 0;
    input_string->text = text;
    input_string->NextChar = (NextCharInterface)InputStringNextChar;
    input_string->RepeatChar = (RepeatCharInterface)InputStringRepeatChar;
    input_string->Seek = (SeekInterface)InputStringSeek;
    input_string->GetAll = (GetAllInterface)InputStringGetAll;
    input_string->input_vtable = &InputStringVTable;
}

void InputStringCreate(struct InputString** input_string, struct Vector* text)
{
    malloc_safe((void**)input_string, sizeof(struct InputString));
    InputStringInit(*input_string, text);
}

void InputStringClear(struct InputString* data)
{
    location_init(&data->loc);
    location_init(&data->prev_loc);
    data->loc.line = 1;
    data->loc.col = 1;
    data->loc.size = 1;
}

/**
 * Get the next character.
 * @param lex_data lexer data
 * @param c the next char
 * @return done
 */
bool InputStringNextChar(struct InputString* data, char* c, struct location* loc)
{
    if (data->loc.byte_pos == 0) {
        InputStringClear(data);
    }

    if (data->repeat_char && data->pos > 0) {
        data->pos--;
        data->loc = data->prev_loc;
        data->repeat_char = false;
    }

    data->prev_loc = data->loc;
    if (data->pos < data->text->count) {
        *c = VECTOR_CHAR(data->text, data->pos++);
        *loc = data->loc;
        data->loc.byte_pos++;
        if (*c == '\n') {
            data->loc.line++;
            data->loc.col = 1;
        } else {
            data->loc.col++;
        }
        return false;
    } else {
        *loc = data->loc;
        return true;
    }
}

/**
 * Repeat the previous character.
 * @param data lexer data
 */
void InputStringRepeatChar(struct InputString* data)
{
    data->repeat_char = true;
}

/**
 * Seek to position in data stream. This call invalidates location data.
 * @param data the data
 * @param pos position to go to
 */
void InputStringSeek(struct InputString* data, size_t pos)
{
    if (pos < data->text->count)
    {
        InputStringClear(data);
        data->pos = pos;
    }
}

/**
 * Get entire input stream.
 * @param data the data
 * @param v the output vector
 */
void InputStringGetAll(struct InputString* data, struct Vector** text)
{
    InputStringClear(data);
    data->pos = data->text->count;
    *text = data->text;
}