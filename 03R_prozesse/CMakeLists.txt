cmake_minimum_required(VERSION 3.0)
project(3R-Material C)

set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE string "clang compiler" FORCE)

include_directories(myshell/include)

add_compile_options(
    -std=c11
    -O0
    -g
    -pedantic
    -Wall
    -Wextra
    -Werror
    -fcolor-diagnostics
    -fsanitize=address
    -fno-omit-frame-pointer
    -fno-optimize-sibling-calls
)

#needed for strdup
add_definitions(-D_XOPEN_SOURCE -D_XOPEN_SOURCE_EXTENDED)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

add_subdirectory(myshell)
add_subdirectory(tests)




