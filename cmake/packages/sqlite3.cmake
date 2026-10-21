find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_library(sqlite3 INTERFACE)

target_link_libraries(sqlite3 INTERFACE
    unofficial::sqlite3::sqlite3
)