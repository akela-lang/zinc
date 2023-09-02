
# files
set(SOURCE_FILES
        unit_test.c
        buffer.c
        memory.c
        result.c
        utf8.c
        hash.c
        os_unix.c
        sort.c
        datetime.c
        piece.c
        buffer_list.c
        error.c
        error_unit_test.c
        list.c
)

add_definitions(-DZINC_EXPORT)
add_library(zinc STATIC ${SOURCE_FILES})
