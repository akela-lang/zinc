
# files
set(SOURCE_FILES
    assert.c
    buffer.c
    memory.c
    result.c
    utf8.c
)

add_definitions(-DZINC_EXPORT)
add_library(zinc SHARED ${SOURCE_FILES})

add_custom_command(
        TARGET zinc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_BINARY_DIR}/zinc.dll
                ${CMAKE_BINARY_DIR}/test/zinc.dll
)
