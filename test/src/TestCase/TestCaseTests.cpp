#include "TestCPP.h"
#include "TestCPPUtil.h"
#include "TestCase/TestCaseTestChunks.h"

using TestCPP::Util::debugLog;

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
                TestSuite::assertThrows(
                    []() {
                        debugLog("Construct with nullptr string", true);
                        debugLog(" - assertThrows lambda");

                        auto test = unique_ptr<TestCase>(new TestCase(
                            nullptr,
                            function<void()>([](){})
                        ));

                        debugLog("Destroying with nullptr string");
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

                TestSuite::assertTrue(
                    test->go(),
                    "Should have succeeded basic no-op test!"
                );
            }

            void TestTestCaseSetNotifyPassed () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "TestCaseSetNotifyPassed case Test",
                    function<void()>([](){}),
                    false, false, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                TestSuite::assertTrue(
                    test->go(),
                    "TestSetNotifyPassed go() 1"
                );

                TestSuite::assertTrue(
                    test->checkLog(string()),
                    "TestSetNotifyPassed checkLog() 1"
                );

                test->outCompareOption(
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );

                test->setNotifyPassed(true);
                TestSuite::assertTrue(
                    test->go(),
                    "TestSetNotifyPassed go() 2"
                );

                stringstream tcLog;
                tcLog << "Test ";
                tcLog << "TestCaseSetNotifyPassed case Test passed! (";
                TestSuite::assertTrue(
                    test->checkLog(tcLog.str()),
                    "TestSetNotifyPassed checkLog() 2"
                );
                TestSuite::assertTrue(
                    test->checkLog(string("s)")),
                    "TestSetNotifyPassed checkLog() 3"
                );

                test->outCompareOption(
                    TestCase::TestCaseOutCompareOptions::EXACT
                );

                test->clearLogCapture();

                test->setNotifyPassed(false);
                TestSuite::assertTrue(
                    test->go(),
                    "TestSetNotifyPassed go() 3"
                );

                TestSuite::assertTrue(
                    test->checkLog(string()),
                    "TestSetNotifyPassed checkLog() 4"
                );
            }
        }
    }
}
