cmake_minimum_required(VERSION 3.5.1)
project(360camera)

add_compile_options(-std=c++17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(OpenCV)

include_directories(
    # ${PROJECT_SOURCE_DIR}
    # ${PROJECT_SOURCE_DIR}/include
    include
    /opt/MVS/include/
)

LINK_DIRECTORIES(
    /opt/MVS/lib/64/
)

add_library(
    hikcam 
    src/hikcam.cpp
)

target_link_libraries(
    hikcam
    ${OpenCV_LIBS}
    MvCameraControl
)

add_executable(${PROJECT_NAME}  src/capture.cpp)
target_link_libraries(
    ${PROJECT_NAME} 
    hikcam 
    ${OpenCV_LIBS}
    MvCameraControl
)
