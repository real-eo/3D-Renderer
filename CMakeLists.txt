cmake_minimum_required(VERSION 3.10)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

add_executable(main main.cpp)

target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_directories(main PRIVATE ${SDL2_LIBRARY_DIRS})
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
