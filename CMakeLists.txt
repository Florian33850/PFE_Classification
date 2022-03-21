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

execute_process(COMMAND unset SESSION_MANAGER)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(OpenCV REQUIRED)

set(SOURCES
    src/application_viewer.cpp
    src/image_label.cpp
    src/preprocessing_tab.cpp
    src/data_augmentation_tab.cpp
    src/data_augmentation_widget.cpp
    src/classification_training_tab.cpp
    src/result_tab.cpp
    src/tab.cpp
    src/image_transformation.cpp
    src/image_transformation_viewer.cpp
    src/image_transformation_widget.cpp
    src/data_handler.cpp
    src/images_preview_widget.cpp
    src/classification_thread.cpp
    src/result_thread.cpp
    src/classification_training_widget.cpp
    src/integer_slider.cpp
)

#add the executable
add_executable(application_viewer
    src/main.cpp
    ${SOURCES}
)

target_link_libraries(application_viewer Qt5::Widgets ${OpenCV_LIBS})

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
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
)
add_dependencies(gcov application_viewer)

    
# Create the lcov target. Run result tests with 'make lcov'
add_custom_target(lcov
    COMMAND mkdir -p lcoverage
)
add_custom_command(TARGET lcov
    COMMAND echo "=================== LCOV ===================="
    COMMAND echo "-- Passing lcov tool under code coverage"
    COMMAND lcov --capture --directory CMakeFiles/ --output-file lcoverage/main_coverage.info
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

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(UnitTests
    tests/result_thread_test.cpp
    tests/classification_thread_test.cpp
    tests/image_transformation_test.cpp
    ${SOURCES})
    target_link_libraries(UnitTests gtest_main Qt5::Widgets ${OpenCV_LIBS}
)
    
include(GoogleTest)
gtest_discover_tests(UnitTests)
    
add_executable(qtTest_TestGUI
   tests/testgui.cpp
   ${SOURCES}
)

add_executable(qtTest_DataHandlerTest
    tests/data_handler_test.cpp
    ${SOURCES}
)

add_test(NAME qtTest_TestGUI COMMAND qtTest_TestGUI)
add_test(NAME qtTest_DataHandlerTest COMMAND qtTest_DataHandlerTest)

target_link_libraries(qtTest_TestGUI Qt5::Widgets Qt5::Test ${OpenCV_LIBS})
target_link_libraries(qtTest_DataHandlerTest Qt5::Widgets Qt5::Test ${OpenCV_LIBS})
