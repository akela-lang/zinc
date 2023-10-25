#ifndef ZINC_INPUT_H
#define ZINC_INPUT_H

#include <stdbool.h>
#include "error.h"
#include "vector.h"

/**
 * Get the next character.
 * @param data interface data
 * @param c pointer to character
 * @param loc location of character
 * @return true if done, otherwise false
 */
typedef bool (*NextCharInterface)(void*, char*, struct location*);

/**
 * Repeat the last character
 * @param data the interface data
 */
typedef void (*RepeatCharInterface)(void*);

/**
 * Seek to position in input.
 * @param data the interface data
 * @param pos the position to go to
 */
typedef void (*SeekInterface)(void*, size_t);

/**
 * Get the entire input.
 * @param data the data
 * @param text the input text
 */
typedef void (*GetAllInterface)(void*, struct Vector**);

typedef struct {
    u_int8_t next_char_offset;
    u_int8_t repeat_char_offset;
    u_int8_t seek_offset;
    u_int8_t get_all_offset;
} InputVTable;

bool InputNextChar(void* input_obj, InputVTable* input_vtable, char* c, struct location* loc);
void InputRepeatChar(void* input_obj, InputVTable* input_vtable);
void InputSeek(void* input_obj, InputVTable* input_vtable, size_t pos);
void InputGetAll(void* input_obj, InputVTable* input_vtable, struct Vector** text);

#endif