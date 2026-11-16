# Create the executable target here
add_executable(nes_emulator
    frontend/main.cpp
    core/cpu.cpp
    core/ppu.cpp
    core/apu.cpp
    core/bus.cpp
    core/cartridge.cpp
    core/mapper.cpp
    # core/cartridge.cpp, etc.
)

# Tell CMake where to look for headers relative to src/
target_include_directories(nes_emulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link external libraries found by the root CMake file
target_link_libraries(nes_emulator PRIVATE SDL3::SDL3)
