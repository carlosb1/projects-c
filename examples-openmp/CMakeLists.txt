cmake_minimum_required (VERSION 2.8)
project (TestsOpenMP)
set(CMAKE_VERBOSE_MAKEFILE 1)

#Add OpenMP dependencies
find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

#Add C++1x support 
#flags to debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++1y -O3")

#Source code
set (SRCFILES 
	./utils_matrix.cpp
	./examples_openmp.cpp
 )
 
 #Add executable
 add_executable(examples_openmp ${SRCFILES})
 set_target_properties(examples_openmp PROPERTIES COMPILE_FLAGS "-DNDEBUG")

 add_executable(examples_openmp_debug ${SRCFILES})
 set_target_properties(examples_openmp_debug PROPERTIES COMPILE_FLAGS "-ggdb")
 
 add_executable(examples_openmp_prof ${SRCFILES})
 set_target_properties(examples_openmp_prof PROPERTIES LINK_FLAGS "-pg")

 #Link process
