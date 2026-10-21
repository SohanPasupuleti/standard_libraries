find_package(SDL3 CONFIG REQUIRED)

add_library(sdl3 INTERFACE)

target_link_libraries(sdl3 INTERFACE
    SDL3::SDL3
)