#include "zinc/unit_test.h"
#include "zinc/data_frame.h"
#include "zinc/csv_lex.h"
#include "zinc/csv_parse.h"
#include <string.h>
#include "zinc/error_unit_test.h"
#include "zinc/memory.h"

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
    lex_data->NextChar = (NextCharInterface)CSVLexNextChar;
    lex_data->RepeatChar = (RepeatCharInterface)CSVLexRepeatChar;
    lex_data->input = input;

    struct DataFrame* df = NULL;
    DataFrameCreate(&df);
    struct CSVParseData* parse_data = NULL;
    CSVParseCreate(&parse_data);
    parse_data->el = el;
    parse_data->lex_data = lex_data;
    parse_data->df = df;

    CSVParse(parse_data, df);

    CSVParseOutputCreate(parse_output);
    (*parse_output)->el = el;
    (*parse_output)->df = df;

    VectorDestroy(lex_data->input);
    free(lex_data->input);
    free(lex_data);
    free(parse_data);
}

void CSVParseTeardown(struct CSVParseOutput* parse_output)
{
    error_list_destroy(parse_output->el);
    free(parse_output->el);
    DataFrameDestroy(parse_output->df);
    free(parse_output->df);
    free(parse_output);
}

void TestCSVParseHeaderName()
{
    test_name(__func__);

    struct CSVParseOutput* parse_output = NULL;
    CSVParseSetup(&parse_output, "First Name\n");

    expect_no_errors(parse_output->el);
    expect_size_t_equal(DataFrameColumnCount(parse_output->df), 1, "column count");
    expect_size_t_equal(DataFrameRowCount(parse_output->df), 0, "row count");
    struct Series* s = DataFrameSeriesByIndex(parse_output->df, 0);
    assert_ptr(s, "ptr s");
    expect_true(VectorMatchStr(&s->name, "First Name"), "First Name");

    CSVParseTeardown(parse_output);
}

void TestCSVParseRowField()
{
    test_name(__func__);

    struct CSVParseOutput* parse_output = NULL;
    CSVParseSetup(&parse_output,
                  "Count\n"
                  "11\n");

    expect_no_errors(parse_output->el);

    expect_size_t_equal(DataFrameColumnCount(parse_output->df), 1, "column count");
    expect_size_t_equal(DataFrameRowCount(parse_output->df), 0, "row count");

    struct Series* s = DataFrameSeriesByIndex(parse_output->df, 0);
    assert_ptr(s, "ptr s");
    expect_true(VectorMatchStr(&s->name, "Count"), "Count");

    enum FieldType field_type = *(enum FieldType*)VECTOR_PTR(&s->types, 0);
    expect_int_equal(field_type, FieldTypeNone, "types");

    struct Vector* v = *(struct Vector**)VECTOR_PTR(&s->raw, 0);
    expect_true(VectorMatchStr(v, "11"), "11");

    CSVParseTeardown(parse_output);
}

void TestCSVParse()
{
    TestCSVParseHeaderName();
    TestCSVParseRowField();
}