namespace TestCPP {
    namespace Testing {
        namespace TestSuiteTests {
            void TestConstructSuite () {
                TestSuite * test = new TestSuite(
                    string("Suite construction")
                );
                delete test;
            }

            void TestAssertTrue () {
                int lower = 5;
                int higher = 9;
                
                TestSuite::assertTrue(higher > lower,
                                      "Negated condtion!");
            }

            void TestAssertFalse () {
                int lower = 5;
                int higher = 9;
                
                TestSuite::assertFalse(higher < lower,
                                       "Negated condtion!");
            }

            void TestAssertNull () {
                string * nullString = nullptr;
                
                TestSuite::assertNull(nullString, "nullptr is null!");
            }

            void TestAssertNotNull () {
                string notNull("non-null");
                
                TestSuite::assertNotNull(
                    &notNull,
                    "A constructed std::string is not null!"
                );
                TestSuite::assertNotNull(
                    "non-null",
                    "A const char * is not null!"
                );
                
                int testInt = 5;
                
                TestSuite::assertNotNull(&testInt,
                                         "An int pointer is not null!");
            }
        }
    }
}
