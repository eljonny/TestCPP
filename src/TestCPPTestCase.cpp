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
using TestCPP::Util::no_destroy;

using std::cerr;
using std::clog;
using std::cout;
using std::endl;
using std::exception;
using std::fixed;
using std::function;
using std::invalid_argument;
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

    no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>
        TestCase::stdoutBuffer =
        no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>(
            unique_ptr<stringstream, void(*)(stringstream*)>(
                nullptr, [](stringstream*){}
            )
        );
    no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>
        TestCase::clogBuffer =
        no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>(
            unique_ptr<stringstream, void(*)(stringstream*)>(
                nullptr, [](stringstream*){}
            )
        );
    no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>
        TestCase::stderrBuffer =
        no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>(
            unique_ptr<stringstream, void(*)(stringstream*)>(
                nullptr, [](stringstream*){}
            )
        );
    no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>
        TestCase::stdoutOriginal =
        no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>(
            unique_ptr<streambuf, void(*)(streambuf*)>(
                nullptr, [](streambuf*){}
            )
        );
    no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>
        TestCase::clogOriginal =
        no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>(
            unique_ptr<streambuf, void(*)(streambuf*)>(
                nullptr, [](streambuf*){}
            )
        );
    no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>
        TestCase::stderrOriginal =
        no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>(
            unique_ptr<streambuf, void(*)(streambuf*)>(
                nullptr, [](streambuf*){}
            )
        );

    TestCase::TestCase (TestObjName&& name,
                        function<void()> testFn,
                        bool testPassedMessage,
                        bool captureOut, bool captureLog,
                        bool captureErr,
                        TestCase::TestCaseOutCompareOptions opt)
    {
        this->notifyTestPassed = testPassedMessage;

        this->test = std::move(testFn);
        this->testName = std::move(name);

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

    TestCase::TestCase (const TestCase& o) {
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

    TestCase::TestCase (TestCase&& o) noexcept {
        this->option = std::move(o.option);

        this->setNotifyPassed(std::move(o.notifyTestPassed));

        this->pass = std::move(o.pass);
        this->lastRunTime = std::move(o.lastRunTime);

        this->stdoutCaptured = std::move(o.stdoutCaptured);
        this->clogCaptured = std::move(o.clogCaptured);
        this->stderrCaptured = std::move(o.stderrCaptured);

        if (this->stdoutCaptured) {
            captureStdout();
        }
        if (this->clogCaptured) {
            captureClog();
        }
        if (this->stderrCaptured) {
            captureStdErr();
        }

        this->testName = std::move(o.testName);
        this->test = std::move(o.test);
    }

    TestCase::~TestCase () {
        if (TestCase::stdoutBuffer.get() != nullptr)
        {
            if (TestCase::stdoutCaptureCasesDestroyed ==
                TestCase::stdoutCaptureCasesConstructed - 1)
            {
                cout.rdbuf(TestCase::stdoutOriginal.get().release());
                TestCase::stdoutBuffer.get() = nullptr;
            }

            TestCase::stdoutCaptureCasesDestroyed += 1;
        }
        if (TestCase::clogBuffer.get() != nullptr)
        {
            if (TestCase::logCaptureCasesDestroyed ==
                TestCase::logCaptureCasesConstructed - 1)
            {
                clog.rdbuf(TestCase::clogOriginal.get().release());
                TestCase::clogBuffer.get() = nullptr;
            }

            TestCase::logCaptureCasesDestroyed += 1;
        }
        if (TestCase::stderrBuffer.get() != nullptr)
        {
            if (TestCase::stderrCaptureCasesDestroyed ==
                TestCase::stderrCaptureCasesConstructed - 1)
            {
                cerr.rdbuf(TestCase::stderrOriginal.get().release());
                TestCase::stderrBuffer.get() = nullptr;
            }

            TestCase::stderrCaptureCasesDestroyed += 1;
        }
    }

    TestCase& TestCase::operator= (const TestCase& rhs) {
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

    TestCase& TestCase::operator= (TestCase&& rhs) noexcept {
        this->option = std::move(rhs.option);

        this->setNotifyPassed(std::move(rhs.notifyTestPassed));

        this->pass = std::move(rhs.pass);
        this->lastRunTime = std::move(rhs.lastRunTime);

        this->stdoutCaptured = std::move(rhs.stdoutCaptured);
        this->clogCaptured = std::move(rhs.clogCaptured);
        this->stderrCaptured = std::move(rhs.stderrCaptured);

        if (this->stdoutCaptured) {
            captureStdout();
        }
        if (this->clogCaptured) {
            captureClog();
        }
        if (this->stderrCaptured) {
            captureStdErr();
        }

        this->testName = std::move(rhs.testName);
        this->test = std::move(rhs.test);

        return *this;
    }

    long long TestCase::getLastRuntime () const {
        return this->lastRunTime;
    }

    void TestCase::logFailure(ostream& out, const string& failureReason) const {
        out << fixed;
        out << setprecision(TCPPNum::TIME_PRECISION);
        out << TCPPStr::TEST << this->testName << TCPPStr::FAIL
            << TCPPStr::PARENL
            << static_cast<double>(this->lastRunTime)/
               TCPPNum::NANOS_IN_SEC
            << TCPPStr::SEC << TCPPStr::PARENR
            << endl;
        out << TCPPStr::REASON_ << failureReason << endl;
    }

    void TestCase::logTestFailure (const string& failureReason) {
        unique_ptr<ostream> logStream = nullptr;

        if (this->clogOriginal.get() != nullptr) {
            logStream = unique_ptr<ostream>(
                new ostream(this->clogOriginal.get().get())
            );
        }
        else {
            logStream = unique_ptr<ostream>(&clog);
        }

        logFailure(*logStream, failureReason);

        if (this->clogOriginal.get() != nullptr) {
            logStream->flush();

            // If someone is looking for something in the message,
            //  and it's captured, make sure it's there.
            logFailure(clog, failureReason);
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
            clog << TCPPStr::TEST << this->testName << TCPPStr::PASS
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

    void TestCase::setNotifyPassed (bool shouldNotify) {
        this->notifyTestPassed = shouldNotify;
    }

    void TestCase::captureStdout () {
        if (TestCase::stdoutCaptureCasesConstructed ==
            TestCase::stdoutCaptureCasesDestroyed)
        {
            TestCase::stdoutCaptureCasesConstructed += 1;
            TestCase::stdoutBuffer =
                no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>(
                    unique_ptr<stringstream, void(*)(stringstream*)>(
                        new stringstream(), [](stringstream *) {}
                    )
                );
            TestCase::stdoutOriginal =
                no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>(
                    unique_ptr<streambuf, void(*)(streambuf*)>(
                        cout.rdbuf(), [](streambuf *) {}
                    )
                );
            cout.rdbuf(TestCase::stdoutBuffer.get()->rdbuf());
        }
        else {
            TestCase::stdoutCaptureCasesConstructed += 1;
        }
    }

    void TestCase::captureClog () {
        if (TestCase::logCaptureCasesConstructed ==
            TestCase::logCaptureCasesDestroyed)
        {
            TestCase::logCaptureCasesConstructed += 1;
            TestCase::clogBuffer =
                no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>(
                    unique_ptr<stringstream, void(*)(stringstream*)>(
                        new stringstream(), [](stringstream *) {}
                    )
                );
            TestCase::clogOriginal =
                no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>(
                    unique_ptr<streambuf, void(*)(streambuf*)>(
                        clog.rdbuf(), [](streambuf *) {}
                    )
                );
            clog.rdbuf(TestCase::clogBuffer.get()->rdbuf());
        }
        else {
            TestCase::logCaptureCasesConstructed += 1;
        }
    }

    void TestCase::captureStdErr () {
        if (TestCase::stderrCaptureCasesConstructed ==
            TestCase::stderrCaptureCasesDestroyed)
        {
            TestCase::stderrCaptureCasesConstructed += 1;
            TestCase::stderrBuffer =
                no_destroy<unique_ptr<stringstream, void(*)(stringstream*)>>(
                    unique_ptr<stringstream, void(*)(stringstream*)>(
                        new stringstream(), [](stringstream *) {}
                    )
                );
            TestCase::stderrOriginal =
                no_destroy<unique_ptr<streambuf, void(*)(streambuf*)>>(
                    unique_ptr<streambuf, void(*)(streambuf*)>(
                        cerr.rdbuf(), [](streambuf *) {}
                    )
                );
            cerr.rdbuf(TestCase::stderrBuffer.get()->rdbuf());
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
            error << TCPPStr::UNK_OPT << opt;
            throw TestCPPException(error.str());
        }
    }

    void TestCase::clearStdoutCapture () {
        if (TestCase::stdoutBuffer.get()) {
            TestCase::stdoutBuffer.get()->str(string());
        }
    }

    void TestCase::clearLogCapture () {
        if (TestCase::clogBuffer.get()) {
            TestCase::clogBuffer.get()->str(string());
        }
    }

    void TestCase::clearStderrCapture () {
        if (TestCase::stderrBuffer.get()) {
            TestCase::stderrBuffer.get()->str(string());
        }
    }

    bool TestCase::checkStdout (const string& against) {
        return checkOutput(TestCase::stdoutBuffer.get()->str(),
                           against);
    }

    bool TestCase::checkLog (const string& against) {
        return checkOutput(TestCase::clogBuffer.get()->str(),
                           against);
    }

    bool TestCase::checkStderr (const string& against) {
        return checkOutput(TestCase::stderrBuffer.get()->str(),
                           against);
    }

    bool TestCase::checkOutput (const string& source, const string& against)
    {
        switch (this->option) {
        case EXACT:
            if (source == against) {
                return true;
            }
            else {
                stringstream nomatch;
                nomatch << TCPPStr::APOS << source << TCPPStr::APOS;
                nomatch << TCPPStr::NEQUIV << TCPPStr::APOS;
                nomatch << against << TCPPStr::APOS;

                if (this->clogOriginal.get() != nullptr) {
                    ostream tmp(this->clogOriginal.get().get());
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
                nomatch << TCPPStr::NCONTAIN << TCPPStr::APOS;
                nomatch << against << TCPPStr::APOS;

                if (this->clogOriginal.get() != nullptr) {
                    ostream tmp(this->clogOriginal.get().get());
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
            re << TCPPStr::UNK_CMP_OPT << this->option;
            throw TestCPPException(re.str());
        }
    }
}
