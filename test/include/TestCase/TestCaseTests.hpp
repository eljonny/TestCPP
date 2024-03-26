#include "TestCaseTestChunks.h"

using std::cout;
using std::endl;

namespace TestCPP {
    namespace Testing {
        namespace TestCaseTests {
            void TestConstructCase() {
                cout << "Construct basic" << endl;
                TestCase * test = new TestCase(
                    string("ConstructCase case Test - bare minimum"),
                    function<void()>([](){})
                );
                delete test;
                
                cout << "Construct with nullptr string" << endl;
                TestSuite::assertThrows(
                    []() {
                        new TestCase(
                            nullptr,
                            function<void()>([](){})
                        );
                    },
                    "Should have thrown on nullptr string!"
                );
                
                parameterVariationTestChunks();
            }

            void TestTestCaseGo() {
                TestCase * test = new TestCase(
                    string("SUB-TEST TestCaseGo case Test"),
                    function<void()>([](){}),
                    true
                );
                
                TestSuite::assertTrue(
                    test->go(),
                    "Should have succeeded basic no-op test!"
                );
                
                delete test;
            }

            void TestTestCaseSetNotifyPassed() {
                TestCase * test = new TestCase(
                    string("TestCaseSetNotifyPassed case Test"),
                    function<void()>([](){}),
                    false, false, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                
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
                
                delete test;
            }
        }
    }
}
