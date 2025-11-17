#ifndef TEST_SUITE_HPP_17112025
#define TEST_SUITE_HPP_17112025

#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <typename T> class TestSuite {
  public:
	struct TestCase {
		std::string name;
		std::function<T()> test_func;
		T expected;
	};

	void addTest(const std::string &name, std::function<T()> test_func,
				 const T &expected) {
		tests.push_back({name, test_func, expected});
	}

	void run() {
		int passed = 0;
		int failed = 0;

		for (const auto &test : tests) {
			T result = test.test_func();
			if (result == test.expected) {
				passed++;
				std::cout << "✓ " << test.name << "\n";
			} else {
				failed++;
				std::cout << "✗ " << test.name << "\n";
				std::cout << "  Expected: " << test.expected << "\n";
				std::cout << "  Actual:   " << result << "\n";
			}
		}

		std::cout << "===========================================\n";
		std::cout << passed << " passed\n";
		std::cout << failed << " failed\n";
		if (failed == 0) {
			std::cout << "🎉 All tests passed!\n";
		};
		std::cout << "===========================================\n";
	}

  private:
	std::vector<TestCase> tests;
};

#endif // TEST_SUITE_HPP_17112025