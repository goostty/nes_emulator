cmake_minimum_required(VERSION 3.25)
project(nes_emulator)

# Find Package
find_package(SDL3 CONFIG REQUIRED)

# Hand control over to the CMakeLists.txt inside the src/ folder
add_subdirectory(src)
