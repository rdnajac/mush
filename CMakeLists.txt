cmake_minimum_required(VERSION 3.0)
project(mush C)

enable_testing()

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(extern/Unity)

add_executable(mush 
	src/mush.c
	src/main.c
)
