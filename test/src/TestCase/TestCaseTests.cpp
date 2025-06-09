#include "TestCPP.h"
#include "TestCase/TestCaseTests.h"
#include "TestCase/TestCaseTestChunks.h"

using TestCPP::Util::debugLog;

using std::cerr;
using std::cout;
using std::endl;

using TCPPStr = TestCPP::TestCPPCommon::Strings;

namespace TestCPP {
    namespace Testing {
        namespace TestCaseTests {
            void TestConstructCase () {
                debugLog("Construct basic");
                auto test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase case Test - bare minimum",
                    function<void()>([](){})
                ));

                debugLog("Construct with nullptr string");
                Assertions::assertThrows(
                    []() {
                        debugLog("Construct with nullptr string", true);
                        debugLog(" - assertThrows lambda");

                        auto testShouldThrow = unique_ptr<TestCase>(
                            new TestCase(
                                nullptr,
                                function<void()>([](){})
                        ));
                    },
                    "Should have thrown on nullptr string!"
                );

                debugLog("Done with nullptr string construction test");


                parameterVariationTestChunks();
            }

            /**
             * Targets various types of non-move assignments.
             */
            void TestAssignTestCase() {
                const auto test = unique_ptr<TestCase>(new TestCase(
                    "Assignment case Test - const TestCase",
                    function<void()>([]() {})
                ));
                const auto test2 = unique_ptr<TestCase>(new TestCase(
                    "Assignment case Test 2 - const TestCase",
                    function<void()>([]() {})
                ));

                Assertions::assertTrue(
                    test->go(),
                    "Should have succeeded basic no-op test!"
                );

                const TestCase& testCopy = *test;
                TestCase testCopy2 = *test2;
                testCopy2 = testCopy;

                Assertions::assertTrue(
                    testCopy2.go(),
                    "Should have succeeded basic no-op test!"
                );
            }

            void TestMoveAssignTestCase() {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "Move Assignment case Test - const TestCase",
                    function<void()>([]() {})
                ));
                auto test2 = unique_ptr<TestCase>(new TestCase(
                    "Move Assignment case Test 2 - const TestCase",
                    function<void()>([]() {})
                ));

                Assertions::assertTrue(
                    test->go(),
                    "Should have succeeded basic no-op test!"
                );

                TestCase tempCpy = *test;
                *test = std::move(*test2);
                *test2 = std::move(tempCpy);

                Assertions::assertTrue(
                    test->go(),
                    "Should have succeeded basic no-op test!"
                );
            }

            void TestTestCaseGo () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "SUB-TEST TestCaseGo case Test",
                    function<void()>([](){}),
                    true
                ));

                Assertions::assertTrue(
                    test->go(),
                    "Should have succeeded basic no-op test!"
                );
            }

            void TestTestCaseGoThrowStr () {
                const string throwStr = "Test throw string!";

                auto test = unique_ptr<TestCase>(new TestCase(
                    "SUB-TEST TestCaseGo case Test - throws str",
#ifdef TESTCPP_STACKTRACE_ENABLED
                    // We use C++14 when stacktraces are enabled, which
                    //  allows us to avoid needing to use
                    //  -Wno-unused-lambda-capture to avoid MSVC C3493
                    //  since the implementations can be reconciled in
                    //  the newer standard.
                    function<void()>([&toThrow = throwStr](){
                        throw toThrow;
                    }),
#else
                    function<void()>([&throwStr](){
                        throw throwStr;
                    }),
#endif
                    true, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                Assertions::assertFalse(
                    test->go(),
                    "Should have succeeded str throws test!"
                );

                Assertions::assertTrue(
                    test->checkLog(throwStr),
                    "Something is off, expected output does not exist!"
                );
            }

            void TestTestCaseGoThrowChr () {
                constexpr const char * throwChr =
                    "Test throw const char *!";

                auto test = unique_ptr<TestCase>(new TestCase(
                    "SUB-TEST TestCaseGo case Test - throws chr",
#ifdef TESTCPP_STACKTRACE_ENABLED
                    // We use C++14 when stacktraces are enabled, which
                    //  allows us to avoid needing to use
                    //  -Wno-unused-lambda-capture to avoid MSVC C3493
                    //  since the implementations can be reconciled in
                    //  the newer standard.
                    function<void()>([&toThrow = throwChr](){
                        throw toThrow;
                    }),
#else
                    function<void()>([&throwChr](){
                        throw throwChr;
                    }),
#endif
                    true, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                Assertions::assertFalse(
                    test->go(),
                    "Should have succeeded chr throws test!"
                );

                string tcLog(throwChr);

                Assertions::assertTrue(
                    test->checkLog(tcLog),
                    "Something is off, expected output does not exist!"
                );
            }

            void TestTestCaseGoThrowInt () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "SUB-TEST TestCaseGo case Test - throws int",
                    function<void()>([](){
                        throw -1;
                    }),
                    true, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                Assertions::assertFalse(
                    test->go(),
                    "Should have succeeded catchall throws test!"
                );

                Assertions::assertTrue(
                    test->checkLog(TCPPStr::UNK_EXC),
                    "Something is off, expected output does not exist!"
                );
            }

            void TestTestCaseSetNotifyPassed () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "TestCaseSetNotifyPassed case Test",
                    function<void()>([](){}),
                    false, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                Assertions::assertTrue(
                    test->go(),
                    "TestSetNotifyPassed go() 1"
                );

                stringstream tcLog;
                tcLog << "Test ";
                tcLog << "TestCaseSetNotifyPassed case Test passed! (";

                Assertions::assertTrue(
                    !test->checkLog(tcLog.str()),
                    "TestSetNotifyPassed checkLog() 1"
                );
                Assertions::assertTrue(
                    !test->checkLog(string("s)")),
                    "TestSetNotifyPassed checkLog() 2"
                );

                test->setNotifyPassed(true);
                Assertions::assertTrue(
                    test->go(),
                    "TestSetNotifyPassed go() 2"
                );

                Assertions::assertTrue(
                    test->checkLog(tcLog.str()),
                    "TestSetNotifyPassed checkLog() 3"
                );
                Assertions::assertTrue(
                    test->checkLog(string("s)")),
                    "TestSetNotifyPassed checkLog() 4"
                );

                test->clearLogCapture();

                test->setNotifyPassed(false);
                Assertions::assertTrue(
                    test->go(),
                    "TestSetNotifyPassed go() 3"
                );

                Assertions::assertTrue(
                    !test->checkLog(tcLog.str()),
                    "TestSetNotifyPassed checkLog() 5"
                );
                Assertions::assertTrue(
                    !test->checkLog(string("s)")),
                    "TestSetNotifyPassed checkLog() 6"
                );
            }

            void TestTestCaseCheckStdout() {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "TestCaseCheckStdout case Test",
                    function<void()>([]() {
                        cout << "Test output to stdout!" << endl;
                    }),
                    false, true, false, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));
                
                Assertions::assertTrue(
                    test->go(),
                    "TestCheckStdout go() 1"
                );
                
                Assertions::assertTrue(
                    test->checkStdout("Test output to stdout!\n"),
                    "TestCheckStdout checkStdout() 1"
                );
            }

            void TestTestCaseCheckStderr() {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "TestCaseCheckStderr case Test",
                    function<void()>([]() {
                        cerr << "Test output to stderr!" << endl;
                    }),
                    false, false, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                Assertions::assertTrue(
                    test->go(),
                    "TestCheckStderr go() 1"
                );

                Assertions::assertTrue(
                    test->checkStderr("Test output to stderr!\n"),
                    "TestCheckStderr checkStderr() 1"
                );
            }
        }
    }
}
