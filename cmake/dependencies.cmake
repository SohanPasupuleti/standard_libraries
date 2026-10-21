get_filename_component(
    MAIN_DEVELOPMENT_ROOT
    "${CMAKE_CURRENT_LIST_DIR}/.."
    ABSOLUTE
)

include("${MAIN_DEVELOPMENT_ROOT}/cmake/packages/sqlite3.cmake")
include("${MAIN_DEVELOPMENT_ROOT}/cmake/packages/glad.cmake")
include("${MAIN_DEVELOPMENT_ROOT}/cmake/packages/sdl3.cmake")

include("${MAIN_DEVELOPMENT_ROOT}/cmake/libraries/standard/utility.cmake")
include("${MAIN_DEVELOPMENT_ROOT}/cmake/libraries/standard/data_structure.cmake")
include("${MAIN_DEVELOPMENT_ROOT}/cmake/libraries/math/data_structure.cmake")