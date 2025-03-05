#ifndef TESTCPP_ASSERTIONS_TESTS_
#define TESTCPP_ASSERTIONS_TESTS_

namespace TestCPP {
    namespace Testing {
        namespace AssertionsTests {
            void TestAssertEquals ();
            void TestAssertEqualsNotEqual ();
            void TestAssertEqualsCStrings ();
            void TestAssertEqualsCStringsNotEqual ();
            void TestAssertNotEquals ();
            void TestAssertNotEqualsEqual ();
            void TestAssertNotEqualsCStrings ();
            void TestAssertNotEqualsCStringsEqual ();
            void TestAssertNull ();
            void TestAssertNullNotNull ();
            void TestAssertNotNull ();
            void TestAssertNotNullNull ();
            void TestAssertThrows ();
            void TestAssertThrowsDoesNotThrow ();
            void TestAssertNoThrows ();
            void TestAssertNoThrowsThrows ();
            void TestAssertTrue ();
            void TestAssertTrueNotTrue ();
            void TestAssertFalse ();
            void TestAssertFalseNotFalse ();
            void TestFail ();
        }
    }
}

#endif
