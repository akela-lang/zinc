#include "zinc/csv_parse.h"
#include <string.h>

void CSVParseSetup(struct CSVParseOutput** parse_output, const char* text)
{
    struct Vector* input = NULL;
    size_t len = strlen(text);
    VectorCreate(&input, sizeof(char));
    VectorAdd(input, (char*)(text), len);
    VectorAddNull(input);

    struct CSVLexData* lex_data = NULL;
    CSVLexDataCreate(&lex_data);
    struct error_list* el = NULL;
    error_list_create(&el);
    lex_data->el = el;
    lex_data->NextChar = (InputCharNextInterface)CSVLexNextChar;
    lex_data->RepeatChar = (InputCharRepeatInterface)CSVLexRepeatChar;
    lex_data->input = input;

    struct CSVParseData* parse_data = NULL;
    CSVParseCreate(&parse_data);
    parse_data->el = el;
    parse_data->lex_data = lex_data;

    struct DataFrame* df = NULL;
    df = CSVParse(parse_data);

    CSVParseOutputCreate(parse_output);
    (*parse_output)->input_text = input;
    (*parse_output)->el = el;
    (*parse_output)->df = df;

    free(lex_data);
    free(parse_data);
}

void CSVParseTeardown(struct CSVParseOutput* parse_output)
{
    VectorDestroy(parse_output->input_text);
    free(parse_output->input_text);
    error_list_destroy(parse_output->el);
    free(parse_output->el);
    DataFrameDestroy(parse_output->df);
    free(parse_output->df);
    free(parse_output);
}
