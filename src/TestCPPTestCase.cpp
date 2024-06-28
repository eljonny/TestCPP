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

#include "internal/TestCPPCommon.h"
#include "internal/TestCPPExceptions.h"
#include "internal/TestCPPTestCase.h"

#ifdef TESTCPP_STACKTRACE_ENABLED
#include <boost/stacktrace.hpp>
#endif

#include <iomanip>

#include "internal/TestCPPUtil.h"

using TestCPP::Util::debugLog;
using std::cerr;
using std::clog;
using std::cout;
using std::endl;
using std::exception;
using std::fixed;
using std::function;
using std::invalid_argument;
using std::move;
using std::rethrow_exception;
using std::runtime_error;
using std::setprecision;
using std::string;
using std::tuple;

using TCPPNum = TestCPP::TestCPPCommon::Nums;
using TCPPStr = TestCPP::TestCPPCommon::Strings;

namespace TestCPP {

    atomic_int TestCase::stdoutCaptureCasesConstructed;
    atomic_int TestCase::logCaptureCasesConstructed;
    atomic_int TestCase::stderrCaptureCasesConstructed;
    atomic_int TestCase::stdoutCaptureCasesDestroyed;
    atomic_int TestCase::logCaptureCasesDestroyed;
    atomic_int TestCase::stderrCaptureCasesDestroyed;

    unique_ptr<stringstream, void(*)(stringstream*)>
        TestCase::stdoutBuffer =
        unique_ptr<stringstream, void(*)(stringstream*)>(
            nullptr, [](stringstream*){}
        );
    unique_ptr<stringstream, void(*)(stringstream*)>
        TestCase::clogBuffer =
        unique_ptr<stringstream, void(*)(stringstream*)>(
            nullptr, [](stringstream*){}
        );
    unique_ptr<stringstream, void(*)(stringstream*)>
        TestCase::stderrBuffer =
        unique_ptr<stringstream, void(*)(stringstream*)>(
            nullptr, [](stringstream*){}
        );
    unique_ptr<streambuf, void(*)(streambuf*)>
        TestCase::stdoutOriginal =
        unique_ptr<streambuf, void(*)(streambuf*)>(
            nullptr, [](streambuf*){}
        );
    unique_ptr<streambuf, void(*)(streambuf*)>
        TestCase::clogOriginal =
        unique_ptr<streambuf, void(*)(streambuf*)>(
            nullptr, [](streambuf*){}
        );
    unique_ptr<streambuf, void(*)(streambuf*)>
        TestCase::stderrOriginal =
        unique_ptr<streambuf, void(*)(streambuf*)>(
            nullptr, [](streambuf*){}
        );

    TestCase::TestCase (TestObjName&& name,
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
            debugLog("CaptureLog windows segfault check - clog cap");
            captureClog();
            debugLog("CaptureLog windows segfault check - clog end");
        }
        if (captureErr) {
            captureStdErr();
        }

        this->stdoutCaptured = captureOut;
        this->clogCaptured = captureLog;
        this->stderrCaptured = captureErr;

