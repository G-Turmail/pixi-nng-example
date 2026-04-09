cmake_minimum_required(VERSION 3.22)

project(pixinng LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define library target
add_library(pixinng src/main.cpp)

# Link NNG
find_package(nng REQUIRED)
target_link_libraries(pixinng PRIVATE nng)
target_include_directories(pixinng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Install rules for export
install(TARGETS pixinng
    EXPORT pixinngTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

install(EXPORT pixinngTargets
    FILE pixinngTargets.cmake
    NAMESPACE pixinng::
    DESTINATION lib/cmake/pixinng
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/pixinngConfigVersion.cmake"
    VERSION "0.1.0"
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/pixinngConfigVersion.cmake"
    DESTINATION lib/cmake/pixinng
)