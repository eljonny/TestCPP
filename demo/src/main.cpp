#include "TestCPP.h"

using TestCPP::TestSuite;
using std::string;
using std::make_tuple;
using std::function;

#include "tests.h"

int main(void)
{
    try {
        TestSuite suite(
            string("Demo Test Suite"),

            make_tuple(
                "simpleTest",
                function<void()>(TestCPP::Demo::Tests::simpleTest)
            ),
            make_tuple(
                "otherSimpleTest",
                function<void()>(TestCPP::Demo::Tests::otherSimpleTest)
            )
        );

        suite.run();
    }
    catch (std::exception& e) {
        std::cerr << "Demo run failed with an exception: "
                  << e.what() << std::endl;
    }

    return 0;
}
