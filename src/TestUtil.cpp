#include "TestUtil.h"

namespace TestCPP {
    namespace Util {
        bool stringContains(string source, string contains) {
            return source.find(contains) != string::npos;
        }
    }
}