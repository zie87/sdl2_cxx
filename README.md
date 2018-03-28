# sdl2_cxx

| Build status          | Systems / Compilers         |
| ------------- | ------------------------------------------ |
| [![CLang / GCC / XCode Builds](https://travis-ci.org/zie87/sdl2_cxx.svg?branch=master)](https://travis-ci.org/zie87/sdl2_cxx) | Linux (clang5  / gcc7) OSX (XCode 8.3 clang) |
| [![Visual Studio Builds](https://ci.appveyor.com/api/projects/status/90ryctsanv84928b/branch/master?svg=true)](https://ci.appveyor.com/project/zie87/sdl2-cxx/branch/master) | Windows (Visual Studio 2017 / 2015)  |

## info
It use basic [C++14](https://isocpp.org/wiki/faq/cpp14-language) syntax, but nothing really complicated.

This project try to follow [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines) whenever its possible.

[CMake](https://cmake.org/) is the chosen build system using [ctest](https://cmake.org/Wiki/CMake/Testing_With_CTest).

## libraries used
- [SDL2](https://www.libsdl.org/) as base for this project.
- [catch](https://github.com/philsquared/Catch) as the test framework.  (as submodule)

##  project structure

| folder       | Content              |
| ------------ | -------------------- |
| [/src](/src) | library sources  |
| [/inc](/inc) | library includes |
| [/doc](/doc) | doxygen documentation (planned) |
| [/example](/example) | example applications |
| [/test](/test) | library tests |
| [/3rd](/3rd) | third party software        |

## Generate project

```shell
  cmake -H. -BBuild
```

Auto detect everything.

If you like to set a implicit compiler set the variable CXX=${COMPILER}, for example COMPILER could be gcc, clang and so on.

Auto detect in Windows usually generate a Visual Studio project since msbuild require it, but in OSX does not generate and XCode project, since is not required for compiling using XCode clang.

Specify build type debug/release

```shell
  # generate a debug project
  cmake -H. -BBuild -DCMAKE_BUILD_TYPE=Debug
  # generate a release project
  cmake -H. -BBuild -DCMAKE_BUILD_TYPE=Release
```

Specify architecture

```shell
  # 64 bits architecture
  cmake -H. -BBuild -Ax64
  # ARM architecture
  cmake -H. -BBuild -AARM
  # Windows 32 bits architecture
  cmake -H. -BBuild -AxWin32
```

Generate different project types

```shell
  # MinGW makefiles
  cmake -H. -BBuild -G "MinGW Makefiles"
  # XCode project
  cmake -H. -BBuild -G "XCode"
  # Visual Studio 15 2017 solution
  cmake -H. -BBuild -G "Visual Studio 15 2017"
```

## Build

From the Build folder

```shell
  # build the default build type (in multi build types usually debug)
  cmake --build .
  # build a specific build type
  cmake --build . --config Release
```
## Run tests

From the Build folder

```shell
  # run all test using the default build type
  ctest -V
  # run all test in Release build type
  ctest -V -C Release
```

## references

- https://cmake.org/
- https://docs.travis-ci.com/user/languages/cpp/
- https://www.appveyor.com/docs/lang/cpp/
- https://github.com/isocpp/CppCoreGuidelines
- https://github.com/philsquared/Catch
- https://github.com/cognitivewaves/CMake-VisualStudio-Example
- http://derekmolloy.ie/hello-world-introductions-to-cmake/
- https://cmake.org/Wiki/CMake/Testing_With_CTest
- https://www.appveyor.com/docs/lang/cpp/
- https://docs.travis-ci.com/user/languages/cpp/
- https://github.com/philsquared/Catch/blob/master/docs/build-systems.md
- https://stackoverflow.com/questions/14446495/cmake-project-structure-with-unit-tests
- https://juan-medina.com/2017/07/01/moderncppci/