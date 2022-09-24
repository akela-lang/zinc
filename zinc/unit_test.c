#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "result.h"
#include "buffer.h"
#include "unit_test.h"

struct test_run tr;

/* static-output */
void test_name(const char* fmt, ...)
{
	va_list args = NULL;
	va_start(args, fmt);
	char buf[TEST_NAME_SIZE];
	int len;

	tr.test_case_name[0] = '\0';
	tr.test_case_has_test = 0;
	tr.test_case_has_error = 0;

	char* name = tr.test_case_name;
	char last_last = 0;
	char last = 0;
	int i = 0;
	while (*fmt != '\0') {
		if (last == '%' && *fmt == '%') {
			if (i < TEST_NAME_SIZE) name[i++] = '%';
		} else if (*fmt == '%') {
			/* nothing */
		} else if (last == '%' && *fmt == 'd') {
			len = snprintf(buf, TEST_NAME_SIZE, "%d", va_arg(args, int));
			for (int j = 0; j < len; j++) {
				if (i < TEST_NAME_SIZE) name[i++] = buf[j];
			}
		} else if (last_last == '%' && last == 'z' && *fmt == 'u') {
			len = snprintf(buf, TEST_NAME_SIZE, "%zu", va_arg(args, size_t));
			for (int j = 0; j < len; j++) {
				if (i < TEST_NAME_SIZE) name[i++] = buf[j];
			}
		} else if (last == '%' && *fmt == 's') {
			len = snprintf(buf, TEST_NAME_SIZE, "%s", va_arg(args, char*));
			for (int j = 0; j < len; j++) {
				if (i < TEST_NAME_SIZE) name[i++] = buf[j];
			}
		} else if (last == '%' && *fmt == 'c') {
			len = snprintf(buf, TEST_NAME_SIZE, "%c", va_arg(args, int));
			for (int j = 0; j < len; j++) {
				if (i < TEST_NAME_SIZE) name[i++] = buf[j];
			}
		} else {
			if (i < TEST_NAME_SIZE) name[i++] = *fmt;
		}
		last_last = last;
		last = *fmt;
		fmt++;
	}

	if (i > TEST_NAME_SIZE - 1) {
		i = TEST_NAME_SIZE - 1;
	}
	name[i++] = '\0';

	va_end(args);
}

/* static-output */
void panic()
{
	fprintf(stderr, "Exiting because of assertion error.\n");
	exit(1);
}

/* static-output */
void test_called()
{
	tr.check_count++;
	if (!tr.test_case_has_test) {
		tr.test_case_count++;
		tr.test_case_has_test = 1;
	}
}

/* static-output */
void error_triggered()
{
	tr.check_error_count++;
	if (!tr.test_case_has_error) {
		tr.test_case_error_count++;
		tr.test_case_has_error = 1;
		printf("\n%s:\n", tr.test_case_name);
	}
}

/* static-output */
void print_results()
{
	printf("\ntest case count: %d\n", tr.test_case_count);
	printf("test case error count: %d\n\n", tr.test_case_error_count);

	printf("check count: %d\n", tr.check_count);
	printf("check error count: %d\n", tr.check_error_count);
}

/* static-output */
void assert_int_equal(int a, int b, const char* message)
{
	test_called();

	if (a == b) return;
	printf("%d = %d assertion error: %s\n", a, b, message);

	error_triggered();
	panic();
}

/* static-output */
void assert_true(int value, const char* message)
{
	test_called();

	if (value) return;
	error_triggered();
	printf("%d = true assertion error: %s\n", value, message);
	panic();
}

/* static-output */
void assert_false(int value, const char* message)
{
	test_called();

	if (!value) return;
	error_triggered();
	printf("%d = false assertion error: %s\n", value, message);
	panic();
}

/* static-output */
void assert_ptr(void* p, const char* message)
{
	test_called();

	if (p) return;
	error_triggered();
	printf("%p != NULL assertion error: %s\n", p, message);
	panic();
}

/* static-output */
void assert_null(void* p, const char* message)
{
	test_called();

	if (p == NULL) return;
	error_triggered();
	printf("%p == null assertion error: %s\n", p, message);
	panic();
}

/* static-output */
void assert_ok(enum result r, const char* message)
{
	test_called();

	if (r == result_ok) return;
	error_triggered();
	printf("ok assertion error: %s: %s\n", message, error_message);
	panic();
}

/* static-output */
void assert_error(enum result r, const char* message)
{
	test_called();

	if (r == result_error) return;
	error_triggered();
	printf("no error detected assertion error: %s\n", message);
	panic();
}

/* static-output */
void expect_int_equal(int a, int b, const char* message)
{
	test_called();
	if (a == b) return;
	error_triggered();
	printf("%d = %d error: %s\n", a, b, message);
}

/* static-output */
void expect_ptr_equal(void* a, void* b, const char* message)
{
	test_called();
	if (a == b) return;
	error_triggered();
	printf("%p = %p error: %s\n", a, b, message);
}

/* static-output */
void expect_char_equal(char a, char b, const char* message)
{
	test_called();
	if (a == b) return;
	error_triggered();
	printf("(%c) = (%c) error: %s\n", a, b, message);
}

/* static-output */
void expect_uint_equal(unsigned int a, unsigned int b, const char* message)
{
	test_called();
	if (a == b) return;
	error_triggered();
	printf("(%u) = (%u) error: %s\n", a, b, message);
}

/* static-output */
void expect_size_t_equal(size_t a, size_t b, const char* message)
{
	test_called();
	if (a == b) return;
	error_triggered();
	printf("(%zu) = (%zu) error: %s\n", a, b, message);
}

/* static-output */
void expect_true(int value, const char* message)
{
	test_called();
	if (value) return;
	error_triggered();
	printf("%d = true error: %s\n", value, message);
}

/* static-output */
void expect_false(int value, const char* message)
{
	test_called();
	if (!value) return;
	error_triggered();
	printf("(%d) = (false) error: %s\n", value, message);
}

/* static-output */
void expect_ptr(void* p, const char* message)
{
	test_called();
	if (p) return;
	error_triggered();
	printf("%p != NULL error: %s\n", p, message);
}

/* static-output */
void expect_null(void* p, const char* message)
{
	test_called();
	if (p == NULL) return;
	error_triggered();
	printf("%p == null error: %s\n", p, message);
}

/* static-output */
void expect_ok(enum result r, const char* message)
{
	test_called();
	if (r == result_ok) return;
	error_triggered();
	printf("ok error: %s: %s\n", message, error_message);
}

/* static-output */
/* dynamic-temp temp */
void expect_str(struct buffer* a, const char* b, const char* message)
{
	test_called();
	if (buffer_str_compare(a, b)) return;
	error_triggered();
	char* temp;

	/* allocate temp */
	buffer2array(a, &temp);
	printf("%s equals %s error: %s\n", temp, b, message);

	/* destroy temp */
	free(temp);
}

/* static-output */
void expect_strcmp(const char* a, const char* b, const char* message)
{
	test_called();
	if (strcmp(a, b) == 0) return;
	error_triggered();
	printf("(%s) = (%s) strcmp error: %s\n", a, b, message);
}

/* static-output */
void expect_nts(const char* a, const char* b, const char* message)
{
	test_called();
	if (strcmp(a, b) == 0) return;
	error_triggered();
	printf("string compare: (%s) = (%s): %s\n", a, b, message);
}

/* static-output */
void expect_error_message(const char* s)
{
	test_called();
	if (strcmp(error_message, s) == 0) return;
	error_triggered();
	printf("(%s) = (%s): error message does not match\n", error_message, s);
}
