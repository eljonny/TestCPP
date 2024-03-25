#include "TestCaseTests.hpp"

namespace TestCPP {
    namespace Testing {
        namespace TestCaseSuite {
            TestSuite suite(
                string("TestCPP TestCase Tests"),
                
                make_tuple(
                    string("Case construction Test"),
                    function<void()>(TestCaseTests::TestConstructCase)
                ),
                make_tuple(
                    string("Case runner Test"),
                    function<void()>(TestCaseTests::TestTestCaseGo)
                ),
                make_tuple(
                    string("Case setNotifyPassed Test"),
                    function<void()>(
                        TestCaseTests::TestTestCaseSetNotifyPassed
                    )
                )
            );
        }   
    }
}
