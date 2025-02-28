#ifndef TESTCPP_ASSERTIONS_SUITE_
#define TESTCPP_ASSERTIONS_SUITE_

#include "BasicAssertionsTests.h"

namespace TestCPP {
    namespace Testing {
        namespace AssertionsSuites {
            TestSuite basicSuite(
                "TestCPP Basic Assertions Tests",

                make_tuple(
                    "Basic Assertion - assertEquals Test",
                    function<void()>(AssertionsTests::TestAssertEquals)
                ),
                make_tuple(
                    "Basic Assertion - assertEquals Not Equal Test",
                    function<void()>(AssertionsTests::TestAssertEqualsNotEqual)
                ),
                make_tuple(
                    "Basic Assertion - assertEquals C Strings Test",
                    function<void()>(AssertionsTests::TestAssertEqualsCStrings)
                ),
                make_tuple(
                    "Basic Assertion - assertEquals C Strings Not Equal Test",
                    function<void()>(AssertionsTests::TestAssertEqualsCStringsNotEqual)
                ),
                make_tuple(
                    "Basic Assertion - assertNotEquals Test",
                    function<void()>(AssertionsTests::TestAssertNotEquals)
                ),
                make_tuple(
                    "Basic Assertion - assertNotEquals Equal Test",
                    function<void()>(AssertionsTests::TestAssertNotEqualsEqual)
                ),
                make_tuple(
                    "Basic Assertion - assertNotEquals C Strings Test",
                    function<void()>(AssertionsTests::TestAssertNotEqualsCStrings)
                ),
                make_tuple(
                    "Basic Assertion - assertNotEquals C Strings Equal Test",
                    function<void()>(AssertionsTests::TestAssertNotEqualsCStringsEqual)
                ),
                make_tuple(
                    "Basic Assertion - assertNull Test",
                    function<void()>(AssertionsTests::TestAssertNull)
                ),
                make_tuple(
                    "Basic Assertion - assertNull not null Test",
                    function<void()>(AssertionsTests::TestAssertNullNotNull)
                ),
                make_tuple(
                    "Basic Assertion - assertNotNull Test",
                    function<void()>(AssertionsTests::TestAssertNotNull)
                ),
                make_tuple(
                    "Basic Assertion - assertNotNull null Test",
                    function<void()>(AssertionsTests::TestAssertNotNullNull)
                ),
                make_tuple(
                    "Basic Assertion - assertThrows Test",
                    function<void()>(AssertionsTests::TestAssertThrows)
                ),
                make_tuple(
                    "Basic Assertion - assertThrows Does Not Throw Test",
                    function<void()>(AssertionsTests::TestAssertThrowsDoesNotThrow)
                ),
                make_tuple(
                    "Basic Assertion - assertNoThrows Test",
                    function<void()>(AssertionsTests::TestAssertNoThrows)
                ),
                make_tuple(
                    "Basic Assertion - assertNoThrows Throws Test",
                    function<void()>(AssertionsTests::TestAssertNoThrowsThrows)
                ),
                make_tuple(
                    "Basic Assertion - assertTrue Test",
                    function<void()>(AssertionsTests::TestAssertTrue)
                ),
                make_tuple(
                    "Basic Assertion - assertTrue not true Test",
                    function<void()>(AssertionsTests::TestAssertTrueNotTrue)
                ),
                make_tuple(
                    "Basic Assertion - assertFalse Test",
                    function<void()>(AssertionsTests::TestAssertFalse)
                ),
                make_tuple(
                    "Basic Assertion - assertFalse not false Test",
                    function<void()>(AssertionsTests::TestAssertFalseNotFalse)
                ),
                make_tuple(
                    "Basic Assertion - fail Test",
                    function<void()>(AssertionsTests::TestFail)
                )
            );
        }
    }
}

#endif
