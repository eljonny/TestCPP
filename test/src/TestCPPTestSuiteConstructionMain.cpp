#include "TestCPP.h"

using TestCPP::TestCase;
using TestCPP::TestSuite;
using std::string;
using std::make_tuple;
using std::function;

#include "TestSuite/TestSuiteConstructionSuite.h"

int main(void)
{
    try {
        TestCPP::Testing::TestSuiteSuites::ctorSuite.run();
        return TestCPP::Util::unsignedToSigned(
            TestCPP::Testing::TestSuiteSuites::ctorSuite.
                getLastRunFailCount()
        );
    }
    catch (std::exception& e) {
        std::cerr << "Test suite run failed with an exception: "
                  << e.what() << std::endl;
        return -1;
    }
}
