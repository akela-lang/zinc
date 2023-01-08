#ifndef BUFFER_LIST_H
#define BUFFER_LIST_H

#include "api.h"
#include "buffer.h"

struct buffer_node {
    struct buffer value;
    struct buffer_node* next;
    struct buffer_node* prev;
};

struct buffer_list {
    struct buffer_node* head;
    struct buffer_node* tail;
};

ZINC_API void buffer_node_init(struct buffer_node* bn);
ZINC_API void buffer_node_destroy(struct buffer_node* bn);
ZINC_API void buffer_list_init(struct buffer_list *bl);
ZINC_API void buffer_list_destroy(struct buffer_list* bl);
ZINC_API void buffer_list_add(struct buffer_list* bl, struct buffer_node* bn);
ZINC_API void buffer_list_add_str(struct buffer_list* bl, const char* str);

#endif