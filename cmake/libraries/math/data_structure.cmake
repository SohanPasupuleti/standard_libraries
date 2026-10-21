file(GLOB MATH_DATA_STRUCTURE_SOURCE_FILES CONFIGURE_DEPENDS 
	"${MAIN_DEVELOPMENT_ROOT}/libraries/math/data_structure/source/*.cpp"
	"${MAIN_DEVELOPMENT_ROOT}/libraries/math/data_structure/source/*.f90"
)

add_library(math_data_structure STATIC ${MATH_DATA_STRUCTURE_SOURCE_FILES})

target_include_directories(math_data_structure PUBLIC ${MAIN_DEVELOPMENT_ROOT}/libraries/math/data_structure/header)

target_link_libraries(math_data_structure PUBLIC gfortran)

set_target_properties(math_data_structure PROPERTIES LINKER_LANGUAGE CXX)