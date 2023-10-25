#include "input_char_string.h"
#include "memory.h"
#include <stddef.h>

InputCharVTable InputStringVTable = {
        .next_offset = offsetof(struct InputCharString, Next),
        .repeat_offset = offsetof(struct InputCharString, Repeat),
        .seek_offset = offsetof(struct InputCharString, Seek),
        .get_all_offset = offsetof(struct InputCharString, GetAll),
};

void InputCharStringInit(struct InputCharString* input_string, struct Vector* text)
{
    location_init(&input_string->loc);
    location_init(&input_string->prev_loc);
    input_string->repeat_char = false;
    input_string->pos = 0;
    input_string->text = text;
    input_string->Next = (InputCharNextInterface) InputCharStringNext;
    input_string->Repeat = (InputCharRepeatInterface) InputCharStringRepeat;
    input_string->Seek = (InputCharSeekInterface) InputCharStringSeek;
    input_string->GetAll = (InputCharGetAllInterface) InputCharStringGetAll;
    input_string->input_vtable = &InputStringVTable;
}

void InputCharStringCreate(struct InputCharString** input_string, struct Vector* text)
{
    malloc_safe((void**)input_string, sizeof(struct InputCharString));
    InputCharStringInit(*input_string, text);
}

void InputCharStringClear(struct InputCharString* data)
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
bool InputCharStringNext(struct InputCharString* data, char* c, struct location* loc)
{
    if (data->loc.byte_pos == 0) {
        InputCharStringClear(data);
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
void InputCharStringRepeat(struct InputCharString* data)
{
    data->repeat_char = true;
}

/**
 * Seek to position in data stream. This call invalidates location data.
 * @param data the data
 * @param pos position to go to
 */
void InputCharStringSeek(struct InputCharString* data, size_t pos)
{
    if (pos < data->text->count)
    {
        InputCharStringClear(data);
        data->pos = pos;
    }
}

/**
 * Get entire input stream.
 * @param data the data
 * @param v the output vector
 */
void InputCharStringGetAll(struct InputCharString* data, struct Vector** text)
{
    InputCharStringClear(data);
    data->pos = data->text->count;
    *text = data->text;
}