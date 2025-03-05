#include "TestCPP.h"
#include "TestSuite/TestSuiteTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteTests {
            unsigned zero = 0;
            unsigned one = 1;
            unsigned three = 3;

            void TestSuiteRunNoTests() {
                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite run - no tests"
                ));

                testSuite->run();
                Assertions::assertEquals(zero,
                    testSuite->getLastRunFailCount());
                Assertions::assertEquals(zero,
                    testSuite->getLastRunSuccessCount());
            }
            void TestSuiteRunOneTest() {
                TestCase test1("dummy 1", []() {});

                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite run - one test",
                    test1
                ));

                testSuite->run();
                Assertions::assertEquals(zero,
                    testSuite->getLastRunFailCount());
                Assertions::assertEquals(one,
                    testSuite->getLastRunSuccessCount());
            }
            void TestSuiteRunManyTests() {
                TestCase test1("dummy 1", []() {}),
                         test2("dummy 2", []() {}),
                         test3("dummy 3", []() {});

                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite run - many tests",
                    test1, test2, test3
                ));

                testSuite->run();
                Assertions::assertEquals(zero,
                    testSuite->getLastRunFailCount());
                Assertions::assertEquals(three,
                    testSuite->getLastRunSuccessCount());
            }

            void TestSuiteRunNoTestsTwice() {
                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite double run - no tests"
                ));

                testSuite->run();
                Assertions::assertEquals(zero,
                    testSuite->getLastRunFailCount());
                Assertions::assertEquals(zero,
                    testSuite->getLastRunSuccessCount());

                testSuite->run();
                Assertions::assertEquals(zero,
                    testSuite->getLastRunFailCount());
                Assertions::assertEquals(zero,
                    testSuite->getLastRunSuccessCount());
            }
            void TestSuiteRunOneTestTwice() {
                TestCase test1("dummy 1", []() {});

                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite double run - one test",
                    test1
                ));

                testSuite->run();
                Assertions::assertEquals(zero,
                    testSuite->getLastRunFailCount());
                Assertions::assertEquals(one,
                    testSuite->getLastRunSuccessCount());

                testSuite->run();
                Assertions::assertEquals(zero,
                    testSuite->getLastRunFailCount());
                Assertions::assertEquals(one,
                    testSuite->getLastRunSuccessCount());
            }
            void TestSuiteRunManyTestsTwice() {
                TestCase test1("dummy 1", []() {}),
                         test2("dummy 2", []() {}),
                         test3("dummy 3", []() {});

                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite double run - many tests",
                    test1, test2, test3
                ));

                testSuite->run();
                Assertions::assertEquals(zero,
                    testSuite->getLastRunFailCount());
                Assertions::assertEquals(three,
                    testSuite->getLastRunSuccessCount());

                testSuite->run();
                Assertions::assertEquals(zero,
                    testSuite->getLastRunFailCount());
                Assertions::assertEquals(three,
                    testSuite->getLastRunSuccessCount());
            }
        }
    }
}
