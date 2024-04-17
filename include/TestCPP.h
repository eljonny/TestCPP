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

#ifndef TESTCPP_CLASSES_
#define TESTCPP_CLASSES_

#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <tuple>
#include <vector>

using std::chrono::nanoseconds;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::enable_if;
using std::endl;
using std::forward;
using std::function;
using std::move;
using std::runtime_error;
using std::string;
using std::streambuf;
using std::stringstream;
using std::unique_ptr;
using std::vector;

namespace TestCPP {
    class TestCPPException : public runtime_error {
    public:
        TestCPPException (const char * msg);
        TestCPPException (string&& msg);
    };

    class TestFailedException : public TestCPPException {
    public:
        TestFailedException (const char * msg);
        TestFailedException (string&& msg);
    };

    class TestCaseName {
    public:
        TestCaseName () = default;
        TestCaseName (const char* name);

        const string& getTestName ();

        friend std::ostream& operator<< (
            std::ostream& s,
            TestCaseName& tcName
        )
        {
            s << tcName.getTestName();
            return s;
        }

    private:
        string testCaseName;

    };

    class TestCase {

    public:
        enum TestCaseOutCompareOptions {
            CONTAINS,
            EXACT
        };

        TestCase (
            TestCaseName&& testName,
            function<void()> test,
            bool testPassedMessage = true,
            bool captureOut = false,
            bool captureLog = false,
            bool captureErr = false,
            TestCaseOutCompareOptions opt = CONTAINS
        );

        TestCase (TestCase& o);
        TestCase (TestCase&& o);

        TestCase& operator= (TestCase& rhs);
        TestCase& operator= (TestCase&& rhs);

        ~TestCase ();

        void setNotifyPassed (bool);
        void captureStdout ();
        void captureClog ();
        void captureStdErr ();
        void outCompareOption (TestCaseOutCompareOptions opt);
        void clearStdoutCapture ();
        void clearLogCapture ();
        void clearStderrCapture ();
        bool checkStdout (string against);
        bool checkLog (string against);
        bool checkStderr (string against);
        bool go ();
        long long getLastRuntime ();

    private:
        bool notifyTestPassed;
        bool pass;
        long long lastRunTime;

        TestCaseName testName;
        function<void()> test;

        TestCaseOutCompareOptions option;

        unique_ptr<stringstream> stdoutBuffer = nullptr;
        unique_ptr<stringstream> clogBuffer = nullptr;
        unique_ptr<stringstream> stderrBuffer = nullptr;
        unique_ptr<streambuf> stdoutOriginal = nullptr;
        unique_ptr<streambuf> clogOriginal = nullptr;
        unique_ptr<streambuf> stderrOriginal = nullptr;

        template<typename F, typename ...Args>
        static nanoseconds duration (F func, Args&&... args)
        {
            auto start = system_clock::now();
            func(forward<Args>(args)...);
            return duration_cast<nanoseconds>(
                system_clock::now() - start
            );
        }

        void logTestFailure (string);
        void runTest ();
        bool checkOutput (TestCaseOutCompareOptions opt, string source,
                          string against);
    };

    class TestSuite {

    public:
        template<typename... TestType>
        TestSuite (string suiteName,
                   typename enable_if<sizeof...(TestType) == 0>::type)
        {
            this->testPassedMessage = true;
            this->setSuiteName(suiteName);
            this->tests = vector<TestCase>();
        }

        template<typename... TestType>
        TestSuite (string suiteName, TestType ...tests) {
            this->testPassedMessage = true;
            this->setSuiteName(suiteName);
            this->tests = vector<TestCase>();

            this->addTests(tests...);
        }

        template<typename T>
        void addTest (T&& test) {
            this->tests.emplace_back(
                std::get<0>(test),
                std::get<1>(test),
                this->testPassedMessage
            );
        }

        template<typename... OtherTests>
        typename enable_if<sizeof...(OtherTests) == 0>::type
        inline addTests () { }

        template<typename Test, typename... OtherTests>
        void addTests (Test test, OtherTests ...tests) {
            addTest(move(test));
            addTests(tests...);
        }

        template<typename T, typename... ConstructionArgs>
        static T getTestObject (ConstructionArgs ...args) {
            return T(args...);
        }

        void setSuiteName (string testSuiteName);

        template<typename T1, typename T2>
        static void assertEquals (
                T1 expected, T2 actual,
                string failureMessage = "Arguments are not equivalent!"
            )
        {
            if (expected != actual) {
                stringstream err;

                err << "Equivalence assertion failed!" << endl;
                err << failureMessage << endl;
                err << "Expected: <" << expected << ">" << endl;
                err << "Actual: <" << actual << ">" << endl;

                throw TestFailedException(err.str());
            }
        }

        template<typename T1, typename T2>
        static void assertNotEquals (
                T1 expected, T2 actual,
                string failureMessage = "Arguments are equivalent!"
            )
        {
            if (expected == actual) {
                stringstream err;

                err << "Non-Equivalence assertion failed!" << endl;
                err << failureMessage << endl;
                err << "Expected: <" << expected << ">" << endl;
                err << "Actual: <" << actual << ">" << endl;

                throw TestFailedException(err.str());
            }
        }

        template<typename T>
        static void assertNull (
                T ptr,
                string failureMessage = "Object is not null!"
            )
        {
            bool null = ptr == nullptr;

            if (!null) {
                stringstream err;

                err << "Null assertion failed!" << endl;
                err << failureMessage << endl;

                throw TestFailedException(err.str());
            }
        }

        template<typename T>
        static void assertNotNull (
                T ptr,
                string failureMessage = "Object is null!"
            )
        {
            bool notNull = ptr != nullptr;

            if (!notNull) {
                stringstream err;

                err << "Not Null assertion failed!" << endl;
                err << failureMessage << endl;

                throw TestFailedException(err.str());
            }
        }

        static void assertThrows (
            function<void()> shouldThrow,
            string failureMessage =
                "Should have thrown something!"
        );

        static void assertNoThrows (
            function<void()> shouldNotThrow,
            string failureMessage =
                "Should not have thrown anything!"
        );

        static void assertTrue (
            bool condition,
            string failureMessage = "Condition is false!"
        );

        static void assertFalse (
            bool condition,
            string failureMessage = "Condition is true!"
        );

        static void fail (
            const string& failureMessage = "Forced test failure!"
        );

        void enableTestPassedMessage ();
        void disableTestPassedMessage ();

        void run ();

    private:
        bool testPassedMessage;
        bool lastRunSucceeded;
        unsigned lastRunSuccessCount;
        unsigned lastRunFailCount;
        unsigned long long totalRuntime;

        string suiteName;
        vector<TestCase> tests;
    };
}

#endif
