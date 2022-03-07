cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

#set the project name
project(PFE_classification)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Create OBJECT_DIR variable
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/PfeApplication.dir/src)
message("-- Object files will be output to: ${OBJECT_DIR}")


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3")

#add the executable
add_executable(application_viewer
  src/main.cpp
  src/application_viewer.cpp
  src/image_label.cpp
  src/preprocessing_tab.cpp
  src/classification_training_tab.cpp
  src/result_tab.cpp
  src/tab.cpp
  src/image_transformation.cpp
  src/preprocessing_viewer.cpp
  src/image_transformation_widget.cpp
  src/data_handler.cpp
  src/classification_thread.cpp
  src/result_thread.cpp
  )

target_link_libraries(application_viewer Qt5::Widgets ${TORCH_LIBRARIES} ${OpenCV_LIBS})

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/src/*.cpp -o ${OBJECT_DIR}
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage  # Need separate command for this line
    )
add_dependencies(gcov application_viewer)

    
# Create the lcov target. Run result tests with 'make lcov'
add_custom_target(lcov
    COMMAND mkdir -p lcoverage
    )
add_custom_command(TARGET lcov
    COMMAND echo "=================== LCOV ===================="
    COMMAND echo "-- Passing lcov tool under code coverage"
    COMMAND lcov --capture --directory CMakeFiles/TestHello.dir/ --output-file lcoverage/main_coverage.info
    COMMAND lcov --quiet --remove lcoverage/main_coverage.info '/usr/*' '*/include/*' '*/build/*' '*/*.h' --output-file lcoverage/main_coverage.info.cleaned
    COMMAND echo "-- Generating HTML output files"
    COMMAND genhtml lcoverage/main_coverage.info.cleaned --output-directory lcoverage
    )

# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files.
add_custom_target(scrub
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Testing
enable_testing()

#add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/RunAdder)
#set_tests_properties(output_test PROPERTIES PASS_REGULAR_EXPRESSION "0;5;10")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(TestHello tests/test_hello.cpp 
  src/application_viewer.cpp
  src/image_label.cpp
  src/preprocessing_tab.cpp
  src/classification_training_tab.cpp
  src/result_tab.cpp
  src/tab.cpp
  src/image_transformation.cpp
  src/preprocessing_viewer.cpp
  src/image_transformation_widget.cpp
  src/data_handler.cpp
  src/classification_thread.cpp
  src/result_thread.cpp)
target_link_libraries(TestHello gtest_main Qt5::Widgets ${TORCH_LIBRARIES} ${OpenCV_LIBS})

include(GoogleTest)
gtest_discover_tests(TestHello)
