#ifndef TESTCPP_ASSERTIONS_SUITE_
#define TESTCPP_ASSERTIONS_SUITE_

#include "AssertionsTests.h"

namespace TestCPP {
    namespace Testing {
        namespace AssertionsSuite {
            TestSuite suite(
                "TestCPP Assertions Tests",

                make_tuple(
                    "assertNull Test",
                    function<void()>(AssertionsTests::TestAssertNull)
                ),
                make_tuple(
                    "assertNotNull Test",
                    function<void()>(AssertionsTests::TestAssertNotNull)
                ),
                make_tuple(
                    "assertTrue Test",
                    function<void()>(AssertionsTests::TestAssertTrue)
                ),
                make_tuple(
                    "assertFalse Test",
                    function<void()>(AssertionsTests::TestAssertFalse)
                )
            );
        }
    }
}

#endif
