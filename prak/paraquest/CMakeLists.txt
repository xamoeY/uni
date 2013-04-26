project(paraquest)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set(CMAKE_AUTOMOC TRUE)
add_definitions("-Wall -Wextra -std=c++11 -g -Og")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(MPI REQUIRED)

qt5_add_resources(RESOURCES paraquest.qrc)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${RESOURCES})
qt5_use_modules(${PROJECT_NAME} Widgets OpenGL)
