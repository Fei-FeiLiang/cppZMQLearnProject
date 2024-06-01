cmake_minimum_required (VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${TARGET})

#静态库
add_compile_definitions(ZMQ_STATIC)

if(NOT ROOTPATH)
  file(TO_CMAKE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../" ROOTPATH)
endif()
 
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${ROOTPATH}/bin/debug)   
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ROOTPATH}/bin/release)

 
file(GLOB SRC_FILES "./src/*.cpp")
file(GLOB HEAD_FILES "./src/*.h")
file(GLOB MOC_FILES "mocs_*.cpp")

#source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${HEAD_FILES})
#source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_FILES})
#add_executable(${PROJECT_NAME} ${HEAD_FILES} ${SRC_FILES} ${MOC_FILES})

include(${ROOTPATH}/cmake/app.cmake)
include(${ROOTPATH}/cmake/cppmq.cmake)