#ifndef ZINC_INPUT_H
#define ZINC_INPUT_H

#include <stdbool.h>
#include "error.h"

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

#endif