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

#include "Test.h"

using std::tuple;
using std::function;
using std::string;
using std::runtime_error;
using std::exception;
using std::clog;
using std::cerr;
using std::endl;
using std::ostringstream;

namespace TestCPP {
    TestCase::TestCase(string name, function<void()> test, bool msg) {
        this->notifyTestPassed = msg;
        this->test = test;
        this->testName = name;
    }

    unsigned long long TestCase::getLastRuntime() {
        return this->lastRunTime;
    }

    bool TestCase::go() {
        try {
            this->lastRunTime = TestCase::duration(this->test).count();
            if(this->notifyTestPassed) {
                clog << "Test " << this->testName << " passed! ("
                        << static_cast<double>(this->lastRunTime)
                            /1000000000.0 << "s)" << endl;
            }
            this->pass = true;
            return true;
        }
        catch(string errorMessage) {
            this->pass = false;
            cerr << "Test " << this->testName << " failed!" << endl;
            cerr << "Reason: " << errorMessage << endl;
            return false;
        }
        catch(runtime_error& re) {
            this->pass = false;
            cerr << "Test " << this->testName << " failed!" << endl;
            cerr << "Reason: " << re.what() << endl;
            return false;
        }
        catch(exception& e) {
            this->pass = false;
            cerr << "Test " << this->testName << " failed!" << endl;
            cerr << "Reason: " << e.what() << endl;
            return false;
        }
    }

    void TestCase::setNotifyPassed(bool notify) {
        this->notifyTestPassed = notify;
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
        this->suiteName = string(" ") + testSuiteName;
    }

    string TestSuite::getRegExpErrorString(
            std::regex_constants::error_type errType
        )
    {
        switch(errType) {
        case std::regex_constants::error_collate:
            return string("The expression contained an invalid collating element name.");
        case std::regex_constants::error_ctype:
            return string("The expression contained an invalid character class name.");
        case std::regex_constants::error_escape:
            return string("The expression contained an invalid escaped character, or a trailing escape.");
        case std::regex_constants::error_backref:
            return string("The expression contained an invalid back reference.");
        case std::regex_constants::error_brack:
            return string("The expression contained mismatched brackets ([ and ]).");
        case std::regex_constants::error_paren:
            return string("The expression contained mismatched parentheses (( and )).");
        case std::regex_constants::error_brace:
            return string("The expression contained mismatched braces ({ and }).");
        case std::regex_constants::error_badbrace:
            return string("The expression contained an invalid range between braces ({ and }).");
        case std::regex_constants::error_range:
            return string("The expression contained an invalid character range.");
        case std::regex_constants::error_space:
            return string("There was insufficient memory to convert the expression info a finite state machine.");
        case std::regex_constants::error_badrepeat:
            return string("The expression contained a repeat specifier (one of *?+{) that was not preceded by a valid regular expression.");
        case std::regex_constants::error_complexity:
            return string("The complexity of an attempted match against a regular expression exceeded a pre-set level.");
        case std::regex_constants::error_stack:
            return string("There was insufficient memory to determine whether the regular expression could match the specified character sequence.");
        default: return string("Unknown regex error");
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
            clog << "All" << this->suiteName
                << " suite tests passed!!! :)"
                << endl;
        }

        double suiteRuntimeElapsed = static_cast<double>(this->totalRuntime)/1000000000.0;
        clog << "Finished running suite" << this->suiteName << " in "
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

    void TestSuite::assertTrue(
            bool condition,
            string failureMessage
        )
    {
        if(!condition) {
            ostringstream err;

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
            ostringstream err;

            err << "Boolean False assertion failed!" << std::endl;
            err << failureMessage << std::endl;

            throw err.str();
        }
    }

    void TestSuite::fail(string failureMessage) {
        throw failureMessage;
    }
}
