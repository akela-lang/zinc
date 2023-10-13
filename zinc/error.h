#ifndef _ERROR_H
#define _ERROR_H

#include <stdarg.h>
#include <stdbool.h>
#include "api.h"
#include <stdlib.h>

struct location {
    size_t byte_pos;
    size_t size;
    size_t line;
    size_t col;
};

#define ERROR_MESSAGE_SIZE 100

struct error {
    char message[ERROR_MESSAGE_SIZE];
    struct location loc;
    struct error* next;
    struct error* prev;
};

struct error_list {
    struct error* head;
    struct error* tail;
};

ZINC_API void error_init(struct error* e);
ZINC_API void error_list_init(struct error_list* el);
ZINC_API void error_list_create(struct error_list** el);
ZINC_API void error_list_add(struct error_list *el, struct error* e);
ZINC_API void error_list_destroy(struct error_list* el);
ZINC_API bool error_list_set(struct error_list *el, struct location* loc, const char* fmt, ...);
ZINC_API void error_list_print(struct error_list* el);
ZINC_API void location_init(struct location* loc);
ZINC_API void location_create(struct location** loc);
ZINC_API const char* plural(int number);

#endif
