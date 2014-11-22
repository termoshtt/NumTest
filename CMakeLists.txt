cmake_minimum_required(VERSION 2.8)
# set(CMAKE_VERBOSE_MAKEFILE 1) # for debug cmake
PROJECT(NumTest)

# basic 
include_directories(.)
add_definitions("-Wall -std=c++11")

# ctest 
enable_testing()
add_custom_target(short_test COMMAND "ctest" "-R" "TEST_.*_S")
add_custom_target(long_test COMMAND "ctest" "-V" "-R" "TEST_.*_L" "2>&1" ">" "long.log" "&")
add_custom_target(plot_test COMMAND "ctest" "-V" "-R" "TEST_.*_PLOT")
add_custom_target(build_test)
add_dependencies(short_test build_test)
macro(mytest name type src)
    set(test_name TEST_${name}_${type})
    add_executable(${test_name} ${src})
    target_link_libraries(${test_name} ${ARGN})
    add_test(${test_name} ${CMAKE_CURRENT_BINARY_DIR}/${test_name})
    add_dependencies(build_test ${test_name})
    unset(test_name)
endmacro(mytest)

# others
add_custom_target(
    ctags ALL
    COMMAND "ctags" "-R" "-f" ".tags" "--languages=C++,python" "--exclude='CMake*'"
)
add_custom_target(
    document
    COMMAND "doxygen" "doc/Doxyfile"
)

add_subdirectory(test EXCLUDE_FROM_ALL)
