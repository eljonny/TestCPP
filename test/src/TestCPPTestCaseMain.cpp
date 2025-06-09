#include "TestCPP.h"

namespace TestCPP {
    namespace Testing {
        namespace TestCaseSuite {
            extern TestSuite suite;
        }
    }
}

#include "TestCase/TestCaseSuite.h"

int main(void)
{
    try {
        TestCPP::Testing::TestCaseSuite::suite.run();
        return TestCPP::Util::unsignedToSigned(
            TestCPP::Testing::TestCaseSuite::suite.
                getLastRunFailCount()
        );
    }
    catch (std::exception& e) {
        std::cerr << "Test suite run failed with an exception: "
                  << e.what() << std::endl;
        return -1;
    }
}
