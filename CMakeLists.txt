# Minimum required CMake version
cmake_minimum_required(VERSION 3.28)

# Project name and language
project(sfcm2 VERSION 0.1.0 LANGUAGES CXX)

# ============================================================================
# Compiler Configuration
# ============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# For debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()

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
    src/sfcm2.cpp
    src/core/block.cpp
    src/core/module.cpp
    src/core/simulation.cpp
    src/core/random.cpp
    src/io/parser.cpp
    src/io/strutils.cpp
    src/render/renderer.cpp
    src/user/camera.cpp
    src/user/interaction.cpp
    src/user/coding.cpp
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
# Packages
# ============================================================================
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)
message(STATUS "Using system SFML: ${SFML_VERSION_STRING}")

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)

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