#define the minimum required cmake version to execute this script (this must be provided in every CMakeLists.txt)
cmake_minimum_required(VERSION 3.0)

#name of the project
project(myshell C)

#override cmake internal compiler settings
set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE string "clang compiler" FORCE)

#add the include folder, so that the compiler will find all files there
include_directories(include)

#take all .c files from src folder and add them to the SOURCE_FILE variable
file(GLOB SOURCE_FILES src/[^m]*.c)
#take all .h files from include folder and add them to the HEADER_FILES variable
file(GLOB HEADER_FILES include/*.h)

#define the compiler options -fsanitize=address enables the address sanatizer
#see http://clang.llvm.org/docs/AddressSanitizer.html for more details
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

#needed for strdup(3)
add_definitions(-D_XOPEN_SOURCE -D_XOPEN_SOURCE_EXTENDED)

#extend the list of CMAKE linker flags by another a linker option related to the address sanitizer
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

add_library(myshellObj OBJECT ${SOURCE_FILES} ${HEADER_FILES})
#define the output executable and the files from which it is created
add_executable(myshell  $<TARGET_OBJECTS:myshellObj> src/main.c)
