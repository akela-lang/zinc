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

void TestFieldLexIntegerUnsigned()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("100", &type);
    expect_int_equal(type, FieldTypeIntUnsigned, "int");
}

void TestFieldLexStringIntegerUnsigned() {
    test_name(__func__);

    enum FieldType type;

    TestFieldLexRun("10a0", &type);
    expect_int_equal(type, FieldTypeString, "string");

    TestFieldLexRun("a100", &type);
    expect_int_equal(type, FieldTypeString, "string");

    TestFieldLexRun("100a", &type);
    expect_int_equal(type, FieldTypeString, "string");
}

void TestFieldLexString() {
    test_name(__func__);

    enum FieldType type;

    TestFieldLexRun("hello", &type);
    expect_int_equal(type, FieldTypeString, "string");
}

void TestFieldLexIntegerSign()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("-100", &type);
    expect_int_equal(type, FieldTypeInt, "int");

    TestFieldLexRun("+100", &type);
    expect_int_equal(type, FieldTypeInt, "int");
}

void TestFieldLexStringIntegerSign()
{
    test_name(__func__);

    enum FieldType type;

    TestFieldLexRun("a+100", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("+a100", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("+100a", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("a-100", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("-a100", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("-100a", &type);
    expect_int_equal(type, FieldTypeString, "int");
}

void TestFieldLexFloatIntegerFraction()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("1.5", &type);
    expect_int_equal(type, FieldTypeFloat, "int");
}

void TestFieldLexStringFloatIntegerFraction()
{
    test_name(__func__);

    enum FieldType type;

    TestFieldLexRun("a1.5", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("1a.5", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("1.a5", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("1.5a", &type);
    expect_int_equal(type, FieldTypeString, "int");
}

void TestFieldLexFloatInteger()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("31.", &type);
    expect_int_equal(type, FieldTypeFloat, "int");
}

void TestFieldLexStringFloatInteger()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("a31.", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("31a.", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("31.a", &type);
    expect_int_equal(type, FieldTypeString, "int");
}

void TestFieldLexFloatFraction()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun(".5", &type);
    expect_int_equal(type, FieldTypeFloat, "int");
}

void TestFieldLexStringFloatFraction()
{
    test_name(__func__);

    enum FieldType type
            ;
    TestFieldLexRun("a.5", &type);
    expect_int_equal(type, FieldTypeString, "string 0");

    TestFieldLexRun(".a5", &type);
    expect_int_equal(type, FieldTypeString, "string 1");

    TestFieldLexRun(".5a", &type);
    expect_int_equal(type, FieldTypeString, "string 2");
}

void TestFieldLexFloatE()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("1e", &type);
    expect_int_equal(type, FieldTypeFloat, "int");
}

void TestFieldLexStringFloatE()
{
    test_name(__func__);

    enum FieldType type;

    TestFieldLexRun("1ae", &type);
    expect_int_equal(type, FieldTypeString, "string 0");

    TestFieldLexRun("1ea", &type);
    expect_int_equal(type, FieldTypeString, "string 1");
}

void TestFieldLexFloatEUpper()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("1E", &type);
    expect_int_equal(type, FieldTypeFloat, "int");
}

void TestFieldLexStringFloatEUpper()
{
    test_name(__func__);

    enum FieldType type;

    TestFieldLexRun("1aE", &type);
    expect_int_equal(type, FieldTypeString, "string 0");

    TestFieldLexRun("1Ea", &type);
    expect_int_equal(type, FieldTypeString, "string 0");
}

void TestFieldLexFloatExponent()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("1e3", &type);
    expect_int_equal(type, FieldTypeFloat, "int");
}

void TestFieldLexStringFloatExponent()
{
    test_name(__func__);

    enum FieldType type;

    TestFieldLexRun("1ea3", &type);
    expect_int_equal(type, FieldTypeString, "string 0");

    TestFieldLexRun("1e3a", &type);
    expect_int_equal(type, FieldTypeString, "string 1");
}

void TestFieldLexFloatExponentNegative()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("1235e-30", &type);
    expect_int_equal(type, FieldTypeFloat, "int");
}

void TestFieldLexStringFloatExponentNegative()
{
    test_name(__func__);

    enum FieldType type;

    TestFieldLexRun("1235ea-30", &type);
    expect_int_equal(type, FieldTypeString, "string 0");

    TestFieldLexRun("1235e-a30", &type);
    expect_int_equal(type, FieldTypeString, "string 1");
}

void TestFieldLexFloatExponentPositive()
{
    test_name(__func__);

    enum FieldType type;
    TestFieldLexRun("1e+43", &type);
    expect_int_equal(type, FieldTypeFloat, "int");
}

void TestFieldLexStringFloatExponentPositive()
{
    test_name(__func__);

    enum FieldType type;

    TestFieldLexRun("1ea+43", &type);
    expect_int_equal(type, FieldTypeString, "int");

    TestFieldLexRun("1e+a43", &type);
    expect_int_equal(type, FieldTypeString, "int");
}

void TestFieldLex()
{
    TestFieldLexEmpty();

    TestFieldLexString();

    TestFieldLexIntegerUnsigned();
    TestFieldLexStringIntegerUnsigned();

    TestFieldLexIntegerSign();
    TestFieldLexStringIntegerSign();

    TestFieldLexFloatIntegerFraction();
    TestFieldLexStringFloatIntegerFraction();

    TestFieldLexFloatInteger();
    TestFieldLexStringFloatInteger();

    TestFieldLexFloatFraction();
    TestFieldLexStringFloatFraction();

    TestFieldLexFloatE();
    TestFieldLexStringFloatE();

    TestFieldLexFloatEUpper();
    TestFieldLexStringFloatEUpper();

    TestFieldLexFloatExponent();
    TestFieldLexStringFloatExponent();

    TestFieldLexFloatExponentNegative();
    TestFieldLexStringFloatExponentNegative();

    TestFieldLexFloatExponentPositive();
    TestFieldLexStringFloatExponentPositive();
}