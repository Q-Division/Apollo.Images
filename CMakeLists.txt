cmake_minimum_required (VERSION 3.1)
project (Apollo.Images)

include(CMakeSetFilter.cmake)

set(CMAKE_CXX_STANDARD 14)

set(APOLLO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "")

message("APOLLO_ROOT: ${APOLLO_ROOT}")
message("BINDIR: ${CMAKE_BINARY_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build/Bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build/Lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

message("ROD: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("LOD: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("AOD: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
option(ENABLE_COVERAGE "Enable coverage (turns on unit tests)" ON)

if(ENABLE_COVERAGE)
	message(STATUS "Coverage Enabled")
	set(ENABLE_UNIT_TESTS ON)
endif()

if(ENABLE_UNIT_TESTS)
	message(STATUS "Unit Testing Enabled")
endif()

set(EXTERNAL_INSTALL_DIR "${CMAKE_BINARY_DIR}/external_libs/install")

# Add Code
include("${CMAKE_CURRENT_SOURCE_DIR}/Code/Apollo.Images.Code.cmake")

if(ENABLE_COVERAGE)
	#Setup Coverage
	if(WIN32)
		string(REGEX REPLACE "/" "\\\\" WIN_APOLLO_ROOT ${APOLLO_ROOT})
		
		add_custom_target(coverage-html
							COMMAND OpenCppCoverage.exe
							--input_coverage ${WIN_APOLLO_ROOT}\\wincoveragetmp\\apollo.images.cov
							--export_type=html:${WIN_APOLLO_ROOT}\\wincoverage
							COMMENT "Generating coverage HTML report"
							DEPENDS coverage-apollo.images)
	else()
		string(REPLACE "+" "\\\\+" COV_APOLLO_ROOT ${APOLLO_ROOT})

		#Add Unix HTML Coverage Directory and File paths
		set(COVERAGE_HTML_DIR "${APOLLO_ROOT}/unixcoverage")
		set(COVERAGE_HTML_FILE "${COVERAGE_HTML_DIR}/coverage.html")
			
		#add_custom_command(OUTPUT ${COVERAGE_HTML_FILE}
		add_custom_target(coverage-html
						   #COMMAND ${CMAKE_COMMAND} -E remove_directory ${COVERAGE_HTML_DIR}	
						   COMMAND ${CMAKE_COMMAND} -E make_directory ${COVERAGE_HTML_DIR}
						   COMMAND gcovr --html --html-details --html-title Apollo.Images --exclude-unreachable-branches --exclude-throw-branches
								-r ${APOLLO_ROOT}
								-f ${COV_APOLLO_ROOT}/Code
								-e ${COV_APOLLO_ROOT}/Code/Apollo.Images.UnitTests
								-o ${COVERAGE_HTML_FILE}
						   COMMENT "Generating coverage HTML report")
						   
		add_dependencies(coverage-html run-apollo.images-unit-tests)
		
		#Add Unix XML Coverage
		set(COVERAGE_XML_FILE "${APOLLO_ROOT}/coverage.xml")
		
		add_custom_target(coverage-xml
						   COMMAND gcovr --xml-pretty --exclude-unreachable-branches --exclude-throw-branches
								-r ${APOLLO_ROOT}
								-f ${COV_APOLLO_ROOT}/Code
								-e ${COV_APOLLO_ROOT}/Code/Apollo.Images.UnitTests
								-o ${COVERAGE_XML_FILE}
						   COMMENT "Generating coverage XML report")
						   
		add_dependencies(coverage-xml run-apollo.images-unit-tests)
	endif()
endif()