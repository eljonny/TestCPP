[![Build-WithStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform-st.yml)
[![Build-NoStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform-nost.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-multi-platform-nost.yml)
[![Test-WithStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-test-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-testst.yml)
[![Test-NoStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-test-nost.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-test-nost.yml)
[![RPM_DEB-Packaging-WithStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack-st.yml)
[![RPM_DEB-Packaging-NoStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack-nost.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-linux-pack-nost.yml)
[![WIX-Packaging-WithStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-windows-pack-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-windows-pack-st.yml)
[![WIX-Packaging-NoStacktraces](https://github.com/eljonny/TestCPP/actions/workflows/cmake-windows-pack-nost.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-windows-pack-nost.yml)
[![Security](https://github.com/eljonny/TestCPP/actions/workflows/codeql.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/codeql.yml)
[![Shellcheck](https://github.com/eljonny/TestCPP/actions/workflows/shellcheck.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/shellcheck.yml)
[![StaticAnalysis](https://github.com/eljonny/TestCPP/actions/workflows/cmake-static-analysis.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-static-analysis.yml)
[![Coverage](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-cov-st.yml/badge.svg?event=push)](https://github.com/eljonny/TestCPP/actions/workflows/cmake-build-cov-st.yml)
[![codecov](https://codecov.io/gh/eljonny/TestCPP/graph/badge.svg?token=WFG41QY4BB)](https://codecov.io/gh/eljonny/TestCPP)

# What is TestCPP?

This is an implementation of a very simple test framework.
It can be built with no dependencies (other than the C++ standard
 library) and can rely on only C++11 features.
It supports stack traces on test failures as of 0.2.1-beta.3, which
 uses Boost.Stacktrace and requires C++14 (because Boost.Stacktrace
 depends on Boost.Describe, which requires C++14), but this is not
 required to use the framework.

The library is most useful for testing educational projects or small
 personal/internal projects, as many features required for testing
 more complex projects are not present.
For testing more complex projects I would recommend using
 [GoogleTest](https://github.com/google/googletest).
 
The code is ~1.3k lines.
The Release builds are optimized for speed over size, so the
 build could probably be tweaked to get a smaller binary if
 desired.

## Features

See the various Milestones in GitHub to get a feel for where the
 project is headed and what features are planned for the future.

Here are the lists of current and planned features.

### Current Features

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

### Planned Features

There is no plan for advanced features like mocking or death tests.
The goal is to keep the library simple and easy to use, and to delegate
 more complex testing to more advanced libraries like GoogleTest, and
 more advanced features like mocking/faking to external libraries;
 maybe this will change in the future, since this is a project of
 exploration with no real constraints other than to maintain
 simplicity (complex things can be simple).

The following features are currently planned:
- Test Discovery
- Test result output to files or stdout/stderr in a variety of formats
  - JUnit XML
  - xUnit XML
  - CRTF JSON
  - TAP (Become a TAP Producer)
  - Maven Surefire XML
- Additional assertions, mostly convenient extensions of the current
  assertions
  - Numerical Analysis Assertions
    - assertLessThan
    - assertGreaterThan
    - assertLessThanOrEqual
    - assertGreaterThanOrEqual
    - assertIsEven
    - assertIsOdd
    - assertIsPrime
    - assertIsNotPrime
    - assertIsComposite
    - assertIsNotComposite
    - assertIsPerfect
    - assertIsNotPerfect
    - assertIsPowerOf
    - assertIsNotPowerOf
    - assertIsDivisorOf
    - assertIsNotDivisorOf
    - assertIsMultipleOf
    - assertIsNotMultipleOf
    - assertIsFactorOf
    - assertIsNotFactorOf
    - assertIsDivisibleBy
    - assertIsNotDivisibleBy
  - Range Assertions - Dates, Times, Durations, Numbers, strings,
    custom-defined ranges of varying types
    - assertWithinRange
    - assertNotWithinRange
  - Container/string Assertions
    - assertEmpty
    - assertNotEmpty
    - assertContains
    - assertNotContains
    - assertStartsWith
    - assertEndsWith
    - assertSizeIs
  - String-only Assertions
    - assertMatches
    - assertNotMatches
  - Miscellaneous Assertions
    - assertIsOneOf
    - assertIsNotOneOf
    - Will apply lexicographically or numerically depending on the
      type of the arguments, with parameters to control what "close"
      means
      - assertIsCloseTo
      - assertIsNotCloseTo

# Installation

This library can be installed in a few ways, depending on your
 preferences and the tools you use.

## Acquiring the Library

You can get the library in a few ways.

### vcpkg

*Will be available for 1.5 release*

You will be able to include TestCPP in your `vcpkg` project by running
 the following in the root of your project (pending vcpkg PR approval
 that I have in right now https://github.com/microsoft/vcpkg/pull/37471):
```
 vcpkg add port eljonny-testcpp
```

### Conan

*Will be available for 2.0 release*

You will be able to include it in your `conan` project (pending
 approval from the Conan community).
First add it as a dependency to your project in conanfile.txt:
```
[requires]
...
testcpp/2.0
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

### Installing with CMake

You can build the library from source and use the resulting build
 outputs to test your project by using the include and lib path
 options in the build system and compiler toolchain that applies to
 your project.

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

# Usage

This library is designed to be easy to use and simply integrate into
 your projects.

## Getting it into your project's build

You can install the library then use it in your project's CMake build
by adding the following to your CMakeLists.txt file:
```
 find_package(TestCPP REQUIRED)
```

Then add it to your test executable target through
 target_link_libraries like so:
```
 target_link_libraries(
    your_test_ExecutableTarget
    PRIVATE
       cpptesting::TestCPP
 )
```

Otherwise, you should generically do the following things:
- Link the library into your test executables with the linker flag
  that is appropriate for your platform, which is usually
  `-lTestCPP` on GCC/Clang and `TestCPP.lib` on Windows.
- Make sure you have the directory where the TestCPP library is
  installed in your library search path, which is usually controlled
  with -L on *nix and /LIBPATH on Windows.

You may also need to add the include directory to your
 compiler's include path, which is usually controlled with -I on
 *nix and /I on Windows.

## Writing Tests

Include the test framework through TestCPP/TestCPP.h, whether you
 make it a part of your project or install the files into
 the standard install locations (like /usr/local/include/TestCPP
 in linux).
This is an entrypoint header that includes all the necessary
 headers for the framework; you can use the individual headers in
 include/internal if you'd like, as there's nothing to prevent that and
 I don't plan on implementing anything to prevent that.

Now you're ready to write tests.
There are contrived examples provided through demo/include/tests.h
 and programmatic test registration and test running in
 demo/src/main.cpp.
The contrived example tests are defined in demo/src/tests.cpp.

Also, the library is tested with itself, so these can be
 used as examples.
You can find these tests in the test/ directory in the project.

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

When you're ready to build tests with assertions, it's important to
 know that as long as there is an `operator==` implementation for the
 types being compared, the `assertEquals` and `assertNotEquals` will
 work as expected.

Test failures are handled with TestFailedException and an error message
 will be logged describing the failure for each test.

Internal library errors are handled with TestCPPException.

Both of these custom exceptions are based on the C++ STL runtime_error.

### Tutorial: Creating your first test

Creating a test that runs and passes is very simple.
- Create a source file for your tests, e.g. `tests.cpp`.
- Create a header file that declares the tests, e.g. `tests.h`.
- Create a main source file that runs the tests, e.g. `main.cpp`.

This is all it takes to get started with the library, and you control
 every step of this process; there's no _magic_ in any of it, which
 aids in the library's simplicity.
If you keep everything organized, this simplicity can be maintained
 with larger projects as well, but at this point in the library's
 development I don't recommned using it for larger projects.

Additionally, there are other steps you can take to organize your tests
 and test code but are not required to use the library:
- Create a test suite header file that includes the tests header and
  defines the test suite, e.g. `TestSuite.h`.
- Create additional test header files used by the tests to separate
  test function declarations, test suite declarations, and test helper
  functions.
- Create additional test source files that implement the test functions
  declared in the test helper header files.

#### The Main File

I'll use the TestCPP tests for `TestCPP::TestCase` as a real example.
The following is [test/src/TestCPPTestCaseMain.cpp](https://github.com/eljonny/TestCPP/blob/main/test/src/TestCPPTestCaseMain.cpp):
```cpp
#include "TestCPP.h"
#include "TestCase/TestCaseSuite.h"

int main(void)
{
    try {
        TestCPP::Testing::TestCaseSuite::suite.run();
        return TestCPP::Util::unsignedToSigned(
            TestCPP::Testing::TestCaseSuite::suite.
                getLastRunFailCount()
        );
    }
    catch (std::exception& e) {
        std::cerr << "Test suite run failed with an exception: "
                  << e.what() << std::endl;
        return -1;
    }
}
```

In my experience, it's uncommon to need to change the main function
 for the test suite, as usually the changes are to the test suite and
 tests themselves.

As you can see, the library tries to be very unobtrusive and simple,
 and is generally focused on three things:
- Building the test suite programmatically and running the
  `TestCPP::TestCase`s it holds, but this is optional
- Running functions that define the testing in a controlled manner; a
  test, by default using the TestCase definition built into the library
  as-is, is just a function reference wrapped in a lambda
- Providing clog, stdout, and stderr output capturing for the test
  cases, which is useful for testing function logging and output, but
  this is optional and is disabled by default.

Here is what each section of this translation unit is doing:
- `#include "TestCPP.h"`: Includes the main TestCPP header that
  includes all the necessary headers for the framework.
  In this case, the only thing that is necessary is using the
  `TestCPP::Util` namespace.
- `#include "TestCase/TestCaseSuite.h"`: Includes the TestCaseSuite
  header that defines the test suite for the tests that run against
  `TestCPP::TestCase`.
  This is where the tests are declared and registered with the
  framework.
- `int main(void)`: Standard C/C++ program entry point that doesn't
  require or use program arguments from the outside.
  You can implement this differently if you want to pass arguments
  from the outside to tests, of course. It is just not necessary in
  this case.
- `try {} catch (std::exception& e) {}`: The framework uses exceptions
  to handle test failures and errors, so the main function
  is wrapped in a try-catch block to catch any exceptions that are
  thrown during the test run to indicate those failures/errors.
- `TestCPP::Testing::TestCaseSuite::suite.run();`: Runs the test suite
- `return TestCPP::Util::unsignedToSigned(...);`:
  The result is an `unsigned int`, which needs to be converted to a
  signed `int` for the return value of `main` to be compliant with what
  the OS expects.
- `TestCPP::Testing::TestCaseSuite::suite.getLastRunFailCount()`
  Returns the number of test failures that occurred during the test run
  as the exit code of the program.
  This is useful for CI/CD pipelines to determine if the tests passed
  or failed, how many, and can be used for thresholding or general
  information.
- The contents of the catch block logs the exception to help the
  developer figure out why the test failed, or if there is another bug/
  issue that needs to be looked at and fixed.

#### The Test Suite Header (Optional, but recommended for organization)

The test suite header file is where the test suite is defined and
 the tests are registered with the framework.

Looking at the `TestCPP::TestCase` suite header file,
 [test/include/TestCase/TestCaseSuite.h](https://github.com/eljonny/TestCPP/blob/main/test/include/TestCase/TestCaseSuite.h), we see the following (some
 tests omitted for brevity):
```cpp
#ifndef TESTCPP_TESTCASE_TEST_SUITE_
#define TESTCPP_TESTCASE_TEST_SUITE_

#include "TestCaseTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestCaseSuite {
            TestSuite suite(
                "TestCPP TestCase Tests",

                make_tuple(
                    "Case construction Test",
                    function<void()>(TestCaseTests::TestConstructCase)
                ),
                make_tuple(
                    "Case assignment Test",
                    function<void()>(TestCaseTests::TestAssignTestCase)
                ),
                ...
                make_tuple(
                    "Case runner Test",
                    function<void()>(TestCaseTests::TestTestCaseGo)
                ),
                ...
                make_tuple(
                    "Case setNotifyPassed Test",
                    function<void()>(
                        TestCaseTests::TestTestCaseSetNotifyPassed
                    )
                ),
                make_tuple(
                    "Case checkStdout Test",
                    function<void()>(
                        TestCaseTests::TestTestCaseCheckStdout
                    )
                ),
                ...
            );
        }
    }
}

#endif
```

In a lot of ways, this references the standard structure of a C++
 header file, with the following sections:
- Header Guard: Prevents multiple inclusions of the header file
  in the same translation unit
- `#include "TestCaseTests.h"`: Includes the header file that
  declares the test functions that are defined in the corresponding
  source file
- Namespace Declaration: Declares the namespace for the test suite
  to avoid name collisions and to organize the code logically
- Here's where it differs from a standard C++ header file, where we
  have a definition of the suite object, which is a `TestCPP::TestSuite`.

  As you can see, we have the following:
  - A string description of the test suite
  - A list of test cases, which are defined as `std::tuple`s that
    contain the name of the test case and a function reference to the
    test function wrapped in a `std::function` that implements the test
    logic.

With this, all the `TestCPP::TestCase` tests are registered with the
 `TestCPP::TestSuite` object, organized, and ready to run.

#### The Test Case Header

The test case header file is where the test case functions are
 declared.

Let's take a look at the `TestCPP::TestCase` tests header file,
 [test/include/TestCase/TestCaseTests.h](https://github.com/eljonny/TestCPP/blob/main/test/include/TestCase/TestCaseTests.h)
```cpp
#ifndef TESTCPP_TESTCASE_TESTS_
#define TESTCPP_TESTCASE_TESTS_

namespace TestCPP {
    namespace Testing {
        namespace TestCaseTests {
            void TestConstructCase ();
            void TestAssignTestCase ();
            void TestMoveAssignTestCase ();
            void TestTestCaseGo ();
            void TestTestCaseGoThrowStr ();
            void TestTestCaseGoThrowChr ();
            void TestTestCaseGoThrowInt ();
            void TestTestCaseSetNotifyPassed ();
            void TestTestCaseCheckStdout ();
            void TestTestCaseCheckStderr ();
        }
    }
}

#endif
```

We have the same structure as the other include for the include guard
 and the namespace declaration.

Then a simple list of function declarations, nothing special here.
So with this we have a list of test functions to implement in the
 corresponding source file!
Sweet. Now we get to the fun part, implementing the tests.

#### The Test Case Source File

The test case source file is where the test cases are defined.
Let's take a look at a portion of the `TestCPP::TestCase` tests source
 file, [test/src/TestCase/TestCaseTests.cpp](https://github.com/eljonny/TestCPP/blob/main/test/src/TestCase/TestCaseTests.cpp):
```cpp
#include "TestCPP.h"
#include "TestCase/TestCaseTestChunks.h"

using TestCPP::Util::debugLog;

using std::cerr;
using std::cout;
using std::endl;

using TCPPStr = TestCPP::TestCPPCommon::Strings;

namespace TestCPP {
    namespace Testing {
        namespace TestCaseTests {
            void TestConstructCase () {
                debugLog("Construct basic");
                auto test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase case Test - bare minimum",
                    function<void()>([](){})
                ));

                debugLog("Construct with nullptr string");
                Assertions::assertThrows(
                    []() {
                        debugLog("Construct with nullptr string", true);
                        debugLog(" - assertThrows lambda");

                        auto test = unique_ptr<TestCase>(new TestCase(
                            nullptr,
                            function<void()>([](){})
                        ));
                    },
                    "Should have thrown on nullptr string!"
                );

                debugLog("Done with nullptr string construction test");


                parameterVariationTestChunks();
            }

            ...

            void TestTestCaseGo () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "SUB-TEST TestCaseGo case Test",
                    function<void()>([](){}),
                    true
                ));

                Assertions::assertTrue(
                    test->go(),
                    "Should have succeeded basic no-op test!"
                );
            }

            ...

            void TestTestCaseGoThrowChr () {
                constexpr const char * throwChr =
                    "Test throw const char *!";

                auto test = unique_ptr<TestCase>(new TestCase(
                    "SUB-TEST TestCaseGo case Test - throws chr",
                    function<void()>([&throwChr](){
                        throw throwChr;
                    }),
                    true, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                Assertions::assertFalse(
                    test->go(),
                    "Should have succeeded chr throws test!"
                );

                string tcLog(throwChr);

                Assertions::assertTrue(
                    test->checkLog(tcLog),
                    "Something is off, expected output does not exist!"
                );
            }

            ...

            void TestTestCaseSetNotifyPassed () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "TestCaseSetNotifyPassed case Test",
                    function<void()>([](){}),
                    false, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                Assertions::assertTrue(
                    test->go(),
                    "TestSetNotifyPassed go() 1"
                );

                stringstream tcLog;
                tcLog << "Test ";
                tcLog << "TestCaseSetNotifyPassed case Test passed! (";

                Assertions::assertTrue(
                    !test->checkLog(tcLog.str()),
                    "TestSetNotifyPassed checkLog() 1"
                );
                Assertions::assertTrue(
                    !test->checkLog(string("s)")),
                    "TestSetNotifyPassed checkLog() 2"
                );

                test->setNotifyPassed(true);
                Assertions::assertTrue(
                    test->go(),
                    "TestSetNotifyPassed go() 2"
                );

                Assertions::assertTrue(
                    test->checkLog(tcLog.str()),
                    "TestSetNotifyPassed checkLog() 3"
                );
                Assertions::assertTrue(
                    test->checkLog(string("s)")),
                    "TestSetNotifyPassed checkLog() 4"
                );

                test->clearLogCapture();

                test->setNotifyPassed(false);
                Assertions::assertTrue(
                    test->go(),
                    "TestSetNotifyPassed go() 3"
                );

                Assertions::assertTrue(
                    !test->checkLog(tcLog.str()),
                    "TestSetNotifyPassed checkLog() 5"
                );
                Assertions::assertTrue(
                    !test->checkLog(string("s)")),
                    "TestSetNotifyPassed checkLog() 6"
                );
            }

            ...

            void TestTestCaseCheckStderr() {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "TestCaseCheckStderr case Test",
                    function<void()>([]() {
                        cerr << "Test output to stderr!" << endl;
                    }),
                    false, false, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                Assertions::assertTrue(
                    test->go(),
                    "TestCheckStderr go() 1"
                );

                Assertions::assertTrue(
                    test->checkStderr("Test output to stderr!\n"),
                    "TestCheckStderr checkStderr() 1"
                );
            }
        }
    }
}
```

Some of the less-interesting test cases have been removed for brevity.
We have a number of things going on in this file; here are the
 components:
- This is where we include `TestCPP.h` for using the bulk of the
  library:
  - `TestCPP::TestCase`, because that's what we're testing
  - and `TestCPP::Assertions` so we have the Assertions library
  - `TCPPString` for library string utility functions
  - `TestCPP::Util::debugLog` for debug logging, behind the DEBUG flag
- We include the extra test file `TestCaseTestChunks.h` so we have the
  the implementation of helper functions that apply assertions to
  different argument sets
- Object lifetimes are per-test-controlled by `std::unique_ptr`

These tests also demonstrate the stream capturing ability of the
 library that can be used to analyze function output to clog, stdout,
 and stderr.

These are not necessarily as nice looking as [BDD tests](https://en.wikipedia.org/wiki/Behavior-driven_development#Overview) but are
 effective.
BDD may be something to support in the future.

#### Additional Test Files - Test helpers, data loading, etc (Optional)

You can create additional headers and sources to hold test helpers,
 data loading functions, and other utility functions that are used by
 or are part of the tests.

For `TestCPP::TestCase`, `TestCaseTestChunks.h`/`.cpp` encapsulates
 logic for testing permutations of arguments, and is an example of this
 conceptual component.

#### Wrap-up

Everything is really just a few regular C++ files, but the structure I
 outlined here emerged while I was writing tests for the library, so I
 figured it was worth writing down for people new to testing in C++ or
 straight-up new to C++, and to show the structure and content of tests
 when testing with TestCPP.

# Building

The project can be built in a few ways.
Whether you prefer an IDE or a terminal, you're covered here.

You will need either a Terminal (PowerShell, Cmd, lxterm, gnome-shell,
 etc.), Visual Studio 2022, or CodeLite, and the necessary underlying
 compiler toolchain(s), that minimally offer support for C++11,
 including: MSVC++, CMake >= 3.16 (or 3.25 if using CMake Presets),
 clang/clang-tidy, and GCC (also, gcov required for code coverage).

If you will be building it with the optional Boost.Stacktrace
 dependency for great backtrace-generation support on test errors and
 test failures, you will need a compiler toolchain, that minimally
 supports C++14, of the same above varieties.

I have not tested the build on compiler toolchains other than those
 listed, but if you do and you run into issues that seem to be with the
 build and/or the library and not the other compiler toolchain, please
 drop an issue on the repo to let me know so I can take a look and
 possibly remedy the issue.

## Building in CodeLite

I originally developed this project in the [CodeLite IDE](https://codelite.org/), for which
 there is a workspace and project in this repository.
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
  includes stack trace functionality via Boost.Stacktrace, which
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
 support via Boost.Stacktrace, and finally Debug and Release).

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
   (CMakeLists.txt). All other components are in cmake/.
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
- Dependency Handling:
  Handling dependencies for the library, including Boost.Stacktrace,
  that are managed through CMake Git submodules that are included
   in the project via add_subdirectory (SubmodulesInit.cmake).
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
    If set to 1, enables compilation with Boost.Stacktrace, which
     adds dependencies on that library and also the following:
     - Boost.Assert
     - Boost.Config
     - Boost.ContainerHash
     - Boost.Core
     - Boost.Describe
     - Boost.mp11
     - Boost.Predef
     - Boost.StaticAssert
     - Boost.ThrowException
     - Boost.Winapi

     Note that none of these Boost.Stacktrace dependencies require
      binaries, they are all header-only, so they are not required in
      downstream builds.

    Boost.Stacktrace, when used with a platform implementation, is
     built in binary mode so that it can properly link with the
     required platform libraries to provide backtrace information.

    Only the most basic implementation is header-only, and that is
     not used in this project.

    This also adds dependencies on platform-specific libraries at
     link-time for address resolution in the stacktraces:
    - Windows
      - WinDbg
      - ole32
      - dbgeng
    - Non-Windows
      - libdl for boost_stacktrace_basic
      - And optionally, depending on what is available, in addition to
        libdl (these depend on libdl):
        - libbacktrace
        - addr2line
        - If nothing is available, only libdl will be used and
          backtrace information will be limited.

There are a number of CMake modules in cmake/ subdirectories, including
 the following:
- Build definitions (cmake/build/):
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
- Linking definitions (cmake/link/):
  - Boost.Stacktrace.cmake
    Defines linking for the Boost.Stacktrace library, which is used
    for stack traces for test failures when TESTCPP_STACKTRACE_ENABLED
    is set to 1 (or true) into the primary library target.
    This builds a list of installation targets for Boost.Stacktrace
    that are required for the library to work properly when
    Boost.Stacktrace is enabled, used in Installing.cmake when the
    aforementioned cache variable is set.
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
- Toolchain files (cmake/toolchains/):
  - Windows
    - Windows.Clang.toolchain.cmake
      Toolchain file for Visual Studio-installed Clang on Windows.
    - Windows.MSVC.toolchain.cmake
      Toolchain file for MSVC on Windows.
    - Windows.Kits.cmake
      Toolchain file for Windows SDKs.
    - VSWhere.cmake
      Toolchain file for finding Visual Studio installations.

### Known issues/limitations

The build does not yet support RelWithDebugInfo, which I am planning to
 add; see [this issue](https://github.com/eljonny/TestCPP/issues/121).

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
- For testing: `-DTESTCPP_TEST_ENABLED=1`
- For code coverage: `-DTESTCPP_COVERAGE_ENABLED=1`

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
- `-DTESTCPP_TEST_ENABLED=1`

The Release configuration does not support code coverage because of the
 compiler optimizations used.

Both Release and Debug configurations support building the demo app,
 which you can enable by adding the following flag to `cmake`:
- `-DTESTCPP_DEMO_ENABLED=1`

Both Release and Debug configurations support building with stack trace
 functionality with the following flag:
- `-DTESTCPP_STACKTRACE_ENABLED`

## Static Analysis of TestCPP

You can run cppcheck, infer, and clang-tidy on the generated
 compile_commands.json.

Another tool that is helpful to run is flawfinder.

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

For infer, you can run the following command after configuring the
 build:
```
infer run --compilation-database path/to/compile_commands.json
```

For flawfinder, you can run the following command to analyze src and
 then include and generate HTML reports about the results in the:
```
flawfinder --minlevel=0 --html --context --columns src > out/report/flawfinder/src-flaws.html
flawfinder --minlevel=0 --html --context --columns include > out/report/flawfinder/i-flaws.html
```

For a concise report on the command line, you can run the following
 commands:
```
flawfinder --minlevel=0 --dataonly --quiet --columns src
flawfinder --minlevel=0 --dataonly --quiet --columns include
```

I would also recommend using the following flawfinder arguments:
- --error-level=0
  - Sets the error level to 0, which is the lowest level of error
    reporting; this is essentially all-warnings-as-errors.

## Testing and Code Coverage

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

## Packaging

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

Please submit an issue on the repo if there are problems building,
 testing, or using the framework.

I would love to help with any issues you may have, and I will try to
 respond as quickly as I can.

# Development

I am occasionally developing this library/framework, if anyone would
 like to contribute please do so by submitting pull requests on the
 GitHub repository.

You must agree to the [WAIVER](https://github.com/eljonny/TestCPP/blob/main/WAIVER) in order to
 contribute, as the code is Public Domain [as noted by the LICENSE](https://github.com/eljonny/TestCPP/blob/main/LICENSE),
 which means the code you contribute is Public Domain as the existing
 code is; you will still be attributed in the GitHub repository.

If you create a pull request and ask me to merge it, you are agreeing
 to the terms of the aforementioned WAIVER and LICENSE.

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
- cmake-static-analysis.yml
  - Runs clang-tidy and cppcheck on the library code using
    JacobDomagala/StaticAnalysis@master
- codeql.yml
  - Runs the CodeQL static analysis tool on the library code.
- shellcheck.yml
  - Runs shellcheck on the shell scripts in the project to ensure they
    are valid and follow best practices.
