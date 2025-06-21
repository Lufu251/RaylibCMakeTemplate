# Minimum required version of CMake
cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined")

# Project name and version
project(MyCppProject VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable compiler warnings
add_compile_options(-Wall)

# Include FetchContent
include(FetchContent)

# --------------- RAYLIB ---------------
message(STATUS "Fetching Raylib...")
FetchContent_Declare(
    raylib
    GIT_REPOSITORY  https://github.com/raysan5/raylib.git
    GIT_SHALLOW True
    #GIT_TAG         5.0
)
# Disable building of examples and shared libraries
option(BUILD_EXAMPLES "Build example of how to use this library." OFF)
option(BUILD_SHARED_LIBS "Build shared libs." OFF)
# set(GRAPHICS "GRAPHICS_API_OPENGL_43" FORCE)
FetchContent_MakeAvailable(raylib)

# Specify the output directories for compiled binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add source files to the project
# You can list all your source files here, or use a glob pattern to include all .cpp files in a directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories for header files
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR} 
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)
