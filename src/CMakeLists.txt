cmake_minimum_required (VERSION 2.6)
project (GoFXMath)

include_directories(${GFXMATH_INCLUDE_DIR})

add_library(GoFXMath STATIC 
	mat44.cpp 
	math_defs.cpp
	matmath.cpp 
	quaternion.cpp 
	ssemat44.cpp 
	ssevec.cpp 
	vec2.cpp 
	vec3.cpp 
	vec4.cpp 
	vecmath.cpp)
	

SET(LIBRARY_OUTPUT_PATH ${GFXMATH_LIB_DIR})

target_link_libraries(GoFXMath  ITKCommon)