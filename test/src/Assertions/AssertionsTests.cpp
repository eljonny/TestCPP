#include "TestCPP.h"
#include "Assertions/AssertionsTests.h"

namespace TestCPP {
    namespace Testing {
        namespace AssertionsTests {
            void TestAssertTrue () {
                int lower = 5;
                int higher = 9;

                Assertions::assertTrue(higher > lower,
                                      "Negated condtion!");
            }

            void TestAssertFalse () {
                int lower = 5;
                int higher = 9;

                Assertions::assertFalse(higher < lower,
                                       "Negated condtion!");
            }

            void TestAssertNull () {
                string * nullString = nullptr;

                Assertions::assertNull(nullString, "nullptr is null!");
            }

            void TestAssertNotNull () {
                string notNull("non-null");

                Assertions::assertNotNull(
                    &notNull,
                    "A constructed std::string is not null!"
                );
                Assertions::assertNotNull(
                    "non-null",
                    "A const char * is not null!"
                );

                int testInt = 5;

                Assertions::assertNotNull(&testInt,
                                         "An int pointer is not null!");
            }
        }
    }
}