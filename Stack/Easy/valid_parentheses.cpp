#include "stack_array.hpp"
#include <iostream>
#include <string>
#include <vector>

bool is_valid(std::string str)
{
	Stack stack{static_cast<int>(str.length())};
	char chars[126]{};
	chars['('] = ')';
	chars['['] = ']';
	chars['{'] = '}';

	for (char &para : str)
	{
		if (para == '(' || para == '[' || para == '{')
		{
			stack.push(para);
			continue;
		}

		if (stack.isEmpty() || chars[stack.pop()] != para)
			return false;
	}

	return stack.isEmpty();
}

void runTests()
{
	struct TestCase
	{
		std::string input;
		bool expected;
	};

	std::vector<TestCase> testCases = {{"()", true},	   {"([])", true},	  {"({[]})", true},	  {"(]", false},
									   {"([)]", false},	   {"(((", false},	  {"))", false},	  {"([]{})", true},
									   {"{[()()]}", true}, {"{[(])}", false}, {"([{}])(", false}, {"", true},
									   {"(", false},	   {"]", false},	  {"()", true},		  {"(]", false}};

	for (const auto &testCase : testCases)
	{
		bool result = is_valid(testCase.input);
		std::cout << "Input: \"" << testCase.input << "\" | Expected: " << (testCase.expected ? "true" : "false")
				  << " | Result: " << (result ? "true" : "false") << " | "
				  << (result == testCase.expected ? "PASS" : "FAIL") << std::endl;
	}
}

int main()
{
	runTests();
	return 0;
}
