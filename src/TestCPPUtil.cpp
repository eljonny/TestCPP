#ifdef DEBUG_LOG

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable: 4668)
#endif

#include <iostream>

#ifdef WIN32
#pragma warning(pop)
#endif

#endif

#include "TestCPPUtil.h"

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