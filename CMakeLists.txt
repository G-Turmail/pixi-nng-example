# Existing stuff
add_library(pixinng src/main.cpp)  # make it a library instead of an executable

# Export targets
install(TARGETS pixinng
    EXPORT pixinngTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

# Generate config file for find_package
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