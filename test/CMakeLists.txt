# files
set(SOURCE_FILES
    test.c
    test_buffer.c
)

include_directories(..)

add_executable("test" ${SOURCE_FILES})
target_link_libraries("test" zinc)
