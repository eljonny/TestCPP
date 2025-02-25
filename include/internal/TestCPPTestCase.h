/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
 */

//Original author: Jonathan Hyry CSU-Fullerton SECS 6896-02 Fall 2014/15

#ifndef TESTCPP_TESTCASE_TYPE_
#define TESTCPP_TESTCASE_TYPE_

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <tuple>
#include <vector>

#include "TestCPPUtil.h"

using std::atomic_int;
using std::chrono::nanoseconds;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::enable_if;
using std::endl;
using std::forward;
using std::function;
using std::move;
using std::ostream;
using std::runtime_error;
using std::string;
using std::streambuf;
using std::stringstream;
using std::unique_ptr;
using std::vector;

/**
 * The base namespace for all TestCPP library code.
 */
namespace TestCPP {

    /**
     * @class TestCase
     * @author Jonathan Hyry
     * @date 03/05/24
     * @file TestCPP.h
     * @brief Provides an interface for implementing tests.
     *
     * TestCase is one of three core types that define the TestCPP API.
     * TestCase provides faculties for defining and controlling tests
     *  and the stdout/stderr/clog environment.
     * TestCase objects are defined by the following elements:
     *  - their name
     *  - the code that will be run that defines what the test does
     *     and how it does it
     *  - whether to log test passage
     *  - output capturing flags
     *  - how captured output is analyzed (exact or contains)
     */
    class TestCase {

    public:
        /**
         * Provides a specification for how to analyze captured stdout,
         *  stderr, and clog data.
         */
        enum TestCaseOutCompareOptions {
            CONTAINS,
            EXACT
        };

        /**
         * @brief Construct a test case with possibility to use all
         *         options.
         *
         * @param testName The name of the test as a TestObjName.
         * @param test The implementation or pointer to the test.
         * @param testPassedMessage Whether to omit a message indicating
         *          test passage.
         * @param captureOut Whether to capture stdout output for
         *          analysis after the test run.
         * @param captureLog Whether to capture clog output for
         *          analysis after the test run.
         * @param captureErr Whether to capture stderr output for
         *          analysis after the test run.
         * @param opt Technique for comparing actual output with
         *          expected output after the test run.
         *
         * Instantiate and define a test case.
         * All parameters are optional other than the test name and the
         *  test function.
         * Optional parameters have the following default values:
         *  - testPassedMessage defaults to true, so by default test
         *      cases will emit a message when the pass.
         *  - captureOut defaults to false, the test case by default
         *      does not capture stdout data.
         *  - captureLog defaults to false, the test case by default
         *      does not capture data streamed to clog.
         *  - captureErr defaults to false, the test case by default
         *      does not capture stderr data.
         *  - opt defaults to CONTAINS, so when output is captured and
         *      checked for something, the default technique is to check
         *      that the output of a given stream contains a given
         *      string.
         */
        TestCase (
            TestObjName&& testName,
            function<void()> test,
            bool testPassedMessage = true,
            bool captureOut = false,
            bool captureLog = false,
            bool captureErr = false,
            TestCaseOutCompareOptions opt = CONTAINS
        );

        /**
         * @brief Construct a TestCase by copying it from another
         *          TestCase.
         * @param o The test case from which to make a copy.
         */
        TestCase (TestCase& o);

        /**
         * @brief Construct a TestCase by moving all data from another
         *          TestCase.
         * @param o Move everything from this TestCase into the new one.
         */
        TestCase (TestCase&& o) noexcept;

        /**
         * @brief Copy a TestCase into another TestCase.
         * @param rhs The test case to copy from.
         * @return A reference to the new TestCase copy.
         */
        TestCase& operator= (TestCase& rhs);
        
        /**
         * @brief Move a TestCase into another TestCase.
         * @param rhs Move everything from this TestCase into the new
         *          one.
         * @return A reference to the TestCase that everything from the
         *          old TestCase was moved into.
         */
        TestCase& operator= (TestCase&& rhs) noexcept;

        /**
         * @brief Destroy a TestCase object.
         */
        ~TestCase ();

        /**
         * @brief Set whether to notify in std::clog when a test passes.
         * @param shouldNotify Will notify on test passed if true.
         */
        void setNotifyPassed (bool shouldNotify);

        /**
         * @brief Set the output comparison mode.
         * @param opt Accepts specified mode from the referenced enum.
         *
         * If this is called with an option specified that is different
         *  from what is set for this test case already, subsequent
         *  calls to any of the output check functions will use the
         *  updated mode that is specified in the call to this function.
         */
        void outCompareOption (TestCaseOutCompareOptions opt);

