cmake_minimum_required (VERSION 2.6)
project (GoFXMath)

include_directories("${GOFXMATH_INCLUDE_DIR}")

FILE(GLOB GOFXMATH_HEADERS "${GOFXMATH_INCLUDE_DIR}/*.h")

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
	vecmath.cpp
	${GOFXMATH_HEADERS}
	)

set(LIBRARY_OUTPUT_PATH "${GOFXMATH_LIB_DIR}")

target_link_libraries(GoFXMath)


