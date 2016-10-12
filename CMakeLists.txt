cmake_minimum_required(VERSION 3.1)
project (PGRProject)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set (CMAKE_CXX_STANDARD 11)

add_executable(pgr-project main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(FTGL REQUIRED)
find_package(Freetype REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} 
                    ${FTGL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(pgr-project ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} 
                                  ${FTGL_LIBRARIES} ${FREETYPE_LIBRARIES})
