#ifndef TESTCPP_TESTSUITE_SUITERUN_SUITE_
#define TESTCPP_TESTSUITE_SUITERUN_SUITE_

#include "TestCPP.h"
#include "TestSuiteTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteSuites {
            TestSuite runSuite(
                "TestCPP TestSuite Tests - Suite Running",

                make_tuple(
                    "Suite run test - no tests",
                    function<void()>(
                        TestSuiteTests::TestSuiteRunNoTests
                    )
                ),
                make_tuple(
                    "Suite run test - one test",
                    function<void()>(
                        TestSuiteTests::TestSuiteRunOneTest
                    )
                ),
                make_tuple(
                    "Suite run test - many tests",
                    function<void()>(
                        TestSuiteTests::TestSuiteRunManyTests
                    )
                ),
                make_tuple(
                    "Suite run test - no tests twice",
                    function<void()>(
                        TestSuiteTests::TestSuiteRunNoTestsTwice
                    )
                ),
                make_tuple(
                    "Suite run test - one test twice",
                    function<void()>(
                        TestSuiteTests::TestSuiteRunOneTestTwice
                    )
                ),
                make_tuple(
                    "Suite run test - many tests twice",
                    function<void()>(
                        TestSuiteTests::TestSuiteRunManyTestsTwice
                    )
                )
            );
        }
    }
}

#endif
