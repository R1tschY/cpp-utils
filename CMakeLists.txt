cmake_minimum_required(VERSION 2.8)

if(CMAKE_VERSION VERSION_GREATER 3.2)
  cmake_policy(VERSION 3.2)
  project(cpp-utils VERSION 0.1 LANGUAGES CXX)
else()
  project(cpp-utils CXX)
endif()



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")

if(CMAKE_VERSION VERSION_GREATER 3.0)
  add_library(cpp-utils-headeronly INTERFACE)
  target_include_directories(cpp-utils-headeronly INTERFACE 
  	"${CMAKE_CURRENT_SOURCE_DIR}/include"
  )
  
  set(cpp_utils_SOURCES include/cpp-utils/assert.cpp)
  
  add_library(cpp-utils32 STATIC EXCLUDE_FROM_ALL ${cpp_utils_SOURCES})
  set_target_properties(cpp-utils32 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
  target_include_directories(cpp-utils32 INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )
  
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_library(cpp-utils64 STATIC EXCLUDE_FROM_ALL ${cpp_utils_SOURCES})
    target_include_directories(cpp-utils64 INTERFACE 
      "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )
  
    add_library(cpp-utils ALIAS cpp-utils64)
  else()
    add_library(cpp-utils ALIAS cpp-utils32)
  endif()
  
else()
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
  add_library(cpp-utils STATIC include/cpp-utils/assert.cpp)
endif()

# Testing
if (NOT CPP_UTILS_NO_TESTS)
	add_custom_target(check)
	add_subdirectory(tests)
endif()

