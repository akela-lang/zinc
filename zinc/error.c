#include "error.h"
#include "memory.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void location_init(struct location* loc)
{
    loc->byte_pos = 0;
    loc->size = 0;
    loc->line = 0;
    loc->col = 0;
}

void error_init(struct error* e)
{
    location_init(&e->loc);
    e->message[0] = '\0';
    e->next = NULL;
    e->prev = NULL;
}

void error_list_init(struct error_list* el)
{
    el->head = NULL;
    el->tail = NULL;
}

void error_list_add(struct error_list *el, struct error* e)
{
    if (el->tail) {
        el->tail->next = e;
        e->prev = el->tail;
    }
    el->tail = e;

    if (!el->head) {
        el->head = e;
    }
}

void error_list_destroy(struct error_list* el)
{
    struct error* p = el->head;
    while (p) {
        struct error* temp = p;
        p = p->next;
        free(temp);
    }
}

/* static-output */
bool error_list_set(struct error_list *el, struct location* loc, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char buf[ERROR_SIZE] = "";
    int len;
    struct error* e = NULL;
    malloc_safe((void**)&e, sizeof(struct error));
    error_init(e);

    char last_last = 0;
    char last = 0;
    int i = 0;
    while (*fmt != '\0') {
        if (last == '%' && *fmt == '%') {
            if (i < ERROR_SIZE) e->message[i++] = '%';
        } else if (*fmt == '%') {
            /* nothing */
        } else if (last == '%' && *fmt == 'z') {
            /* nothing */
        } else if (last == '%' && *fmt == 'd') {
            len = snprintf(buf, ERROR_SIZE, "%d", va_arg(args, int));
            for (int j = 0; j < len; j++) {
                if (i < ERROR_SIZE) e->message[i++] = buf[j];
            }
        } else if (last_last == '%' && last == 'z' && *fmt == 'u') {
            len = snprintf(buf, ERROR_SIZE, "%zu", va_arg(args, size_t));
            for (int j = 0; j < len; j++) {
                if (i < ERROR_SIZE) e->message[i++] = buf[j];
            }
        } else if (last == '%' && *fmt == 's') {
            len = snprintf(buf, ERROR_SIZE, "%s", va_arg(args, char*));
            for (int j = 0; j < len; j++) {
                if (i < ERROR_SIZE) e->message[i++] = buf[j];
            }
        } else if (last == '%' && *fmt == 'c') {
            len = snprintf(buf, ERROR_SIZE, "%c", va_arg(args, int));
            for (int j = 0; j < len; j++) {
                if (i < ERROR_SIZE) e->message[i++] = buf[j];
            }
        } else {
            if (i < ERROR_SIZE) e->message[i++] = *fmt;
        }
        last_last = last;
        last = *fmt;
        fmt++;
    }
    if (i >= ERROR_SIZE) {
        i = ERROR_SIZE - 1;
    }
    e->message[i++] = '\0';

    va_end(args);

    error_list_add(el, e);
    if (loc) {
        e->loc = *loc;
    }

    return false;
}

void error_list_print(struct error_list* el)
{
    struct error* e = el->head;
    while (e) {
        fprintf(stderr, "(%zu,%zu): %s\n", e->loc.line, e->loc.col, e->message);
        e = e->next;
    }
}

void location_create(struct location** loc)
{
    malloc_safe((void**)loc, sizeof(struct location));
    location_init(*loc);
}

const char* plural(int number)
{
    if (number == 1) return "";
    else return "s";
}
