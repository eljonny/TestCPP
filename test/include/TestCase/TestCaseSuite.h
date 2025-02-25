#ifndef TESTCPP_TESTCASE_TEST_SUITE_
#define TESTCPP_TESTCASE_TEST_SUITE_

#include "TestCaseTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestCaseSuite {
            TestSuite suite(
                "TestCPP TestCase Tests",

                make_tuple(
                    "Case construction Test",
                    function<void()>(TestCaseTests::TestConstructCase)
                ),
                make_tuple(
                    "Case runner Test",
                    function<void()>(TestCaseTests::TestTestCaseGo)
                ),
                make_tuple(
                    "Case runner Test - string thrown",
                    function<void()>(
                        TestCaseTests::TestTestCaseGoThrowStr
                    )
                ),
                make_tuple(
                    "Case runner Test - char thrown",
                    function<void()>(
                        TestCaseTests::TestTestCaseGoThrowChr
                    )
                ),
                make_tuple(
                    "Case runner Test - test catchall",
                    function<void()>(
                        TestCaseTests::TestTestCaseGoThrowInt
                    )
                ),
                make_tuple(
                    "Case setNotifyPassed Test",
                    function<void()>(
                        TestCaseTests::TestTestCaseSetNotifyPassed
                    )
                ),
                make_tuple(
                    "Case checkStdout Test",
                    function<void()>(
                        TestCaseTests::TestTestCaseCheckStdout
                    )
                ),
                make_tuple(
                    "Case checkStderr Test",
                    function<void()>(
                        TestCaseTests::TestTestCaseCheckStderr
                    )
                )
            );
        }
    }
}

#endif
