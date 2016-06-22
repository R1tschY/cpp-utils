cmake_minimum_required(VERSION 2.8)

if(CMAKE_VERSION VERSION_GREATER 3.2)
  cmake_policy(VERSION 3.2)
endif()

project(cpp-utils VERSION 0.1 LANGUAGES CXX)

if(CMAKE_VERSION VERSION_GREATER 3.0)
  add_library(cpp-utils-headeronly INTERFACE)
  target_include_directories(cpp-utils-headeronly INTERFACE 
  	"${CMAKE_CURRENT_SOURCE_DIR}/include"
  )
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1y")

add_library(cpp-utils STATIC include/cpp-utils/assert.cpp)
target_include_directories(cpp-utils INTERFACE 
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Testing
if (NOT CPP_UTILS_NO_TESTS)
	add_custom_target(check)
	add_subdirectory(tests)
endif()

