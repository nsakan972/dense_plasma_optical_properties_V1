# Inspired by this project https://github.com/andystanton/glfw-skeleton


cmake_minimum_required(VERSION 3.16)
project(denseplas_simple LANGUAGES CXX VERSION 1.0.0) 

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FETCHCONTENT_QUIET FALSE)

#
# glfw
#
set(GLFW_BUILD_DOCS FALSE)
set(GLFW_BUILD_EXAMPLES FALSE)
set(GLFW_BUILD_TESTS FALSE)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.4
  GIT_PROGRESS TRUE)

#
# glad
#
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad
  GIT_TAG v0.1.34
  GIT_PROGRESS TRUE)

#
# glm
#
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 0.9.9.8
  GIT_PROGRESS TRUE)


# pugixml
FetchContent_Declare(
  pugixml
  GIT_REPOSITORY https://github.com/zeux/pugixml.git
  GIT_TAG v1.10
  GIT_PROGRESS TRUE
)

# 
# lua
# 

#FetchContent_Declare(
#    lua
#    GIT_REPOSITORY "https://github.com/marovira/lua"
#    GIT_TAG v5.4.7
#    GIT_PROGRESS TRUE
#)

FetchContent_Declare(lua
    URL https://www.lua.org/ftp/lua-5.4.6.tar.gz
    URL_HASH SHA256=7d5ea1b9cb6aa0b59ca3dde1c6adcb57ef83a1ba8e5432c0ecd06bf439b3ad88)

#
# fetch dependencies
#
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glad)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(pugixml)
FetchContent_MakeAvailable(lua)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -ffast-math")
#
# SWsim source code
#
set(
        PROJECT_SOURCES
        src/main/main.cpp
        src/main/main.hpp
        src/globals/globals.hpp
        src/globals/globals.cpp
        src/IF_parser/IF_parser.hpp
        src/IF_parser/IF_parser.cpp
)

# Include OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message("OpenMP found")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

add_dependencies(${PROJECT_NAME} glfw glad glm pugixml)

target_include_directories(
        ${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/globals/
        ${CMAKE_CURRENT_SOURCE_DIR}/src/IF_parser/
)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm OpenMP::OpenMP_CXX pugixml)