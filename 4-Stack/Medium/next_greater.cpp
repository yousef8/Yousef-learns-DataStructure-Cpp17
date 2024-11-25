#include "stack_array.hpp"
#include <cassert>
#include <iostream>
#include <vector>

std::vector<int> nextGreaterElement(std::vector<int> elements) {
	Stack stk(elements.size() + 1);
	std::vector<int> res(elements.size());

	for (int i(elements.size() - 1); i >= 0; --i) {
		while (!stk.isEmpty() && stk.peek() <= elements[i]) {
			stk.pop();
		}

		res[i] = stk.isEmpty() ? -1 : stk.peek();

		if (elements[i] > elements[i - 1]) {
			stk.push(elements[i]);
		}
	}

	return res;
}

int main() {
	// Test Case 1: General case
	{
		std::vector<int> input = {10, 5, 7, 15, 11};
		std::vector<int> expected = {15, 7, 15, -1, -1};
		auto actual = nextGreaterElement(input);
		assert(actual == expected);
	}

	// Test Case 2: All elements are in ascending order
	{
		std::vector<int> input = {1, 2, 3, 4, 5};
		std::vector<int> expected = {2, 3, 4, 5, -1};
		assert(nextGreaterElement(input) == expected);
	}

	// Test Case 3: All elements are in descending order
	{
		std::vector<int> input = {5, 4, 3, 2, 1};
		std::vector<int> expected = {-1, -1, -1, -1, -1};
		assert(nextGreaterElement(input) == expected);
	}

	// Test Case 4: Mixed values with duplicates
	{
		std::vector<int> input = {2, 1, 2, 4, 3};
		std::vector<int> expected = {4, 2, 4, -1, -1};
		assert(nextGreaterElement(input) == expected);
	}

	// Test Case 5: Single element
	{
		std::vector<int> input = {42};
		std::vector<int> expected = {-1};
		assert(nextGreaterElement(input) == expected);
	}

	// Test Case 6: Repeated elements
	{
		std::vector<int> input = {7, 7, 7, 7};
		std::vector<int> expected = {-1, -1, -1, -1};
		assert(nextGreaterElement(input) == expected);
	}

	// Test Case 7: Negative values
	{
		std::vector<int> input = {-5, -2, -3, -1};
		std::vector<int> expected = {-2, -1, -1, -1};
		assert(nextGreaterElement(input) == expected);
	}

	// Test Case 8: Mixed positive and negative values
	{
		std::vector<int> input = {3, -2, 4, -1, 5};
		std::vector<int> expected = {4, 4, 5, 5, -1};
		auto actual = nextGreaterElement(input);
		assert(actual == expected);
	}

	// Test Case 9: Large numbers
	{
		std::vector<int> input = {100000, 99999, 100001};
		std::vector<int> expected = {100001, 100001, -1};
		assert(nextGreaterElement(input) == expected);
	}

	// Test Case 10: Empty array
	{
		std::vector<int> input = {};
		std::vector<int> expected = {};
		assert(nextGreaterElement(input) == expected);
	}

	std::cout << "All test cases passed!" << std::endl;
	return 0;
}
