cmake_minimum_required (VERSION 2.6)
project (GoFXTests)

set(GOFXTESTS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/tests/include")

include_directories(
	"${GOFXMATH_INCLUDE_DIR}"
	"${GOFXTESTS_INCLUDE_DIR}"
	"${GOFXTESTS_INCLUDE_DIR}/Catch"
	)

link_directories("${GOFXMATH_LIB_DIR}/${BUILD_TYPE_DIR}")

FILE(GLOB GOFXTESTS_HEADERS "${GOFXTESTS_INCLUDE_DIR}/*.h")
	
add_executable (GoFXTests
	main.cpp
	matmath_tests.cpp
	scalar_tests.cpp
	ssevec_tests.cpp
	vec_tests.cpp
	string_convert.cpp
	${GOFXTESTS_HEADERS}
	)

set(EXECUTABLE_OUTPUT_PATH "${GOFXTESTS_DIR}")

target_link_libraries(GoFXTests GoFXMath)