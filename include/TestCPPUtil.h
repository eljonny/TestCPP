#ifndef TESTCPP_UTIL_
#define TESTCPP_UTIL_

#include <string>

using std::string;

namespace TestCPP {
    namespace Util {
        void debugLog (const string& message, bool omitNewline = false);
        bool stringContains (const string& source,
                             const string& contains);
    }
}

#endif
