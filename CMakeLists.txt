cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

project(cpp-samples)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(04)
add_subdirectory(05)
add_subdirectory(06)
add_subdirectory(07)
add_subdirectory(08)
add_subdirectory(09)
