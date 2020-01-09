# Locate and configure the downloaded zlib library
#
#
# Defines the following variables:
#
#   ZLIB_FOUND - Found the ZLIB
#   ZLIB_INCLUDE_DIRS - The directories needed on the include paths
#   ZLIB_LIBRARIES - The libraries to link to

if(NOT DEFINED ZLIB_INSTALL_DIR)
  if(NOT DEFINED EXTERNAL_INSTALL_DIR)
    set(ZLIB_INSTALL_DIR ${CMAKE_BINARY_DIR}/external_libs/zlib/install)
  else()
    set(ZLIB_INSTALL_DIR ${EXTERNAL_INSTALL_DIR})
  endif() 
endif()

message("Found zlib. (Install Dir: ${ZLIB_INSTALL_DIR}")

set(ZLIB_FOUND TRUE)
set(ZLIB_INCLUDE_DIRS ${ZLIB_INSTALL_DIR}/include)
set(ZLIB_INCLUDE_DIR ${ZLIB_INCLUDE_DIRS})
set(ZLIB_NAME zlib-external)

if(NOT TARGET zlib-external)
	include("${CMAKE_CURRENT_LIST_DIR}/zlib.cmake")
endif()

if(WIN32)
  if(MINGW)
    set(ZLIB_LIBRARIES ${ZLIB_INSTALL_DIR}/lib/libzlib.a)
  else()
    set(ZLIB_LIBRARIES optimized ${ZLIB_INSTALL_DIR}/lib/zlibstatic.lib debug ${ZLIB_INSTALL_DIR}/lib/zlibstaticd.lib)
  endif()
else()
  set(ZLIB_LIBRARIES ${ZLIB_INSTALL_DIR}/lib/libz.a)
endif()

set(ZLIB_LIBRARY ${ZLIB_LIBRARIES})

if(DEBUG_MODULES)
  message("ZLIB_INCLUDE_DIRS = ${ZLIB_INCLUDE_DIRS}")
  message("ZLIB_LIBRARIES = ${ZLIB_LIBRARIES}")
endif()

mark_as_advanced(ZLIB_INCLUDE_DIRS ZLIB_INCLUDE_DIR ZLIB_LIBRARIES ZLIB_LIBRARY)

