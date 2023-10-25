
# files
set(SOURCE_FILES
        unit_test.c
        buffer.c
        memory.c
        result.c
        utf8.c
        hash.c
        os_unix.c
        datetime.c
        piece.c
        buffer_list.c
        error.c
        error_unit_test.c
        list.c
        vector.c
        series.c
        data_frame.c
        field.c
        field_lex.c
        input_string.c
        csv_lex.c
        csv_parse.c
        csv_write.c
        input.c
)

add_definitions(-DZINC_EXPORT)
add_library(zinc STATIC ${SOURCE_FILES})
