#include "stack_ll.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>

// Test helper macros
#define TEST_START(name) std::cout << "[ RUNNING ] " << name << "\n";
#define TEST_PASS(name) std::cout << "[  PASSED  ] " << name << "\n";
#define TEST_FAIL(name, msg)                                                   \
	std::cout << "[  FAILED  ] " << name << ": " << msg << "\n";

// Individual test functions
void testPush() {
	TEST_START("Test Push")
	Stack<char> stack;
	stack.push('A');
	stack.push('B');
	stack.push('C');

	// Check stack contents using peek
	assert(stack.peek() == 'C' && "Top element should be C after pushes");
	stack.pop();
	assert(stack.peek() == 'B' && "Top element should be B after popping C");
	stack.pop();
	assert(stack.peek() == 'A' && "Top element should be A after popping B");

	TEST_PASS("Test Push")
}

void testPop() {
	TEST_START("Test Pop")
	Stack<char> stack;
	stack.push('A');
	stack.push('B');
	stack.push('C');

	// Pop and validate
	assert(stack.pop() == 'C' && "First pop should return C");
	assert(stack.pop() == 'B' && "Second pop should return B");
	assert(stack.pop() == 'A' && "Third pop should return A");

	// Check empty state
	assert(stack.isEmpty() &&
		   "Stack should be empty after popping all elements");

	// Test popping from an empty stack
	try {
		stack.pop();
		TEST_FAIL("Test Pop",
				  "Exception not thrown when popping from an empty stack")
	} catch (const std::underflow_error &) {
		TEST_PASS("Test Pop")
	}
}

void testPeek() {
	TEST_START("Test Peek")
	Stack<char> stack;
	stack.push('A');
	stack.push('B');
	stack.push('C');

	// Validate top element without popping
	assert(stack.peek() == 'C' &&
		   "Peek should return C without modifying stack");
	stack.pop();
	assert(stack.peek() == 'B' && "Peek should return B after popping C");
	TEST_PASS("Test Peek")
}

void testIsEmpty() {
	TEST_START("Test IsEmpty")
	Stack<char> stack;

	// Empty check
	assert(stack.isEmpty() && "Stack should be empty initially");

	// Push and check again
	stack.push('A');
	assert(!stack.isEmpty() &&
		   "Stack should not be empty after pushing an element");

	// Pop and check again
	stack.pop();
	assert(stack.isEmpty() &&
		   "Stack should be empty after popping the only element");
	TEST_PASS("Test IsEmpty")
}

void testDisplay() {
	TEST_START("Test Display")
	Stack<char> stack;
	stack.push('A');
	stack.push('B');
	stack.push('C');

	// Display stack
	std::cout << "Expected display: C B A\n";
	std::cout << "Actual display: ";
	stack.display();
	TEST_PASS("Test Display")
}

void runTests() {
	testPush();
	testPop();
	testPeek();
	testIsEmpty();
	testDisplay();
}

int main() {
	runTests();
	return 0;
}
