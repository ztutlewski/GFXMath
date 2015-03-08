cmake_minimum_required (VERSION 2.6)
project (GFXTests)

include_directories(
	${GFXMATH_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/tests/include
	${CMAKE_SOURCE_DIR}/tests/include/Catch
	)
	
add_executable (GFXTests
	main.cpp
	matmath_tests.cpp
	scalar_tests.cpp
	ssevec_tests.cpp
	vec_tests.cpp
	string_convert.cpp
	)
	
SET(EXECUTABLE_OUTPUT_PATH ${GFXTESTS_DIR})
	
target_link_libraries(GFXTests ${GFXMATH_LIB})