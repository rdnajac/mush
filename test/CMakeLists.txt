# Function to create test executable
function(add_unity_test test_name)
    add_executable(${test_name} 
        ${test_name}.c
        ${CMAKE_SOURCE_DIR}/src/mush.c
    )
    target_link_libraries(${test_name} unity)
    target_include_directories(${test_name} PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/extern/Unity/src
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# Add tests
add_unity_test(test_mush)
# Add other tests here