# Boost Test
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_TEST_DYN_LINK)

# Sources
include_directories(../include)
file(GLOB_RECURSE cpp_utils_tests_SOURCES "*.cpp")

# Target
add_definitions(-DCPP_ASSERT_FAIL=CPP_ASSERT_FAIL_INLINE_THROW)
add_executable(test-cpp-utils EXCLUDE_FROM_ALL ${cpp_utils_tests_SOURCES})
target_link_libraries(test-cpp-utils ${Boost_LIBRARIES})

# make check
add_custom_command(TARGET test-cpp-utils
                   POST_BUILD
                   COMMAND test-cpp-utils -i -s --detect_fp_exceptions=y -l message
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Running test-cpp-utils ..." VERBATIM)
add_dependencies(check test-cpp-utils)


