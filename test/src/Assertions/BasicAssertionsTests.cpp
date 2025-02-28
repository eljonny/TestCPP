#include "TestCPP.h"
#include "Assertions/BasicAssertionsTests.h"

namespace TestCPP {
    namespace Testing {
        namespace AssertionsTests {
            void TestAssertEquals() {
                int expected = 5;
                int actual = 5;
                Assertions::assertEquals(expected, actual,
                                         "5 == 5");
            }

            void TestAssertEqualsNotEqual() {
                int notEqual = 3;
                int actual = 5;

                try {
                    Assertions::assertEquals(notEqual, actual,
                        "3 != 5");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "Equivalence assertion failed!\n3 != 5\nExpectation value: <3>\nActual: <5>\n",
                        e.what(),
                        "Should be: <Equivalence assertion failed!\n3 != 5\nExpectation value: <3>\nActual: <5>\n>"
                    );
                }
            }

            void TestAssertEqualsCStrings() {
                const char* expected = "Hello, World!";
                const char* actual = "Hello, World!";
                Assertions::assertEquals(expected, actual,
                    "Hello, World! == Hello, World!");
            }

            void TestAssertEqualsCStringsNotEqual() {
                const char* notEqual = "Hello World!";
                const char* actual = "Hello, World!";

                try {
                    Assertions::assertEquals(notEqual, actual,
                        "Hello World! != Hello, World!");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "Equivalence assertion failed!\nHello World! != Hello, World!\nExpectation value: <Hello World!>\nActual: <Hello, World!>\n",
                        e.what(),
                        "Should be: Hello World! != Hello, World!"
                    );
                }
            }

            void TestAssertNotEquals() {
                int shouldNotBe = 5;
                int actual = 9;
                Assertions::assertNotEquals(shouldNotBe, actual,
                                            "5 != 9");
            }

            void TestAssertNotEqualsEqual() {
                int shouldNotBe = 9;
                int actual = 9;

                try {
                    Assertions::assertNotEquals(shouldNotBe, actual,
                        "9 == 9");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "Non-Equivalence assertion failed!\n9 == 9\nExpectation value: <9>\nActual: <9>\n",
                        e.what(),
                        "Should be: 9 == 9"
                    );
                }
            }

            void TestAssertNotEqualsCStrings() {
                const char* shouldNotBe = "Hello, World!";
                const char* actual = "Goodbye, World!";
                Assertions::assertNotEquals(shouldNotBe, actual,
                    "Hello, World! != Goodbye, World!");
            }

            void TestAssertNotEqualsCStringsEqual() {
                const char* shouldNotBe = "Hello, World!";
                const char* actual = "Hello, World!";

                try {
                    Assertions::assertNotEquals(shouldNotBe, actual,
                        "Hello, World! == Hello, World!");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "Non-Equivalence assertion failed!\nHello, World! == Hello, World!\nExpectation value: <Hello, World!>\nActual: <Hello, World!>\n",
                        e.what(),
                        "Should be: Hello, World! == Hello, World!"
                    );
                }
            }

            void TestAssertNull() {
                string* nullString = nullptr;

                Assertions::assertNull(nullString, "nullptr is null!");
            }

            void TestAssertNullNotNull() {
                string nonnullString = "nullptr";

                try {
                    Assertions::assertNull(&nonnullString, "nullptr is not null!");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "Null assertion failed!\nnullptr is not null!\n",
                        e.what(),
                        "Should be: nullptr is not null!"
                    );
                }
            }

            void TestAssertNotNull() {
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

            void TestAssertNotNullNull() {
                string* nullString = nullptr;

                try {
                    Assertions::assertNotNull(nullString, "nullptr is null!");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "Not Null assertion failed!\nnullptr is null!\n",
                        e.what(),
                        "Should be: nullptr is null!"
                    );
                }
            }

            void TestAssertThrows() {
                auto shouldThrow = []() {
                    throw std::runtime_error("This should throw!");
                };
                Assertions::assertThrows(shouldThrow,
                                         "This should throw!");
            }

            void TestAssertThrowsDoesNotThrow() {
                auto shouldThrow = []() {
                    return;
                };

                try {
                    Assertions::assertThrows(shouldThrow,
                        "This should throw!");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "This should throw!",
                        e.what(),
                        "Should be: This should throw!"
                    );
                }
            }

            void TestAssertNoThrows() {
                auto shouldNotThrow = []() {
                    return;
                };
                Assertions::assertNoThrows(shouldNotThrow,
                                           "This should not throw!");
            }

            void TestAssertNoThrowsThrows() {
                auto shouldThrow = []() {
                    throw std::runtime_error("This should throw!");
                };

                try {
                    Assertions::assertNoThrows(shouldThrow,
                        "This should throw!");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "This should throw!",
                        e.what(),
                        "Should be: This should throw!"
                    );
                }
            }

            void TestAssertTrue () {
                int lower = 5;
                int higher = 9;

                Assertions::assertTrue(higher > lower,
                                       "Negated condtion!");
            }

            void TestAssertTrueNotTrue() {
                int lower = 5;
                int higher = 9;

                try {
                    Assertions::assertTrue(higher < lower,
                        "Negated condtion!");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "Boolean Truth assertion failed!\nNegated condtion!\n",
                        e.what(),
                        "Should be: Negated condtion!"
                    );
                }
            }

            void TestAssertFalse () {
                int lower = 5;
                int higher = 9;

                Assertions::assertFalse(higher < lower,
                                        "Negated condtion!");
            }

            void TestAssertFalseNotFalse() {
                int lower = 5;
                int higher = 9;

                try {
                    Assertions::assertFalse(higher > lower,
                        "Negated condtion!");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "Boolean False assertion failed!\nNegated condtion!\n",
                        e.what(),
                        "Should be: Negated condtion!"
                    );
                }
            }

            void TestFail() {
                try {
                    Assertions::fail("Forced test failure!");
                }
                catch (TestFailedException& e) {
                    Assertions::assertEquals(
                        "Forced test failure!",
                        e.what(),
                        "Should be: Forced test failure!"
                    );
                }
            }
        }
    }
}