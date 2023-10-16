#include "zinc/unit_test.h"
#include "zinc/field_lex.h"
#include <string.h>
#include "zinc/field.h"

void TestFieldLexRun(char* text, enum FieldType* type)
{
    struct Vector* text2 = NULL;
    VectorCreate(&text2, sizeof(char));
    size_t len = strlen(text);
    VectorAdd(text2, text, len);

    struct InputString* input_string = NULL;
    InputStringCreate(&input_string, text2);

    struct FieldLexData* lex_data = NULL;
    FieldLexDataCreate(&lex_data);
    lex_data->NextChar = (NextCharInterface)InputStringNextChar;
    lex_data->data = input_string;

    FieldLex(lex_data, type);

    struct InputString* data = lex_data->data;
    VectorDestroy(text2);
    free(text2);
    free(input_string);
    free(lex_data);
}

void TestFieldLexEmpty()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("", &type);
    expect_int_equal(type, FieldTypeEmpty, "empty");
}

void TestFieldLexInteger()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("100", &type);
    expect_int_equal(type, FieldTypeIntUnsigned, "int");
}

void TestFieldLexNegativeInteger()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("-100", &type);
    expect_int_equal(type, FieldTypeInt, "int");
}

void TestFieldLexPositiveInteger()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("+100", &type);
    expect_int_equal(type, FieldTypeInt, "int");
}

void TestFieldLex()
{
    TestFieldLexEmpty();
    TestFieldLexInteger();
    TestFieldLexNegativeInteger();
    TestFieldLexPositiveInteger();
}