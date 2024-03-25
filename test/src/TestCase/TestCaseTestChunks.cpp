#include "TestCase/TestCaseTestChunks.h"

using TestCPP::TestCase;

namespace TestCPP {
    namespace Testing {
        namespace TestCaseTests {
            void parameterVariationTestChunks() {
                varyingPassMessageEnabled();
                varyingCaptureStdout();
                varyingCaptureLog();
                varyingCaptureStderr();
                varyingTestCaseOutCompareOptionsExact();
                varyingTestCaseOutCompareOptionsContains();
            }
            
            void varyingPassMessageEnabled() {
                TestCase * test = new TestCase(
                    string("ConstructCase Test - w/NF"),
                    function<void()>([](){}),
                    false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT"),
                    function<void()>([](){}),
                    true
                );
                delete test;
            }
            
            void varyingCaptureStdout() {
                TestCase * test = new TestCase(
                    string("ConstructCase Test - w/NFCOF"),
                    function<void()>([](){}),
                    false, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NFCOT"),
                    function<void()>([](){}),
                    false, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NTCOF"),
                    function<void()>([](){}),
                    true, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NTCOT"),
                    function<void()>([](){}),
                    true, true
                );
                delete test;
            }
            
            void varyingCaptureLog() {
                TestCase * test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLF"),
                    function<void()>([](){}),
                    false, false, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLT"),
                    function<void()>([](){}),
                    false, false, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLF"),
                    function<void()>([](){}),
                    false, true, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLT"),
                    function<void()>([](){}),
                    false, true, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLF"),
                    function<void()>([](){}),
                    true, false, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLT"),
                    function<void()>([](){}),
                    true, false, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLF"),
                    function<void()>([](){}),
                    true, true, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLT"),
                    function<void()>([](){}),
                    true, true, true
                );
                delete test;
            }
            
            void varyingCaptureStderr() {
                TestCase * test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLF,CEF"),
                    function<void()>([](){}),
                    false, false, false, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLF,CET"),
                    function<void()>([](){}),
                    false, false, false, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLT,CEF"),
                    function<void()>([](){}),
                    false, false, true, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLF,CEF"),
                    function<void()>([](){}),
                    false, true, false, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLT,CEF"),
                    function<void()>([](){}),
                    false, true, true, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLF,CET"),
                    function<void()>([](){}),
                    false, true, false, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLT,CET"),
                    function<void()>([](){}),
                    false, false, true, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLT,CET"),
                    function<void()>([](){}),
                    false, true, true, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLF,CEF"),
                    function<void()>([](){}),
                    true, false, false, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLF,CET"),
                    function<void()>([](){}),
                    true, false, false, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLT,CEF"),
                    function<void()>([](){}),
                    true, false, true, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLF,CEF"),
                    function<void()>([](){}),
                    true, true, false, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLT,CEF"),
                    function<void()>([](){}),
                    true, true, true, false
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLF,CET"),
                    function<void()>([](){}),
                    true, true, false, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLT,CET"),
                    function<void()>([](){}),
                    true, false, true, true
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLT,CET"),
                    function<void()>([](){}),
                    true, true, true, true
                );
                delete test;
            }
            
            void varyingTestCaseOutCompareOptionsExact() {
                TestCase * test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLF,CEF,EX"),
                    function<void()>([](){}),
                    false, false, false, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLF,CET,EX"),
                    function<void()>([](){}),
                    false, false, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLT,CEF,EX"),
                    function<void()>([](){}),
                    false, false, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLF,CEF,EX"),
                    function<void()>([](){}),
                    false, true, false, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLT,CEF,EX"),
                    function<void()>([](){}),
                    false, true, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLF,CET,EX"),
                    function<void()>([](){}),
                    false, true, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLT,CET,EX"),
                    function<void()>([](){}),
                    false, false, true, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLT,CET,EX"),
                    function<void()>([](){}),
                    false, true, true, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLF,CEF,EX"),
                    function<void()>([](){}),
                    true, false, false, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLF,CET,EX"),
                    function<void()>([](){}),
                    true, false, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLT,CEF,EX"),
                    function<void()>([](){}),
                    true, false, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLF,CEF,EX"),
                    function<void()>([](){}),
                    true, true, false, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLT,CEF,EX"),
                    function<void()>([](){}),
                    true, true, true, false,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLF,CET,EX"),
                    function<void()>([](){}),
                    true, true, false, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLT,CET,EX"),
                    function<void()>([](){}),
                    true, false, true, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLT,CET,EX"),
                    function<void()>([](){}),
                    true, true, true, true,
                    TestCase::TestCaseOutCompareOptions::EXACT
                );
                delete test;
            }
            
            void varyingTestCaseOutCompareOptionsContains() {
                TestCase * test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLF,CEF,CTS"),
                    function<void()>([](){}),
                    false, false, false, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLF,CET,CTS"),
                    function<void()>([](){}),
                    false, false, false, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLT,CEF,CTS"),
                    function<void()>([](){}),
                    false, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLF,CEF,CTS"),
                    function<void()>([](){}),
                    false, true, false, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLT,CEF,CTS"),
                    function<void()>([](){}),
                    false, true, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLF,CET,CTS"),
                    function<void()>([](){}),
                    false, true, false, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COF,CLT,CET,CTS"),
                    function<void()>([](){}),
                    false, false, true, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NF,COT,CLT,CET,CTS"),
                    function<void()>([](){}),
                    false, true, true, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLF,CEF,CTS"),
                    function<void()>([](){}),
                    true, false, false, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLF,CET,CTS"),
                    function<void()>([](){}),
                    true, false, false, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLT,CEF,CTS"),
                    function<void()>([](){}),
                    true, false, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLF,CEF,CTS"),
                    function<void()>([](){}),
                    true, true, false, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLT,CEF,CTS"),
                    function<void()>([](){}),
                    true, true, true, false,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLF,CET,CTS"),
                    function<void()>([](){}),
                    true, true, false, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COF,CLT,CET,CTS"),
                    function<void()>([](){}),
                    true, false, true, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
                test = new TestCase(
                    string("ConstructCase Test - w/NT,COT,CLT,CET,CTS"),
                    function<void()>([](){}),
                    true, true, true, true,
                    TestCase::TestCaseOutCompareOptions::CONTAINS
                );
                delete test;
            }
        }
    }
}
