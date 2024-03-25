#include "Test.h"

using TestCPP::TestSuite;
using std::string;
using std::make_tuple;
using std::function;

#include "tests.hpp"

int main(void)
{
	TestSuite suite(
        string("Demo Test Suite"),
        
		make_tuple(
			string("simpleTest"),
			function<void()>(simpleTest)
		),
        make_tuple(
			string("otherSimpleTest"),
			function<void()>(otherSimpleTest)
		)
	);

	suite.run();

	return 0;
}
