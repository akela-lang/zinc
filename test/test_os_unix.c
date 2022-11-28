#include "zinc/unit_test.h"
#include "zinc/os_unix.h"
#include <string.h>
#include "zinc/memory.h"

void test_os_unix_get_temp_file()
{
    test_name(__func__);
    FILE* fp;
    struct buffer name;
    buffer_init(&name);

    enum result r = get_temp_file(&fp, &name);
    assert_ok(r, "get_temp_file");

    const char* in = "hello";
    size_t count = strlen(in);
    size_t n = fwrite(in, 1, count, fp);
    expect_size_t_equal(n, count, "fwrite");

    r = close_temp_file(fp);
    assert_ok(r, "close_temp_file");

    fp = fopen(name.buf, "r");
    assert_ptr(fp, "ptr fp");

    char* out = NULL;
    malloc_safe((void**)&out, count + 1);
    memset(out, 0, count + 1);
    n = fread(out, 1, count, fp);

    expect_size_t_equal(n, count, "fread");

    r = close_temp_file(fp);
    assert_ok(r, "close_temp_file 2");

    expect_true(strcmp(in, out) == 0, "strcmp");

    r = delete_temp_file(&name);
    assert_ok(r, "delete_temp_file");

    buffer_destroy(&name);
}

void test_os_unix()
{
    test_os_unix_get_temp_file();
}