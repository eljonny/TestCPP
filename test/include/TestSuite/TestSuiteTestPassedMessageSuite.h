#ifndef TESTCPP_TESTSUITE_TESTPASSEDMESSAGE_SUITE_
#define TESTCPP_TESTSUITE_TESTPASSEDMESSAGE_SUITE_

#include "TestCPP.h"
#include "TestSuiteTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteSuites {
            TestSuite testPassedMessageSuite(
                "TestCPP TestSuite Tests - Test Passed Message enable/disable",

                make_tuple(
                    "Suite enable test passed message - no tests",
                    function<void()>(
                   TestSuiteTests::TestEnableTestPassedMessageNoTests
                    )
                ),
                make_tuple(
                    "Suite enable test passed message - one test",
                    function<void()>(
                   TestSuiteTests::TestEnableTestPassedMessageOneTest
                    )
                ),
                make_tuple(
                    "Suite enable test passed message - many tests",
                    function<void()>(
                   TestSuiteTests::TestEnableTestPassedMessageManyTests
                    )
                ),
                make_tuple(
                    "Suite disable test passed message - no tests",
                    function<void()>(
                   TestSuiteTests::TestDisableTestPassedMessageNoTests
                    )
                ),
                make_tuple(
                    "Suite disable test passed message - one test",
                    function<void()>(
                   TestSuiteTests::TestDisableTestPassedMessageOneTest
                    )
                ),
                make_tuple(
                    "Suite disable test passed message - many tests",
                    function<void()>(
                   TestSuiteTests::TestDisableTestPassedMessageManyTests
                    )
                )
            );
        }
    }
}

#endif
