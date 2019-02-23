cmake_minimum_required(VERSION 3.0)
project(tests C)

include_directories(include)
#link_directories(lib)

# include files
file(GLOB INCLUDES "include/*.h")

add_executable(test-input src/test-input.c ${INCLUDES} $<TARGET_OBJECTS:myshellObj>)
add_executable(test-foreground src/test-foreground.c ${INCLUDES} $<TARGET_OBJECTS:myshellObj>)
add_executable(test-background src/test-background.c ${INCLUDES} $<TARGET_OBJECTS:myshellObj>)
add_executable(test-zombies src/test-zombies.c ${INCLUDES} $<TARGET_OBJECTS:myshellObj>)
add_executable(test-cd src/test-cd.c ${INCLUDES} $<TARGET_OBJECTS:myshellObj>)

#add_executable(test-walklist src/test-walklist.c ${INCLUDES} $<TARGET_OBJECTS:myshellObj>)
#target_link_libraries(test-walklist libshellfunctions_helper.a)

# collect all ressources
file(GLOB ressources ressources/*)

# this will make ressources visible in IDE
add_custom_target(list_ressources 
    SOURCES ${RESSOURCES}
)

# copy ressources into build folder after test-walklist was build
#add_custom_command(TARGET test-walklist POST_BUILD
#    WORKING_DIRECTORY .
#    COMMAND cp ${RESSOURCES} ${CMAKE_BINARY_DIR}
#)

