cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.2)
project(cpp-utils CXX)

add_library(cpp-utils INTERFACE)
target_include_directories(cpp-utils INTERFACE 
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Testing
if (NOT CPP_UTILS_NO_TESTS)
	add_custom_target(check)
	add_subdirectory(tests)
endif()

