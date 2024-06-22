#ifndef TESTCPP_TESTSUITE_SUITE_
#define TESTCPP_TESTSUITE_SUITE_

#include "TestSuiteTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteSuite {
            TestSuite suite(
                "TestCPP TestSuite Tests",

                make_tuple(
                    "Suite construction Test - no tests",
                    function<void()>(
                   TestSuiteTests::TestConstructSuiteBare
                    )
                ),
                make_tuple(
                    "Suite construction Test - TestCases",
                    function<void()>(
                   TestSuiteTests::TestConstructSuiteTestCases
                    )
                ),
                make_tuple(
                    "Suite construction Test - tuples",
                    function<void()>(
                   TestSuiteTests::TestConstructSuiteTuples
                    )
                ),
                make_tuple(
                    "Suite construction Test - mixed",
                    function<void()>(
                   TestSuiteTests::TestConstructSuiteMixed
                    )
                ),
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
