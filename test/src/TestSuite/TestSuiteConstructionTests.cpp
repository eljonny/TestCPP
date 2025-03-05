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
        }
    }
}
