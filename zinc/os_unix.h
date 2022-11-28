#ifndef OS_UNIX_H
#define OS_UNIX_H

#ifdef __unix__
#include "api.h"
ZINC_API enum result get_temp_file(FILE** fp_out, struct buffer* name);
ZINC_API enum result close_temp_file(FILE* fp);
ZINC_API enum result delete_temp_file(struct buffer* name);
#endif

#endif