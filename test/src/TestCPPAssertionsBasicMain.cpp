#include "TestCPP.h"

using TestCPP::TestCase;
using TestCPP::TestSuite;
using std::string;
using std::make_tuple;
using std::function;

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
