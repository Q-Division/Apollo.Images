cmake_minimum_required(VERSION 3.1)

get_filename_component(APOLLO_IMAGES_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

set(APOLLO_IMAGES_INCLUDE_DIRS ${APOLLO_IMAGES_DIR})
set(APOLLO_IMAGES_LIBRARIES Apollo.Images)
