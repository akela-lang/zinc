
# files
set(SOURCE_FILES
    assert.c
    buffer.c
    memory.c
    result.c
)

add_definitions(-DEXPORT)
add_library(zinc SHARED ${SOURCE_FILES})

add_custom_command(
        TARGET zinc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_BINARY_DIR}/zinc.dll
                ${CMAKE_BINARY_DIR}/test/zinc.dll
)
