
# set the project name
project(Mandelbrot)
set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.16)

find_package(OpenCV REQUIRED)
# add the executable
add_executable(Mandelbrot main.cpp)
target_link_libraries( Mandelbrot ${OpenCV_LIBS} )

# opencv library
find_package(OpenCV) 
