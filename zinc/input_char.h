#ifndef ZINC_INPUT_CHAR_H
#define ZINC_INPUT_CHAR_H

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
typedef bool (*InputCharNextInterface)(void*, char*, struct location*);

/**
 * Repeat the last character
 * @param data the interface data
 */
typedef void (*InputCharRepeatInterface)(void*);

/**
 * Seek to position in input.
 * @param data the interface data
 * @param pos the position to go to
 */
typedef void (*InputCharSeekInterface)(void*, size_t);

/**
 * Get the entire input.
 * @param data the data
 * @param text the input text
 */
typedef void (*InputCharGetAllInterface)(void*, Vector**);

typedef struct {
    u_int8_t next_offset;
    u_int8_t repeat_offset;
    u_int8_t seek_offset;
    u_int8_t get_all_offset;
} InputCharVTable;

bool InputCharNext(void* input_obj, InputCharVTable* input_vtable, char* c, struct location* loc);
void InputCharRepeat(void* input_obj, InputCharVTable* input_vtable);
void InputCharSeek(void* input_obj, InputCharVTable* input_vtable, size_t pos);
void InputCharGetAll(void* input_obj, InputCharVTable* input_vtable, Vector** text);

#endif