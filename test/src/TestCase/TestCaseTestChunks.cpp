#include <memory>

#include "TestCPP.h"
#include "TestCase/TestCaseTestChunks.h"

using TestCPP::TestCase;
using TestCPP::Util::debugLog;
using std::unique_ptr;

namespace TestCPP {
    namespace Testing {
        namespace TestCaseTests {
            void parameterVariationTestChunks () {
                debugLog("Start ctor param variation test chunks");

                debugLog("PassMessage param ctor test chunks");
                varyingPassMessageEnabled();
                debugLog("CaptureStdout param ctor test chunks");
                varyingCaptureStdout();
                debugLog("CaptureLog param ctor test chunks");
                varyingCaptureLog();
                debugLog("CaptureStderr param ctor test chunks");
                varyingCaptureStderr();
                debugLog("OCO Exact param ctor test chunks");
                varyingTestCaseOutCompareOptionsExact();
                debugLog("OCO Contains param ctor test chunks");
                varyingTestCaseOutCompareOptionsContains();

                debugLog("Ctor param variation test chunks complete");
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
                debugLog("CaptureLog param ctor test chunk FFF");
                auto test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLF",
                    function<void()>([](){}),
                    false, false, false
                ));

                debugLog("CaptureLog param ctor test chunk FFT");
                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COF,CLT",
                    function<void()>([](){}),
                    false, false, true
                ));

                debugLog("CaptureLog param ctor test chunk FTF");
                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLF",
                    function<void()>([](){}),
                    false, true, false
                ));

                debugLog("CaptureLog param ctor test chunk FTT");
                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NF,COT,CLT",
                    function<void()>([](){}),
                    false, true, true
                ));

                debugLog("CaptureLog param ctor test chunk TFF");
                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLF",
                    function<void()>([](){}),
                    true, false, false
                ));

                debugLog("CaptureLog param ctor test chunk TFT");
                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COF,CLT",
                    function<void()>([](){}),
                    true, false, true
                ));

                debugLog("CaptureLog param ctor test chunk TTF");
                test = unique_ptr<TestCase>(new TestCase(
                    "ConstructCase Test - w/NT,COT,CLF",
                    function<void()>([](){}),
                    true, true, false
                ));

                debugLog("CaptureLog param ctor test chunk TTT");
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
