#include "unit_test.h"
#include "error.h"
#include <string.h>

void assert_no_errors(struct error_list* el)
{
    test_called();

    if (!el->head) return;
    error_triggered();
    fprintf(stderr, "assert no errors: has errors\n");
    struct error* e = el->head;
    while (e) {
        fprintf(stderr, "(%zu,%zu): %s\n", e->loc.line, e->loc.col, e->message);
        e = e->next;
    }

    error_triggered();
    panic();
}

void expect_no_errors(struct error_list* el)
{
    test_called();

    if (!el->head) return;
    error_triggered();
    fprintf(stderr, "assert no errors: has errors\n");
    struct error* e = el->head;
    while (e) {
        fprintf(stderr, "(%zu,%zu): %s\n", e->loc.line, e->loc.col, e->message);
        e = e->next;
    }

    error_triggered();
}

void assert_has_errors(struct error_list* el)
{
    test_called();

    if (el->head) return;
    error_triggered();
    fprintf(stderr, "assert has errors: there are no errors\n");

    error_triggered();
    panic();
}

void expect_has_errors(struct error_list* el)
{
    test_called();

    if (el->head) return;
    error_triggered();
    fprintf(stderr, "assert has errors: there are no errors\n");

    error_triggered();
}

void expect_error(struct error_list* el, const char message[])
{
    test_called();
    struct error* e = el->head;
    while (e) {
        if (strcmp(e->message, message) == 0) {
            return;
        }
        e = e->next;
    }
    error_triggered();
    fprintf(stderr, "error not found: %s\n", message);
}