#ifndef OS_UNIX_H
#define OS_UNIX_H

#ifdef __unix__
#include "api.h"
#include <stdbool.h>
#include "buffer_list.h"

ZINC_API enum result get_temp_file(FILE** fp_out, struct buffer* name);
ZINC_API enum result close_temp_file(FILE* fp);
ZINC_API enum result delete_temp_file(struct buffer* name);
ZINC_API enum result get_user_home_directory(struct buffer* dir);
ZINC_API void path_join(struct buffer* a, struct buffer* b, struct buffer* c);
ZINC_API enum result get_user_app_directory(struct buffer* lower_name, struct buffer* dir);
ZINC_API enum result make_directory(struct buffer* dir);
ZINC_API enum result delete_directory(struct buffer* dir);
ZINC_API bool file_exists(struct buffer* filename);
ZINC_API enum result get_dir_files(struct buffer* dir, struct buffer_list* bl);

#endif

#endif