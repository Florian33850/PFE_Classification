cmake_minimum_required(VERSION 3.10)

#set the project name
project(PFE_classification)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

#add the executable
add_executable(classifier_viewer main.cpp classifier_viewer.cpp image_label.cpp image_collection.cpp)
target_link_libraries(classifier_viewer Qt5::Widgets)
