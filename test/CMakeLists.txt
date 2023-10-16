# files
set(SOURCE_FILES
        test.c
        test_result.c
        test_buffer.c
        test_memory.c
        test_unit_test.c
        test_utf8.c
        test_hash.c
        test_os_unix.c
        test_datetime.c
        test_piece.c
        test_buffer_list.c
        test_error.c
        test_list.c
        test_vector.c
        test_data_frame.c
        test_input_string.c
        test_field_lex.c
)

include_directories(..)

add_executable("test" ${SOURCE_FILES})
target_link_libraries("test" zinc)
