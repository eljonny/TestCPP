/*
	This is free and unencumbered software released into the public domain.

	Anyone is free to copy, modify, publish, use, compile, sell, or
	distribute this software, either in source code form or as a compiled
	binary, for any purpose, commercial or non-commercial, and by any
	means.

	In jurisdictions that recognize copyright laws, the author or authors
	of this software dedicate any and all copyright interest in the
	software to the public domain. We make this dedication for the benefit
	of the public at large and to the detriment of our heirs and
	successors. We intend this dedication to be an overt act of
	relinquishment in perpetuity of all present and future rights to this
	software under copyright law.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
	IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.

	For more information, please refer to <http://unlicense.org/>
 */

//Original author: Jonathan Hyry CSU-Fullerton SECS 6896-02 Fall 2014/15

#ifndef TESTFRAMEWORK_CLASSES
#define TESTFRAMEWORK_CLASSES

#include <iostream>
#include <sstream>
#include <functional>
#include <tuple>
#include <vector>
#include <chrono>
#include <regex>

class TestCase {

	using TimeT = std::chrono::nanoseconds;

public:
	TestCase(
		std::string testName,
		std::function<void()> test,
		bool testPassedMessage = true
	);
	bool go();
	void setNotifyPassed(bool);
	unsigned long long getLastRuntime();

private:
	bool notifyTestPassed;
	bool pass;
	unsigned long long lastRunTime;
	std::string testName;
	std::function<void()> test;

	template<typename F, typename ...Args>
	static TimeT duration(F func, Args&&... args)
	{
		auto start = std::chrono::system_clock::now();
		func(std::forward<Args>(args)...);
		return std::chrono::duration_cast<TimeT>(std::chrono::system_clock::now()-start);
	}
};

class TestSuite {

public:

	template<typename... TestType>
	TestSuite(typename std::enable_if<sizeof...(TestType) == 0>::type) {
		this->testPassedMessage = true;
		this->tests = std::vector<TestCase>();
	}

	template<typename... TestType>
	TestSuite(TestType ...tests) {

		this->testPassedMessage = true;
		this->tests = std::vector<TestCase>();

		this->addTests(tests...);
	}

	template<typename T>
	void addTest(T test);

	template<typename... OtherTests>
	typename std::enable_if<sizeof...(OtherTests) == 0>::type
	inline addTests() { }

	template<typename Test, typename... OtherTests>
	void addTests(Test test, OtherTests ...tests) {
		addTest(test);
		addTests(tests...);
	}

	template<typename T, typename... ConstructionArgs>
	static T getTestObject(ConstructionArgs ...args) {
		return T(args...);
	}

	void setSuiteName(std::string testSuiteName);

	static std::string getRegExpErrorString(std::regex_constants::error_type errType);

	template<typename T1, typename T2>
	static void assertEquals(
			T1 expected, T2 actual,
			std::string failureMessage =
				std::string("Arguments are not equivalent!")
		)
	{
		if(expected != actual) {
			std::ostringstream err;

			err << "Equivalence assertion failed!" << std::endl;
			err << failureMessage << std::endl;
			err << "Expected: <" << expected << ">" << std::endl;
			err << "Actual: <" << actual << ">" << std::endl;

			throw err.str();
		}
	}

	template<typename T1, typename T2>
	static void assertNotEquals(
			T1 expected, T2 actual,
			std::string failureMessage =
				std::string("Arguments are equivalent!")
		)
	{
		if(expected == actual) {
			std::ostringstream err;

			err << "Non-Equivalence assertion failed!" << std::endl;
			err << failureMessage << std::endl;
			err << "Expected: <" << expected << ">" << std::endl;
			err << "Actual: <" << actual << ">" << std::endl;

			throw err.str();
		}
	}

	template<typename T>
	static void assertNull(
			T ptr,
			std::string failureMessage =
				std::string("Object is not null!")
		)
	{
		bool null = ptr == nullptr;

		if(!null) {
			std::ostringstream err;

			err << "Null assertion failed!" << std::endl;
			err << failureMessage << std::endl;

			throw err.str();
		}
	}

	template<typename T>
	static void assertNotNull(
			T ptr,
			std::string failureMessage =
				std::string("Object is null!")
		)
	{
		bool notNull = ptr != nullptr;

		if(!notNull) {
			std::ostringstream err;

			err << "Not Null assertion failed!" << std::endl;
			err << failureMessage << std::endl;

			throw err.str();
		}
	}

	static void assertTrue(
		bool condition,
		std::string failureMessage =
			std::string("Condition is false!")
	);

	static void assertFalse(
		bool condition,
		std::string failureMessage =
			std::string("Condition is true!")
	);

	static void fail(
		std::string failureMessage =
			std::string("Test failed!")
	);

	void enableTestPassedMessage();
	void disableTestPassedMessage();

	void run();

private:
	bool testPassedMessage;
	bool lastRunSucceeded;
	unsigned lastRunSuccessCount;
	unsigned lastRunFailCount;
	unsigned long long totalRuntime;
	std::string suiteName;
	std::vector<TestCase> tests;
};

#endif
