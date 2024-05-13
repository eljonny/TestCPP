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

#ifndef TESTCPP_COMMON_
#define TESTCPP_COMMON_

/**
 * The base namespace for all TestCPP library code.
 */
namespace TestCPP {

    /**
     * @class TestCPPCommon
     * @author Jonathan Hyry
     * @date 03/05/24
     * @file TestCPP.h
     * @brief Categories of common objects that are used.
     */
    class TestCPPCommon {
    public:
        /**
         * @class Nums
         * @author Jonathan Hyry
         * @date 03/05/24
         * @file TestCPP.h
         * @brief Common magic numbers used by the library.
         */
        struct Nums {
            static constexpr const int TIME_PRECISION = 4;
            static constexpr const double NANOS_IN_SEC = 1000000000.0;
        };

        /**
         * @class Strings
         * @author Jonathan Hyry
         * @date 03/05/24
         * @file TestCPP.h
         * @brief Common literal strings used by the library.
         * 
         * As struct member name prefixes and postfixes, underscores
         *  denote leading and trailing spaces, respectively.
         */
        struct Strings {
            static constexpr const char * ALL_ = "All ";
            static constexpr const char * APOS = "'";
            static constexpr const char * _FAIL_ = " failed! ";
            static constexpr const char * FINISHED_SUITE_ =
                "Finished running test suite ";
            static constexpr const char * FWSL = "/";
            static constexpr const char * _IN_ABOUT_ = " in about ";
            static constexpr const char * _NCONTAIN_ =
                " does not contain ";
            static constexpr const char * _NEQUIV_ =
                " is not equivalent to ";
            static constexpr const char * NTR = "No tests to run!";
            static constexpr const char * NVTN =
                "Not a valid test name!";
            static constexpr const char * PARENL = "(";
            static constexpr const char * PARENR = ")";
            static constexpr const char * _PASS_ = " passed! ";
            static constexpr const char * _PASSED = " passed";
            static constexpr const char * REASON_ = "Reason: ";
            static constexpr const char * SEC = "s";
            static constexpr const char * SP = " ";
            static constexpr const char * START_RUN =
                "Starting run of test ";
            static constexpr const char * SUITE_ = "Suite ";
            static constexpr const char * _SUITE_TESTS_PASSED =
                " suite tests passed!";
            static constexpr const char * TEST_ = "Test ";
            static constexpr const char * TEST_EXC_ =
                "Exception occurred during test run: ";
            static constexpr const char * UNK_CMP_OPT_ =
                "Unknown comparison option! ";
            static constexpr const char * UNK_EXC =
                "Unknown error occurred in test!";
            static constexpr const char * UNK_OPT_ = "Unknown option ";
        };
    };
}

#endif