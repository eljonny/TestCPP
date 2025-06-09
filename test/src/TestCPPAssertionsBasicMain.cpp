#include "TestCPP.h"

namespace TestCPP {
    namespace Testing {
        namespace AssertionsSuites {
            extern TestSuite basicSuite;
        }
    }
}

#include "Assertions/AssertionsBasicSuite.h"

int main(void)
{
    try {
        TestCPP::Testing::AssertionsSuites::basicSuite.run();
        int basicSuiteFailCount = TestCPP::Util::unsignedToSigned(
            TestCPP::Testing::AssertionsSuites::basicSuite.
                getLastRunFailCount()
        );

        return basicSuiteFailCount;
    }
    catch (std::exception& e) {
        std::cerr << "Test suite run failed with an exception: "
                  << e.what() << std::endl;
        return -1;
    }
}
