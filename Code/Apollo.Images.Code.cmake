cmake_minimum_required (VERSION 3.1)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Apollo.Images")

if(ENABLE_UNIT_TESTS)
	add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Apollo.Images.UnitTests")
endif()