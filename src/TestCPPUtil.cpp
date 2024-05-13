/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
 */

#include <climits>
#include <stdexcept>

#include "internal/TestCPPCommon.h"
#include "internal/TestCPPExceptions.h"
#include "internal/TestCPPUtil.h"

#ifdef DEBUG_LOG
#include <iostream>
#endif

#ifdef DEBUG_LOG
using std::clog;
using std::endl;
#endif

using TCPPStr = TestCPP::TestCPPCommon::Strings;

namespace TestCPP {

    TestObjName::TestObjName (const char* name) {
        if (name) {
            this->testCaseName = name;
        }
        else {
            throw TestCPPException(TCPPStr::NVTN);
        }
    }

    const string& TestObjName::getName () {
        return this->testCaseName;
    }

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

        int unsignedToSigned(unsigned toCast) {
            if (toCast <= INT_MAX) {
                return static_cast<int>(toCast);
            }

            if (toCast >= static_cast<unsigned>(INT_MIN)) {
                return static_cast<int>(toCast - INT_MIN) + INT_MIN;
            }

            throw std::runtime_error(
                "Conversion would produce an invalid value!"
            );
        }
    }
}