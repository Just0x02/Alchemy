#ifndef __TEST_H__
#define __TEST_H__

#include <functional>
#include <alchemy/types.hpp>
#include <alchemy/color.hpp>
#include <alchemy/time.hpp>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <vector>


#define REGISTER_TEST(test_class) active_tests.push_back(new test_class())
#define RUN_TESTS() std::for_each(active_tests.begin(), active_tests.end(), [&](Test *test) { TestResult res = test->_RunWrapper(); if (!res.success) std::cout << alc::Color::ForegroundRGB(255, 80, 80) << "[FAIL][" << res.test_file << "][" << (string)(res.timer) << "] Test error! => " << res.err->what() << "\n" << alc::Color::reset(); else std::cout << alc::Color::ForegroundRGB(80, 255, 80) << "[SUCCESS][" << res.test_file << "][" << (string)(res.timer) << "] Test success!" << "\n" << alc::Color::reset(); })

struct TestResult
{
	bool success;

	string test_file, test_name, test_desc;

	alc::Timer timer;

	std::runtime_error *err = nullptr;
};

struct Test
{
	string test_name, test_desc, test_file;

	Test(string test_name, string test_desc, string test_file) : test_name(test_name), test_desc(test_desc), test_file(test_file)
	{

	};

	virtual ~Test() {};

	TestResult _RunWrapper()
	{
		TestResult res { true, this->test_file, this->test_name, this->test_desc };

		res.timer.begin();

		try {
			this->RunTest();
		} catch(std::runtime_error *err) {
			res.err = err;
			res.success = false;
		}

		res.timer.stop();

		return res;
	}

	virtual void RunTest() { throw new std::runtime_error("No test implemented!"); };
};

static std::vector<Test*> active_tests;


#endif // __TEST_H__