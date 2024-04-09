#ifndef TESTCPP_TESTSUITE_SUITE_
#define TESTCPP_TESTSUITE_SUITE_

#include "TestSuiteTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteSuite {
            TestSuite suite(
                "TestCPP TestSuite Tests",

                make_tuple(
                    "Suite construction Test",
                    function<void()>(TestSuiteTests::TestConstructSuite)
                ),
                make_tuple(
                    "assertNull Test",
                    function<void()>(TestSuiteTests::TestAssertNull)
                ),
                make_tuple(
                    "assertNotNull Test",
                    function<void()>(TestSuiteTests::TestAssertNotNull)
                ),
                make_tuple(
                    "assertTrue Test",
                    function<void()>(TestSuiteTests::TestAssertTrue)
                ),
                make_tuple(
                    "assertFalse Test",
                    function<void()>(TestSuiteTests::TestAssertFalse)
                )
            );
        }
    }
}

#endif
