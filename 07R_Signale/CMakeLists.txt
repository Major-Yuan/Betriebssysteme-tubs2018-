#define the minimum required cmake version to execute this script (this must be provided in every CMakeLists.txt)
cmake_minimum_required(VERSION 3.0)

#name of the project
project(7R C)

#tell cmake to put all created binaries directly into the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#override cmake internal compiler settings
set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE string "clang compiler" FORCE)

#these definitions enable some new standard library functions
add_definitions(-D_XOPEN_SOURCE -D_XOPEN_SOURCE_EXTENDED -D_GNU_SOURCE)

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
    -Wno-unused-function
    -fcolor-diagnostics
)

# collect all ressources
file(GLOB RESSOURCES Ressources/*)

# list ressources in IDE
add_custom_target(listRessources SOURCES
    ${RESSOURCES}
)

# copy ressources into build folder
add_custom_target(deployRessources ALL
    COMMAND cp ${RESSOURCES} ${CMAKE_BINARY_DIR}
)


add_subdirectory(Backtrace)
add_subdirectory(Send-signal)

