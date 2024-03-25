#include "TestSuiteTests.hpp"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteSuite {
            TestSuite suite(
                string("TestCPP TestSuite Tests"),
                
                make_tuple(
                    string("Suite construction Test"),
                    function<void()>(TestSuiteTests::TestConstructSuite)
                ),
                make_tuple(
                    string("assertNull Test"),
                    function<void()>(TestSuiteTests::TestAssertNull)
                ),
                make_tuple(
                    string("assertNotNull Test"),
                    function<void()>(TestSuiteTests::TestAssertNotNull)
                ),
                make_tuple(
                    string("assertTrue Test"),
                    function<void()>(TestSuiteTests::TestAssertTrue)
                ),
                make_tuple(
                    string("assertFalse Test"),
                    function<void()>(TestSuiteTests::TestAssertFalse)
                )
            );
        }   
    }
}
