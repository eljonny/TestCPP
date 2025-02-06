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

#ifndef TESTCPP_ASSERTIONS_
#define TESTCPP_ASSERTIONS_

#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "TestCPPExceptions.h"

using std::endl;
using std::function;
using std::string;
using std::stringstream;

/**
 * The base namespace for all TestCPP library code.
 */
namespace TestCPP {

    /**
     * @class Assertions
     * @author Jonathan Hyry
     * @date 11/05/24
     * @file TestCPPAssertions.h
     * @brief Contains the TestCPP library's assertions.
     * 
     * Defines some assertions here, where they are templated.
     * Declares the rest.
     * 
     * This is the place where the TestCPP Assertions API is defined.
     */
    class Assertions {
    public:
        /**
         * @brief Check that something equals something else using the
         *          built-in operator== for each type.
         * @param expected The value that the actual value should be
         *                  equivalent to.
         * @param actual The actual value that will be checked against
         *                  the expected value.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         */
        template<typename T1, typename T2>
        static void assertEquals (
                T1 expected, T2 actual,
                string failureMessage = "Arguments are not equivalent!"
            )
        {
            if (expected != actual) {
                stringstream err;

                err << "Equivalence assertion failed!" << endl;
                err << failureMessage << endl;
                err << "Expected: <" << expected << ">" << endl;
                err << "Actual: <" << actual << ">" << endl;

                throw TestFailedException(err.str());
            }
        }

        /**
         * @brief Check that something is not equivalent to something
         *          else using the built-in operator== for each type.
         * @param expected The value that the actual value should not be
         *                  equivalent to.
         * @param actual The actual value that will be checked against
         *                  the expected value.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         */
        template<typename T1, typename T2>
        static void assertNotEquals (
                T1 expected, T2 actual,
                string failureMessage = "Arguments are equivalent!"
            )
        {
            if (expected == actual) {
                stringstream err;

                err << "Non-Equivalence assertion failed!" << endl;
                err << failureMessage << endl;
                err << "Expected: <" << expected << ">" << endl;
                err << "Actual: <" << actual << ">" << endl;

                throw TestFailedException(err.str());
            }
        }

        /**
         * @brief Check that a pointer is null.
         * @param ptr The pointer to check.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         */
        template<typename T>
        static void assertNull (
                T ptr,
                string failureMessage = "Object is not null!"
            )
        {
            bool null = ptr == nullptr;

            if (!null) {
                stringstream err;

                err << "Null assertion failed!" << endl;
                err << failureMessage << endl;

                throw TestFailedException(err.str());
            }
        }

        /**
         * @brief Check that a pointer is non-null.
         * @param ptr The pointer to check.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         */
        template<typename T>
        static void assertNotNull (
                T ptr,
                string failureMessage = "Object is null!"
            )
        {
            bool notNull = ptr != nullptr;

            if (!notNull) {
                stringstream err;

                err << "Not Null assertion failed!" << endl;
                err << failureMessage << endl;

                throw TestFailedException(err.str());
            }
        }

        /**
         * @brief Verify that a function throws something.
         * @param shouldThrow The function to check, to ensure that it
         *                      throws something.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         */
        static void assertThrows (
            function<void()> shouldThrow,
            string failureMessage =
                "Should have thrown something!"
        );

        /**
         * @brief Verify that a function does not throw something.
         * @param shouldNotThrow The function to check, to ensure that it
         *                      does not throw something.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         */
        static void assertNoThrows (
            function<void()> shouldNotThrow,
            string failureMessage =
                "Should not have thrown anything!"
        );

        /**
         * @brief Verify that a logical condition is true.
         * @param condition The result of the logical condition to
         *                      check.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         */
        static void assertTrue (
            bool condition,
            string failureMessage = "Condition is false!"
        );

        /**
         * @brief Verify that a logical condition is not true.
         * @param condition The result of the logical condition to
         *                      check.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         */
        static void assertFalse (
            bool condition,
            string failureMessage = "Condition is true!"
        );

        /**
         * @brief Force a test to fail.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         *
         * Useful in certain situations when:
         *  - Generating code for test cases, to ensure that skeletons
         *      fail by default.
         *  - Forcing test failure in certain circumstances where there
         *      is nothing to assert but a certain code path is taken.
         */
        static void fail [[noreturn]] (
            string failureMessage = "Forced test failure!"
        );
    };
}

#endif
