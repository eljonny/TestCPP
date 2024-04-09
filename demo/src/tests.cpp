#include "TestCPP.h"

namespace TestCPP {
    namespace Demo {
        namespace Tests {
            void simpleTest () {
                int lower = 5;
                int higher = 9;
                TestSuite::assertTrue(higher > lower, "Something is seriously wrong.");
            }

            void otherSimpleTest () {
                string s1 = string("A string");
                string s2 = string("another string");
                TestSuite::assertNotEquals(s1, s2);
            }
        }
    }
}
