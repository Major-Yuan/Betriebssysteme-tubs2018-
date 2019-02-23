#define the minimum required cmake version to execute this script (this must be provided in every CMakeLists.txt)
cmake_minimum_required(VERSION 3.0)

#name of the project
project(backtrace C)

#define the compiler options -fsanitize=address enables the address sanatizer
#see http://clang.llvm.org/docs/AddressSanitizer.html for more details
add_compile_options(
    -fsanitize=address
    -fno-omit-frame-pointer
    -fno-optimize-sibling-calls
)

#extend the list of CMAKE linker flags by another a linker option related to the address sanitizer
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")


#add the include folder, so that the compiler will find all files there
include_directories(include)

#take all .c files from src folder and add them to the SOURCE_FILE variable
file(GLOB SOURCE_FILES src/*.c)
#take all .h files from include folder and add them to the HEADER_FILES variable
file(GLOB HEADER_FILES include/*.h)

#extend linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--export-dynamic")

#define the output executable and the files from which it is created
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
