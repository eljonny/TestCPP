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

#ifdef TESTCPP_STACKTRACE_ENABLED
#include <boost/stacktrace.hpp>
#endif

#include <iomanip>

#include "TestCPP.h"
#include "TestCPPUtil.h"

using std::cerr;
using std::clog;
using std::cout;
using std::current_exception;
using std::endl;
using std::exception;
using std::exception_ptr;
using std::fixed;
using std::function;
using std::invalid_argument;
using std::move;
using std::rethrow_exception;
using std::runtime_error;
using std::setprecision;
using std::string;
using std::tuple;

namespace TestCPP {
    TestCPPException::TestCPPException (const char * msg) :
        runtime_error(msg)
    {
#ifdef TESTCPP_STACKTRACE_ENABLED
        clog << boost::stacktrace::stacktrace();
#endif
    }
    TestCPPException::TestCPPException (string&& msg) :
        runtime_error(move(msg))
    {
#ifdef TESTCPP_STACKTRACE_ENABLED
        clog << boost::stacktrace::stacktrace();
#endif
    }

    TestFailedException::TestFailedException (const char * msg) :
        TestCPPException(msg)
    {
#ifdef TESTCPP_STACKTRACE_ENABLED
        clog << boost::stacktrace::stacktrace();
#endif
    }

    TestFailedException::TestFailedException (string&& msg) :
        TestCPPException(move(msg))
    {
#ifdef TESTCPP_STACKTRACE_ENABLED
        clog << boost::stacktrace::stacktrace();
#endif
    }

    TestCaseName::TestCaseName (const char* name) {
        if (name) {
            this->testCaseName = name;
        }
        else {
            throw TestCPPException("Not a valid test name!");
        }
    }

    const string& TestCaseName::getTestName () {
        return this->testCaseName;
    }

    TestCase::TestCase (TestCaseName&& name,
                        function<void()> test,
                        bool msg,
                        bool captureOut, bool captureLog,
                        bool captureErr,
                        TestCase::TestCaseOutCompareOptions opt)
    {
        this->notifyTestPassed = msg;
        this->test = test;

        this->testName = name;

        if (captureOut) {
            captureStdout();
        }
        if (captureLog) {
            captureClog();
        }
        if (captureErr) {
            captureStdErr();
        }

        this->option = opt;
    }

    TestCase::TestCase (TestCase& o) {
        this->outCompareOption(o.option);
        this->setNotifyPassed(o.notifyTestPassed);

        this->pass = o.pass;
        this->lastRunTime = o.lastRunTime;

        this->testName = o.testName;
        this->test = o.test;

        this->clogBuffer = unique_ptr<stringstream>(
            o.clogBuffer.release()
        );
        this->stderrBuffer = unique_ptr<stringstream>(
            o.stderrBuffer.release()
        );
        this->stdoutBuffer = unique_ptr<stringstream>(
            o.stdoutBuffer.release()
        );

        this->clogOriginal = unique_ptr<streambuf>(
            o.clogOriginal.release()
        );
        this->stderrOriginal = unique_ptr<streambuf>(
            o.stderrOriginal.release()
        );
        this->stdoutOriginal = unique_ptr<streambuf>(
            o.stdoutOriginal.release()
        );
    }

    TestCase::TestCase (TestCase&& o) {
        this->outCompareOption(move(o.option));
        this->setNotifyPassed(move(o.notifyTestPassed));

        this->pass = move(o.pass);
        this->lastRunTime = move(o.lastRunTime);

        this->testName = move(o.testName);
        this->test = move(o.test);

        this->clogBuffer = unique_ptr<stringstream>(
            move(o.clogBuffer.release())
        );
        this->stderrBuffer = unique_ptr<stringstream>(
            move(o.stderrBuffer.release())
        );
        this->stdoutBuffer = unique_ptr<stringstream>(
            move(o.stdoutBuffer.release())
        );

        this->clogOriginal = unique_ptr<streambuf>(
            move(o.clogOriginal.release())
        );
        this->stderrOriginal = unique_ptr<streambuf>(
            move(o.stderrOriginal.release())
        );
        this->stdoutOriginal = unique_ptr<streambuf>(
            move(o.stdoutOriginal.release())
        );
    }

    TestCase::~TestCase () {
        if (this->stdoutBuffer != nullptr) {
            cout.rdbuf(this->stdoutOriginal.release());
        }
        if (this->clogBuffer != nullptr) {
            clog.rdbuf(this->clogOriginal.release());
        }
        if (this->stderrBuffer != nullptr) {
            cerr.rdbuf(this->stderrOriginal.release());
        }
    }

