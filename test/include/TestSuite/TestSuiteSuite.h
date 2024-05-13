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
                )
            );
        }
    }
}

#endif
