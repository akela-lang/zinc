cmake_minimum_required(VERSION 3.16)
project(zinc)

if (WIN32)
  set(SHARED_FILE_NAME zinc.dll)
else()
  set(SHARED_FILE_NAME libzinc.so)
endif()

if (UNIX)
  set(CMAKE_C_FLAGS "-O1 -fsanitize=address -fno-omit-frame-pointer")
endif()

add_subdirectory("zinc")
add_subdirectory("test")
