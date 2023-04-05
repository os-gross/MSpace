cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(MSpace)

# Add the matrix library target
add_library(matrix
    src/MatrixConstructor.cpp
    src/MatrixGetters.cpp
    src/MatrixSetters.cpp
    src/MSpace.hpp
)

# Add the test executable target
add_executable(test
  test/matrix_test.cpp
)

find_package(GTest REQUIRED)
# Link the main executable against the matrix library
target_link_libraries(test 
  PRIVATE 
  matrix   
  GTest::GTest
  GTest::Main
)

# Set the output directory for the binaries
set_target_properties(matrix test
    PROPERTIES
        CXX_STANDARD 17
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

add_custom_target(run_test
    COMMAND test
    DEPENDS test
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    COMMENT "Running tests."
)
