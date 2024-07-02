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

#ifndef TESTCPP_EXCEPTIONS_
#define TESTCPP_EXCEPTIONS_

#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

/**
 * The base namespace for all TestCPP library code.
 */
namespace TestCPP {

    /**
     * @class TestCPPException
     * @author Jonathan Hyry
     * @date 03/05/24
     * @file TestCPP.h
     * @brief Provides a custom base exception for failure conditions.
     * 
     * There are two types of failures in the library:
     *  - Errors caused by bugs, system problems, etc.
     *  - Test failures
     * 
     * This type, when used directly, is for representing the first type
     *  of failure: errors in the library caused by bugs or other
     *  problems.
     */
    class TestCPPException : public runtime_error {
    public:
        /**
         * Construct an exception of this type with a string literal for
         *  its failure message.
         */
        explicit TestCPPException (const char * msg);

        /**
         * Construct an exception of this type with a string object for
         *  its failure message.
         */
        explicit TestCPPException (string&& msg);
    };

    /**
     * @class TestFailedException
     * @author Jonathan Hyry
     * @date 03/05/24
     * @file TestCPP.h
     * @brief Provides an exception type specifically for test failures.
     * 
     * There are two types of failures in the library:
     *  - Errors caused by bugs, system problems, etc.
     *  - Test failures
     * 
     * This type is for representing the second type of failure: test
     *  failures.
     */
    class TestFailedException : public TestCPPException {
    public:
        /**
         * Construct an exception of this type with a string literal for
         *  its failure message.
         */
        explicit TestFailedException (const char * msg);

        /**
         * Construct an exception of this type with a string literal for
         *  its failure message.
         */
        explicit TestFailedException (string&& msg);
    };
}

#endif
