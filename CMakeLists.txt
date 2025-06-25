# Minimum required version of CMake
cmake_minimum_required(VERSION 3.22)
# Project name and version
project(MyCppProject VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##########################################################################################
# Configurable options
##########################################################################################

# toggle libs to be used with ON and OFF
option(USE_RAYLIB "Use raylib" ON)
option(USE_RAYGUI "Use raygui" OFF)
option(USE_BOX2D "Use Box2D" OFF)
option(USE_LDTKLOADER "Use LDtk Loader" OFF)


##########################################################################################
# Add dependencies with FetchContent
##########################################################################################

# libraries array to be linked
set(LIBRARIES ${PROJECT_NAME})

include(FetchContent)
function(add_git_dependency libName gitURL gitTag)
    message(STATUS "Fetching ${libName}...")

    FetchContent_Declare(${libName}
        GIT_REPOSITORY ${gitURL}
        GIT_TAG        ${gitTag}
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()


##########################################################################################
# Raylib Setup
##########################################################################################

if(USE_RAYLIB)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
    set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
    set(CUSTOMIZE_BUILD OFF CACHE BOOL "" FORCE) 

    add_git_dependency(
        raylib
        https://github.com/raysan5/raylib.git
        master
    )

    # add the dependency here to be linked
    list(APPEND LIBRARIES raylib)
endif()


##########################################################################################
# Raygui Setup
##########################################################################################

if(USE_RAYGUI)
    set(BUILD_RAYGUI_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_git_dependency(
        raygui
        https://github.com/raysan5/raygui.git
        master
    )

    # add the dependency here to be linked
    list(APPEND LIBRARIES raygui)
endif()


##########################################################################################
# Box2D Setup
##########################################################################################

if(USE_BOX2D)
    set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    add_git_dependency(
        box2d
        https://github.com/erincatto/box2d.git
        master
    )

    # add the dependency here to be linked
    list(APPEND LIBRARIES box2d)
endif()


##########################################################################################
# LDtk Loader Setup
##########################################################################################

if(USE_LDTKLOADER)
    add_git_dependency(
        LDtkLoader
        https://github.com/Madour/LDtkLoader.git
        master
    )

    # add the dependency here to be linked
    list(APPEND LIBRARIES LDtkLoader)
endif()


##########################################################################################
# Project executable setup
##########################################################################################

# Specify the output directories for compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Adding our source files
# Define PROJECT_SOURCES as a list of all source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

# Define PROJECT_INCLUDE to be the path to the include directory of the project
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/include/")

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})


##########################################################################################
# Project build settings
##########################################################################################

# Build for web instructions
if (${PLATFORM} STREQUAL "Web")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
endif ()

# Link libraries
target_link_libraries(${LIBRARIES})

# Set common compiler options for your target
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra      # More warnings
    -Wpedantic   # Strict ISO C++ compliance warnings
    # Add other warning flags like -Wshadow, -Wconversion, etc. as needed
)