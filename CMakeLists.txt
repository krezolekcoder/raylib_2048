cmake_minimum_required(VERSION 3.0)
project(raylib2048)
set(CMAKE_CXX_STANDARD 11)
# Find raylib package
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(raylib REQUIRED)

set(INCLUDE_DIRS
	src
)
# Add your main executable
add_executable(raylib2048 
	src/main.c 
	src/platform_port.c
	src/core_2048.c
)
# Link raylib and other required libraries
target_link_libraries(raylib2048 PRIVATE raylib)

