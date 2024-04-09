#include <memory>

#include "TestCPP.h"
#include "TestCase/TestCaseTestChunks.h"

using TestCPP::TestCase;
using std::unique_ptr;

namespace TestCPP {
    namespace Testing {
        namespace TestCaseTests {
            void parameterVariationTestChunks () {
                varyingPassMessageEnabled();
                varyingCaptureStdout();
                varyingCaptureLog();
                varyingCaptureStderr();
                varyingTestCaseOutCompareOptionsExact();
                varyingTestCaseOutCompareOptionsContains();
            }

            void varyingPassMessageEnabled () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF",
                    function<void()>([](){}),
                    false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT",
                    function<void()>([](){}),
                    true
                ));
            }

            void varyingCaptureStdout () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NFCOF",
                    function<void()>([](){}),
                    false, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NFCOT",
                    function<void()>([](){}),
                    false, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NTCOF",
                    function<void()>([](){}),
                    true, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NTCOT",
                    function<void()>([](){}),
                    true, true
                ));

            }

            void varyingCaptureLog () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLF",
                    function<void()>([](){}),
                    false, false, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLT",
                    function<void()>([](){}),
                    false, false, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLF",
                    function<void()>([](){}),
                    false, true, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLT",
                    function<void()>([](){}),
                    false, true, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLF",
                    function<void()>([](){}),
                    true, false, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLT",
                    function<void()>([](){}),
                    true, false, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLF",
                    function<void()>([](){}),
                    true, true, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLT",
                    function<void()>([](){}),
                    true, true, true
                ));

            }

            void varyingCaptureStderr () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLF,CEF",
                    function<void()>([](){}),
                    false, false, false, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLF,CET",
                    function<void()>([](){}),
                    false, false, false, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLT,CEF",
                    function<void()>([](){}),
                    false, false, true, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLF,CEF",
                    function<void()>([](){}),
                    false, true, false, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLT,CEF",
                    function<void()>([](){}),
                    false, true, true, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLF,CET",
                    function<void()>([](){}),
                    false, true, false, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLT,CET",
                    function<void()>([](){}),
                    false, false, true, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLT,CET",
                    function<void()>([](){}),
                    false, true, true, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLF,CEF",
                    function<void()>([](){}),
                    true, false, false, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLF,CET",
                    function<void()>([](){}),
                    true, false, false, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLT,CEF",
                    function<void()>([](){}),
                    true, false, true, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLF,CEF",
                    function<void()>([](){}),
                    true, true, false, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLT,CEF",
                    function<void()>([](){}),
                    true, true, true, false
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLF,CET",
                    function<void()>([](){}),
                    true, true, false, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLT,CET",
                    function<void()>([](){}),
                    true, false, true, true
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLT,CET",
                    function<void()>([](){}),
                    true, true, true, true
                ));

            }

            void varyingTestCaseOutCompareOptionsExact () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLF,CEF,EX",
                    function<void()>([](){}),
                    false, false, false, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLF,CET,EX",
                    function<void()>([](){}),
                    false, false, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLT,CEF,EX",
                    function<void()>([](){}),
                    false, false, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLF,CEF,EX",
                    function<void()>([](){}),
                    false, true, false, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLT,CEF,EX",
                    function<void()>([](){}),
                    false, true, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLF,CET,EX",
                    function<void()>([](){}),
                    false, true, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLT,CET,EX",
                    function<void()>([](){}),
                    false, false, true, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLT,CET,EX",
                    function<void()>([](){}),
                    false, true, true, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLF,CEF,EX",
                    function<void()>([](){}),
                    true, false, false, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLF,CET,EX",
                    function<void()>([](){}),
                    true, false, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLT,CEF,EX",
                    function<void()>([](){}),
                    true, false, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLF,CEF,EX",
                    function<void()>([](){}),
                    true, true, false, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLT,CEF,EX",
                    function<void()>([](){}),
                    true, true, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLF,CET,EX",
                    function<void()>([](){}),
                    true, true, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLT,CET,EX",
                    function<void()>([](){}),
                    true, false, true, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLT,CET,EX",
                    function<void()>([](){}),
                    true, true, true, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                ));

            }

            void varyingTestCaseOutCompareOptionsContains () {
                auto test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLF,CEF,CTS",
                    function<void()>([](){}),
                    false, false, false, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLF,CET,CTS",
                    function<void()>([](){}),
                    false, false, false, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLT,CEF,CTS",
                    function<void()>([](){}),
                    false, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLF,CEF,CTS",
                    function<void()>([](){}),
                    false, true, false, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLT,CEF,CTS",
                    function<void()>([](){}),
                    false, true, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLF,CET,CTS",
                    function<void()>([](){}),
                    false, true, false, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLT,CET,CTS",
                    function<void()>([](){}),
                    false, false, true, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLT,CET,CTS",
                    function<void()>([](){}),
                    false, true, true, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLF,CEF,CTS",
                    function<void()>([](){}),
                    true, false, false, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLF,CET,CTS",
                    function<void()>([](){}),
                    true, false, false, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLT,CEF,CTS",
                    function<void()>([](){}),
                    true, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLF,CEF,CTS",
                    function<void()>([](){}),
                    true, true, false, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLT,CEF,CTS",
                    function<void()>([](){}),
                    true, true, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLF,CET,CTS",
                    function<void()>([](){}),
                    true, true, false, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLT,CET,CTS",
                    function<void()>([](){}),
                    true, false, true, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLT,CET,CTS",
                    function<void()>([](){}),
                    true, true, true, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                ));

            }
        }
    }
}
