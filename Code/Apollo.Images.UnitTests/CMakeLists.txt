cmake_minimum_required (VERSION 3.1)

string(TOLOWER "Apollo.Images" ProjectNameLC)

#Include GoogleTest
list(APPEND CMAKE_MODULE_PATH "${APOLLO_ROOT}/external_libs")
find_package(GoogleTest REQUIRED)
include_directories("${GOOGLETEST_INCLUDE_DIRS}")

#Include libpng and zlib
find_package(ZLIB REQUIRED)
find_package(LIBPNG REQUIRED)

include_directories("${ZLIB_INCLUDE_DIRS}")
include_directories("${LIBPNG_INCLUDE_DIRS}")

#Include Apollo.Images
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../Apollo.Images")
find_package(Apollo.Images REQUIRED)
include_directories("${APOLLO_IMAGES_INCLUDE_DIRS}")

set(APOLLO_IMAGES_UNIT_TEST_DIR "${CMAKE_CURRENT_LIST_DIR}")

#Set Source List
set(source_list
	"${CMAKE_CURRENT_LIST_DIR}/ColorTest.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/ImageTest.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/PathHelper.h"
	"${CMAKE_CURRENT_LIST_DIR}/PngLoaderTest.cpp"
)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

SetFilter("${source_list}" "${CMAKE_CURRENT_LIST_DIR}")

if(UNIX)
	message("Adding GCOV options")
	add_compile_options(-pthread -fprofile-arcs -ftest-coverage)

	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl")
endif()

add_executable(Apollo.Images.UnitTests ${source_list})

if(TARGET googletest-external)
	add_dependencies(Apollo.Images.UnitTests googletest-external)
endif()

if(WIN32)
	target_link_libraries(Apollo.Images.UnitTests ${GOOGLETEST_LIBRARIES} Apollo.Images)
else()
	target_link_libraries(Apollo.Images.UnitTests ${GOOGLETEST_LIBRARIES} Apollo.Images.Coverage)
endif()

if(WIN32)
	set(UNITTESTS_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}")
	set(UNITTESTS_ARG --gtest_output="xml:${APOLLO_ROOT}/wintestresults.xml")
else()
	set(UNITTESTS_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")	
	set(UNITTESTS_ARG --gtest_output="xml:${APOLLO_ROOT}/unixtestresults.xml")
endif()

#Copy Test Images
add_custom_command(TARGET Apollo.Images.UnitTests POST_BUILD
				   COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/TestImages ${UNITTESTS_DIR}/TestImages
				   COMMENT "Copy Test Images")

set(UNITTESTS_CMD "${UNITTESTS_DIR}/Apollo.Images.UnitTests")
message("UNITTESTS_CMD: ${UNITTESTS_CMD}")

#Add Run UnitTests Command
add_custom_target(run-${ProjectNameLC}-unit-tests
				   COMMAND ${UNITTESTS_CMD} ${UNITTESTS_ARG} 
				   WORKING_DIRECTORY ${UNITTESTS_DIR}
				   DEPENDS Apollo.Images.UnitTests
				   COMMENT "Run UnitTests")

if(WIN32)
	string(REGEX REPLACE "/" "\\\\" WIN_APOLLO_ROOT ${APOLLO_ROOT})
	string(REGEX REPLACE "/" "\\\\" WIN_SOURCES ${APOLLO_ROOT}/Code/Apollo.Images/)
	string(REGEX REPLACE "/" "\\\\" WIN_UNITTESTS_CMD ${UNITTESTS_CMD})
	
	message("WIN_SOURCES: ${WIN_SOURCES}")
	message("WIN_UNITTESTS_CMD: ${WIN_UNITTESTS_CMD}")

	add_custom_target(coverage-${ProjectNameLC}
					   COMMAND OpenCppCoverage.exe
							--sources ${WIN_SOURCES}
							--excluded_sources ${WIN_SOURCES}\\*.UnitTests
							--export_type=binary:${WIN_APOLLO_ROOT}\\wincoveragetmp\\apollo.images.cov
							-- ${WIN_UNITTESTS_CMD}
					   COMMENT "Generating coverage XML report")					
endif()