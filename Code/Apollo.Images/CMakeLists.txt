cmake_minimum_required (VERSION 3.1)
project (Apollo.Images)

if(NOT DEFINED APOLLO_ROOT)
	set(APOLLO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../..")
endif()

if(CMAKE_COMPILER_IS_GNUCC)
	message("Setting -fvisibility=hidden")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
	SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fvisibility=hidden")
endif()

message("APOLLO_ROOT: ${APOLLO_ROOT}")
message("BINDIR: ${CMAKE_BINARY_DIR}")

#Include GoogleTest
list(APPEND CMAKE_MODULE_PATH "${APOLLO_ROOT}/external_libs")
find_package(ZLIB REQUIRED)
find_package(LIBPNG REQUIRED)

include_directories("${ZLIB_INCLUDE_DIRS}")
include_directories("${LIBPNG_INCLUDE_DIRS}")
message("LIBPNG: ${LIBPNG_INCLUDE_DIRS}")

set(source_list
	"${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt"
	"${CMAKE_CURRENT_LIST_DIR}/Color.h"
	"${CMAKE_CURRENT_LIST_DIR}/Image.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/Image.h"
	"${CMAKE_CURRENT_LIST_DIR}/IImageLoader.h"
	"${CMAKE_CURRENT_LIST_DIR}/InvalidPngException.h"
	"${CMAKE_CURRENT_LIST_DIR}/PixelFormat.h"
	"${CMAKE_CURRENT_LIST_DIR}/PngHeader.h"
	"${CMAKE_CURRENT_LIST_DIR}/PngLoader.cpp"
	"${CMAKE_CURRENT_LIST_DIR}/PngLoader.h"	
)

include_directories("${CMAKE_CURRENT_LIST_DIR}")

add_library(Apollo.Images ${source_list})
target_link_libraries(Apollo.Images ${LIBPNG_LIBRARIES} ${ZLIB_LIBRARIES})
set_target_properties(Apollo.Images PROPERTIES OUTPUT_NAME "Apollo.Images$<$<CONFIG:Debug>:d>")

if(TARGET libpng-external)
	add_dependencies(Apollo.Images libpng-external)
endif()

if(TARGET zlib-external)
	add_dependencies(Apollo.Images zlib-external)
endif()

if(ENABLE_COVERAGE)
	#Setup Coverage Version (Unix Only)
	if(UNIX)
		add_compile_options(-pthread -fprofile-arcs -ftest-coverage)
		add_library(Apollo.Images.Coverage ${source_list})
		add_dependencies(Apollo.Images.Coverage libpng-external)
		target_link_libraries(Apollo.Images.Coverage ${LIBPNG_LIBRARIES} ${ZLIB_LIBRARIES})	
	endif()
endif()

#Install
set(public_include
	"${CMAKE_CURRENT_LIST_DIR}/Color.h"
	"${CMAKE_CURRENT_LIST_DIR}/Image.h"
	"${CMAKE_CURRENT_LIST_DIR}/InvalidPngException.h"
	"${CMAKE_CURRENT_LIST_DIR}/PixelFormat.h"
	"${CMAKE_CURRENT_LIST_DIR}/PngHeader.h"
	"${CMAKE_CURRENT_LIST_DIR}/PngLoader.h"	
)

set_target_properties(Apollo.Images PROPERTIES PUBLIC_HEADER "${public_include}")

install(TARGETS Apollo.Images
		RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
		ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
		PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/Apollo/Images)
