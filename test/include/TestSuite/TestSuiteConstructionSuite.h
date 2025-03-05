#ifndef TESTCPP_TESTSUITE_CONSTRUCTION_SUITE_
#define TESTCPP_TESTSUITE_CONSTRUCTION_SUITE_

#include "TestCPP.h"
#include "TestSuiteTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteSuites {
            TestSuite ctorSuite(
                "TestCPP TestSuite Tests - Construction",

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
                )
            );
        }
    }
}

#endif
