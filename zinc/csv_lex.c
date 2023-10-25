#include <stdio.h>
#include <stdbool.h>
#include "buffer.h"
#include "vector.h"
#include "csv_lex.h"
#include <assert.h>
#include "memory.h"

#define CSV_CHUNK_SIZE 1024

void CSVLexDispatch(struct CSVLexData* lex_data, struct CSVToken* token);

void CSVLexStartLocation(struct location* loc)
{
    loc->byte_pos = 0;
    loc->size = 0;
    loc->line = 1;
    loc->col = 1;
}

/**
 * Get the next character.
 * @param lex_data lexer data
 * @param c the next char
 * @return done
 */
bool CSVLexNextChar(struct CSVLexData* lex_data, char* c, struct location* loc)
{
    if (lex_data->loc.byte_pos == 0) {
        CSVLexStartLocation(&lex_data->loc);
        CSVLexStartLocation(&lex_data->prev_loc);
    }

    if (lex_data->repeatChar && lex_data->pos > 0) {
        lex_data->pos--;
        lex_data->loc = lex_data->prev_loc;
        lex_data->repeatChar = false;
    }

    lex_data->prev_loc = lex_data->loc;
    if (lex_data->pos < lex_data->input->count) {
        *c = VECTOR_CHAR(lex_data->input, lex_data->pos++);
        *loc = lex_data->loc;
        lex_data->loc.byte_pos++;
        if (*c == '\n') {
            lex_data->loc.line++;
            lex_data->loc.col = 1;
        } else {
            lex_data->loc.col++;
        }
        return false;
    } else {
        *loc = lex_data->loc;
        return true;
    }
}

/**
 * Repeat the previous character.
 * @param lex_data lexer data
 */
void CSVLexRepeatChar(struct CSVLexData* lex_data)
{
    lex_data->repeatChar = true;
}


void CSVTokenInit(struct CSVToken* token)
{
    token->type = CSVTokenTypeNone;
    VectorInit(&token->value, sizeof(char));
    location_init(&token->loc);
}

void CSVTokenCreate(struct CSVToken** token)
{
    malloc_safe((void**)token, sizeof(struct CSVToken));
    CSVTokenInit(*token);
}

void CSVTokenDestroy(struct CSVToken* token)
{
    VectorDestroy(&token->value);
}

void CSVLexDataInit(struct CSVLexData* lex_data)
{
    lex_data->el = NULL;
    lex_data->state = CSVStateTypeStart;
    lex_data->NextChar = NULL;
    lex_data->input = NULL;
    lex_data->pos = 0;
    lex_data->repeatChar = false;
    location_init(&lex_data->loc);
    lex_data->loc.size = 1;
    location_init(&lex_data->prev_loc);
    lex_data->prev_loc.size = 1;
}

void CSVLexDataCreate(struct CSVLexData** lex_data)
{
    malloc_safe((void**)lex_data, sizeof(struct CSVLexData));
    CSVLexDataInit(*lex_data);
}

/* NOLINTNEXTLINE(misc-no-recursion) */
void CSVLexStart(struct CSVLexData* lex_data, struct CSVToken* token)
{
    char c;
    struct location loc;
    lex_data->NextChar(lex_data, &c, &loc);
    if (c == '"') {
        lex_data->state = CSVStateTypeFieldQuoted;
        token->loc = lex_data->loc;
        token->loc.size++;
    } else {
        lex_data->state = CSVStateTypeField;
        lex_data->RepeatChar(lex_data);
    }
    token->type = CSVTokenTypeField;
    CSVLexDispatch(lex_data, token);
}

/* NOLINTNEXTLINE(misc-no-recursion) */
void CSVLexField(struct CSVLexData* lex_data, struct CSVToken* token) {
    bool done = false;
    char c;

    token->loc = lex_data->loc;

    while (true) {
        struct location loc;
        done = lex_data->NextChar(lex_data, &c, &loc);
        if (done) {
            lex_data->state = CSVStateTypeEOF;
            break;
        } else if (c == ',') {
            lex_data->state = CSVStateTypeStart;
            break;
        } else if (c == '\n') {
            lex_data->state = CSVStateTypeEndOfRow;
            lex_data->RepeatChar(lex_data);
            break;
        } else if (c == '"') {
            loc.size = 1;
            error_list_set(lex_data->el, &loc, "quote found in unquoted field");
            /* test case: CSVLexErrorQuote */
        } else {
            VectorAdd(&token->value, &c, 1);
            token->loc.size++;
        }
    }
}

