cmake_minimum_required(VERSION 2.8)

project(luasyslog)

include("default.cmake")

include_directories("${CMAKE_CURRENT_LIST_DIR}/inc")

aux_source_directory("${CMAKE_CURRENT_LIST_DIR}/src" _src_files)
taco_get_obj_files("${CMAKE_CURRENT_LIST_DIR}/src" _obj_files)

add_library(${PROJECT_NAME} SHARED ${_src_files} ${_obj_files})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION "lib")
