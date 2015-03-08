cmake_minimum_required (VERSION 2.6)
	
# Set the compiler-specific 
if(MINGW OR CMAKE_COMPILER_IS_GNUCXX)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -msse4.1")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Wall")
	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og")
elseif (MSVC)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /Ob2 /Oi /Ot /GL")
	set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W3")
	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi /W4")
endif(MINGW OR CMAKE_COMPILER_IS_GNUCXX)

if(WIN32)
	if(CMAKE_CL_64)
	
		if(MINGW)
		
			set(ARCH_DIR "MinGW_w64")
			
		elseif(MSVC)
		
			set(ARCH_DIR "MSVCPP 2013 x86_64")
			
		endif(MINGW)
		
		set(OS_DIR "Windows x86_64")
		
	else(CMAKE_CL_64)
	
		if(MINGW)
		
			set(ARCH_DIR "MinGW")
			
		elseif(MSVC)
		
			set(ARCH_DIR "MSVCPP 2013 x86")
			
		endif(MINGW)
		
		set(OS_DIR "Windows x86")
		
	endif(CMAKE_CL_64)

	set(GFXMATH_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/${ARCH_DIR}")
			
	set(GFXMATH_LIB "${CMAKE_SOURCE_DIR}/lib/${ARCH_DIR}/GfxMath.lib")
		
	set(GFXTESTS_DIR "${CMAKE_SOURCE_DIR}/tests/${OS_DIR}")
		
else(WIN32)

	set(OS_DIR "Linux x86_64")
	
	set(GFXMATH_LIB_DIR "${CMAKE_SOURCE_DIR}/lib/Linux")
		
	set(GFXMATH_LIB "${GFX_MATH_LIB_DIR}/libGfxMath.a")
		
endif(WIN32)

set(GFXMATH_INCLUDE_DIR
	${CMAKE_SOURCE_DIR}/include)
set(GFXMATH_DOC_DIR 
	${CMAKE_SOURCE_DIR}/doc)
	
	

add_subdirectory(${CMAKE_BINARY_DIR}/src)
add_subdirectory(${CMAKE_BINARY_DIR}/tests/src)