# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(CM2SIM VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find packages (example)
# find_package(OpenMP REQUIRED)

# Source files
set(SOURCES
    src/vector2.cpp
    src/module.cpp
    src/block.cpp
)

set(HEADERS
    include/block.hpp
    include/module.hpp
    include/vector2.hpp
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries (example)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

# Set properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD ${CMAKE_CXX_STANDARD}
    CXX_STANDARD_REQUIRED ON
)

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)