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

#ifndef TESTCPP_UTIL_
#define TESTCPP_UTIL_

#include <string>

using std::string;

/**
 * The base namespace for all TestCPP library code.
 */
namespace TestCPP {

    /**
     * @class TestObjName
     * @author Jonathan Hyry
     * @date 03/05/24
     * @file TestCPP.h
     * @brief Provides a null-safe name for test objects.
     * 
     * Both TestCase and TestSuite objects use this for their name to
     *  protect against nullptr/NULL being used to create a std::string
     *  and name the test with that non-null-char-*-based std::string.
     */
    class TestObjName {
    public:
        /**
         * @brief Construct an empty Test Object Name object.
         * @return The empty TestObjName.
         *
         * This should never be called by user code but is required for
         *  the code to compile.
         */
        TestObjName () = default;

        /**
         * @brief Construct a Test Object Name object with a string
         *          literal or existing const char *.
         * @return The TestObjName, where it is verified that the name
         *          used to construct it was not null.
         */
        TestObjName (const char* name);

        /**
         * @brief Get the encapsulated name for the TestCPP object that
         *          holds this object.
         * @return The name of the TestCPP object that this object
         *          names.
         */
        const string& getName ();

        /**
         * @brief Output the test object name to the specified stream.
         * @param s The stream to output to.
         * @param tcName The test object name object.
         * @return The stream for chaining.
         */
        friend std::ostream& operator<< (
            std::ostream& s,
            TestObjName& tcName
        )
        {
            s << tcName.getName();
            return s;
        }

    private:
        string testCaseName;
    };
    
    /**
     * The namespace for general TestCPP utility code.
     */
    namespace Util {

        /**
         * @brief Log a message that will only be output when debug
         *          logging is enabled.
         *
         * @param message The debug message to log.
         * @param omitNewline Whether or not to end the log with a
         *                      newline character.
         *                    Defaults to false.
         */
        void debugLog (const string& message, bool omitNewline = false);

        /**
         * @brief Check if a std::string is contained within another
         *          std::string; this exists since we're not using C++26
         *          here.
         *
         * @param source The base std::string to check within.
         * @param contains Checks the base std::string to see if it
         *                  contains this std::string.
         *
         * @return True if source includes contains in whole, false
         *          otherwise.
         */
        bool stringContains (const string& source,
                             const string& contains);

        /**
         * @brief Safely converts unsigned integer values to signed.
         * @param toCast The unsigned value to convert.
         * @return The signed value equivalent to the unsigned value.
         */
        int unsignedToSigned(unsigned toCast);
    }
}

#endif
