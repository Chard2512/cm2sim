# Minimum required CMake version
cmake_minimum_required(VERSION 3.15)

# Project name and language
project(cm2sim VERSION 0.1.0 LANGUAGES CXX)

# ============================================================================
# Compiler Configuration
# ============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for tools like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ============================================================================
# Output Directories
# ============================================================================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ============================================================================
# Source Files
# ============================================================================
set(SOURCES
    src/cm2sim.cpp
    src/parser.cpp
    src/vector2.cpp
    src/module.cpp
    src/block.cpp
)

set(HEADERS
    include/block.hpp
    include/module.hpp
    include/vector2.hpp
    include/parser.hpp
)

# ============================================================================
# Main Executable
# ============================================================================
add_executable(${PROJECT_NAME} ${SOURCES})

# Set include directories for the target
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

# Set compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wvla)
endif()

# ============================================================================
# Find Packages (example)
# ============================================================================
# find_package(OpenMP REQUIRED)
# target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)

# ============================================================================
# Testing
# ============================================================================
#enable_testing()
# Add test directory once tests are created
# add_subdirectory(tests)

# ============================================================================
# Install Rules
# ============================================================================
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)