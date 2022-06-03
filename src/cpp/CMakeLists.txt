cmake_minimum_required(VERSION 3.12)
project(Engine)
project(OpenGL)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build/cpp)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${dir}/build/cpp)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${dir}/build/cpp)

set(SOURCE_FILES Engine.c GLAD/src/glad.c shader.c model.c matrix.c vector.c)
set(HEADER_FILES shader.h model.h Engine.h matrix.h vector.h)

include_directories(C:/Users/andru/.jdks/openjdk-17/include)
include_directories(C:/Users/andru/.jdks/openjdk-17/include/win32)

include_directories(GLAD/include)
include_directories(glm/include)

add_subdirectory(dependencies)

add_library(Engine SHARED ${SOURCE_FILES} ${HEADER_FILES})
add_executable(OpenGL ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Engine glfw)
target_link_libraries(OpenGL glfw)