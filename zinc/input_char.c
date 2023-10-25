#include <stdbool.h>
#include "input_char.h"

bool InputCharNext(void* input_obj, InputCharVTable* input_vtable, char* c, struct location* loc)
{
    InputCharNextInterface *get_char = input_obj + input_vtable->next_offset;
    return (*get_char)(input_obj, c, loc);
}

void InputCharRepeat(void* input_obj, InputCharVTable* input_vtable)
{
    InputCharRepeatInterface *repeat_char = input_obj + input_vtable->repeat_offset;
    (*repeat_char)(input_obj);
}

void InputCharSeek(void* input_obj, InputCharVTable* input_vtable, size_t pos)
{
    InputCharSeekInterface *seek = input_obj + input_vtable->seek_offset;
    (*seek)(input_obj, pos);
}

void InputCharGetAll(void* input_obj, InputCharVTable* input_vtable, Vector** text)
{
    InputCharGetAllInterface *get_all = input_obj + input_vtable->get_all_offset;
    (*get_all)(input_obj, text);
}
