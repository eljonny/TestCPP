#ifndef TESTCPP_TESTSUITE_TESTS_
#define TESTCPP_TESTSUITE_TESTS_

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteTests {
            void TestConstructSuiteBare ();
            void TestConstructSuiteTestCases ();
            void TestConstructSuiteTuples ();
            void TestConstructSuiteMixed ();
            void TestEnableTestPassedMessageNoTests ();
            void TestEnableTestPassedMessageOneTest ();
            void TestEnableTestPassedMessageManyTests ();
            void TestDisableTestPassedMessageNoTests ();
            void TestDisableTestPassedMessageOneTest ();
            void TestDisableTestPassedMessageManyTests ();
        }
    }
}

#endif
