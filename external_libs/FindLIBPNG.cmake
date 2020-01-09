# Locate and configure the downloaded LIBPNG library
#
#
# Defines the following variables:
#
#   LIBPNG_FOUND - Found the LIBPNG
#   LIBPNG_INCLUDE_DIRS - The directories needed on the include paths
#   LIBPNG_LIBRARIES - The libraries to link to

include(GNUInstallDirs)

if(NOT DEFINED LIBPNG_INSTALL_DIR)
  if(NOT DEFINED EXTERNAL_INSTALL_DIR)
    set(LIBPNG_INSTALL_DIR ${CMAKE_BINARY_DIR}/external_libs/libpng/install)
  else()
    set(LIBPNG_INSTALL_DIR ${EXTERNAL_INSTALL_DIR})
  endif() 
endif()

message("Found LIBPNG. (Install Dir: ${LIBPNG_INSTALL_DIR})")

set(LIBPNG_FOUND TRUE)
set(LIBPNG_INCLUDE_DIRS ${LIBPNG_INSTALL_DIR}/include)
set(LIBPNG_INCLUDE_DIR ${LIBPNG_INCLUDE_DIRS})
set(LIBPNG_NAME libpng-external)

if(NOT TARGET libpng-external)
	include("${CMAKE_CURRENT_LIST_DIR}/libpng.cmake")
endif()

if(WIN32)
  if(MINGW)
    set(LIBPNG_LIBRARIES ${LIBPNG_INSTALL_DIR}/lib/libpng.a)
  else()
    set(LIBPNG_LIBRARIES optimized ${LIBPNG_INSTALL_DIR}/lib/libpng16_static.lib debug ${LIBPNG_INSTALL_DIR}/lib/libpng16_staticd.lib)
  endif()
else()
  set(LIBPNG_LIBRARIES ${LIBPNG_INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}/libpng.a)
endif()

set(LIBPNG_LIBRARY ${LIBPNG_LIBRARIES})

if(DEBUG_MODULES)
  message("LIBPNG_INCLUDE_DIRS = ${LIBPNG_INCLUDE_DIRS}")
  message("LIBPNG_LIBRARIES = ${LIBPNG_LIBRARIES}")
endif()

mark_as_advanced(LIBPNG_INCLUDE_DIRS LIBPNG_INCLUDE_DIR LIBPNG_LIBRARIES LIBPNG_LIBRARY)

