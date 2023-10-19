#include "csv_parse.h"
#include "csv_lex.h"
#include "memory.h"
#include <assert.h>
#include "field_lex.h"

bool CSVParseHeader(struct CSVParseData* parse_data, struct DataFrame* df);
bool CSVParseRow(struct CSVParseData* parse_data, struct DataFrame* df);

void CSVParseDataInit(struct CSVParseData* parse_data)
{
    parse_data->el = NULL;
    parse_data->lex_data = NULL;
    parse_data->df = NULL;
}

void CSVParseCreate(struct CSVParseData** parse_data)
{
    malloc_safe((void**)parse_data, sizeof(struct CSVParseData));
    CSVParseDataInit(*parse_data);
}

void CSVParseOutputInit(struct CSVParseOutput* parse_output)
{
    parse_output->el = NULL;
    parse_output->df = NULL;
}

void CSVParseOutputCreate(struct CSVParseOutput** parse_output)
{
    malloc_safe((void**)parse_output, sizeof(struct CSVParseOutput));
    CSVParseOutputInit(*parse_output);
}

/**
 * Parse a CSV file and add header and values to data frame.
 * @param parse_data parse data
 * @param df data frame
 */
void CSVParse(struct CSVParseData* parse_data, struct DataFrame* df)
{
    bool done = false;

    done = CSVParseHeader(parse_data, df);
    while (!done) {
        done = CSVParseRow(parse_data, df);
    }
}

/**
 * Add a series for each field in header row.
 * @param parse_data parse data
 * @param df dataframe add series to
 * @return true if done, otherwise false
 */
bool CSVParseHeader(struct CSVParseData* parse_data, struct DataFrame* df)
{
    while (true) {
        struct CSVToken* token = NULL;
        CSVLex(parse_data->lex_data, &token);
        if (token->type == CSVTokenTypeEOF) {
            CSVTokenDestroy(token);
            free(token);
            return true;
        } else if (token->type == CSVTokenTypeNewline) {
            CSVTokenDestroy(token);
            free(token);
            return false;
        } else if (token->type == CSVTokenTypeField) {
            struct Series* s = NULL;
            SeriesCreate(&s);
            s->type = FieldTypeEmpty;
            VectorAdd(&s->name, token->value.buffer, token->value.count);
            DataFrameAdd(df, s);
            CSVTokenDestroy(token);
            free(token);
        } else {
            assert(false);
        }
    }
}

/**
 * Add row to data frame.
 * @param parse_data parse data
 * @param df data frame
 * @return true if done with input, otherwise false
 */
bool CSVParseRow(struct CSVParseData* parse_data, struct DataFrame* df)
{
    size_t i = 0;
    while (true) {
        struct CSVToken* token = NULL;
        CSVLex(parse_data->lex_data, &token);
        if (token->type == CSVTokenTypeEOF) {
            CSVTokenDestroy(token);
            free(token);
            return true;
        } else if (token->type == CSVTokenTypeNewline) {
            CSVTokenDestroy(token);
            free(token);
            return false;
        } else if (token->type == CSVTokenTypeField) {
            struct Series* s = DataFrameSeriesByIndex(df, i);
            if (!s) {
                error_list_set(parse_data->el, &token->loc, "Row has more fields than header");
            } else {
                /* field type */
                enum FieldType field_type;
                FieldGetType(&token->value, &field_type);
                VectorAdd(&s->types, &field_type, 1);

                /* field raw */
                struct Vector* v = NULL;
                VectorCreate(&v, sizeof(char));
                VectorAdd(v, token->value.buffer, token->value.count);
                VectorAdd(&s->raw, &v, 1);

                /* field value */
            }
            i++;
            CSVTokenDestroy(token);
            free(token);
        } else {
            assert(false);
        }
    }
}