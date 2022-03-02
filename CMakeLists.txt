#cmake_minimum_required(VERSION 3.10)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

#set the project name
project(PFE_classification)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 ${TORCH_CXX_FLAGS}")

#add the executable
add_executable(application_viewer main.cpp application_viewer.cpp pytorch_model_runner.cpp image_label.cpp
preprocessing_tab.cpp classification_training_tab.cpp result_tab.cpp tab.cpp image_transformation.cpp preprocessing_viewer.cpp
image_transformation_widget.cpp data_handler.cpp classification_thread.cpp result_thread.cpp)
target_link_libraries(application_viewer Qt5::Widgets ${TORCH_LIBRARIES} ${OpenCV_LIBS})