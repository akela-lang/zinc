#ifndef _UNIT_TEST_H
#define _UNIT_TEST_H

#include "api.h"
#include "buffer.h"
#include "vector.h"

#define TEST_NAME_SIZE 100

struct test_run {
	char test_case_name[TEST_NAME_SIZE];
	int test_case_count;
	int test_case_error_count;
	int test_case_has_test;
	int test_case_has_error;
	int check_count;
	int check_error_count;
};

/* static-output */
ZINC_API void test_name(const char* fmt, ...);

/* static-output */
ZINC_API void panic();

/* static-output */
ZINC_API void test_called();

/* static-output */
ZINC_API void error_triggered();

/* static-output */
ZINC_API void print_results();

/* static-output */
ZINC_API void assert_int_equal(int a, int b, const char* message);

/* static-output */
ZINC_API void assert_true(int value, const char* message);

/* static-output */
ZINC_API void assert_false(int value, const char* message);

/* static-output */
ZINC_API void assert_ptr(void* p, const char* message);

/* static-output */
ZINC_API void assert_null(void* p, const char* message);

/* static-output */
ZINC_API void assert_ok(enum result r, const char* message);

/* static-output */
ZINC_API void assert_error(enum result r, const char* message);

/* static-output */
ZINC_API void expect_int_equal(int a, int b, const char* message);

ZINC_API void expect_long_equal(long a, long b, const char* message);

ZINC_API void expect_u_long_equal(unsigned long a, unsigned long b, const char* message);

ZINC_API void expect_double_equal(double a, double b, const char* message);

/* static-output */
ZINC_API void expect_ptr_equal(void* a, void* b, const char* message);

/* static-output */
ZINC_API void expect_char_equal(char a, char b, const char* message);

/* static-output */
ZINC_API void expect_uint_equal(unsigned int a, unsigned int b, const char* message);

ZINC_API void assert_size_t_equal(size_t a, size_t b, const char* message);

/* static-output */
ZINC_API void expect_size_t_equal(size_t a, size_t b, const char* message);

/* static-output */
ZINC_API void expect_true(int value, const char* message);

/* static-output */
ZINC_API void expect_false(int value, const char* message);

/* static-output */
ZINC_API void expect_ptr(void* p, const char* message);

/* static-output */
ZINC_API void expect_null(void* p, const char* message);

/* static-output */
ZINC_API void expect_ok(enum result r, const char* message);

/* static-output */
ZINC_API void expect_str(struct buffer* a, const char* b, const char* message);

ZINC_API void expect_vector_str(struct Vector* a, const char* b, const char* message);

ZINC_API void expect_vector(struct Vector* a, struct Vector* b, const char* message);

/* static-output */
ZINC_API void expect_strcmp(const char* a, const char* b, const char* message);

/* static-output */
ZINC_API void expect_nts(const char* a, const char* b, const char* message);

/* static-output */
ZINC_API void expect_error_message(const char* s);

ZINC_API void expect_vector_double(struct Vector* a, struct Vector* b, double threshold, const char* message);

#endif
