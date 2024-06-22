#include "TestCPP.h"
#include "TestSuite/TestSuiteTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteTests {
            void TestConstructSuiteBare () {
                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - bare"
                ));
            }
            void TestConstructSuiteTestCases () {
                TestCase test1("dummy 1", [](){}),
                         test2("dummy 2", [](){});

                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - TestCases",
                    test1
                ));
                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - TestCases",
                    test1, test2
                ));
            }
            void TestConstructSuiteTuples () {
                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - tuples",
                    make_tuple("dummy 1", function<void()>([](){}))
                ));
                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - tuples",
                    make_tuple("dummy 1", function<void()>([](){})),
                    make_tuple("dummy 2", function<void()>([](){}))
                ));
            }
            void TestConstructSuiteMixed () {
                TestCase test1("dummy 1", [](){}),
                         test2("dummy 2", [](){});
                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - mixed",
                    test1,
                    make_tuple("dummy 1", function<void()>([](){}))
                ));
                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - mixed",
                    test1, test2,
                    make_tuple("dummy 1", function<void()>([](){}))
                ));
                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - mixed",
                    test1,
                    make_tuple("dummy 1", function<void()>([](){})),
                    make_tuple("dummy 2", function<void()>([](){}))
                ));
                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - mixed",
                    test1, test2,
                    make_tuple("dummy 1", function<void()>([](){})),
                    make_tuple("dummy 2", function<void()>([](){}))
                ));
                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - mixed",
                    test1,
                    make_tuple("dummy 1", function<void()>([](){})),
                    make_tuple("dummy 2", function<void()>([](){})),
                    test2
                ));
                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - mixed",
                    make_tuple("dummy 1", function<void()>([](){})),
                    test1, test2,
                    make_tuple("dummy 2", function<void()>([](){}))
                ));
                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - mixed",
                    test1,
                    make_tuple("dummy 1", function<void()>([](){})),
                    test2,
                    make_tuple("dummy 2", function<void()>([](){}))
                ));
                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction - mixed",
                    make_tuple("dummy 1", function<void()>([](){})),
                    test2,
                    make_tuple("dummy 2", function<void()>([](){})),
                    test1
                ));
            }

            void TestEnableTestPassedMessageNoTests() {
                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "SUBSUITE - Test Passed Message Enabled - no tests"
                ));
                testSuite->enableTestPassedMessage();
                testSuite->run();
            }
            void TestEnableTestPassedMessageOneTest() {
                const char * suiteName =
                    "SUBSUITE - Test Passed Message Enabled - one test";
                const char * testName =
                    "SUBTEST - enable test passed message dummy 1";

                TestCase test(
                    testName,
                    [](){},
                    false,
                    false,
                    true,
                    false
                );

                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    suiteName, test
                ));

                testSuite->enableTestPassedMessage();
                testSuite->run();

                stringstream tsLog;
                tsLog << "All '";
                tsLog << suiteName;
                tsLog << "' suite tests passed!";

                stringstream tcLog;
                tcLog << "Test ";
                tcLog << testName;
                tcLog << " passed! (";

                string secondsParen = "s)";

                Assertions::assertTrue(
                    test.checkLog(tcLog.str()),
                    "Should have notified on test passage! 1"
                );
                Assertions::assertTrue(
                    test.checkLog(secondsParen),
                    "Should have notified on test passage! 2"
                );
                Assertions::assertTrue(
                    test.checkLog(tsLog.str()),
                    "Should have notified on suite passage! 1"
                );

                test.clearLogCapture();

                test = TestCase(
                    testName,
                    [](){},
                    true,
                    false,
                    true,
                    false
                );

                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    suiteName, test
                ));

                testSuite->enableTestPassedMessage();
                testSuite->run();

                Assertions::assertTrue(
                    test.checkLog(tcLog.str()),
                    "Should have notified on test passage! 3"
                );
                Assertions::assertTrue(
                    test.checkLog(secondsParen),
                    "Should have notified on test passage! 4"
                );
                Assertions::assertTrue(
                    test.checkLog(tsLog.str()),
                    "Should have notified on suite passage! 2"
                );
            }
            void TestEnableTestPassedMessageManyTests() {
                const char * suiteName =
                  "SUBSUITE - Test Passed Message Enabled - many tests";
                const char * test1Name =
                  "SUBTEST - enable test passed message dummy 1";
                const char * test2Name =
                  "SUBTEST - enable test passed message dummy 2";
                const char * test3Name =
                  "SUBTEST - enable test passed message dummy 3";

                TestCase test1(
                    test1Name,
                    [](){},
                    false,
                    false,
                    true,
                    false
                );
                TestCase test2(
                    test2Name,
                    [](){},
                    false,
                    false,
                    true,
                    false
                );
                TestCase test3(
                    test3Name,
                    [](){},
                    false,
                    false,
                    true,
                    false
                );

                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    suiteName, test1, test2, test3
                ));
                testSuite->enableTestPassedMessage();
                testSuite->run();

                stringstream tsLog;
                tsLog << "All '";
                tsLog << suiteName;
                tsLog << "' suite tests passed!";

                stringstream tc1Log;
                tc1Log << "Test ";
                tc1Log << test1Name;
                tc1Log << " passed! (";
                stringstream tc2Log;
                tc2Log << "Test ";
                tc2Log << test2Name;
                tc2Log << " passed! (";
                stringstream tc3Log;
                tc3Log << "Test ";
                tc3Log << test3Name;
                tc3Log << " passed! (";

                string secondsParen = "s)";

                Assertions::assertTrue(
                    test1.checkLog(tc1Log.str()),
                    "Should have notified on test passage! 1"
                );
                Assertions::assertTrue(
                    test1.checkLog(tc2Log.str()),
                    "Should have notified on test passage! 2"
                );
                Assertions::assertTrue(
                    test1.checkLog(tc3Log.str()),
                    "Should have notified on test passage! 3"
                );
                Assertions::assertTrue(
                    test1.checkLog(secondsParen),
                    "Should have notified on test passage! 4"
                );
                Assertions::assertTrue(
                    test1.checkLog(tsLog.str()),
                    "Should have notified on suite passage! 1"
                );

                test1.clearLogCapture();

                test1 = TestCase(
                    test1Name,
                    [](){},
                    true,
                    false,
                    true,
                    false
                );
                test2 = TestCase(
                    test2Name,
                    [](){},
                    true,
                    false,
                    true,
                    false
                );
                test3 = TestCase(
                    test3Name,
                    [](){},
                    true,
                    false,
                    true,
                    false
                );

                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    suiteName, test1, test2, test3
                ));

                testSuite->enableTestPassedMessage();
                testSuite->run();

                Assertions::assertTrue(
                    test1.checkLog(tc1Log.str()),
                    "Should have notified on test passage! 5"
                );
                Assertions::assertTrue(
                    test1.checkLog(tc2Log.str()),
                    "Should have notified on test passage! 6"
                );
                Assertions::assertTrue(
                    test1.checkLog(tc3Log.str()),
                    "Should have notified on test passage! 7"
                );
                Assertions::assertTrue(
                    test1.checkLog(secondsParen),
                    "Should have notified on test passage! 8"
                );
                Assertions::assertTrue(
                    test1.checkLog(tsLog.str()),
                    "Should have notified on suite passage! 2"
                );
            }

            void TestDisableTestPassedMessageNoTests() {
                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    "Test Passed Message Disabled - no tests"
                ));
                testSuite->disableTestPassedMessage();
                testSuite->run();
            }
            void TestDisableTestPassedMessageOneTest() {
                const char * suiteName =
                  "SUBSUITE - Test Passed Message Disabled - one test";
                const char * testName =
                  "SUBTEST - disable test passed message dummy 1";

                TestCase test(
                    testName,
                    [](){},
                    false,
                    false,
                    true,
                    false
                );

                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    suiteName, test
                ));

                testSuite->disableTestPassedMessage();
                testSuite->run();

                stringstream tsLog;
                tsLog << "All '";
                tsLog << suiteName;
                tsLog << "' suite tests passed!";

                stringstream tcLog;
                tcLog << "Test ";
                tcLog << testName;
                tcLog << " passed! (";

                string secondsParen = "s)";

                Assertions::assertFalse(
                    test.checkLog(tcLog.str()),
                    "Should not have notified on test passage! 1"
                );
                Assertions::assertFalse(
                    test.checkLog(secondsParen),
                    "Should not have notified on test passage! 2"
                );
                Assertions::assertFalse(
                    test.checkLog(tsLog.str()),
                    "Should not have notified on suite passage! 1"
                );

                test = TestCase(
                    testName,
                    [](){},
                    true,
                    false,
                    true,
                    false
                );

                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    suiteName, test
                ));

                testSuite->disableTestPassedMessage();
                testSuite->run();

                Assertions::assertFalse(
                    test.checkLog(tcLog.str()),
                    "Should not have notified on test passage! 3"
                );
                Assertions::assertFalse(
                    test.checkLog(secondsParen),
                    "Should not have notified on test passage! 4"
                );
                Assertions::assertFalse(
                    test.checkLog(tsLog.str()),
                    "Should not have notified on suite passage! 2"
                );
            }
            void TestDisableTestPassedMessageManyTests() {
                const char * suiteName =
                 "SUBSUITE - Test Passed Message Disabled - many tests";
                const char * test1Name =
                 "SUBTEST - disable test passed message dummy 1";
                const char * test2Name =
                 "SUBTEST - disable test passed message dummy 2";
                const char * test3Name =
                 "SUBTEST - disable test passed message dummy 3";

                TestCase test1(
                    test1Name,
                    [](){},
                    false,
                    false,
                    true,
                    false
                );
                TestCase test2(
                    test2Name,
                    [](){},
                    false,
                    false,
                    true,
                    false
                );
                TestCase test3(
                    test3Name,
                    [](){},
                    false,
                    false,
                    true,
                    false
                );

                auto testSuite = unique_ptr<TestSuite>(new TestSuite(
                    suiteName, test1, test2, test3
                ));
                testSuite->disableTestPassedMessage();
                testSuite->run();

                stringstream tsLog;
                tsLog << "All '";
                tsLog << suiteName;
                tsLog << "' suite tests passed!";

                stringstream tc1Log;
                tc1Log << "Test ";
                tc1Log << test1Name;
                tc1Log << " passed! (";
                stringstream tc2Log;
                tc2Log << "Test ";
                tc2Log << test2Name;
                tc2Log << " passed! (";
                stringstream tc3Log;
                tc3Log << "Test ";
                tc3Log << test3Name;
                tc3Log << " passed! (";

                string secondsParen = "s)";

                Assertions::assertFalse(
                    test1.checkLog(tc1Log.str()),
                    "Should not have notified on test passage! 1"
                );
                Assertions::assertFalse(
                    test1.checkLog(tc2Log.str()),
                    "Should not have notified on test passage! 2"
                );
                Assertions::assertFalse(
                    test1.checkLog(tc3Log.str()),
                    "Should not have notified on test passage! 3"
                );
                Assertions::assertFalse(
                    test1.checkLog(secondsParen),
                    "Should not have notified on test passage! 4"
                );
                Assertions::assertFalse(
                    test1.checkLog(tsLog.str()),
                    "Should not have notified on suite passage! 1"
                );

                test1 = TestCase(
                    test1Name,
                    [](){},
                    true,
                    false,
                    true,
                    false
                );
                test2 = TestCase(
                    test2Name,
                    [](){},
                    true,
                    false,
                    true,
                    false
                );
                test3 = TestCase(
                    test3Name,
                    [](){},
                    true,
                    false,
                    true,
                    false
                );

                testSuite = unique_ptr<TestSuite>(new TestSuite(
                    suiteName, test1, test2, test3
                ));

                testSuite->disableTestPassedMessage();
                testSuite->run();

                Assertions::assertFalse(
                    test1.checkLog(tc1Log.str()),
                    "Should not have notified on test passage! 5"
                );
                Assertions::assertFalse(
                    test1.checkLog(tc2Log.str()),
                    "Should not have notified on test passage! 6"
                );
                Assertions::assertFalse(
                    test1.checkLog(tc3Log.str()),
                    "Should not have notified on test passage! 7"
                );
                Assertions::assertFalse(
                    test1.checkLog(secondsParen),
                    "Should not have notified on test passage! 8"
                );
                Assertions::assertFalse(
                    test1.checkLog(tsLog.str()),
                    "Should not have notified on suite passage! 2"
                );
            }
        }
    }
}
