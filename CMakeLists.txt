cmake_minimum_required(VERSION 3.1)
project (PGRProject)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Debug)

include_directories(src)
file(GLOB PROJECT_SRC src/*.cpp)
add_executable(pgr-project ${PROJECT_SRC})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(FTGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} 
                    ${FTGL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS}
                    ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIRS})
target_link_libraries(pgr-project ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} 
                                  ${FTGL_LIBRARIES} ${FREETYPE_LIBRARIES} 
                                  ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
