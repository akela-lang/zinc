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

#endif