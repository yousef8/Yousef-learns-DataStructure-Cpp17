#include "../include/stack_array.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
	// Test 1: Simple push_back on an empty stack
	{
		Stack s(5);
		s.push_back(10);
		assert(s.peek() == 10); // Top should now be 10
		assert(s.capacity() == 1);
		cout << "Test 1 passed.\n";
	}

	// Test 2: push_back on a non-empty stack
	{
		Stack s(5);
		s.push(20);
		s.push(30);
		s.push_back(10); // Insert 10 at the bottom

		// Check that the top remains the same
		assert(s.peek() == 30);

		// Check the order by popping all elements
		assert(s.pop() == 30); // Topmost element
		assert(s.pop() == 20); // Next element
		assert(s.pop() == 10); // Bottom element
		assert(s.isEmpty());
		cout << "Test 2 passed.\n";
	}

	// Test 3: push_back on a full stack
	{
		Stack s(3);
		s.push(40);
		s.push(50);
		s.push(60);

		try {
			s.push_back(10); // Should trigger assertion failure
		} catch (std::overflow_error const &e) {
			cout << "Test 3 passed (assertion failed as expected).\n";
		}
	}

	// Test 4: push_back multiple times
	{
		Stack s(5);
		s.push(70);
		s.push(80);
		s.push_back(60); // Insert 60 at the bottom
		s.push_back(50); // Insert 50 at the bottom

		// Check the order by popping all elements
		assert(s.pop() == 80); // Topmost element
		assert(s.pop() == 70);
		assert(s.pop() == 60);
		assert(s.pop() == 50);
		assert(s.isEmpty());
		cout << "Test 4 passed.\n";
	}

	return 0;
}
