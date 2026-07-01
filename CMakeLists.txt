cmake_minimum_required(VERSION 3.10)
project(Sdl-Testing)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)  # Optional, for image loading

# Include SDL2 directories
include_directories(${SDL2_INCLUDE_DIRS})

# Create the executable
add_executable(square main.c)

# Link SDL2 libraries
target_link_libraries(square ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# For better debugging, include compile commands for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
