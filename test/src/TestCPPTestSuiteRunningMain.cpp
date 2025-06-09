#include "TestCPP.h"

namespace TestCPP {
    namespace Testing {
        namespace TestSuiteSuites {
            extern TestSuite runSuite;
        }
    }
}

#include "TestSuite/TestSuiteRunningSuite.h"

int main(void)
{
    try {
        TestCPP::Testing::TestSuiteSuites::runSuite.run();
        return TestCPP::Util::unsignedToSigned(
            TestCPP::Testing::TestSuiteSuites::runSuite.
                getLastRunFailCount()
        );
    }
    catch (std::exception& e) {
        std::cerr << "Test suite run failed with an exception: "
                  << e.what() << std::endl;
        return -1;
    }
}
