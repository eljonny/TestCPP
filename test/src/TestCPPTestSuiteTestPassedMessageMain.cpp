#include "TestCPP.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteSuites {
            extern TestSuite testPassedMessageSuite;
        }
    }
}

#include "TestSuite/TestSuiteTestPassedMessageSuite.h"

int main(void)
{
    try {
        TestCPP::Testing::TestSuiteSuites::testPassedMessageSuite.run();
        return TestCPP::Util::unsignedToSigned(
            TestCPP::Testing::TestSuiteSuites::testPassedMessageSuite.
                getLastRunFailCount()
        );
    }
    catch (std::exception& e) {
        std::cerr << "Test suite run failed with an exception: "
                  << e.what() << std::endl;
        return -1;
    }
}
