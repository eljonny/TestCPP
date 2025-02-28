#include "TestCPP.h"

using TestCPP::TestCase;
using TestCPP::TestSuite;
using std::string;
using std::make_tuple;
using std::function;

#include "Assertions/AssertionsSuites.h"

int main(void)
{
    try {
        TestCPP::Testing::AssertionsSuites::basicSuite.run();
        int basicSuiteFailCount = TestCPP::Util::unsignedToSigned(
            TestCPP::Testing::AssertionsSuites::basicSuite.
                getLastRunFailCount()
        );

        int allSuitesFailCount = 0;
        allSuitesFailCount += basicSuiteFailCount;

        return allSuitesFailCount;
    }
    catch (std::exception& e) {
        std::cerr << "Test suite run failed with an exception: "
                  << e.what() << std::endl;
        return -1;
    }
}
