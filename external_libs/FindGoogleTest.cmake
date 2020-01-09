# Locate and configure the downloaded googletest library
#
#
# Defines the following variables:
#
#   GOOGLETEST_FOUND - Found the GOOGLETEST
#   GOOGLETEST_INCLUDE_DIRS - The directories needed on the include paths
#   GOOGLETEST_LIBRARIES - The libraries to link to

cmake_minimum_required (VERSION 3.2)

include(GNUInstallDirs)

if(NOT DEFINED GOOGLETEST_INSTALL_DIR)
  if(NOT DEFINED EXTERNAL_INSTALL_DIR)
    set(GOOGLETEST_INSTALL_DIR ${CMAKE_BINARY_DIR}/external_libs/googletest/install)
  else()
    set(GOOGLETEST_INSTALL_DIR ${EXTERNAL_INSTALL_DIR})
  endif() 
endif()

message("Found googletest. (Install Dir: ${GOOGLETEST_INSTALL_DIR})")

set(GOOGLETEST_FOUND TRUE)
set(GOOGLETEST_INCLUDE_DIRS ${GOOGLETEST_INSTALL_DIR}/include)
set(GOOGLETEST_INCLUDE_DIR ${GOOGLETEST_INCLUDE_DIRS})
set(GOOGLETEST_NAME googletest-external)

if(NOT TARGET googletest-external)
	include("${CMAKE_CURRENT_LIST_DIR}/googletest.cmake")
endif()

if(WIN32)
	if(MINGW)
		set(GOOGLETEST_LIBRARIES ${GOOGLETEST_INSTALL_DIR}/lib/libgtest.a ${GOOGLETEST_INSTALL_DIR}/lib/libgmock.a ${GOOGLETEST_INSTALL_DIR}/lib/libgtest_main.a)
	else()
		set(GOOGLETEST_LIBRARIES 
			optimized ${GOOGLETEST_INSTALL_DIR}/lib/gtest.lib debug ${GOOGLETEST_INSTALL_DIR}/lib/gtestd.lib
			optimized ${GOOGLETEST_INSTALL_DIR}/lib/gmock.lib debug ${GOOGLETEST_INSTALL_DIR}/lib/gmockd.lib
			optimized ${GOOGLETEST_INSTALL_DIR}/lib/gtest_main.lib debug ${GOOGLETEST_INSTALL_DIR}/lib/gtest_maind.lib)
	endif()
else()
	set(GOOGLETEST_LIBRARIES ${GOOGLETEST_INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}/libgtest.a ${GOOGLETEST_INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}/libgmock.a ${GOOGLETEST_INSTALL_DIR}/${CMAKE_INSTALL_LIBDIR}/libgtest_main.a)
endif()

set(GOOGLETEST_LIBRARY ${GOOGLETEST_LIBRARIES})

message("GOOGLETEST_INCLUDE_DIRS = ${GOOGLETEST_INCLUDE_DIRS}")

if(DEBUG_MODULES)
  message("GOOGLETEST_INCLUDE_DIRS = ${GOOGLETEST_INCLUDE_DIRS}")
  message("GOOGLETEST_LIBRARIES = ${GOOGLETEST_LIBRARIES}")
endif()

mark_as_advanced(GOOGLETEST_INCLUDE_DIRS GOOGLETEST_INCLUDE_DIR GOOGLETEST_LIBRARIES GOOGLETEST_LIBRARY)

