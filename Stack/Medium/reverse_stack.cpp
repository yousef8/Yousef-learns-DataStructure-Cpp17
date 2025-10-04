#include "../include/stack_array.hpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
	// Test 1: Reverse an empty stack
	{
		Stack s(5);
		s.reverse();		 // Should not cause any errors
		assert(s.isEmpty()); // Stack remains empty
		cout << "Test 1 passed.\n";
	}

	// Test 2: Reverse a stack with a single element
	{
		Stack s(5);
		s.push(10);
		s.reverse();
		assert(s.peek() == 10); // Single element remains unchanged
		assert(s.capacity() == 1);
		cout << "Test 2 passed.\n";
	}

	// Test 3: Reverse a stack with multiple elements
	{
		Stack s(5);
		s.push(10);
		s.push(20);
		s.push(30);
		s.reverse();

		// After reversal, the elements should be in reverse order
		assert(s.pop() == 10); // Bottom-most element becomes top
		assert(s.pop() == 20);
		assert(s.pop() == 30); // Top-most element becomes bottom
		assert(s.isEmpty());
		cout << "Test 3 passed.\n";
	}

	// Test 4: Reverse a full stack
	{
		Stack s(3);
		s.push(1);
		s.push(2);
		s.push(3);
		s.reverse();

		// Verify the new order
		assert(s.pop() == 1); // Bottom-most element becomes top
		assert(s.pop() == 2);
		assert(s.pop() == 3); // Top-most element becomes bottom
		assert(s.isEmpty());
		cout << "Test 4 passed.\n";
	}

	// Test 5: Reverse a stack twice
	{
		Stack s(5);
		s.push(5);
		s.push(10);
		s.push(15);

		s.reverse(); // First reversal
		s.reverse(); // Second reversal (should return to original order)

		// Verify the original order is restored
		assert(s.pop() == 15);
		assert(s.pop() == 10);
		assert(s.pop() == 5);
		assert(s.isEmpty());
		cout << "Test 5 passed.\n";
	}

	return 0;
}
