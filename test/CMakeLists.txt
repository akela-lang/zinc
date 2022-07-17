# files
set(SOURCE_FILES
    test.c
    test_result.c
    test_buffer.c
    test_memory.c
    test_assert.c
)

include_directories(..)

add_executable("test" ${SOURCE_FILES})
target_link_libraries("test" zinc)
