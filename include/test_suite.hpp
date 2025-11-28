#ifndef TEST_SUITE_HPP_17112025
#define TEST_SUITE_HPP_17112025

#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// Type trait to detect if T can be printed with operator<<
template <typename T, typename = void> struct is_printable : std::false_type {};

template <typename T>
struct is_printable<T, std::void_t<decltype(std::declval<std::ostream &>()
											<< std::declval<T>())>>
	: std::true_type {};

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

	void setFormatter(std::function<std::string(const T &)> formatter) {
		custom_formatter = formatter;
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
				if (custom_formatter) {
					std::cout
						<< "  Expected: " << custom_formatter(test.expected)
						<< "\n";
					std::cout << "  Actual:   " << custom_formatter(result)
							  << "\n";
				} else {
					printValue("  Expected: ", test.expected);
					printValue("  Actual:   ", result);
				}
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
	std::function<std::string(const T &)> custom_formatter;

	// Print value if it's printable, otherwise print a generic message
	template <typename U>
	void printValue(const std::string &label, const U &value) {
		if constexpr (is_printable<U>::value) {
			std::cout << label << value << "\n";
		} else {
			std::cout << label << "<non-printable type>\n";
		}
	}
};

#endif // TEST_SUITE_HPP_17112025