#ifndef ZINC_CSV_PARSE_H
#define ZINC_CSV_PARSE_H

#include <stdbool.h>
#include "csv_lex.h"

struct CSVParseData {
    struct error_list* el;
    struct CSVToken* lookahead;
    struct CSVLexData* lex_data;
};


#endif