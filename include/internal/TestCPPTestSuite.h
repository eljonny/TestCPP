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

#ifndef TESTCPP_TESTSUITE_TYPE_
#define TESTCPP_TESTSUITE_TYPE_

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <tuple>
#include <vector>

using std::atomic_int;
using std::chrono::nanoseconds;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::enable_if;
using std::endl;
using std::function;
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
     * @class TestSuite
     * @author Jonathan Hyry
     * @date 05/05/24
     * @file TestCPP.h
     * @brief Defines a container for a collection of TestCase objects.
     * 
     * 
     */
    class TestSuite {

    public:
        /**
         * @brief Specialization for constructing a test suite with no
         *          tests.
         */
        template<typename... TestType>
        TestSuite (TestObjName&& newSuiteName,
                   typename enable_if<sizeof...(TestType) == 0>::type)
        {
            commonInit(std::forward<TestObjName>(newSuiteName));
        }

        /**
         * @brief The general case for constructing a test suite with
         *          tests.
         */
        template<typename... TestType>
        TestSuite (TestObjName&& newSuiteName, TestType ...tests)
        {
            commonInit(std::forward<TestObjName>(newSuiteName));
            this->addTests(tests...);
        }

        /**
         * @brief Add a test to this test suite.
         *
         * Appropriate specializations defined in the source file.
         */
        template<typename T>
        void addTest (T&& test);

        /**
         * @brief Specialization to handle when someone tries to call
         *          the template function with no tests.
         *
         * This is a noop.
         */
        template<typename... OtherTests>
        typename enable_if<sizeof...(OtherTests) == 0>::type
        static inline addTests () { }

        /**
         * @brief Add one or more tests at once to the test suite.
         * @param test The first test to add.
         * @param tests The rest of the tests to add.
         */
        template<typename Test, typename... OtherTests>
        void addTests (Test test, OtherTests ...tests) {
            addTest(std::move(test));
            addTests(tests...);
        }

        /**
         * @brief Sets the name of this test suite.
         */
        void setSuiteName (TestObjName&& testSuiteName);

        /**
         * @brief After called, all tests in the suite will emit a
         *          message if they pass.
         */
        void enableTestPassedMessage ();
        
        /**
         * @brief After called, all tests in the suite will not emit a
         *          message if they pass.
         */
        void disableTestPassedMessage ();

        /**
         * @brief Retrieve the total number of tests in the suite that
         *          failed during the last suite run.
         * @return The total number of tests that failed in the last
         *          suite run.
         */
        unsigned getLastRunFailCount ();

        /**
         * @brief Retrieve the total number of tests in the suite that
         *          succeeded (passed) during the last suite run.
         * @return The total number of tests that passed in the last
         *          suite run.
         */
        unsigned getLastRunSuccessCount();

        /**
         * @brief Run all tests in the test suite.
         */
        void run ();

    private:
        unsigned zeroInit = 0;

        bool firstRun;
        bool testSuitePassedMessage;
        bool lastRunSucceeded;
        unsigned lastRunSuccessCount;
        unsigned lastRunFailCount;
        long long totalRuntime;

        TestObjName suiteName;
        vector<TestCase> tests;

        // It's ok that this function is removed, because it's private
        //  and inlined and is not externally visible or used
        //  externally.
        // It's appropriate to suppress this instance of C4514.
#pragma warning(suppress: 4514)
        void commonInit(TestObjName&& newSuiteName) {

            this->firstRun = true;
            this->testSuitePassedMessage = true;
            this->lastRunSucceeded = true;
            this->lastRunFailCount = zeroInit;
            this->lastRunSuccessCount = zeroInit;
            this->totalRuntime = 0;

            this->setSuiteName(std::forward<TestObjName>(newSuiteName));
            this->tests = vector<TestCase>();
        }
    };
}

#endif
