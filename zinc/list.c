#include "list.h"
#include <stdlib.h>
#include "memory.h"

void list_node_init(struct list_node* ln)
{
    ln->item = NULL;
    ln->next = NULL;
    ln->prev = NULL;
}

void list_init(struct list* l)
{
    l->head = NULL;
    l->tail = NULL;
}

void list_add(struct list* l, struct list_node* ln)
{
    if (l->head && l->tail) {
        ln->prev = l->tail->next;
        l->tail->next = ln;
        l->tail = ln;
    } else {
        l->head = l->tail = ln;
    }
}

void list_add_item(struct list* l, void* item)
{
    struct list_node* ln = NULL;
    malloc_safe((void**)&ln, sizeof(struct list_node));
    list_node_init(ln);
    ln->item = item;
    list_add(l, ln);
}

void list_destroy(struct list* l, list_node_destroy lnd)
{
    struct list_node* ln = l->head;
    while (ln) {
        struct list_node* temp = ln;
        ln = ln->next;
        if (lnd) {
            lnd(temp->item);
        }
        free(temp);
    }
}