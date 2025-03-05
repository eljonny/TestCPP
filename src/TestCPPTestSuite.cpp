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

#include "internal/TestCPPCommon.h"
#include "internal/TestCPPTestCase.h"
#include "internal/TestCPPTestSuite.h"

using std::cerr;
using std::clog;
using std::cout;
using std::endl;
using std::exception;
using std::fixed;
using std::function;
using std::invalid_argument;
using std::ostream;
using std::rethrow_exception;
using std::runtime_error;
using std::setprecision;
using std::string;
using std::tuple;

using TCPPNum = TestCPP::TestCPPCommon::Nums;
using TCPPStr = TestCPP::TestCPPCommon::Strings;

namespace TestCPP {

    void TestSuite::enableTestPassedMessage () {
        this->testSuitePassedMessage = true;
        for (unsigned i = 0; i < this->tests.size(); i += 1) {
            this->tests[i].setNotifyPassed(true);
        }
    }
    void TestSuite::disableTestPassedMessage () {
        this->testSuitePassedMessage = false;
        for (unsigned i = 0; i < this->tests.size(); i += 1) {
            this->tests[i].setNotifyPassed(false);
        }
    }

    void TestSuite::setSuiteName (TestObjName&& testSuiteName) {
        this->suiteName = std::move(testSuiteName);
    }

    unsigned TestSuite::getLastRunFailCount () {
        return this->lastRunFailCount;
    }

    void TestSuite::run () {
        if (this->tests.size() == 0) {
            clog << TCPPStr::NTR << endl;
            return;
        }

        if (!this->firstRun) {
            this->lastRunSucceeded = true;
            this->lastRunFailCount = 0;
            this->lastRunSuccessCount = 0;
            this->totalRuntime = 0;
        }
        else {
            this->firstRun = false;
        }

        clog << endl
             << TCPPStr::START_RUN << TCPPStr::SUITE
             << TCPPStr::APOS << this->suiteName << TCPPStr::APOS
             << endl
             << endl;

        for (TestCase test : this->tests) {
            bool testPassed = false;
            try {
                testPassed = test.go();
            }
            catch (exception& e) {
                clog << TCPPStr::TEST_EXC << e.what()
                     << endl;
            }
            catch (...) {
                cerr << TCPPStr::UNK_EXC
                     << endl;
            }

            if (!testPassed) {
                this->lastRunFailCount++;

                if (this->lastRunSucceeded) {
                    this->lastRunSucceeded = false;
                }
            }
            else {
                this->lastRunSuccessCount++;
            }

            this->totalRuntime += test.getLastRuntime();
        }

        clog << endl;

        if (this->testSuitePassedMessage &&
            this->lastRunFailCount == 0) {
            clog << TCPPStr::ALL << TCPPStr::APOS << this->suiteName
                 << TCPPStr::APOS << TCPPStr::SUITE_TESTS_PASSED
                 << endl;
        }

        double suiteRuntimeElapsed = static_cast<double>(
            this->totalRuntime)/TCPPNum::NANOS_IN_SEC;

        clog << fixed;
        clog << setprecision(0);
        clog << TCPPStr::FINISHED_SUITE << TCPPStr::APOS
             << this->suiteName << TCPPStr::APOS << TCPPStr::IN_ABOUT
             << suiteRuntimeElapsed << TCPPStr::SEC << TCPPStr::SP
             << TCPPStr::PARENL << this->lastRunSuccessCount
             << TCPPStr::FWSL << this->tests.size() << TCPPStr::PASSED
             << TCPPStr::PARENR
             << endl;
    }

    /**
     * @brief Add a test to this test suite.
     *
     * The test should be a TestCase object.
     */
    template<>
    void TestSuite::addTest (TestCase&& test) {
        this->tests.emplace_back(test);
    }

    /**
     * @brief Add a test to this test suite.
     *
     * The test should be defined as a tuple with 2 elements to use
     *  this. The first element is the test name, and the second
     *  element is the test function that defines the test.
     */
    template<>
    void TestSuite::addTest (tuple<const char *, function<void()>>&&
                             test)
    {
        this->tests.emplace_back(
            std::get<0>(test),
            std::get<1>(test),
            this->testSuitePassedMessage
        );
    }
}
