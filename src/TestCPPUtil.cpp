#include "TestCPPUtil.h"

#ifdef DEBUG_LOG
#include <iostream>
#endif

#ifdef DEBUG_LOG
using std::clog;
using std::endl;
#endif

namespace TestCPP {
    namespace Util {
        void debugLog(const string& message, bool omitNewline) {
#ifdef DEBUG_LOG
            clog << message;
            if (!omitNewline) {
                clog << endl;
            }
#endif
        }

        bool stringContains(const string& source,
                            const string& contains)
        {
            return source.find(contains) != string::npos;
        }
    }
}