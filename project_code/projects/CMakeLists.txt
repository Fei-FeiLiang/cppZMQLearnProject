cmake_minimum_required (VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${TARGET})

if(NOT ROOTPATH)
  file(TO_CMAKE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../" ROOTPATH)
endif()

file(GLOB children LIST_DIRECORIES true "${CMAKE_CURRENT_SOURCE_DIR}/*")
set(dirlist "")
foreach(child ${children})
    if(IS_DIRECTORY ${child})
	    get_filename_component(subdirectory ${child} NAME)
		if(EXISTS "${child}/CMakeLists.txt")
		    add_subdirectory(${subdirectory})
		endif()
	endif()
endforeach()