cmake_minimum_required(VERSION 3.22)

project(pixinng LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find NNG library
find_package(nng REQUIRED)

# Define library target
add_library(pixinng src/main.cpp)

# Link NNG
target_link_libraries(pixinng PRIVATE nng)

# Use installed headers for PUBLIC include directories
target_include_directories(pixinng
    PUBLIC 
        $<INSTALL_INTERFACE:include>  # <- downstream consumers see this
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src  # <- only for local build
)

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Install library target and export
install(TARGETS pixinng
    EXPORT pixinngTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(EXPORT pixinngTargets
    FILE pixinngTargets.cmake
    NAMESPACE pixinng::
    DESTINATION lib/cmake/pixinng
)

# Package config version
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/pixinngConfigVersion.cmake"
    VERSION "0.1.0"
    COMPATIBILITY AnyNewerVersion
)

# Install package config version file
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/pixinngConfigVersion.cmake"
    DESTINATION lib/cmake/pixinng
)