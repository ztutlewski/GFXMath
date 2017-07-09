
# (G○F)(X) Math


## Introduction

The (GoF)(X) Math library (abbreviated GoFXMath) is a lightweight, powerful, cross-platform math library focused on the development of graphics-oriented applications in C++.  

## Design

Given that the GoFXMath library is designed with data flexibility in mind, much of its functionality is overloaded between two major sections: SISD code and SIMD code.

#### SISD

---

The SISD code is all standard C++, and generally does not leverage the hardware or compiler for optimizations more than is absolutely necessary, keeping the code relatively fast without sacrificing too much readability.  Given that the compiler will typically optimize the types of standard C++ operations used here far better than most programmers ever could anyway, this doesn't affect the performance of the SISD code much.

#### SIMD

---

The SIMD side, on the other hand, almost exclusively utilizes intel® SSE intrinsics, and frequently makes use of some _very_ low-level techniques.  However, while these will somewhat reduce readability, many of the more common operations (such as absolute value, negation, etc.) have been written into helper functions.  Additionally, the many of the intel® SSE functions have been given wrapper functions to improve their readability, and maintainability for future changes to SSE functions or additions of similar functionality from other libraries such as ARM NEON™.  For example, `_mm_mul_ps(__m128)` is wrapped in `VecMul(SseVec)`.  It should be noted that almost all the functions in the SIMD portions are marked as `inline`, including the wrapper functions, and are fully defined in the header files.  As well, GoFXMath library does not make use of .inl files, or split header files for `inline` functions; the declarations and definitions are fully contained in the same files.  

It should be noted that the defined functions and constants for the GoFXMath library rely on big-endian logic for the SSE registers.  That is to say that the logic incorporated positions the values in "reverse" order in the register from what the built-in sse functions use.  The reason for this is to improve readability of complex SSE logic, and to prevent extra loading/unloading overhead when switching between the standard registers and the SSE registers.  What this means is that when loading a `Vec4` into or out from an SSE register, its values will not need to be reversed on each transfer, and can simply be loaded and unloaded in-order.  Similarly, when calling one of the `SetSseVec` functions, the arguments passed are to be used in the same logical order for the desired vector (e.g. `SetSseVec3(x,y,z)` loads the SSE register with the values like this: `<1.0f, z, y, x>` where the `1.0f` is used with calculations involving transformation matrices.


## Binaries

Compiler-specific binaries, as well as a few other various zipped forms of the project, can be found in  [this project's releases](https://github.com/ztutlewski/GoFXMath/releases).


## Requirements

The GoFXMath library doesn't have any particular dependencies attached to it.  It has been built and tested with Visual C++ 2013 (32 and 64-bit versions, on Windows 7 64-bit), MinGW-w64 g++4.9.2 (64-bit version on Windows 7 64-bit), and GNU g++4.8.2 (Ubuntu 14.04.2 LTS 64-bit).  As of yet, it has not been tested on an Apple machine, though the standard XCode C++ compiler should yield similarly successful results.

The GoFXMath library does make use of some C++11 features, so any compiler that should have any hope of building or using it would need to be up to at least the same level of C++11 standards as Visual C++ 12.

Additionally, as mentioned in the **SIMD** section, the GoFXMath library makes heavy use of intel® SSE functions.  While most of this functionality is defined in earlier forms of the SSE intrinsics, some require SSE-4.1.  However, most currently used, standard, consumer-grade CPUs should be able to accommodate this requirement, as it has had fairly wide support for quite some time.

## Tests and Demo Projects

The prepackaged distribution files, in addition to the binaries and documentation, also contain the compiled test projects and a demo project written for OpenGL (using [GLEW](http://glew.sourceforge.net/) and [GLFW](http://www.glfw.org/)).

#### Tests

---

The tests should build and run on any Windows 7 or higher machine, as well as any Linux distribution capable of running g++4.8.2 compiled libraries.  The tests have been built with the [Catch Testing Framework](https://github.com/philsquared/Catch).  Note that there are (sometimes significantly) more than one assertion-per-test, in many, if not most, of the test cases.  The tests are written this way due to the fact that the catch framework offers a method of posing an assert while not forcing a halt on a specific test case, and all the tests have been written with this method in mind.  There are also numerous fringe-cases when working with matrices and vectors (especially SSE vectors) that must be accounted for to maintain the expected mathematical behavior.

More information on how to run (or even add to) the tests can be found on the [Catch Testing Framework github page](https://github.com/philsquared/Catch).

#### Demo

---

There are included windows and linux executables for the demo project.  Naturally, the source code is included alongside the executable.  As mentioned  in the beginning of this section, the demo project uses [GLEW](http://glew.sourceforge.net/) and [GLFW](http://www.glfw.org/), and will require both to be properly linked before it can be built.

Binaries for the demo can be obtained from the [GoFXDemoEngine Sourceforge page.](https://sourceforge.net/projects/gofx/files/demo/)
