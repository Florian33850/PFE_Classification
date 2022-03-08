cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

#set the project name
project(PFE_classification)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3")

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
  src/classification_training_widget
  )

target_link_libraries(application_viewer Qt5::Widgets ${TORCH_LIBRARIES} ${OpenCV_LIBS})
