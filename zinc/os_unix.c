#ifdef __unix__

#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "result.h"
#include "buffer.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>

enum result get_temp_file(FILE** fp_out, struct buffer* name)
{
    enum result r = result_ok;
    buffer_copy_str(name, "/tmp/zinc-XXXXXX");
    buffer_finish(name);
    errno = 0;
    int fd = mkstemp(name->buf);
    if (fd < 1) {
        return set_error("creation of temp file failed with error [%s]", strerror(errno));
    }
    FILE* fp = fdopen(fd, "w");
    if (!fp) {
        return set_error("creation of temp file failed with error [%s]", strerror(errno));
    }
    *fp_out = fp;

    return r;
}

enum result close_temp_file(FILE* fp)
{
    if (fclose(fp)) {
        return set_error("close of temp file failed with error [%s]", strerror(errno));
    }
    return result_ok;
}

enum result delete_temp_file(struct buffer* name)
{
    if (unlink(name->buf)) {
        return set_error("removal of temp file failed with error [%s]", strerror(errno));
    }
    return result_ok;
}

enum result get_user_home_directory(struct buffer* dir)
{
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL) {
        return set_error("Could not get home directory");
    }

    buffer_copy_str(dir, homedir);
    return result_ok;
}

void path_join(struct buffer* a, struct buffer* b, struct buffer* c)
{
    buffer_copy(a, c);
    buffer_add_char(c, '/');
    buffer_copy(b, c);
}

enum result get_user_app_directory(struct buffer* lower_name, struct buffer* dir)
{
    struct buffer home;
    buffer_init(&home);
    enum result r = get_user_home_directory(&home);
    if (r == result_error) {
        return r;
    }

    struct buffer app;
    buffer_init(&app);
    buffer_copy_str(&app, ".app");

    struct buffer temp;
    buffer_init(&temp);

    path_join(&home, &app, &temp);
    path_join(&temp, lower_name, dir);

    buffer_destroy(&home);
    buffer_destroy(&app);
    buffer_destroy(&temp);

    return result_ok;
}

enum result make_directory(struct buffer* dir)
{
    enum result r = result_ok;

    for (int i = 0; i < dir->size; i++) {
        bool is_subdir = false;
        int end;
        if (i > 0 && dir->buf[i] == '/') {
            is_subdir = true;
            end = i;
        } else if (dir->buf[i] != '/' && i == dir->size - 1) {
            is_subdir = true;
            end = i + 1;
        }
        if (is_subdir) {
            struct buffer subdir;
            buffer_init(&subdir);
            for (int j = 0; j < end; j++) {
                buffer_add_char(&subdir, dir->buf[j]);
            }
            buffer_finish(&subdir);
            DIR* dp = opendir(subdir.buf);
            bool exists;
            if (dp) {
                closedir(dp);
                exists = true;
            } else if (errno == ENOENT){
                exists = false;
            } else {
                exists = true;
                buffer_destroy(&subdir);
                return set_error("Could not check directory [%s]: %s",
                     strerror(errno), subdir.buf);
            }
            if (!exists) {
                if (mkdir(subdir.buf, 0700)) {
                    buffer_destroy(&subdir);
                    return set_error("Could not make directory [%s]: %s",
                         strerror(errno), subdir.buf);
                }
            }
            buffer_destroy(&subdir);
        }
    }

    return result_ok;
}

enum result delete_directory(struct buffer* dir)  /* NOLINT(misc-no-recursion) */
{
    enum result r;
    buffer_finish(dir);
    DIR* dp = opendir(dir->buf);
    if (!dp) {
        return set_error("Could not open directory: [%s]: %s", strerror(errno), dir->buf);
    }

    struct dirent *de = NULL;
    while ((de = readdir(dp)) != NULL) {
        if (strcmp(de->d_name, "..") == 0) {
            continue;
        }
        if (strcmp(de->d_name, ".") == 0) {
            continue;
        }

        struct buffer name;
        buffer_init(&name);
        buffer_copy_str(&name, de->d_name);

        struct buffer path;
        buffer_init(&path);

        path_join(dir, &name, &path);

        buffer_finish(&path);
        DIR* dp2 = opendir(path.buf);
        if (dp2) {
            if (closedir(dp2)) {
                return set_error("Could not check type directory item: [%s]: %s", strerror(errno), path.buf);
            }

            r = delete_directory(&path);
            if (r == result_error) {
                return r;
            }
        } else {
            if (remove(path.buf)) {
                return set_error("Could not remove file: [%s]: %s", strerror(errno), path.buf);
            }
        }

        buffer_destroy(&name);
        buffer_destroy(&path);
    }

    if (closedir(dp)) {
        return set_error("Error closing directory: [%s]: %s", strerror(errno), dir->buf);
    }

    if (remove(dir->buf)) {
        return set_error("Could not remove directory: [%s]: %s", strerror(errno), dir->buf);
    }

    return result_ok;
}

#endif