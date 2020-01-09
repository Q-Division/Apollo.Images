cmake_minimum_required (VERSION 3.0)

include(ExternalProject)

message("Setting up libpng...")

set(LIBPNG_URL "${CMAKE_CURRENT_LIST_DIR}/libpng-1.6.37.tar.gz")
set(LIBPNG_DIR "${CMAKE_BINARY_DIR}/external_libs/libpng")

if(DEFINED EXTERNAL_INSTALL_DIR)
  set(ZLIB_INSTALL_DIR ${EXTERNAL_INSTALL_DIR})    
else()
  set(ZLIB_INSTALL_DIR "${LIBPNG}/install")
endif() 

set(LIBPNG_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${LIBPNG_INSTALL_DIR})
set(LIBPNG_CMAKE_ARGS ${LIBPNG_CMAKE_ARGS} -DPNG_SHARED:BOOL=OFF -DPNG_STATIC:BOOL=ON -DSKIP_INSTALL_EXECUTABLES:BOOL=ON -DSKIP_INSTALL_FILES:BOOL=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON)
set(LIBPNG_CMAKE_CACHE_ARGS "")
set(LIBPNG_PATCH_COMMAND "")

# Set compiler
set(LIBPNG_CMAKE_CACHE_ARGS ${LIBPNG_CMAKE_CACHE_ARGS} -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER})
set(LIBPNG_CMAKE_CACHE_ARGS ${LIBPNG_CMAKE_CACHE_ARGS} -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER})

#Add ZLIB
#set(ZLIB_INSTALL_DIR "${CMAKE_BINARY_DIR}/external_libs/zlib/install")
find_package(ZLIB REQUIRED)
message("ZLIB_FOUND: ${ZLIB_FOUND}")
message("ZLIB_INSTALL_DIR: ${ZLIB_INSTALL_DIR}")

if(DEFINED ZLIB_FOUND AND DEFINED ZLIB_INSTALL_DIR)
  if(MSVC)
    set(ZLIB_INCLUDE_DIR "${ZLIB_INCLUDE_DIRS}")
    set(ZLIB_LIBRARY "${ZLIB_LIBRARIES}")
  endif()
  
  #set(LIBPNG_CMAKE_ARGS ${LIBPNG_CMAKE_ARGS} -DZLIB_INSTALL_DIR:STRING=${ZLIB_INSTALL_DIR})
  set(LIBPNG_CMAKE_CACHE_ARGS ${LIBPNG_CMAKE_CACHE_ARGS} -DZLIB_FOUND:BOOL=YES -DZLIB_INCLUDE_DIR:STRING=${ZLIB_INCLUDE_DIR} -DZLIB_LIBRARY:STRING=${ZLIB_LIBRARY}) #-DZLIB_INSTALL_DIR:STRING=${ZLIB_INSTALL_DIR})
  
  if(DEFINED EXTERNAL_INSTALL_DIR)
	set(LIBPNG_CMAKE_CACHE_ARGS ${LIBPNG_CMAKE_CACHE_ARGS} -DEXTERNAL_INSTALL_DIR:STRING=${EXTERNAL_INSTALL_DIR})
  endif()
  
  #message("LIBPNG_CMAKE_CACHE_ARGS: ${LIBPNG_CMAKE_CACHE_ARGS}")
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

ExternalProject_Add(
  libpng-external
  DEPENDS zlib-external
  URL ${LIBPNG_URL}
  URL_MD5 6c7519f6c75939efa0ed3053197abd54
  DOWNLOAD_DIR ${LIBPNG_DIR}/download
  SOURCE_DIR ${LIBPNG_DIR}/source
  BINARY_DIR ${LIBPNG_DIR}
  INSTALL_DIR ${LIBPNG_INSTALL_DIR}
  CMAKE_ARGS "${LIBPNG_CMAKE_ARGS}"
  CMAKE_CACHE_ARGS "${LIBPNG_CMAKE_CACHE_ARGS}"
  BUILD_BYPRODUCTS ${LIBPNG_LIBRARIES}
  UPDATE_COMMAND ""
  PATCH_COMMAND "${LIBPNG_PATCH_COMMAND}"
)