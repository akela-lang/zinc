#ifndef _ASSERT_H
#define _ASSERT_H

#include "api.h"

ZINC_API void assert_int_equal(int a, int b, char* message);
ZINC_API void assert_true(int value, char* message);
ZINC_API void assert_ptr(void* p, char* message);
ZINC_API void assert_null(void* p, char* message);
ZINC_API void assert_ok(enum result r, char* message);
ZINC_API void assert_error(enum result r, char* message);
ZINC_API void expect_int_equal(int a, int b, char* message);
ZINC_API void expect_uint_equal(unsigned int a, unsigned int b, char* message);
ZINC_API void expect_true(int value, char* message);
ZINC_API void expect_ptr(void* p, char* message);
ZINC_API void expect_null(void* p, char* message);
ZINC_API void expect_ok(enum result r, char* message);
ZINC_API void expect_str(struct buffer* a, char* b, char* message);
ZINC_API void expect_nts(char* a, char* b, char* message);
ZINC_API void test_name(const char* fmt, ...);
ZINC_API void print_results();
ZINC_API void expect_error_message(char* s);

#endif
