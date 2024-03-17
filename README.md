![Build](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform.yml/badge.svg?event=push)
![Test](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-test.yml/badge.svg?event=push)
![RPM/DEB Packaging](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack.yml/badge.svg?event=push)
![Coverage](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-cov.yml/badge.svg?event=push)
[![codecov](https://codecov.io/gh/eljonny/TestCPP/graph/badge.svg?token=WFG41QY4BB)](https://codecov.io/gh/eljonny/TestCPP)

# Introduction

This is an implementation of a very simple test framework.
It has no dependencies (other than the C++ standard library)
 and relies on C++11 features.

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

To build outside of the CodeLite IDE, you can run the following
 commands, after cloning the repo, for the debug build:
```
    cd TestCPP
    mkdir build-debug
    cd build-debug
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
    make
```

For the release build:
```
    cd TestCPP
    mkdir build-release
    cd build-release
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=1
    make
```

# Installing

After building, run the variant of the commands that aligns with your
 build configuration (starting from the project directory).
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

# Issues

I'm more than willing to work on issues as they come up.
Please submit and issue on the repo if there are problems building
 or using the framework.

# Development

I am semi-actively developing this library/framework, if
 anyone would like to contribute please do so by submitting
 pull requests on GitHub.
