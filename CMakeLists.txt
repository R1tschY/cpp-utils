cmake_minimum_required(VERSION 2.8)

if(CMAKE_VERSION VERSION_GREATER 3.2)
  cmake_policy(VERSION 3.2)
  project(cpp-utils VERSION 0.1 LANGUAGES CXX)
else()
  project(cpp-utils CXX)
endif()



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1y")

if(CMAKE_VERSION VERSION_GREATER 3.0)
  add_library(cpp-utils-headeronly INTERFACE)
  target_include_directories(cpp-utils-headeronly INTERFACE 
  	"${CMAKE_CURRENT_SOURCE_DIR}/include"
  )
  
  add_library(cpp-utils STATIC include/cpp-utils/assert.cpp)
  target_include_directories(cpp-utils INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )
else()
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
  add_library(cpp-utils STATIC include/cpp-utils/assert.cpp)
endif()

# Testing
if (NOT CPP_UTILS_NO_TESTS)
	add_custom_target(check)
	add_subdirectory(tests)
endif()

