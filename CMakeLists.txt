# Define the minimum CMake version required
# Define the project name, version, and programming language
cmake_minimum_required(VERSION 3.20)
project(tesseractui VERSION 0.1.0 LANGUAGES CXX)

# Set the C++ standard to C++20
# REQUIRED ON means fail if the compiler doesn't support C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# PkgConfig is used to find and configure external libraries
# pkg_check_modules is used to find the Notcurses library
# require means that the build will fail if Notcurses is not found
find_package(PkgConfig REQUIRED)
pkg_check_modules(NOTCURSES REQUIRED IMPORTED_TARGET notcurses)

# Create a library target named tesseractui
# The source file for this library is src/app.cpp
# List all source files needed for the library here
add_library(tesseractui
    src/app.cpp
    src/buffer.cpp
    src/renderer.cpp
    src/widget.cpp
    src/widgets/label.cpp
    src/widgets/button.cpp
)

# PUBLIC means that the include directories are needed by consumers of the library
# ${CMAKE_CURRENT_SOURCE_DIR}/include is the path to the include directory
# This is why you can write #include <tesseractui/app.h> in your source files
target_include_directories(tesseractui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${NOTCURSES_INCLUDE_DIRS}
)

# Link the Notcurses libraries to the tesseractui target
# PUBLIC means that consumers of tesseractui will also link against Notcurses
target_link_libraries(tesseractui
    PUBLIC
        PkgConfig::NOTCURSES
)

add_executable(test_widgets examples/test_widgets.cpp)
target_link_libraries(test_widgets tesseractui)