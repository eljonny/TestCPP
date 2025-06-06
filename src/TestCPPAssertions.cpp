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

#include "internal/TestCPPAssertions.h"

using std::clog;
using std::current_exception;
using std::endl;
using std::exception;
using std::exception_ptr;
using std::function;
using std::rethrow_exception;
using std::string;
using std::stringstream;

namespace TestCPP {

    template<>
    const string Assertions::checkEquals<const char*, const char*>(
        const char* expected, const char* actual,
        const string& failureMessage
    )
    {
        if (strcmp(expected, actual)) {
            return logTestFailure(
                expected, actual,
                equivalenceAssertionMessage,
                failureMessage,
                true
            );
        }
        return {};
    }

    template<>
    const string Assertions::checkNotEquals<const char*, const char*>(
        const char* shouldNotBe, const char* actual,
        const string& failureMessage
    )
    {
        if (!strcmp(shouldNotBe, actual)) {
            return logTestFailure(
                shouldNotBe, actual,
                nonequivalenceAssertionMessage,
                failureMessage,
                true
            );
        }
        return {};
    }

    template<>
    void Assertions::assertEquals<const char*, const char*>(
        const char* expected, const char* actual,
        const string& failureMessage
    )
    {
        const string err = checkEquals(expected, actual, failureMessage);
        if (err.size()) {
            throw TestFailedException(std::move(err));
        }
    }

    template<>
    void Assertions::assertNotEquals<const char*, const char*>(
        const char* shouldNotBe, const char* actual,
        const string& failureMessage
    )
    {
        const string err = checkNotEquals(shouldNotBe, actual,
            failureMessage);
        if (err.size()) {
            throw TestFailedException(std::move(err));
        }
    }

    void Assertions::assertThrows (
            function<void()> shouldThrow,
            const string& failureMessage
        )
    {
        try {
            shouldThrow();
        }
        catch (...) {
            exception_ptr eptr = current_exception();

            if (eptr) {
                try {
                    rethrow_exception(eptr);
                }
                catch (const exception& e) {
                    clog << "assertThrows caught exception: "
                         << TestFailedException(e.what()).what()
                         << endl;
                }
            }
            else {
                clog << "Something was thrown, not sure what." << endl
                     << "This satisfies the assertion, so no failure is"
                     << " present. "
                     << TestFailedException("Unknown thrown object").
                            what();
            }

            return;
        }

        throw TestFailedException(std::move(failureMessage));
    }

    void Assertions::assertNoThrows (
            const function<void()>& shouldNotThrow,
            const string& failureMessage
        )
    {
        try {
            shouldNotThrow();
        }
        catch (...) {
            throw TestFailedException(std::move(failureMessage));
        }
    }

    void Assertions::assertTrue (
            bool condition,
            const string& failureMessage
        )
    {
        if (!condition) {
            static constexpr const char* atMsg = "Boolean Truth assertion failed!";

            const string err = logTestFailure(
                "", "",
                atMsg,
                failureMessage,
                false
            );

            if (err.size()) {
                throw TestFailedException(std::move(err));
            }
        }
    }

    void Assertions::assertFalse (
            bool condition,
            const string& failureMessage
        )
    {
        if (condition) {
            static constexpr const char* atMsg = "Boolean False assertion failed!";

            const string err = logTestFailure(
                "", "",
                atMsg,
                failureMessage,
                false
            );

            if (err.size()) {
                throw TestFailedException(std::move(err));
            }
        }
    }

    [[noreturn]] void Assertions::fail(string failureMessage) {
        throw TestFailedException(std::move(failureMessage));
    }
}
