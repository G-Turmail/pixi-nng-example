cmake_minimum_required(VERSION 3.22)
project(PixiNNGExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(nng REQUIRED)

# ---- Library ----
add_library(pixinng STATIC src/main.cpp)  # rename later if needed

target_include_directories(pixinng
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(pixinng PUBLIC nng)

# ---- Install ----
install(TARGETS pixinng
    EXPORT pixinngTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)