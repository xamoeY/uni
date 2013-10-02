project(paraquest)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(visualization SRC_LIST_VISUALIZATION)
aux_source_directory(simulation SRC_LIST_SIMULATION)
aux_source_directory(common SRC_LIST_COMMON)
set(CMAKE_AUTOMOC TRUE)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_definitions("-Wall -Wextra -Wno-unused-parameter -std=c++11 -g -O0")
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(MPI)

include_directories(common common/cereal/include/)

if(${Qt5Widgets_FOUND} AND ${Qt5OpenGL_FOUND})
    qt5_add_resources(RESOURCES visualization/paraquest.qrc)
    add_executable(${PROJECT_NAME}_visualization ${SRC_LIST_VISUALIZATION} ${SRC_LIST_COMMON} ${RESOURCES})
    qt5_use_modules(${PROJECT_NAME}_visualization Widgets OpenGL)
target_link_libraries(${PROJECT_NAME}_visualization ${MPI_CXX_LIBRARIES})
endif()

add_executable(${PROJECT_NAME}_simulation ${SRC_LIST_SIMULATION} ${SRC_LIST_COMMON})
target_link_libraries(${PROJECT_NAME}_simulation ${MPI_CXX_LIBRARIES})
