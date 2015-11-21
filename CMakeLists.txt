IF(BIICODE)
	ADD_BII_TARGETS()

	TARGET_INCLUDE_DIRECTORIES(${BII_BLOCK_TARGET} INTERFACE include)

	# C++11
	IF(APPLE)
		   TARGET_COMPILE_OPTIONS(${BII_BLOCK_TARGET} INTERFACE "-std=c++14 -stdlib=libc++")
	ELSEIF (WIN32 OR UNIX)
		   TARGET_COMPILE_OPTIONS(${BII_BLOCK_TARGET} INTERFACE "-std=c++14")
	ENDIF(APPLE)
	
  RETURN()
ENDIF()

cmake_minimum_required(VERSION 2.8.11)
project(cpp-utils)

# C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1y")

# Warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Wunused -Woverloaded-virtual -Wcast-qual -Wconversion -Wold-style-cast -Wno-unused-parameter")

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Testing
enable_testing ()
set(CMAKE_CTEST_COMMAND ctest --output-on-failure)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_subdirectory(tests)

