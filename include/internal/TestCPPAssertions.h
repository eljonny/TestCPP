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

#include <cstring>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "TestCPPExceptions.h"

using std::endl;
using std::function;
using std::strcmp;
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
                const string& failureMessage = "Arguments are not equivalent!"
            )
        {
            const string err = checkEquals(expected, actual, failureMessage);
            if (err.size()) {
                throw TestFailedException(std::move(err));
            }
        }

        /**
         * @brief Check that something is not equivalent to something
         *          else using the built-in operator== for each type.
         * @param shouldNotBe The value that the actual value should
         *                     not be equivalent to.
         * @param actual The actual value that will be checked against
         *                  the expectation value.
         * @param failureMessage Failure message that should be logged
         *                          if the assertion fails. This
         *                          defaults to a generic failure
         *                          message related to the assertion
         *                          type.
         */
        template<typename T1, typename T2>
        static void assertNotEquals (
                T1 shouldNotBe, T2 actual,
                const string& failureMessage = "Arguments are equivalent!"
            )
        {
            const string err = checkNotEquals(shouldNotBe, actual,
                                        failureMessage);
            if (err.size()) {
                throw TestFailedException(std::move(err));
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
                const string& failureMessage = "Object is not null!"
            )
        {
            const string err = checkNull(ptr, failureMessage);
            if (err.size()) {
                throw TestFailedException(std::move(err));
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
                const string& failureMessage = "Object is null!"
            )
        {
            const string err = checkNotNull(ptr, failureMessage);
            if (err.size()) {
                throw TestFailedException(std::move(err));
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
            const string& failureMessage =
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
            const function<void()>& shouldNotThrow,
            const string& failureMessage =
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
            const string& failureMessage = "Condition is false!"
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
            const string& failureMessage = "Condition is true!"
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

    private:

        static constexpr const char* equivalenceAssertionMessage = "Equivalence assertion failed!";
        static constexpr const char* nonequivalenceAssertionMessage = "Non-Equivalence assertion failed!";

        template<typename T1, typename T2>
        static const string logTestFailure(
            T1 expectationValue, T2 actual,
            const string& assertionTypeMessage,
            const string& failureMessage,
            const bool logValues
        )
        {
            stringstream err;

            err << assertionTypeMessage << endl;
            err << failureMessage << endl;

            if (logValues) {
                err << "Expectation value: <" << expectationValue << ">"
                    << endl;
                err << "Actual: <" << actual << ">" << endl;
            }

            return err.str();
        }

        template<typename T1, typename T2>
        static const string checkEquals(
            T1 expected, T2 actual,
            const string& failureMessage
        )
        {
            if (expected != actual) {
                return logTestFailure(
                    expected, actual,
                    equivalenceAssertionMessage,
                    failureMessage,
                    true
                );
            }
            return {};
        }

        template<typename T1, typename T2>
        static const string checkNotEquals(
            T1 shouldNotBe, T2 actual,
            const string& failureMessage
        )
        {
            if (shouldNotBe == actual) {
                return logTestFailure(
                    shouldNotBe, actual,
                    nonequivalenceAssertionMessage,
                    failureMessage,
                    true
                );
            }
            return {};
        }

        template<typename T>
        static const string checkNull(
            T ptr,
            const string& failureMessage
        )
        {
            bool null = ptr == nullptr;
            if (!null) {
                static constexpr const char* nullAssertionMessage = "Null assertion failed!";
                return logTestFailure(
                    "", "",
                    nullAssertionMessage,
                    failureMessage,
                    false
                );
            }
            return {};
        }

        template<typename T>
        static const string checkNotNull(
            T ptr,
            const string& failureMessage
        )
        {
            bool notNull = ptr != nullptr;
            if (!notNull) {
                static constexpr const char* notNullAssertionMessage = "Not Null assertion failed!";
                return logTestFailure(
                    "", "",
                    notNullAssertionMessage,
                    failureMessage,
                    false
                );
            }
            return {};
        }
    };
}

/**
 * @brief Check that char*'s are equal using strcmp.
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
template<>
void TestCPP::Assertions::assertEquals<const char*, const char*>(
    const char* expected, const char* actual,
    const string& failureMessage
);

extern template
void TestCPP::Assertions::assertEquals<const char*, const char*>(
    const char* expected, const char* actual,
    const string& failureMessage
);

/**
 * @brief Check that char*'s are not equal using strcmp.
 * @param expected The value that the actual value should not
 *                  be equivalent to.
 * @param actual The actual value that will be checked against
 *                  the expected value.
 * @param failureMessage Failure message that should be logged
 *                          if the assertion fails. This
 *                          defaults to a generic failure
 *                          message related to the assertion
 *                          type.
 */
template<>
void TestCPP::Assertions::assertNotEquals<const char*, const char*>(
    const char* shouldNotBe, const char* actual,
    const string& failureMessage
);

extern template
void TestCPP::Assertions::assertNotEquals<const char*, const char*>(
    const char* shouldNotBe, const char* actual,
    const string& failureMessage
);

template<>
const string TestCPP::Assertions::checkEquals<const char*, const char*>(
    const char* expected, const char* actual,
    const string& failureMessage
);

template<>
const string TestCPP::Assertions::checkNotEquals<const char*, const char*>(
    const char* shouldNotBe, const char* actual,
    const string& failureMessage
);

#endif