    TestCase& TestCase::operator= (TestCase& rhs) {
        this->outCompareOption(rhs.option);
        this->setNotifyPassed(rhs.notifyTestPassed);

        this->pass = rhs.pass;
        this->lastRunTime = rhs.lastRunTime;

        this->testName = rhs.testName;
        this->test = rhs.test;

        this->clogBuffer = unique_ptr<stringstream>(
            rhs.clogBuffer.release()
        );
        this->stderrBuffer = unique_ptr<stringstream>(
            rhs.stderrBuffer.release()
        );
        this->stdoutBuffer = unique_ptr<stringstream>(
            rhs.stdoutBuffer.release()
        );

        this->clogOriginal = unique_ptr<streambuf>(
            rhs.clogOriginal.release()
        );
        this->stderrOriginal = unique_ptr<streambuf>(
            rhs.stderrOriginal.release()
        );
        this->stdoutOriginal = unique_ptr<streambuf>(
            rhs.stdoutOriginal.release()
        );

        return *this;
    }

    TestCase& TestCase::operator= (TestCase&& rhs) {
        this->outCompareOption(move(rhs.option));
        this->setNotifyPassed(move(rhs.notifyTestPassed));

        this->pass = move(rhs.pass);
        this->lastRunTime = move(rhs.lastRunTime);

        this->testName = move(rhs.testName);
        this->test = move(rhs.test);

        this->clogBuffer = unique_ptr<stringstream>(
            move(rhs.clogBuffer.release())
        );
        this->stderrBuffer = unique_ptr<stringstream>(
            move(rhs.stderrBuffer.release())
        );
        this->stdoutBuffer = unique_ptr<stringstream>(
            move(rhs.stdoutBuffer.release())
        );

        this->clogOriginal = unique_ptr<streambuf>(
            move(rhs.clogOriginal.release())
        );
        this->stderrOriginal = unique_ptr<streambuf>(
            move(rhs.stderrOriginal.release())
        );
        this->stdoutOriginal = unique_ptr<streambuf>(
            move(rhs.stdoutOriginal.release())
        );

        return *this;
    }

    unsigned long long TestCase::getLastRuntime () {
        return this->lastRunTime;
    }

    void TestCase::logTestFailure (string reason) {
        clog << fixed;
        clog << setprecision(4);
        clog << "Test " << this->testName << " failed! ("
                << static_cast<double>(this->lastRunTime)
                    /1000000000.0 << "s)" << endl;
        clog << "Reason: " << reason << endl;
    }

    void TestCase::runTest () {
        clog << "Starting run of test " << this->testName << endl;
        this->lastRunTime = duration(this->test).count();
        if (this->notifyTestPassed) {
            clog << fixed;
            clog << setprecision(4);
            clog << "Test " << this->testName << " passed! ("
                    << static_cast<double>(this->lastRunTime)
                        /1000000000.0 << "s)" << endl;
        }
        this->pass = true;
    }

    bool TestCase::go () {
        try {
            runTest();
            return true;
        }
        catch(const char * errorMessage) {
            this->pass = false;
            logTestFailure(errorMessage);
        }
        catch(string errorMessage) {
            this->pass = false;
            logTestFailure(errorMessage);
        }
        catch (exception& e) {
            this->pass = false;
            logTestFailure(e.what());
        }
        catch (...) {
            this->pass = false;
            logTestFailure("Unknown error occurred in test!");
        }

        return false;
    }

    void TestCase::setNotifyPassed (bool notify) {
        this->notifyTestPassed = notify;
    }

    void TestCase::captureStdout () {
        this->stdoutBuffer = unique_ptr<stringstream>(
            new stringstream()
        );
        this->stdoutOriginal = unique_ptr<streambuf>(cout.rdbuf());
        cout.rdbuf(this->stdoutBuffer->rdbuf());
    }
    void TestCase::captureClog () {
        this->clogBuffer = unique_ptr<stringstream>(
            new stringstream()
        );
        this->clogOriginal = unique_ptr<streambuf>(clog.rdbuf());
        clog.rdbuf(this->clogBuffer->rdbuf());
    }
    void TestCase::captureStdErr () {
        this->stderrBuffer = unique_ptr<stringstream>(
            new stringstream()
        );
        this->stderrOriginal = unique_ptr<streambuf>(cerr.rdbuf());
        cerr.rdbuf(this->stderrBuffer->rdbuf());
    }

    void TestCase::outCompareOption (TestCaseOutCompareOptions opt) {
        switch (opt) {
        case EXACT:
        case CONTAINS:
            this->option = opt;
            break;

        default:
            stringstream error;
            error << "Unknown option " << opt;
            throw TestCPPException(error.str());
        }
    }

    void TestCase::clearStdoutCapture () {
        if (this->stdoutBuffer) {
            this->stdoutBuffer->str(string());
        }
    }

    void TestCase::clearLogCapture () {
        if (this->clogBuffer) {
            this->clogBuffer->str(string());
        }
    }

    void TestCase::clearStderrCapture () {
        if (this->stderrBuffer) {
            this->stderrBuffer->str(string());
        }
    }

