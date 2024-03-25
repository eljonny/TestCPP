#include "Test.h"

using TestCPP::TestCase;
using TestCPP::TestSuite;
using std::string;
using std::make_tuple;
using std::function;

#include "TestCase/TestCaseSuite.hpp"

int main(void)
{
	TestCPP::Testing::TestCaseSuite::suite.run();

	return 0;
}
