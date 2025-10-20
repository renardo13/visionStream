cmake_minimum_required(VERSION 3.10)
project(VisionStreamCPU LANGUAGES CXX)

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Create executable
add_executable(app app.cpp)

# Link OpenCV libraries
target_link_libraries(app ${OpenCV_LIBS})