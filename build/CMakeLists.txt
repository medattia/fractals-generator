cmake_minimum_required(VERSION 3.1)
# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
SET(OpenCV_DIR ~/OpenCV/OpenCV4.3.0/OpenCV-master/lib/cmake/opencv4)
project( Binary )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( Binary ../src/mandelbrot.cpp )
target_link_libraries( Binary ${OpenCV_LIBS} )

