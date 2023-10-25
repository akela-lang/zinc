#ifndef ZINC_CSV_LEX_H
#define ZINC_CSV_LEX_H

#include "buffer.h"
#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>
#include "error.h"
#include "input_char.h"

enum CSVTokenType {
    CSVTokenTypeNone,
    CSVTokenTypeField,
    CSVTokenTypeNewline,
    CSVTokenTypeEOF,
};

enum CSVStateType {
    CSVStateTypeStart,
    CSVStateTypeField,
    CSVStateTypeFieldQuoted,
    CSVStateTypeFieldEndOfQuote,
    CSVStateTypeEndOfRow,
    CSVStateTypeEOF,
};

struct CSVToken {
    enum CSVTokenType type;
    struct Vector value;
    struct location loc;
};

struct CSVLexData {
    struct error_list* el;
    enum CSVStateType state;
    InputCharNextInterface NextChar;
    InputCharRepeatInterface RepeatChar;
    InputCharSeekInterface Seek;
    struct Vector* input;
    size_t pos;
    bool repeatChar;
    struct location loc;
    struct location prev_loc;
};

bool CSVLexNextChar(struct CSVLexData* lex_data, char* c, struct location* loc);
void CSVLexRepeatChar(struct CSVLexData* lex_data);
void CSVTokenInit(struct CSVToken* token);
void CSVTokenCreate(struct CSVToken** token);
void CSVTokenDestroy(struct CSVToken* token);
void CSVLexDataInit(struct CSVLexData* lex_data);
void CSVLexDataCreate(struct CSVLexData** lex_data);
void CSVLex(struct CSVLexData* lex_data, struct CSVToken** token);
enum result CSVLoad(const char* filename, struct Vector* text);

#endif