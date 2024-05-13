#include "TestCPP.h"
#include "TestCase/TestCaseTestChunks.h"

using TestCPP::Util::debugLog;

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

                        auto test = unique_ptr<TestCase>(new TestCase(
                            nullptr,
                            function<void()>([](){})
                        ));
                    },
                    "Should have thrown on nullptr string!"
                );

                debugLog("Done with nullptr string construction test");


                parameterVariationTestChunks();
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
                    function<void()>([&throwStr](){
                        throw throwStr;
                    }),
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
                    function<void()>([](){
                        throw throwChr;
                    }),
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
        }
    }
}
