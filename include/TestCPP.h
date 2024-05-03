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

    class TestObjName {
    public:
        TestObjName () = default;
        TestObjName (const char* name);

        const string& getTestName ();

        friend std::ostream& operator<< (
            std::ostream& s,
            TestObjName& tcName
        )
        {
            s << tcName.getTestName();
            return s;
        }

    private:
        string testCaseName;

        struct TCNStr {
            static constexpr const char * NVTN =
                "Not a valid test name!";
        };
    };

    class TestCase {

    public:
        enum TestCaseOutCompareOptions {
            CONTAINS,
            EXACT
        };

        TestCase (
            TestObjName&& testName,
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

        TestObjName testName;
        function<void()> test;

        TestCaseOutCompareOptions option;

        void captureStdout ();
        void captureClog ();
        void captureStdErr ();
        void logTestFailure (string);
        void runTest ();
        bool checkOutput (TestCaseOutCompareOptions opt, string source,
                          string against);

        static atomic_int stdoutCaptureCasesConstructed;
        static atomic_int logCaptureCasesConstructed;
        static atomic_int stderrCaptureCasesConstructed;
        static atomic_int stdoutCaptureCasesDestroyed;
        static atomic_int logCaptureCasesDestroyed;
        static atomic_int stderrCaptureCasesDestroyed;

        static unique_ptr<stringstream> stdoutBuffer;
        static unique_ptr<stringstream> clogBuffer;
        static unique_ptr<stringstream> stderrBuffer;
        static unique_ptr<streambuf> stdoutOriginal;
        static unique_ptr<streambuf> clogOriginal;
        static unique_ptr<streambuf> stderrOriginal;

        template<typename F, typename ...Args>
        static nanoseconds duration (F func, Args&&... args)
        {
            auto start = system_clock::now();
            func(forward<Args>(args)...);
            return duration_cast<nanoseconds>(
                system_clock::now() - start
            );
        }

        struct TCStr {
            static constexpr const char * APOS = "'";
            static constexpr const char * FAIL = " failed! (";
            static constexpr const char * NCONTAIN =
                " does not contain ";
            static constexpr const char * NEQUIV =
                " is not equivalent to ";
            static constexpr const char * PASS = " passed! (";
            static constexpr const char * REASON = "Reason: ";
            static constexpr const char * SEC = "s)";
            static constexpr const char * START_RUN =
                "Starting run of test ";
            static constexpr const char * TEST_ = "Test ";
            static constexpr const char * UNK_CMP_OPT =
                "Unknown comparison option! ";
            static constexpr const char * UNK_EXC =
                "Unknown error occurred in test!";
            static constexpr const char * UNK_OPT = "Unknown option ";
        };
    };

    class TestSuite {

    public:
        template<typename... TestType>
        TestSuite (TestObjName&& suiteName,
                   typename enable_if<sizeof...(TestType) == 0>::type)
        {
            this->testPassedMessage = true;
            this->setSuiteName(move(suiteName));
            this->tests = vector<TestCase>();
        }

        template<typename... TestType>
        TestSuite (TestObjName&& suiteName, TestType ...tests) {
            this->testPassedMessage = true;
            this->setSuiteName(move(suiteName));
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

        void setSuiteName (TestObjName&& testSuiteName);

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
            string failureMessage = "Forced test failure!"
        );

        void enableTestPassedMessage ();
        void disableTestPassedMessage ();

        unsigned getLastRunFailCount ();

        void run ();

    private:
        bool testPassedMessage;
        bool lastRunSucceeded;
        unsigned lastRunSuccessCount;
        unsigned lastRunFailCount;
        unsigned long long totalRuntime;

        TestObjName suiteName;
        vector<TestCase> tests;
    };
}

#endif
