#include "stack_array.hpp"
#include <iostream>
#include <string>
#include <vector>

std::string removeDuplicates(const std::string &s)
{
	int string_length = static_cast<int>(s.length());
	Stack uniques{string_length};
	std::string unique_string = "";

	for (int i{string_length - 1}; i >= 0; --i)
	{
		if (uniques.isEmpty() || uniques.peek() != s[i])
		{
			uniques.push(s[i]);
		}
		else
		{
			uniques.pop();
		}
	}

	while (!uniques.isEmpty())
	{
		unique_string += uniques.pop();
	}

	return unique_string;
}

void runTests()
{
	struct TestCase
	{
		std::string input;
		std::string expected;
	};

	std::vector<TestCase> testCases = {
		{"abbaca", "ca"},	  // Basic case with multiple removals
		{"azxxzy", "ay"},	  // Case with nested removals
		{"aabbcc", ""},		  // Case with all characters removable
		{"abccba", ""},		  // Symmetrical case with complete removal
		{"abcddcba", ""},	  // Palindrome with complete removal
		{"abc", "abc"},		  // No duplicates
		{"aa", ""},			  // Single pair removal
		{"a", "a"},			  // Single character
		{"aabbccddeeff", ""}, // Multiple pairs
		{"aabba", "a"},		  // Removal leaves some characters
		{"ababab", "ababab"}, // No adjacent duplicates
		{"bbaaccbb", ""}	  // Entire string collapses to empty
	};

	for (const auto &testCase : testCases)
	{
		std::string result = removeDuplicates(testCase.input);
		std::cout << "Input: \"" << testCase.input << "\" | Expected: \"" << testCase.expected << "\" | Result: \""
				  << result << "\" | " << (result == testCase.expected ? "PASS" : "FAIL") << std::endl;
	}
}

int main()
{
	runTests();
	return 0;
}
