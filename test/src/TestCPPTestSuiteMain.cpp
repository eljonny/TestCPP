#include "Test.h"

using TestCPP::TestCase;
using TestCPP::TestSuite;
using std::string;
using std::make_tuple;
using std::function;

#include "TestSuite/TestSuiteSuite.hpp"

int main(void)
{
	TestCPP::Testing::TestSuiteSuite::suite.run();

	return 0;
}
