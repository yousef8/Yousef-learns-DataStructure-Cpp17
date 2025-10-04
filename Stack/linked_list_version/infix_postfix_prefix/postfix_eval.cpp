#include "../../include/stack_ll.hpp"
#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>

double perform_operation(double operand1, double operand2, char op) {
	switch (op) {
	case '+':
		return operand1 + operand2;
	case '-':
		return operand1 - operand2;
	case '*':
		return operand1 * operand2;
	case '/': {
		if (operand2 == 0)
			throw std::runtime_error("Division by zero is not allowed");
		return operand1 / operand2;
	}
	case '^':
		return static_cast<int>(std::pow(operand1, operand2));
	default:
		throw std::invalid_argument("Invalid Operator");
	};
}

double evaluate_postfix(std::string postfix) {
	Stack<double> stk;

	for (auto &token : postfix) {
		if (std::isdigit(token)) {
			stk.push(token - '0');
			continue;
		}

		double operand2nd = stk.pop();
		double operand1st = stk.pop();
		stk.push(perform_operation(operand1st, operand2nd, token));
	}

	return !stk.isEmpty() ? stk.peek() : 0;
}

void runTests() {
	auto test_should_success = [](const std::string &expression,
								  double expected,
								  const std::string &description) {
		try {
			double result = evaluate_postfix(expression);
			assert(std::abs(result - expected) < 1e-6 && "Incorrect result");
			std::cout << "[  PASSED  ] " << description << "\n";
		} catch (const std::exception &e) {
			std::cout << "[  FAILED  ] " << description << ": " << e.what()
					  << "\n";
		}
	};
	auto test_should_fail = [](const std::string &expression, double expected,
							   const std::string &description) {
		try {
			double result = evaluate_postfix(expression);
			assert(std::abs(result - expected) < 1e-6 && "Incorrect result");
			std::cout << "[  FAILED  ] " << description << "\n";
		} catch (const std::exception &e) {
			std::cout << "[  PASSED  ] " << description << ": " << e.what()
					  << "\n";
		}
	};

	// Test cases
	test_should_success("52/", 2.5, "Division: 5 / 2");
	test_should_success("34+", 7, "Addition: 3 + 4");
	test_should_success("105 -", 5, "Subtraction: 10 - 5");
	test_should_success("63*", 18, "Multiplication: 6 * 3");
	test_should_success("84/", 2, "Division: 8 / 4");
	test_should_success("52/", 2.5, "Division with decimals: 5 / 2");
	test_should_success("12+3+", 6, "Complex expression: (1 + 2) + 3");
	test_should_success("123*+", 7, "Complex expression: 1 + 2 * 3");
	test_should_success("23*4+", 10, "Complex expression: 2 * 3 + 4");
	test_should_success("135*+72/-", 12.5,
						"Complex expression: 1 + 3 * 5 - 7 / 2");
	test_should_success("432^^", 262144, "Complex expression: 4 ^ 3 ^ 2");
	test_should_success("512+4*+3-", 14,
						"Complex expression: 5 + (1 + 2) * 4 - 3");
	test_should_success("34+2*7/", 2, "Chained operations: ((3 + 4) * 2) / 7");

	// Edge cases
	test_should_success("", 0, "Empty expression (should throw error)");
	test_should_fail("4+", 0, "Single operand (should throw error)");
	test_should_fail("90/", 0, "Division by zero (should throw error)");
}

int main() {
	runTests();
	return 0;
}
