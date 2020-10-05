cmake_minimum_required(VERSION 3.15)
project(Glut)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


add_executable(Glut main.cpp)
target_link_libraries(Glut ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})