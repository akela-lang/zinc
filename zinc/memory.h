#ifndef _MEMORY_H
#define _MEMORY_H

#include "api.h"
#include <stdlib.h>
#include "result.h"

/* dynamic-output buf */
ZINC_API void malloc_safe(void** buf, size_t size);

/* dynamic-output buf */
ZINC_API enum result realloc_safe(void** buf, size_t size);

#endif
