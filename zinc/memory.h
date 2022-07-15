#ifndef _MEMORY_H
#define _MEMORY_H

#include "api.h"
#include <stdlib.h>
#include "result.h"

ZINC_API enum result malloc_safe(void** buf, size_t size);
ZINC_API enum result realloc_safe(void** buf, size_t size);

#endif
