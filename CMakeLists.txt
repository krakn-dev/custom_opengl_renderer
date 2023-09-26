cmake_minimum_required(VERSION 3.20)
project(strworld)
set(CMAKE_CXX_FLAGS "-Wall -g")

set(GLAD_SRC_FILE "lib/GLAD/glad.c")
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(strworld
  ${SRC_FILES}
  ${GLAD_SRC_FILE}
)

target_link_libraries(strworld ${CMAKE_SOURCE_DIR}/lib/GLFW/libglfw3.a)
