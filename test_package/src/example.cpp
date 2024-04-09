#include "TestCPP/TestCPP.h"

using TestCPP::TestSuite;

int main() {
    try {
        TestSuite suite;

        suite.run();
    }
    catch (std::exception& e) {
        std::cerr << "Package test failed with exception: "
                  << e.what() << std::endl;
        throw e;
    }
    
    return 0;
}
