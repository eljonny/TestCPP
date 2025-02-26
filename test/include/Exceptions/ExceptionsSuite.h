#ifndef TESTCPP_EXCEPTIONS_SUITE_
#define TESTCPP_EXCEPTIONS_SUITE_

#include "ExceptionsTests.h"

namespace TestCPP {
    namespace Testing {
        namespace ExceptionsSuite {
            TestSuite suite(
                "TestCPP Exceptions Tests",

                make_tuple(
                    "TestFailedException Construction Test",
                    function<void()>(
                        ExceptionsTests::TestTestFailedExceptionCtor
                    )
                ),
                make_tuple(
                    "TestCPPException Construction Test",
                    function<void()>(
                        ExceptionsTests::TestTestCPPExceptionCtor
                    )
                )
            );
        }
    }
}

#endif
