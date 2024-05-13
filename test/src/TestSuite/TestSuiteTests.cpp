#include "TestCPP.h"
#include "TestSuite/TestSuiteTests.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteTests {
            void TestConstructSuite () {
                auto test = unique_ptr<TestSuite>(new TestSuite(
                    "Suite construction"
                ));
            }
        }
    }
}