    bool TestCase::checkStdout (string against) {
        return checkOutput(this->option, stdoutBuffer->str(), against);
    }

    bool TestCase::checkLog (string against) {
        return checkOutput(this->option, clogBuffer->str(), against);
    }

    bool TestCase::checkStderr (string against) {
        return checkOutput(this->option, stderrBuffer->str(), against);
    }

    bool TestCase::checkOutput (TestCase::TestCaseOutCompareOptions opt,
                                string source, string against)
    {
        switch (opt) {
        case EXACT:
            return source == against;

        case CONTAINS:
            return Util::stringContains(source, against);

        default:
            stringstream re;
            re << "Unknown comparison option! " << opt;
            throw TestCPPException(re.str());
        }
    }

    void TestSuite::enableTestPassedMessage () {
        this->testPassedMessage = true;
        for (TestCase test : this->tests) {
            test.setNotifyPassed(true);
        }
    }
    void TestSuite::disableTestPassedMessage () {
        this->testPassedMessage = false;
        for (TestCase test : this->tests) {
            test.setNotifyPassed(false);
        }
    }

    void TestSuite::setSuiteName (string testSuiteName) {
        if (testSuiteName.data()) {
            this->suiteName = testSuiteName;
        }
        else {
            stringstream e;
            e << "An invalid string was passed as the Test Suite Name!";
            throw TestCPPException(e.str());
        }
    }

    void TestSuite::run () {
        if (this->tests.size() == 0) {
            clog << "No tests to run!" << endl;
            return;
        }

        this->lastRunSucceeded = true;
        this->lastRunFailCount = 0;
        this->lastRunSuccessCount = 0;
        this->totalRuntime = 0;

        clog << endl
             << "Starting to run test suite '" << this->suiteName << "'"
             << endl << endl;

        for (TestCase test : this->tests) {
            bool testPassed = false;
            try {
                testPassed = test.go();
            }
            catch (exception& e) {
                clog << "Exception occurred during test run: "
                     << e.what() << endl;
            }
            catch (...) {
                cerr << "An unknown error occurred during test run."
                     << endl;
            }

            if (!testPassed && this->lastRunSucceeded) {
                this->lastRunFailCount++;
                this->lastRunSucceeded = false;
            }
            else if (!testPassed) {
                this->lastRunFailCount++;
            }
            else {
                this->lastRunSuccessCount++;
            }

            this->totalRuntime += test.getLastRuntime();
        }

        clog << endl;

        if (this->testPassedMessage &&
            this->lastRunFailCount == 0) {
            clog << "All '" << this->suiteName
                 << "' suite tests passed!" << endl;
        }

        double suiteRuntimeElapsed = static_cast<double>(
            this->totalRuntime)/1000000000.0;

        clog << fixed;
        clog << setprecision(0);
        clog << "Finished running suite '" << this->suiteName << "' in "
             << suiteRuntimeElapsed << "s ("<< this->lastRunSuccessCount
             << "/" << this->tests.size() << " passed)" << endl;
        clog << endl;
    }

    template<>
    void TestSuite::addTest (TestCase&& test) {
        this->tests.emplace_back(test);
    }

    void TestSuite::assertThrows (
            function<void()> shouldThrow,
            string failureMessage
        )
    {
        try {
            shouldThrow();
        }
        catch (...) {
            exception_ptr eptr = current_exception();

            if (eptr) {
                try {
                    rethrow_exception(eptr);
                }
                catch (const exception& e) {
                    clog << "assertThrows caught exception: "
                         << TestFailedException(e.what()).what()
                         << endl;
                }
            }
            else {
                clog << "Something was thrown, not sure what." << endl
                     << "This satisfies the assertion, so no failure is"
                     << " present. "
                     << TestFailedException("Unknown thrown object").
                            what();
            }

            return;
        }

        throw TestFailedException(failureMessage);
    }

    void TestSuite::assertNoThrows (
            function<void()> shouldNotThrow,
            string failureMessage
        )
    {
        try {
            shouldNotThrow()
        }
        catch (...) {
            throw TestFailedException(failureMessage);
        }
    }

    void TestSuite::assertTrue (
            bool condition,
            string failureMessage
        )
    {
        if (!condition) {
            stringstream err;

            err << "Boolean Truth assertion failed!" << std::endl;
            err << failureMessage << std::endl;

            throw TestFailedException(err.str());
        }
    }

    void TestSuite::assertFalse (
            bool condition,
            string failureMessage
        )
    {
        if (condition) {
            stringstream err;

            err << "Boolean False assertion failed!" << std::endl;
            err << failureMessage << std::endl;

            throw TestFailedException(err.str());
        }
    }

    void TestSuite::fail(const string& failureMessage) {
        throw TestFailedException(move(string(failureMessage)));
    }
}
