# Create a library from all source files except main.c
file(GLOB SRC_FILES *.c)
list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

add_library(mush_lib ${SRC_FILES})

target_include_directories(mush_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)