void CSVLexFieldQuoted(struct CSVLexData* lex_data, struct CSVToken* token)
{
    bool done = false;
    char c;
    struct location loc;

    while (true) {
        done = lex_data->NextChar(lex_data, &c, &loc);
        if (done) {
            loc.size++;
            error_list_set(lex_data->el, &loc,
                           "End of file found before end of quoted field");
            /* test case: CSVLexErrorExtraEOFBeforeQuote */
            lex_data->state = CSVStateTypeEOF;
            break;
        } else if (c == '"') {
            done = lex_data->NextChar(lex_data, &c, &loc);
            if (done) {
                token->loc.size++;
                lex_data->state = CSVStateTypeEOF;
                break;
            }
            if (c == '"') {
                token->loc.size++;
                VectorAdd(&token->value, &c, 1);
            } else {
                token->loc.size++;
                lex_data->state = CSVStateTypeFieldEndOfQuote;
                lex_data->RepeatChar(lex_data);
                break;
            }
        } else {
            token->loc.size++;
            VectorAdd(&token->value, &c, 1);
        }
    }
}

/* NOLINTNEXTLINE(misc-no-recursion) */
void CSVLexFieldEndOfQuote(struct CSVLexData* lex_data, struct CSVToken* token)
{
    bool done = false;
    char c;
    struct location loc;

    while (true) {
        done = lex_data->NextChar(lex_data, &c, &loc);
        if (done) {
            token->type = CSVTokenTypeEOF;
            lex_data->state = CSVStateTypeEOF;
            break;
        } else if (c == ',') {
            lex_data->state = CSVStateTypeStart;
            CSVLexDispatch(lex_data, token);
            break;
        } else if (c == '\n') {
            lex_data->state = CSVStateTypeEndOfRow;
            lex_data->RepeatChar(lex_data);
            CSVLexDispatch(lex_data, token);
            break;
        } else {
            loc.size = 1;
            error_list_set(lex_data->el, &loc, "extra characters after field ending quote");
            /* test case: CSVLexErrorExtraCharactersAfterQuote */
        }
    }
}

void CSVLexEndOfRow(struct CSVLexData* lex_data, struct CSVToken* token)
{
    bool done = false;
    char c;
    struct location loc;

    lex_data->NextChar(lex_data, &c, &loc);
    if (c == '\n') {
        token->type = CSVTokenTypeNewline;
        done = lex_data->NextChar(lex_data, &c, &loc);
        lex_data->RepeatChar(lex_data);
        if (done) {
            lex_data->state = CSVStateTypeEOF;
        } else {
            lex_data->state = CSVStateTypeStart;
        }
    } else {
        assert(false);
    }
}

void CSVLexEOF(struct CSVToken* token)
{
    token->type = CSVTokenTypeEOF;
}

/* NOLINTNEXTLINE(misc-no-recursion) */
void CSVLexDispatch(struct CSVLexData* lex_data, struct CSVToken* token)
{
    switch (lex_data->state) {
        case CSVStateTypeStart:
            CSVLexStart(lex_data, token);
            break;
        case CSVStateTypeField:
            CSVLexField(lex_data, token);
            break;
        case CSVStateTypeFieldQuoted:
            CSVLexFieldQuoted(lex_data, token);
            break;
        case CSVStateTypeFieldEndOfQuote:
            CSVLexFieldEndOfQuote(lex_data, token);
            break;
        case CSVStateTypeEndOfRow:
            CSVLexEndOfRow(lex_data, token);
            break;
        case CSVStateTypeEOF:
            CSVLexEOF(token);
            break;
        default:
            assert(false);
    }
}

void CSVLex(struct CSVLexData* lex_data, struct CSVToken** token)
{
    CSVTokenCreate(token);
    CSVLexDispatch(lex_data, *token);
}

enum result CSVLoad(const char* filename, Vector* text)
{
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if (!fp) {
        return set_error("Could not open file: %v", filename);
    }

    while (true) {
        VectorExpand(text, CSV_CHUNK_SIZE);
        size_t n = fread(VECTOR_PTR(text, text->count),
                         text->value_size, CSV_CHUNK_SIZE,
                         fp);
        text->count += n;
        if (n < CSV_CHUNK_SIZE) {
            break;
        }
    }
    VectorAddNull(text);
    return result_ok;
}
