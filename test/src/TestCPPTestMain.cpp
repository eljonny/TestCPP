#include "Test.h"

using TestCPP::TestSuite;
using std::string;
using std::make_tuple;
using std::function;

#include "TestCPPTests.hpp"

int main(void)
{
	TestSuite suite(
		make_tuple(
			string("assertNull Test"),
			function<void()>(TestAssertNull)
		),
		make_tuple(
			string("assertNotNull Test"),
			function<void()>(TestAssertNotNull)
		),
		make_tuple(
			string("assertTrue Test"),
			function<void()>(TestAssertTrue)
		),
		make_tuple(
			string("assertFalse Test"),
			function<void()>(TestAssertFalse)
		)
	);

	suite.run();

	return 0;
}