        /**
         * @brief Clears the captured output from stdout.
         *
         * This can be used for checking sections of output based on
         *  test configuration.
         */
        void clearStdoutCapture ();

        /**
         * @brief Clears the captured output from std::clog.
         *
         * This can be used for checking sections of output based on
         *  test configuration.
         */
        void clearLogCapture ();

        /**
         * @brief Clears the captured output from stderr.
         *
         * This can be used for checking sections of output based on
         *  test configuration.
         */
        void clearStderrCapture ();

        /**
         * @brief Check the argument against what is captured from
         *          stdout using the configured comparison mode.
         * @param against The value to check the captured output against
         * @return True if the argument results in a successful check
         *          using the configured comparison mode.
         */
        bool checkStdout (const string& against);

        /**
         * @brief Check the argument against what is captured from
         *          std::clog using the configured comparison mode.
         * @param against The value to check the captured output against
         * @return True if the argument results in a successful check
         *          using the configured comparison mode.
         */
        bool checkLog (const string& against);

        /**
         * @brief Check the argument against what is captured from
         *          stderr using the configured comparison mode.
         * @param against The value to check the captured output against
         * @return True if the argument results in a successful check
         *          using the configured comparison mode, false
         *          otherwise.
         */
        bool checkStderr (const string& against);

        /**
         * @brief Run the test case.
         * @return True if the test ran successfully, false otherwise.
         */
        bool go ();

        /**
         * @brief Returns the duration of the last run in nanoseconds.
         * @return The duration of the last run of this TestCase in
         *          nanoseconds.
         */
        long long getLastRuntime () const;

    private:
        bool notifyTestPassed = false;
        bool pass = false;
        bool stdoutCaptured = false;
        bool clogCaptured = false;
        bool stderrCaptured = false;
        long long lastRunTime = -1;

        TestObjName testName;
        function<void()> test;

        TestCaseOutCompareOptions option =
            TestCaseOutCompareOptions::CONTAINS;

        /**
         * @brief If instructed, capture stdout while this test is
         *          active.
         */
        void captureStdout ();
        /**
         * @brief If instructed, capture clog while this test is
         *          active.
         */
        void captureClog ();
        /**
         * @brief If instructed, capture stderr while this test is
         *          active.
         */
        void captureStdErr ();
        /**
         * @brief Write a test failure reason to the specified stream.
         * @param out The stream to write the test failure reason to.
         * @param reason The test failure reason to write.
         */
        void logFailure (ostream& out, string& reason);
        /**
         * @brief If a test encounters an error while running, this
         *          function will be called to log the test error.
         * @param failureMessage The error message from the test that
         *          should be logged.
         */
        void logTestFailure (string failureMessage);
        /**
         * @brief Internal test run controller.
         */
        void runTest ();
        /**
         * @brief Handles the internal logic for calls to checkStdout,
         *          checkLog, and checkStderr based on the selected
         *          comparison technique for this test.
         * @param source The actual output
         * @param against The expected output, or a portion of the
         *          expected output.
         * @return True if the argument results in a successful check
         *          using the configured comparison mode, false
         *          otherwise.
         */
        bool checkOutput (const string& source, const string& against);

        static atomic_int stdoutCaptureCasesConstructed;
        static atomic_int logCaptureCasesConstructed;
        static atomic_int stderrCaptureCasesConstructed;
        static atomic_int stdoutCaptureCasesDestroyed;
        static atomic_int logCaptureCasesDestroyed;
        static atomic_int stderrCaptureCasesDestroyed;

        static Util::no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>
            stdoutBuffer;
        static Util::no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>
            clogBuffer;
        static Util::no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>
            stderrBuffer;
        static Util::no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>
            stdoutOriginal;
        static Util::no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>
            clogOriginal;
        static Util::no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>
            stderrOriginal;

        /**
         * @brief Measure the duration of a function when run.
         * @param func Measure the duration of this function when run.
         * @param args A template pack of arguments to apply to the
         *          given function of which to measure the duration.
         * @return The duration of the function run, in nanoseconds.
         */
        template<typename F, typename ...Args>
        static nanoseconds duration (F func, Args&&... args)
        {
            auto start = system_clock::now();
            func(forward<Args>(args)...);
            return duration_cast<nanoseconds>(
                system_clock::now() - start
            );
        }
    };
}

#endif
