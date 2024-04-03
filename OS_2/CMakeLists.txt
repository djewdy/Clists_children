# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(MyProcessProject)

# Set the C standard to use
set(CMAKE_C_STANDARD 99)

# Add the executable
add_executable(ProcessExecutable main.c)

# Specify installation rules (optional step if you want to install your program)
install(TARGETS ProcessExecutable DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
