# GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Sources
include_directories(../include)
file(GLOB_RECURSE cpp_utils_tests_SOURCES "*.cpp")

# Target
add_executable(test-cpp-utils EXCLUDE_FROM_ALL ${cpp_utils_tests_SOURCES})
target_link_libraries(test-cpp-utils ${GTEST_BOTH_LIBRARIES} pthread)

# make check
add_test(NAME test-cpp-utils COMMAND test-cpp-utils)
add_dependencies(check test-cpp-utils)


