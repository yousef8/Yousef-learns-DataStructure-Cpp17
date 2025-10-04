#include "../../include/stack_ll.hpp"
#include <cctype>
#include <iostream>
#include <string>

int precedence(char ch) {
	switch (ch) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return 0;
	}
}

bool isRightAssociative(char ch) { return ch == '^'; }
bool isOperand(char ch) { return isdigit(ch) || isalpha(ch); }

std::string infix_to_postfix(std::string infix) {
	infix += '-';
	Stack<int> stk;
	stk.push('#');
	std::string postfix{};

	for (auto &token : infix) {
		if (isOperand(token)) {
			postfix += token;
			continue;
		}

		if (token == '(') {
			stk.push(token);
			continue;
		}

		if (token == ')') {
			while (stk.peek() != '(')
				postfix += stk.pop();
			stk.pop();
			continue;
		}

		while (precedence(stk.peek()) > precedence(token) ||
			   (precedence(stk.peek()) == precedence(token) &&
				!isRightAssociative(token))) {
			postfix += stk.pop();
		}

		stk.push(token);
	}

	return postfix;
}

int main() {
	{
		std::string infix = "1+2+3";
		std::string expected_postfix = "12+3+";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "1+2*3";
		std::string expected_postfix = "123*+";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "2*3+4";
		std::string expected_postfix = "23*4+";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "1+3*5-8/2";
		std::string expected_postfix = "135*+82/-";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "2+3*4-5*6+7";
		std::string expected_postfix = "234*+56*-7+";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "(3+6)*(2-4)+7";
		std::string expected_postfix = "36+24-*7+";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "2+(3*(4-5*2)*(9/3+6))";
		std::string expected_postfix = "23452*-*93/6+*+";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "4^3^2";
		std::string expected_postfix = "432^^";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "5+4^3^2-9";
		std::string expected_postfix = "5432^^+9-";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "a+b*(c^d-e)^(f+G*h)-i";
		std::string expected_postfix = "abcd^e-fGh*+^*+i-";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}
	{
		std::string infix = "1+2^3^4*5-6";
		std::string expected_postfix = "1234^^5*+6-";
		std::string actual_postfix = infix_to_postfix(infix);
		assert(expected_postfix == actual_postfix);
		std::cout << infix << " ==> " << actual_postfix << " successfully\n";
	}

	std::cout << "\n============>ALL TESTS PASSED FULLY<=============\n";
	return 0;
}
