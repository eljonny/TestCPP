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

#include <iomanip>

#include "Test.h"
#include "TestUtil.h"

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
using std::rethrow_exception;
using std::runtime_error;
using std::setprecision;
using std::string;
using std::tuple;

namespace TestCPP {
    TestCase::TestCase(string name, function<void()> test, bool msg,
                       bool captureOut, bool captureLog,
                       bool captureErr,
                       TestCase::TestCaseOutCompareOptions opt)
    {
        this->notifyTestPassed = msg;
        this->test = test;
        
        if (name.data())
        {
            this->testName = name;
        }
        else
        {
            stringstream e;
            e << "An invalid string was passed as the Test Case Name!";
            throw invalid_argument(e.str());
        }
        
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
    
    TestCase::~TestCase() {
        if (this->stdoutBuffer != nullptr) {
            delete this->stdoutBuffer;
            cout.rdbuf(this->stdoutOriginal);
        }
        if (this->clogBuffer != nullptr) {
            delete this->clogBuffer;
            clog.rdbuf(this->clogOriginal);
        }
        if (this->stderrBuffer != nullptr) {
            delete this->stderrBuffer;
            cerr.rdbuf(this->stderrOriginal);
        }
    }

    unsigned long long TestCase::getLastRuntime() {
        return this->lastRunTime;
    }
    
    void TestCase::logTestFailure(string reason) {
        cerr << fixed;
        cerr << setprecision(4);
        cerr << "Test " << this->testName << " failed! ("
                << static_cast<double>(this->lastRunTime)
                    /1000000000.0 << "s)" << endl;
        cerr << "Reason: " << reason << endl;
    }
    
    void TestCase::runTest() {
        clog << "Starting run of test " << this->testName << endl;
        this->lastRunTime = duration(this->test).count();
        if(this->notifyTestPassed) {
            clog << fixed;
            clog << setprecision(4);
            clog << "Test " << this->testName << " passed! ("
                    << static_cast<double>(this->lastRunTime)
                        /1000000000.0 << "s)" << endl;
        }
        this->pass = true;
    }

    bool TestCase::go() {
        try {
            runTest();
            return true;
        }
        catch(string errorMessage) {
            this->pass = false;
            logTestFailure(errorMessage);
        }
        catch(runtime_error& re) {
            this->pass = false;
            logTestFailure(re.what());
        }
        catch(exception& e) {
            this->pass = false;
            logTestFailure(e.what());
        }
        
        return false;
    }

    void TestCase::setNotifyPassed(bool notify) {
        this->notifyTestPassed = notify;
    }
    
    void TestCase::captureStdout() {
        this->stdoutBuffer = new stringstream();
        this->stdoutOriginal = cout.rdbuf();
        cout.rdbuf(this->stdoutBuffer->rdbuf());
    }
    void TestCase::captureClog() {
        this->clogBuffer = new stringstream();
        this->clogOriginal = clog.rdbuf();
        clog.rdbuf(this->clogBuffer->rdbuf());
    }
    void TestCase::captureStdErr() {
        this->stderrBuffer = new stringstream();
        this->stderrOriginal = cerr.rdbuf();
        cerr.rdbuf(this->stderrBuffer->rdbuf());
    }
    
    void TestCase::outCompareOption(TestCaseOutCompareOptions opt) {
        switch (opt) {
        case EXACT:
        case CONTAINS:
            this->option = opt;
            break;
            
        default:
            stringstream error;
            error << "Unknown option " << opt;
            throw std::runtime_error(error.str());
        }
    }
    
    void TestCase::clearStdoutCapture() {
        if (this->stdoutBuffer) {
            this->stdoutBuffer->str(string());
        }
    }
    
    void TestCase::clearLogCapture() {
        if (this->clogBuffer) {
            this->clogBuffer->str(string());
        }
    }
    
    void TestCase::clearStderrCapture() {
        if (this->stderrBuffer) {
            this->stderrBuffer->str(string());
        }
    }
    
    bool TestCase::checkStdout(string against) {
        return checkOutput(this->option, stdoutBuffer->str(), against);
    }
        
    bool TestCase::checkLog(string against) {
        return checkOutput(this->option, clogBuffer->str(), against);
    }
        
    bool TestCase::checkStderr(string against) {
        return checkOutput(this->option, stderrBuffer->str(), against);
    }
    
    bool TestCase::checkOutput(TestCase::TestCaseOutCompareOptions opt,
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
            throw runtime_error(re.str());
        }
    }

