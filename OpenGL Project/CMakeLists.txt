cmake_minimum_required(VERSION 3.0)
project(ClassProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(ClassProject main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
target_include_directories(
        ClassProject
        PUBLIC
        ${GLUT_INCLUDE_DIR}
)
target_link_libraries(ClassProject OpenGL::GLU ${GLUT_LIBRARIES})