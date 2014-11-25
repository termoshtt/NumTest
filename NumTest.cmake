#.rst:
# NumTest
# -------
# 
# Register test using termoshtt/NumTest
#
# This script serves following commands and targets:
#
# Commands:
#  - add_num_test        - register executable using termoshtt/NumTest
#  - add_num_test_long   - register executable which needs much time
#  - add_num_test_short  - register executable which finish in a minute
#
# Targets:
#  - num_test        - compile and execute all registered tests
#  - num_test_long   - compile and execute tests registered via add_num_test_long
#  - num_test_short  - compile and execute tests registered via add_num_test_short
#  - new_num_test    - compile, remove old XML and execute all
#

set(NUMTESTXML "NumTest.xml" CACHE PATH "Path of result XML")
enable_testing()

add_custom_target(num_test COMMAND "ctest" "-R" "NumTest_.*")
add_custom_target(num_test_short COMMAND "ctest" "-R" "NumTest_.*_S")
add_custom_target(num_test_long COMMAND "ctest" "-R" "NumTest_.*_L")
add_custom_target(build_num_test)
add_dependencies(num_test build_num_test)
add_dependencies(num_test_short build_num_test)
add_dependencies(num_test_long build_num_test)

add_custom_target(new_num_test COMMAND "ctest" "-R" "NumTest_.*")
add_custom_target(discard_xml COMMAND "touch" ${NUMTESTXML} "&&" "rm" ${NUMTESTXML})
add_dependencies(new_num_test discard_xml build_num_test)

macro(add_num_test name type src)
  add_definitions(-DNUMTESTXML=${NUMTESTXML})
  set(test_name NumTest_${name}_${type})
  add_executable(${test_name} ${src})
  target_link_libraries(${test_name} ${ARGN})
  target_link_libraries(${test_name} ${Boost_LIBRARIES})
  add_test(${test_name} ${CMAKE_CURRENT_BINARY_DIR}/${test_name})
  add_dependencies(build_num_test ${test_name})
  unset(test_name)
endmacro(add_num_test)
macro(add_num_test_short name src)
  add_num_test(${name} "S" ${src} ${ARGN})
endmacro(add_num_test_short)
macro(add_num_test_long name src)
  add_num_test(${name} "L" ${src} ${ARGN})
endmacro(add_num_test_long)
