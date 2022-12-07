#include "zinc/unit_test.h"
#include "zinc/os_unix.h"
#include <string.h>
#include "zinc/memory.h"
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

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

void test_os_unix_get_user_home_directory()
{
    test_name(__func__);

    const char* temp = getenv("HOME");
    setenv("HOME", "/home/abc", 1);

    struct buffer dir;
    buffer_init(&dir);
    enum result r = get_user_home_directory(&dir);
    assert_ok(r, "get_user_home_directory");
    expect_str(&dir, "/home/abc", "/home/abc");
    buffer_destroy(&dir);

    setenv("HOME", temp, 1);
}

void test_os_unix_path_join()
{
    test_name(__func__);

    struct buffer a;
    struct buffer b;
    struct buffer c;

    buffer_init(&a);
    buffer_init(&b);
    buffer_init(&c);

    buffer_copy_str(&a, "/home");
    buffer_copy_str(&b, "alf");

    path_join(&a, &b, &c);

    expect_str(&c, "/home/alf", "/home/alf");
}

void test_os_unix_get_user_app_directory()
{
    test_name(__func__);

    struct buffer app_name;
    buffer_init(&app_name);
    buffer_copy_str(&app_name, "stone");

    struct buffer dir;
    buffer_init(&dir);

    const char* temp = getenv("HOME");
    setenv("HOME", "/home/abc", 1);
    get_user_app_directory(&app_name, &dir);
    expect_str(&dir, "/home/abc/.app/stone", "/home/abc/.app/stone");

    buffer_destroy(&app_name);
    buffer_destroy(&dir);

    setenv("HOME", temp, 1);
}

void test_os_unix_make_directory()
{
    test_name(__func__);

    struct buffer dir;
    buffer_init(&dir);
    buffer_copy_str(&dir, "/tmp/apple/bear/creek/doe/eddy");
    buffer_finish(&dir);
    enum result r = make_directory(&dir);
    assert_ok(r, "make directory");
    DIR* dp = opendir(dir.buf);
    assert_ptr(dp, "ptr dp");
    closedir(dp);
    buffer_destroy(&dir);
    system("cd /tmp && rmdir -p apple/bear/creek/doe/eddy");
}

void test_os_unix()
{
    test_os_unix_get_temp_file();
    test_os_unix_get_user_home_directory();
    test_os_unix_path_join();
    test_os_unix_get_user_app_directory();
    test_os_unix_make_directory();
}