    void TestSuite::enableTestPassedMessage() {
        this->testPassedMessage = true;
        for(TestCase test : this->tests) {
            test.setNotifyPassed(true);
        }
    }
    void TestSuite::disableTestPassedMessage() {
        this->testPassedMessage = false;
        for(TestCase test : this->tests) {
            test.setNotifyPassed(false);
        }
    }

    void TestSuite::setSuiteName(string testSuiteName) {
        if (testSuiteName.data())
        {
            this->suiteName = testSuiteName;
        }
        else
        {
            stringstream e;
            e << "An invalid string was passed as the Test Suite Name!";
            throw invalid_argument(e.str());
        }
    }

    void TestSuite::run() {

        if(this->tests.size() == 0) {
            cerr << "No tests to run!" << endl;
            return;
        }

        this->lastRunSucceeded = true;
        this->lastRunFailCount = 0;
        this->lastRunSuccessCount = 0;
        this->totalRuntime = 0;
        
        clog << endl
             << "Starting to run test suite '" << this->suiteName << "'"
             << endl << endl;

        for(TestCase test : this->tests) {
            bool testPassed = test.go();
            if(!testPassed && this->lastRunSucceeded) {
                this->lastRunFailCount++;
                this->lastRunSucceeded = false;
            }
            else if(!testPassed) {
                this->lastRunFailCount++;
            }
            else {
                this->lastRunSuccessCount++;
            }
            this->totalRuntime += test.getLastRuntime();
        }

        clog << endl;

        if(this->testPassedMessage &&
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
    void TestSuite::addTest(tuple<string, function<void()>> test) {
        this->tests.push_back( TestCase(
                std::get<0>(test),
                std::get<1>(test),
                this->testPassedMessage
            )
        );
    }

    template<>
    void TestSuite::addTest(TestCase test) {
        this->tests.push_back(test);
    }
    
    void TestSuite::assertThrows(
            function<void()> shouldThrow,
            string failureMessage
        )
    {
        try {
            shouldThrow();
        }
        catch (const char * errStr) {
            clog << "assertThrows Caught char*: " << errStr << endl;
            return;
        }
        catch (const string errStr) {
            clog << "assertThrows Caught string: " << errStr << endl;
            return;
        }
        catch (...) {
            exception_ptr eptr = current_exception();
            
            if (eptr)
            {
                try
                {
                    rethrow_exception(eptr);
                }
                catch (const exception& e)
                {
                    clog << "assertThrows caught exception: "
                         << e.what() << endl;
                }
            }
            else
            {
                clog << "Something was thrown, not sure what." << endl
                     << "This satisfies the assertion, so no failure is"
                     << " present.";
            }
            
            return;
        }
        
        fail(failureMessage);
    }

    void TestSuite::assertTrue(
            bool condition,
            string failureMessage
        )
    {
        if(!condition) {
            stringstream err;

            err << "Boolean Truth assertion failed!" << std::endl;
            err << failureMessage << std::endl;

            throw err.str();
        }
    }

    void TestSuite::assertFalse(
            bool condition,
            string failureMessage
        )
    {
        if(condition) {
            stringstream err;

            err << "Boolean False assertion failed!" << std::endl;
            err << failureMessage << std::endl;

            throw err.str();
        }
    }

    void TestSuite::fail(string failureMessage) {
        throw failureMessage;
    }
}
