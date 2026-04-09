cmake_minimum_required(VERSION 3.22)
project(PixiNNGExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(nng REQUIRED)

# Add executable
add_executable(main src/main.cpp)

# Link NNG library
target_link_libraries(main PRIVATE nng)