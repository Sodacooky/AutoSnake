cmake_minimum_required(VERSION 3.0.0)
set(VCPKG_TARGET_TRIPLET x64-windows)
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
project(Proj VERSION 0.1.0)

aux_source_directory(./src SRC)
add_executable(Proj ${SRC})

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)