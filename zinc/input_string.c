#include "input_string.h"

void InputStringInit(struct InputString* input_string, struct Vector* text)
{
    location_init(&input_string->loc);
    location_init(&input_string->prev_loc);
    input_string->repeat_char = false;
    input_string->pos = 0;
    input_string->text = text;
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
        location_init(&data->loc);
        location_init(&data->prev_loc);
        data->loc.line = 1;
        data->loc.col = 1;
        data->loc.size = 1;
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