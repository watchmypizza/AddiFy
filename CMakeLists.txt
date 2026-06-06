cmake_minimum_required(VERSION 3.15)
project(AddiFy VERSION 1.2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

find_package(yaml-cpp REQUIRED)
find_package(CURL REQUIRED)

set(SOURCES
    Classes/main.cpp
    Classes/menu.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp::yaml-cpp
                                              CURL::libcurl)