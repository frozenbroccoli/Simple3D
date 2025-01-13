# Minimum version of CMake required
cmake_minimum_required(VERSION 3.15)

# Define the project name and version
project(Simple3D VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define include directories
include_directories(include)

# Define the main source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/Rendering/*.cpp
)

# Define the header files
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    include/Geometry/*.h
    include/Rendering/*.h
)

# Create a library target for the main project (shared or static)
add_library(Simple3DLib ${SOURCES} ${HEADERS})

# Enable testing
enable_testing()

# Find all test files
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

# Create an executable for each test file
foreach(TEST_SRC ${TEST_SOURCES})
    # Extract the test name from the file name
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SRC})

    # Link the main library to the test executables
    target_link_libraries(${TEST_NAME} PRIVATE Simple3DLib)

    # Register the test with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Optional: Add warnings for better code quality
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Simple3DLib PRIVATE -Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(Simple3DLib PRIVATE /W4)
endif()
