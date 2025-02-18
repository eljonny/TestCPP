[![Build-WithStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform-st.yml)
[![Build-NoStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform-nost.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform-nost.yml)
[![Test-WithStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-test-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-testst.yml)
[![Test-NoStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-test-nost.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-test-nost.yml)
[![RPM_DEB-Packaging-WithStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack-st.yml)
[![RPM_DEB-Packaging-NoStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack-nost.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack-nost.yml)
[![WIX-Packaging-WithStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-windows-pack-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-windows-pack-st.yml)
[![WIX-Packaging-NoStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-windows-pack-nost.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-windows-pack-nost.yml)
[![Coverage](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-cov-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-cov-st.yml)
[![Security](https://github.com/eljonny/TestCPP/actions/workflows/codeql.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/codeql.yml)
[![StaticAnalysis](https://github.com/eljonny/TestCPP/actions/workflows/cmake-static-analysis.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-static-analysis.yml)
[![codecov](https://codecov.io/gh/eljonny/TestCPP/graph/badge.svg?token=WFG41QY4BB)](https://codecov.io/gh/eljonny/TestCPP)

# Introduction

This is an implementation of a very simple test framework.
It can be built with no dependencies (other than the C++ standard
 library) and can rely on only C++11 features.
It supports stack traces on test failures as of 0.2.1-beta.3, which
 uses Boost.StackTrace, but this is not required to use the framework.

The library is most useful for educational projects or small
 personal/internal projects, as many features required for
 testing more complex projects are not present.
For testing more complex projects I would recommend using
 [GoogleTest](https://github.com/google/googletest).
 
The code is ~2k lines.
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
   - assertThrows
   - assertNoThrows
 - fail function, for marking incomplete or skeleton tests,
   or failing in certain cases in a managed way that reduces
   boilerplate.

# Getting Started

## Acquiring the Library

### Including after manual installation

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

### vcpkg

*In process, not working yet*

As of 0.1.0-beta.1, you might soon be able to also include it
 in your `vcpkg` project by running the following in the root of
 your project (pending vcpkg PR approval that I have in right
 now https://github.com/microsoft/vcpkg/pull/37471):
```
 vcpkg add port testcpp
```

### Conan

*In process, not working yet*

As of 0.1.1-beta.2, you might soon be able to also include it
 in your `conan` project (pending approval from the Conan
 community).
First add it as a dependency to your project in conanfile.txt:
```
[requires]
...
testcpp/0.1.1-beta.2
```

Then installing TestCPP into your project by running the
 following in the root of your project (pending Conan Center
 PR approval):
```
 conan install . --output-folder=build --build=missing
```

### GitHub Releases on the TestCPP repo

You can get binary packages from the Releases page on the GitHub
 repo, or get them directly from the latest successful build on
 the Actions page from the multi-platform or linux-package
 workflows on the repo.
Currently binaries are generated by the workflows for 64-bit
 Linux and Windows, and the 32-bit packages are generated
 elsewhere (my local dev machine currently).

## Writing Tests

Include the test framework through TestCPP/TestCPP.h, whether you
 make it a part of your project or install the files into
 the standard install locations (like /usr/local/include/TestCPP
 in linux).
Link in the test library through a linker flag if you
 installed it, most commonly `-lTestCPP`.

Now you're ready to write tests.
There are contrived examples provided through demo/include/tests.h
 and programmatic test registration and test running in
 demo/src/main.cpp.
The contrived example tests are defined in demo/src/tests.cpp.
Also, the library is tested with itself, so these can also be
 used as examples.

The Test Suite creation API is used to collect and run tests
 as in the example files and the tests for the library itself.
Test Cases are defined as STL tuples where the first element is
 the test name and the second element is the function that
 contains the test code to execute.
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

Test failures are handled with TestFailedException and an error
 message will be logged describing the failure for each test.
Internal library errors are handled with TestCPPException.
Both of these custom exceptions are based on the STL runtime_error.

# Building

The project can be built in a couple ways.
Whether you prefer an IDE or a terminal, you're covered here.

## Building in CodeLite

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
 - Click cmake (or for Release builds where you actually want to
   deploy the library, cmake-rls or cmake-nost-rls)

In the Custom Targets... context menu option there are also, depending
 on the build configuration chose, ctest, cpack, cppcheck, clean,
 clang-tidy, cmake-nost-rls, and cmake-rls targets, which will,
 respectively:
 - Run the test suite for the library and, if the Debug configuration
   is selected, generate code coverage reports for the library code.
 - Create binary and/or source packages (depending on the build
   configuration selected), and if you're on a Linux distro that
   supports building RPM and/or DEB packages, will build those too.
 - Runs CMake without actually running the build so the build system
   is generated with compile_commands.json, then runs cppcheck against
   what is defined in compile_commands.json. In this case, this is
   only the core library header and source files.
 - Runs the CMake clean command and completely removes the build
   directory, based on the selected configuration.
 - Runs the build with the TESTCPP_ANALYSIS_ENABLED build variable
   set, which enables clang-tidy for each compilation step, as in
   it will run clang-tidy on each file that is compiled immediately
   after successful compilation.
 - Configures the build with the minimal amount of code to build the
   library, such that the result is suitable for distribution.
   In this way, the build omits the demo, lib tests, and dependencies
   to provide a pure C++11 library.
 - Configures the build in the same way as cmake-nost-rls but
   includes stack trace functionality via Boost.StackTrace, which
   causes the library to have link-time dependencies as explained in
   other elements of this README.

## Building in Visual Studio

I have been able to successfully configure and build the project in
 [Visual Studio 2022 Community](https://visualstudio.microsoft.com/vs/community/)
 using the built-in CMake project integration, so this does work if you
 would like to proceed this way.

There are a number of CMake Presets defined in CMakePresets.json that
 align with different build configurations and analysis profiles,
 including all build feature variations (with/without the Demo project,
 with/without the tests, and subsequently with/without stacktrace
 support via Boost.StackTrace).

To get started, open the root project folder in Visual Studio 2022 and
 select the desired CMake Preset from the Build Configurations dropdown
 which will be populated with all applicable buildPresets once the
 project has fully loaded. Visual Studio automatically detects the
 presence of the CMakePresets.json and CMakeLists.txt files and will
 configure the project with the lexicographically-first build preset.
Subsequently, you can build the project from the Build menu or by
 pressing F7 after successful configuration.

## CMake build structure and variables

The CMake build is split into components that get included into the
 main build file to make modifying each piece more logical and
 manageable.

The top-level components are as follows:
- CMake Build File:
  The main build file that includes all the other components
   (CMakeLists.txt).
- Code Analysis:
  Configuring code analysis tools (Analysis.cmake).
  Currently, this includes clang-tidy in the build process.
  - CPPCheck is also included in the build process, but it is
    not included in the Analysis.cmake file because it is
    run as part of the static analysis GitHub Action (see
    .github/workflows/cmake-static-analysis.yml).
- Build Type Handling:
  Handling the build type which sets compile options for the platform
   on which the build is being run based on the build type (Debug,
   Release, I still need to work on getting RelWithDebugInfo
   configured properly) (BuildTypeHandling.cmake).
- Target Includes:
  Which includes should be applied to which targets (Includes.cmake).
- Installing:
  Configuring installation of the library (Installing.cmake).
- Target Link Libraries:
  Which libraries need to be linked in which build targets, based on
   the result of VarChecks in terms of code coverage (Linking.cmake).
- Packaging:
  Configuring library packaging parameters, enable CPack
   (Packing.cmake).
- Build Targets Configuration:
  Setting up the build targets (Targets.cmake).
  Lists each translation unit that applies to each target.
- Testing:
  Testing configuration, based on the result of VarChecks
   (Testing.cmake).
- Variable Checks:
  Checking the variables to enable or disable certain sections of the
   build (VarChecks.cmake).
  Variables that are checked:
  - TESTCPP_COVERAGE_ENABLED
    If set to 1, enables code coverage with gcov if testing is also
     enabled. If undefined or set to 0, coverage will be disabled
     even if testing is enabled.
  - TESTCPP_DEMO_ENABLED
    If set to 1, enables the demo target, which builds a small
     executable that runs some contrived tests to verify compilation
     and runtime. If undefined or set to 0, the demo target will not
     be built. The name of the demo target is ${PROJECT_NAME}_run.
  - TESTCPP_TEST_ENABLED
    If set to 1, CTest is included and the test targets are enabled.
    If undefined or set to 0, testing for the library will be
     disabled and the tests will not be built.
  - TESTCPP_ANALYSIS_ENABLED
    If set to 1, enables running clang-tidy, which runs clang-tidy
     on each translation unit that is compiled based on the config-
     uration in the clang-tidy dot file (.clang-tidy in the project
     root).
    If undefined or set to 0, clang-tidy will not be run.
  - TESTCPP_STACKTRACE_ENABLED
    If set to 1, enables compilation with Boost.StackTrace, which
     adds dependencies on that library (header-only, included in
     the project in the 3rdparty directory) and also the following:
     - Boost.Config
     - Boost.ContainerHash
     - Boost.Core
     - Boost.Functional
     - Boost.Predef
     - Boost.Utility
     - Boost.Winapi on Windows
    Note that none of these require binaries, they are all header-
     only, so they are not required in downstream builds.
    This also adds dependencies on platform-specific libraries at
     link-time for address resolution in the stacktraces:
     - Windows
       - ole32
       - dbgeng
     - Non-Windows
       - libdl

There are a number of CMake modules in the cmake directory, including
 the following:
- Build definitions:
  - CompileDefs.cmake
    Defines compile definitions for all configurations of the project.
  - DebugCompileDefs.cmake
    Defines compile definitions specific to the Debug configuration of
    the project.
  - GCCClangDebug.cmake
    Defines compiler flags specific to the Debug configuration of the
    project when building with GCC or Clang.
  - GCCClangRelease.cmake
    Defines compiler flags specific to the Release configuration of the
    project when building with GCC or Clang.
  - GCCCoverage.cmake
    Defines compiler flags specific to the Debug configuration of the
    project when building with GCC and generating code coverage data.
  - MSVCDebug.cmake
    Defines compiler flags specific to the Debug configuration of the
    project when building with MSVC.
  - MSVCRelease.cmake
    Defines compiler flags specific to the Release configuration of the
    project when building with MSVC.
- Linking definitions:
  - Demo.cmake
    Defines the linking for the demo targets.
  - TestCPPWithCoverage.cmake
    Defines the linking for the TestCPP library when code coverage is
    enabled.
  - Tests.cmake
    Defines the linking for the test targets.
  - TestsWithCoverage.cmake
    Defines the linking for the test targets when code coverage is
    enabled.
- Toolchain files:
  - Windows
    - Windows.Clang.toolchain.cmake
      Toolchain file for Visual Studio-installed Clang on Windows.
    - Windows.MSVC.toolchain.cmake
      Toolchain file for MSVC on Windows.
    - Windows.Kits.cmake
      Toolchain file for Windows SDKs.
    - VSWhere.cmake
      Toolchain file for finding Visual Studio installations.

## Building outside the IDE

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
 those in the build, add one or both of the following flags to `cmake`:
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
 test target in the build, add the following flag to `cmake`:
 - `-DCMAKE_TEST_ENABLED=1`

The Release configuration does not support code coverage because of the
 compiler optimizations used.

Both Release and Debug configurations support building the demo app,
 which you can enable by adding the following flag to `cmake`:
 - `-DCMAKE_DEMO_ENABLED=1`

Both Release and Debug configurations support building with stack trace
 functionality with the folloeing flag:
 - `-DTESTCPP_STACKTRACE_ENABLED`

# Static Analysis of TestCPP

You can run cppcheck and clang-tidy on the generated
 compile_commands.json.

For clang-tidy, you can also use the CMake flag to have CMake run
 clang-tidy during the build.

clang-tidy uses the .clang-tidy configuration file so you don't need to
 specify any options unless you want to run it with different checks/
 behavior from what I usually run for this project.

My suggested options for cppcheck are:
- --project=compile_commands.json
  - Uses the generated CMake output to define a check project; you need
    to adjust the argument to this parameter to match the path to the
    compile_commands.json file that was generated.
- --enable=all
  - Enables all CPPCheck checks applicable to the project.
- --suppress=missingIncludeSystem
  - Then suppress missing system includes, there are no <>-enclosed
    includes that need to be checked for this project.
- --suppress=unusedFunction
  - Then suppress checking for unused functions. Most API functions
    are not used within the library itself, and CPPCheck will generate
    numerous errors saying the functions are unused.
- --suppress=checkersReport
  - Then suppress the checkers report, which is a summary of the checks
    that were run and how many were skipped.
- --suppress='\*:3rdparty/\*'
  - Ignore all checks in the 3rdparty directory, which is where the
    Boost headers are stored for this project.
- --inconclusive
  - Allow inconclusive results to be reported, which can identify more
    potential issues in the code.
- --force
  - Forces checking of all preprocessor configurations
- --check-level=exhaustive
  - Analysis covers all possible paths and more expensive checks
- --inline-suppr
  - Obeys inline suppression of errors in the code, which are used in
    this project to suppress specific instances of errors/warnings that
    are not applicable or are false positives.
- --quiet
  - Suppresses all output except for errors and warnings
- --std=c++11
  - Specifies the C++ standard to use for checking the code

I would recommend against using the -j parameter with cppcheck because
 it disables certain checks that are used in the project.

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

Building the basic binary packages on Windows will generate an NSIS
 executable installer while building on Linux will generate multiple
 tarballs and an executable sh installer file.

To create source packages, run the following command from the
 CMake build directory (either build-debug or build-release):
 - `cpack --config CPackSourceConfig.cmake`

If you are building on Linux, the build supports generating
 deb and rpm packages. To build those, run the following
 respective commands from the CMake build directory (either
 build-debug or build-release):
 - `cpack -G DEB`
 - `cpack -G RPM`

If you are building on Windows, the build supports generating MSI
 packages. To build those (make sure you have the WiX toolkit installed
 first), run the following command from the CMake build directory:
 - `cpack -G WIX`

Both Windows and Linux builds also support generating a zip
 package by running the following command from the CMake
 build directory (either build-debug or build-release):
 - `cpack -G ZIP`

# Issues

I'm more than willing to work on issues as they come up.
Please submit an issue on the repo if there are problems
 building, testing, or using the framework.

# Development

I am semi-actively developing this library/framework, if
 anyone would like to contribute please do so by
 submitting pull requests on GitHub.

## GitHub Actions

The project is configured to use GitHub Actions for CI/CD.
There are several workflows that are used to build, test, and package
 the library.
The workflows are as follows:
- cmake-multi-platform-st.yml
  - Builds the library on Windows and Linux with stack traces enabled.
- cmake-multi-platform-nost.yml
  - Builds the library on Windows and Linux with stack traces disabled.
- cmake-build-test-st.yml
  - Builds and tests the library on Windows and Linux with stack traces
    enabled.
- cmake-build-test-nost.yml
  - Builds and tests the library on Windows and Linux with stack traces
    disabled.
- cmake-linux-pack-st.yml
  - Builds and packages the library on Linux with stack traces enabled.
- cmake-linux-pack-nost.yml
  - Builds and packages the library on Linux with stack traces
    disabled.
- cmake-windows-pack-st.yml
  - Builds and packages the library on Windows with stack traces
    enabled.
- cmake-windows-pack-nost.yml
  - Builds and packages the library on Windows with stack traces
    disabled.
- cmake-build-cov-st.yml
  - Builds and tests the library on Linux with stack traces enabled and
    generates code coverage reports that are then pushed to CodeCov for
    helpful visualizations and reporting.
- codeql.yml
  - Runs the CodeQL static analysis tool on the library code.
- cmake-static-analysis.yml
  - Runs clang-tidy and cppcheck on the library code using
    JacobDomagala/StaticAnalysis@master
