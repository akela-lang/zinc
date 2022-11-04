
# files
set(SOURCE_FILES
    unit_test.c
    buffer.c
    memory.c
    result.c
    utf8.c
    hash.c
)

add_definitions(-DZINC_EXPORT)
add_library(zinc SHARED ${SOURCE_FILES})

add_custom_command(
        TARGET zinc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_BINARY_DIR}/${SHARED_FILE_NAME}
                ${CMAKE_BINARY_DIR}/test/${SHARED_FILE_NAME}
)

install(TARGETS zinc
    DESTINATION $ENV{HOME}/lib
)
