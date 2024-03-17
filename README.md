[![Build](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform.yml)
[![Test](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-test.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-test.yml)
[![RPM/DEB Packaging](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack.yml)
[![Coverage](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-cov.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-cov.yml)
[![Security](https://github.com/eljonny/TestCPP/actions/workflows/codeql.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/codeql.yml)
[![codecov](https://codecov.io/gh/eljonny/TestCPP/graph/badge.svg?token=WFG41QY4BB)](https://codecov.io/gh/eljonny/TestCPP)

# Introduction

This is an implementation of a very simple test framework.
It has no dependencies (other than the C++ standard library)
 and relies on C++11 features.

The library is most useful for educational projects or small
 personal/internal projects, as many features required for
 testing more complex projects are not present.
For testing more complex projects I would recommend using
 [GoogleTest](https://github.com/google/googletest).
 
The code is about 380 lines and resulting Debug binary
 packages are about 330kb on Linux, while the Release
 packages are about 280kb; this includes the header, the
 static library, and the CMake targets for including it in
 your CMake build.
The Release builds are optimized for speed over size, so the
 build could probably be tweaked to get a smaller binary if
 desired.

# Features

Features of the test framework are very minimal and include:
 - Test case definition
 - Test suite definition
 - Test elapsed time logging
 - Basic assertions
   - assertEquals
   - assertNotEquals
   - assertNull
   - assertNotNull
   - assertTrue
   - assertFalse
 - fail function, for marking incomplete or skeleton tests

# Getting Started

## Acquiring the Library

As of 0.1.0-beta.1 this library can be included in a CMake build
 using the `find_package` CMake function after installing, like
 so:
```
 find_package(TestCPP CONFIG REQUIRED)
```

Then add it to your test executable target through
 target_link_libraries like so:
```
 target_link_libraries(
    yourTestExecutableTarget
    PRIVATE
       cpptesting::TestCPP
 )
```

As of 0.1.0-beta.1, you can also include it in your `vcpkg` project
 by running the following in the root of your project (pending
 vcpkg PR approval that I have in right now
 https://github.com/microsoft/vcpkg/pull/37471):
```
 vcpkg add port testcpp
```

You can get binary packages from the Releases page on the GitHub
 repo, or get them directly from the latest successful build on
 the Actions page from the multi-platform or linux-package
 workflows on the repo.
Currently binaries are generated for Linux and Windows.

## Writing Tests

Include the test framework through TestCPP/Test.h, whether you
 make it a part of your project or install the files into
 the standard install locations (like /usr/local/include/TestCPP
 in linux).
Link in the test library through a linker flag if you
 installed it, most commonly `-lTestCPP`.

Now you're ready to write tests.
There are contrived examples provided through test.hpp and
 programmatic test registration and test running in main.cpp.

The Test Suite creation API is used to collect and run tests
 as in the example files.
Test Cases are defined as C++ STL tuples where the first
 element is the test name and the second element is the
 function that contains the test code to execute.
The framework can be easily modified to support other test
 definition formats if desired as the constructor is
 vararg templatized, so you would just need to add a new
 implementation of addTest to support the way you would like
 to construct your Test Cases.
The Test Suite creation API is a single constructor function
 that looks like this:
```
    template<typename... TestType>
    TestFramework::TestSuite suite(TestType ...tests)
```

You can also create a TestSuite object through the default
 constructor and add tests programmatically that way if
 desired.

As long as there is an `operator==` implementation for the types
 being compared, the `assertEquals` and `assertNotEquals` will work
 as expected.

Test failures are handled through a range of exceptions and
 an error message will be logged describing the failure for
 each test.

# Building

I developed this project in the [CodeLite IDE](https://codelite.org/),
 for which there is a workspace and project in this repository.
In the project, there are CMake targets defined for Release and Debug
 builds.
It is, as far as I know, strictly compliant with the C++11 standard,
 and should work on any platform where there is a compiler toolchain
 that supports this standard, which at this point is almost anywhere.

To build within the CodeLite IDE:
 - Load the workspace
 - Select your desired build configuration (Debug or Release)
 - Right click on the TestFramework project
 - Move to the Custom Targets... context menu option
 - Click cmake

In the Custom Targets... context menu option there are also ctest
 and cpack targets, which will, respectively:
 - Run the test suite for the library and (if the Debug
   configuration is selected) generate code coverage reports for
   the library code.
 - Create binary and/or source packages (depending on the build
   configuration selected), and if you're on a Linux distro that
   supports building RPM and/or DEB packages, will build those too.

To build outside of the CodeLite IDE, you can run the following
 commands, after cloning the repo, for the debug build:
```
    cd TestCPP
    mkdir build-debug
    cd build-debug
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
    make
```
The Debug configuration supports testing and code coverage. To enable
 those in the build, add one or both of the following flags to the cmake
 command:
 - For testing: `-DCMAKE_TEST_ENABLED=1`
 - For code coverage: `-DCMAKE_COVERAGE_ENABLED=1`

For the release build:
```
    cd TestCPP
    mkdir build-release
    cd build-release
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
    make
```
The Release configuration supports testing. To enable generation of the
 test target in the build, add the following flag to the cmake command:
 - `-DCMAKE_TEST_ENABLED=1`

The Release configuration does not support code coverage because of the
 compiler optimizations used.

# Testing and Code Coverage

The library is tested using itself.

If you would like to test the framework after building it, ensure the
 test flag was passed to CMake when you built it then run the following
 command from the build-debug or build-release directory:
```
ctest --progress --verbose
```

If you would like to generate code coverage reports from the tests,
 ensure that the code coverage flag was passed to CMake when you built
 it and that you built it using GCC and with the Debug configuration
 then run the following commands after running the tests (running the
 tests generates the raw coverage data):
```
mkdir -p coverage && cd coverage
find .. -name '*.gcda' | xargs gcov -abcfmu
find . -type f -not -name 'Test*.gcov' | xargs rm
```
These commands do the following:
 - create and enter a directory for storing the coverage reports
 - collect all the raw coverage data files generated by the
   GCC compiler (gcov does not work with clang as far as I
   understand, and the toolchain is generally not present when
   building with cl on Windows)
 - Pass the list of files to gcov to process the raw data and
   output human-readable code coverage reports
 - Remove all the coverage data for non-project code

The GitHub repo is linked to Codecov which visualizes this data.

# Installing

After building, run the variant of the commands that align with
 your build configuration (starting from the project directory).
For the debug build:
```
    cd build-debug
    sudo cmake --install .
```

For the release build:
```
    cd build-release
    sudo cmake --install .
```

# Packaging

The project is configured to use CPack, if you would like to
 create your own binary and/or source distribution of the
 project.

To create basic binary packages that can be used on the
 target OS and architecture (I believe this is based on what
 type of system you run the build process), run the following
 command from the CMake build directory (either build-debug
 or build-release):
 - `cpack --config CPackConfig.cmake`

To create source packages, run the following command from the
 CMake build directory (either build-debug or build-release):
 - `cpack --config CPackSourceConfig.cmake`

If you are building on Linux, the build supports generating
 deb and rpm packages. To build those, run the following
 respective commands from the CMake build directory (either
 build-debug or build-release):
 - `cpack -G DEB`
 - `cpack -G RPM`

# Issues

I'm more than willing to work on issues as they come up.
Please submit an issue on the repo if there are problems
 building, testing, or using the framework.

# Development

I am semi-actively developing this library/framework, if
 anyone would like to contribute please do so by
 submitting pull requests on GitHub.
