#include "TestCPP.h"
#include "Exceptions/ExceptionsTests.h"

using TestCPP::Assertions;
using TestCPP::TestCPPException;
using TestCPP::TestFailedException;

namespace TestCPP {
    namespace Testing {
        namespace ExceptionsTests {
            constexpr const char* msg = "Test message";

            void TestTestCPPExceptionCtor() {
                Assertions::assertNoThrows([]() {
                    TestCPPException e(msg);
                });

                TestCPPException e(msg);
                Assertions::assertEquals(msg, e.what());

                e = TestCPPException(string(msg));
                Assertions::assertEquals(msg, e.what());
            }

            void TestTestFailedExceptionCtor() {
                Assertions::assertNoThrows([]() {
                    TestFailedException e(msg);
                });

                TestFailedException e(msg);
                Assertions::assertEquals(msg, e.what());

                e = TestFailedException(string(msg));
                Assertions::assertEquals(msg, e.what());
            }
        }
    }
}