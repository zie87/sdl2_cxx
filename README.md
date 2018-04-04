# sdl2_cxx [![Codacy Badge](https://api.codacy.com/project/badge/Grade/bc2bbf89f51e4844b6531c93e2705220)](https://www.codacy.com/app/zie87/sdl2_cxx?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=zie87/sdl2_cxx&amp;utm_campaign=Badge_Grade)

Header only modern c++ wrapper for sdl2 and extensions

| Build status          | Systems / Compilers         |
| ------------- | ------------------------------------------ |
[![CLang / GCC / XCode Builds](https://travis-ci.org/zie87/sdl2_cxx.svg?branch=master)](https://travis-ci.org/zie87/sdl2_cxx) | Linux (clang5  / gcc7) OSX (XCode 9.3 clang) |
[![Visual Studio Builds](https://ci.appveyor.com/api/projects/status/90ryctsanv84928b/branch/master?svg=true)](https://ci.appveyor.com/project/zie87/sdl2-cxx/branch/master) | Windows (Visual Studio 2017)  |

## libraries used
- [SDL2](https://www.libsdl.org/) as base for this project.
- [catch](https://github.com/philsquared/Catch) as the test framework.  (as
submodule)

##  project structure

| folder       | Content              |
| ------------ | -------------------- |
| [/src](/src) | test and example sources |
| [/inc](/inc) | library includes |
| [/doc](/doc) | doxygen documentation (planned) |
| [/3rd](/3rd) | third party software        |  |

## Generate project

```shell
  cmake -H. -BBuild
```

Auto detect everything.

If you like to set a implicit compiler set the variable CXX=${COMPILER}, for
example COMPILER could be gcc, clang and so on.

Auto detect in Windows usually generate a Visual Studio project since msbuild
require it, but in OSX does not generate and XCode project, since is not
required for compiling using XCode clang.

Specify build type debug/release

```shell
  # generate a debug project
  cmake -H. -BBuild -DCMAKE_BUILD_TYPE=Debug
  # generate a release project
  cmake -H. -BBuild -DCMAKE_BUILD_TYPE=Release
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
