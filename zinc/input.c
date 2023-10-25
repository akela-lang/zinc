#include <stdbool.h>
#include "input.h"

bool InputNextChar(void* input_obj, InputVTable* input_vtable, char* c, struct location* loc)
{
    NextCharInterface *get_char = input_obj + input_vtable->next_char_offset;
    return (*get_char)(input_obj, c, loc);
}

void InputRepeatChar(void* input_obj, InputVTable* input_vtable)
{
    RepeatCharInterface *repeat_char = input_obj + input_vtable->repeat_char_offset;
    (*repeat_char)(input_obj);
}

void InputSeek(void* input_obj, InputVTable* input_vtable, size_t pos)
{
    SeekInterface *seek = input_obj + input_vtable->seek_offset;
    (*seek)(input_obj, pos);
}

void InputGetAll(void* input_obj, InputVTable* input_vtable, struct Vector** text)
{
    GetAllInterface *get_all = input_obj + input_vtable->get_all_offset;
    (*get_all)(input_obj, text);
}
