file(GLOB DATA_STRUCTURE_SOURCE_FILES CONFIGURE_DEPENDS 
	"${MAIN_DEVELOPMENT_ROOT}/libraries/standard/data_structure/source/*.cpp"
)

add_library(standard_data_structure STATIC ${DATA_STRUCTURE_SOURCE_FILES})

target_include_directories(standard_data_structure PUBLIC ${MAIN_DEVELOPMENT_ROOT}/libraries/standard/data_structure/header)

target_link_libraries(standard_data_structure PUBLIC standard_utility)
