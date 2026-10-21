find_package(glad CONFIG REQUIRED)

add_library(glad INTERFACE)

target_link_libraries(glad INTERFACE
    glad::glad
)