file(GLOB UTILITY_SOURCE_FILES CONFIGURE_DEPENDS 
	"${MAIN_DEVELOPMENT_ROOT}/libraries/standard/utility/source/*.cpp"
)

add_library(standard_utility STATIC ${UTILITY_SOURCE_FILES})

target_include_directories(standard_utility PUBLIC
    ${MAIN_DEVELOPMENT_ROOT}/libraries/standard/data_structure/header
    ${MAIN_DEVELOPMENT_ROOT}/libraries/standard/utility/header
)

target_link_libraries(standard_utility PUBLIC
    sqlite3
)