        this->option = opt;
    }

    TestCase::TestCase (TestCase& o) {
        this->outCompareOption(o.option);
        this->setNotifyPassed(o.notifyTestPassed);

        this->pass = o.pass;
        this->lastRunTime = o.lastRunTime;

        this->stdoutCaptured = o.stdoutCaptured;
        this->clogCaptured = o.clogCaptured;
        this->stderrCaptured = o.stderrCaptured;

        if (this->stdoutCaptured) {
            captureStdout();
        }
        if (this->clogCaptured) {
            captureClog();
        }
        if (this->stderrCaptured) {
            captureStdErr();
        }

        this->testName = o.testName;
        this->test = o.test;
    }

    TestCase::TestCase (TestCase&& o) {
        this->outCompareOption(move(o.option));
        this->setNotifyPassed(move(o.notifyTestPassed));

        this->pass = move(o.pass);
        this->lastRunTime = move(o.lastRunTime);

        this->stdoutCaptured = move(o.stdoutCaptured);
        this->clogCaptured = move(o.clogCaptured);
        this->stderrCaptured = move(o.stderrCaptured);

        if (this->stdoutCaptured) {
            captureStdout();
        }
        if (this->clogCaptured) {
            captureClog();
        }
        if (this->stderrCaptured) {
            captureStdErr();
        }

        this->testName = move(o.testName);
        this->test = move(o.test);
    }

    TestCase::~TestCase () {
        if (TestCase::stdoutBuffer != nullptr)
        {
            if (TestCase::stdoutCaptureCasesDestroyed ==
                TestCase::stdoutCaptureCasesConstructed - 1)
            {
                cout.rdbuf(TestCase::stdoutOriginal.release());
                delete TestCase::stdoutBuffer.get();
                TestCase::stdoutBuffer = nullptr;
            }

            TestCase::stdoutCaptureCasesDestroyed += 1;
        }
        if (TestCase::clogBuffer != nullptr)
        {
            if (TestCase::logCaptureCasesDestroyed ==
                TestCase::logCaptureCasesConstructed - 1)
            {
                clog.rdbuf(TestCase::clogOriginal.release());
                delete TestCase::clogBuffer.get();
                TestCase::clogBuffer = nullptr;
            }

            TestCase::logCaptureCasesDestroyed += 1;
        }
        if (TestCase::stderrBuffer != nullptr)
        {
            if (TestCase::stderrCaptureCasesDestroyed ==
                TestCase::stderrCaptureCasesConstructed - 1)
            {
                cerr.rdbuf(TestCase::stderrOriginal.release());
                delete TestCase::stderrBuffer.get();
                TestCase::stderrBuffer = nullptr;
            }

            TestCase::stderrCaptureCasesDestroyed += 1;
        }
    }

    TestCase& TestCase::operator= (TestCase& rhs) {
        this->outCompareOption(rhs.option);
        this->setNotifyPassed(rhs.notifyTestPassed);

        this->pass = rhs.pass;
        this->lastRunTime = rhs.lastRunTime;

        this->stdoutCaptured = rhs.stdoutCaptured;
        this->clogCaptured = rhs.clogCaptured;
        this->stderrCaptured = rhs.stderrCaptured;

        if (this->stdoutCaptured) {
            captureStdout();
        }
        if (this->clogCaptured) {
            captureClog();
        }
        if (this->stderrCaptured) {
            captureStdErr();
        }

        this->testName = rhs.testName;
        this->test = rhs.test;

        return *this;
    }

    TestCase& TestCase::operator= (TestCase&& rhs) {
        this->outCompareOption(move(rhs.option));
        this->setNotifyPassed(move(rhs.notifyTestPassed));

        this->pass = move(rhs.pass);
        this->lastRunTime = move(rhs.lastRunTime);

        this->stdoutCaptured = move(rhs.stdoutCaptured);
        this->clogCaptured = move(rhs.clogCaptured);
        this->stderrCaptured = move(rhs.stderrCaptured);

        if (this->stdoutCaptured) {
            captureStdout();
        }
        if (this->clogCaptured) {
            captureClog();
        }
        if (this->stderrCaptured) {
            captureStdErr();
        }

        this->testName = move(rhs.testName);
        this->test = move(rhs.test);

        return *this;
    }

    long long TestCase::getLastRuntime () {
        return this->lastRunTime;
    }

    void TestCase::logFailure(ostream& out, string& reason) {
        out << fixed;
        out << setprecision(TCPPNum::TIME_PRECISION);
        out << TCPPStr::TEST_ << this->testName << TCPPStr::_FAIL_
            << TCPPStr::PARENL
            << static_cast<double>(this->lastRunTime)/
               TCPPNum::NANOS_IN_SEC
            << TCPPStr::SEC << TCPPStr::PARENR
            << endl;
        out << TCPPStr::REASON_ << reason << endl;
    }

    void TestCase::logTestFailure (string reason) {
        unique_ptr<ostream> logStream = nullptr;

        if (this->clogOriginal != nullptr) {
            logStream = unique_ptr<ostream>(
                new ostream(this->clogOriginal.get())
            );
        }
        else {
            logStream = unique_ptr<ostream>(&clog);
        }

        logFailure(*logStream, reason);

        if (this->clogOriginal != nullptr) {
            logStream->flush();

            // If someone is looking for something in the message,
            //  and it's captured, make sure it's there.
            logFailure(clog, reason);
        }

        logStream.release();
        logStream.reset();
    }

    void TestCase::runTest () {
        clog << TCPPStr::START_RUN << this->testName << endl;
        this->lastRunTime = duration(this->test).count();
        if (this->notifyTestPassed) {
            clog << fixed;
            clog << setprecision(TCPPNum::TIME_PRECISION);
            clog << TCPPStr::TEST_ << this->testName << TCPPStr::_PASS_
                 << TCPPStr::PARENL
                 << static_cast<double>(this->lastRunTime)/
                    TCPPNum::NANOS_IN_SEC
                 << TCPPStr::SEC << TCPPStr::PARENR
                 << endl;
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
        catch(string& errorMessage) {
            this->pass = false;
            logTestFailure(errorMessage);
        }
        catch (exception& e) {
            this->pass = false;
            logTestFailure(e.what());
        }
        catch (...) {
            this->pass = false;
            logTestFailure(TCPPStr::UNK_EXC);
        }

        return false;
    }

    void TestCase::setNotifyPassed (bool notify) {
        this->notifyTestPassed = notify;
    }

    void TestCase::captureStdout () {
        if (TestCase::stdoutCaptureCasesConstructed ==
            TestCase::stdoutCaptureCasesDestroyed)
        {
            TestCase::stdoutCaptureCasesConstructed += 1;
            TestCase::stdoutBuffer =
                unique_ptr<stringstream, void(*)(stringstream*)>(
                    new stringstream(), [](stringstream *) {}
                );
            TestCase::stdoutOriginal =
                unique_ptr<streambuf, void(*)(streambuf*)>(
                    cout.rdbuf(), [](streambuf *) {}
                );
            cout.rdbuf(TestCase::stdoutBuffer->rdbuf());
        }
        else {
            TestCase::stdoutCaptureCasesConstructed += 1;
        }
    }

    void TestCase::captureClog () {
        debugLog("captureClog winseg check - open");
        if (TestCase::logCaptureCasesConstructed ==
            TestCase::logCaptureCasesDestroyed)
        {
            debugLog("captureClog winseg check - clogConstruct");
            TestCase::logCaptureCasesConstructed += 1;
            debugLog("captureClog winseg check - atomic++");
            TestCase::clogBuffer =
                unique_ptr<stringstream, void(*)(stringstream*)>(
                    new stringstream(), [](stringstream *) {}
                );
            debugLog("captureClog winseg check - clogBuffer");
            TestCase::clogOriginal =
                unique_ptr<streambuf, void(*)(streambuf*)>(
                    cout.rdbuf(), [](streambuf *) {}
                );
            debugLog("captureClog winseg check - clogStream");
            clog.rdbuf(TestCase::clogBuffer->rdbuf());
            debugLog("captureClog winseg check - clogSet");
        }
        else {
            debugLog("captureClog winseg check - clogNoConstruct");
            TestCase::logCaptureCasesConstructed += 1;
            debugLog("captureClog winseg check - atomic++");
        }
        debugLog("captureClog winseg check - close");
    }

    void TestCase::captureStdErr () {
        if (TestCase::stderrCaptureCasesConstructed ==
            TestCase::stderrCaptureCasesDestroyed)
        {
            TestCase::stderrCaptureCasesConstructed += 1;
            TestCase::stderrBuffer =
                unique_ptr<stringstream, void(*)(stringstream*)>(
                    new stringstream(), [](stringstream *) {}
                );
            TestCase::stderrOriginal =
                unique_ptr<streambuf, void(*)(streambuf*)>(
                    cout.rdbuf(), [](streambuf *) {}
                );
            cerr.rdbuf(TestCase::stderrBuffer->rdbuf());
        }
        else {
            TestCase::stderrCaptureCasesConstructed += 1;
        }
    }

    void TestCase::outCompareOption (TestCaseOutCompareOptions opt) {
        switch (opt) {
        case EXACT:
        case CONTAINS:
            this->option = opt;
            break;

        default:
            stringstream error;
            error << TCPPStr::UNK_OPT_ << opt;
            throw TestCPPException(error.str());
        }
    }

    void TestCase::clearStdoutCapture () {
        if (TestCase::stdoutBuffer) {
            TestCase::stdoutBuffer->str(string());
        }
    }

    void TestCase::clearLogCapture () {
        if (TestCase::clogBuffer) {
            TestCase::clogBuffer->str(string());
        }
    }

    void TestCase::clearStderrCapture () {
        if (TestCase::stderrBuffer) {
            TestCase::stderrBuffer->str(string());
        }
    }

    bool TestCase::checkStdout (string against) {
        return checkOutput(TestCase::stdoutBuffer->str(),
                           against);
    }

    bool TestCase::checkLog (string against) {
        return checkOutput(TestCase::clogBuffer->str(),
                           against);
    }

    bool TestCase::checkStderr (string against) {
        return checkOutput(TestCase::stderrBuffer->str(),
                           against);
    }

    bool TestCase::checkOutput (string source, string against)
    {
        switch (this->option) {
        case EXACT:
            if (source == against) {
                return true;
            }
            else {
                stringstream nomatch;
                nomatch << TCPPStr::APOS << source << TCPPStr::APOS;
                nomatch << TCPPStr::_NEQUIV_ << TCPPStr::APOS;
                nomatch << against << TCPPStr::APOS;

                if (this->clogOriginal != nullptr) {
                    ostream tmp(this->clogOriginal.get());
                    tmp << nomatch.str() << endl;
                    tmp.flush();
                }
                else {
                    clog << nomatch.str() << endl;
                }

                return false;
            }

        case CONTAINS:
            if (Util::stringContains(source, against)) {
                return true;
            }
            else {
                stringstream nomatch;
                nomatch << TCPPStr::APOS << source << TCPPStr::APOS;
                nomatch << TCPPStr::_NCONTAIN_ << TCPPStr::APOS;
                nomatch << against << TCPPStr::APOS;

                if (this->clogOriginal != nullptr) {
                    ostream tmp(this->clogOriginal.get());
                    tmp << nomatch.str() << endl;
                    tmp.flush();
                }
                else {
                    clog << nomatch.str() << endl;
                }

                return false;
            }

        default:
            stringstream re;
            re << TCPPStr::UNK_CMP_OPT_ << this->option;
            throw TestCPPException(re.str());
        }
    }
}
