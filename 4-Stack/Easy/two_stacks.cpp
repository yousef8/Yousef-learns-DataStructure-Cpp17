#include <iostream>
#include <cassert>

class Stack
{
  private:
	int size{};
	int top{};
	int *array{};

  public:
	Stack(int size) : size(size), top(-1)
	{
		array = new int[size];
	}

	~Stack()
	{
		delete[] array;
	}

	void push(int x)
	{
		assert(!isFull());
		array[++top] = x;
	}

	int pop()
	{
		assert(!isEmpty());
		return array[top--];
	}

	int peek()
	{
		assert(!isEmpty());
		return array[top];
	}

	int isFull()
	{
		return top == size - 1;
	}

	int isEmpty()
	{
		return top == -1;
	}

	void display()
	{
		for (int i = top; i >= 0; i--)
			std::cout << array[i] << " ";
		std::cout << "\n";
	}
};

// Test functions for each case
void testCase1() {
    TwoStack ts(100);
    ts.push(1, 10);
    ts.push(1, 20);
    ts.push(1, 30);
    assert(ts.pop(1) == 30);
    assert(ts.peek(1) == 20);
    std::cout << "Test case 1 passed.\n";
}

void testCase2() {
    TwoStack ts(100);
    ts.push(2, 100);
    ts.push(2, 200);
    ts.push(2, 300);
    assert(ts.pop(2) == 300);
    assert(ts.peek(2) == 200);
    std::cout << "Test case 2 passed.\n";
}

void testCase3() {
    TwoStack ts(100);
    ts.push(1, 10);
    ts.push(2, 100);
    ts.push(1, 20);
    ts.push(2, 200);
    assert(ts.pop(1) == 20);
    assert(ts.pop(2) == 200);
    std::cout << "Test case 3 passed.\n";
}

void testCase4() {
    TwoStack ts(100);
    for (int i = 0; i < 50; ++i) ts.push(1, i);
    for (int i = 0; i < 50; ++i) ts.push(2, i);
    assert(ts.isFull());
    std::cout << "Test case 4 passed.\n";
}

void testCase5() {
    TwoStack ts(100);
    for (int i = 0; i < 50; ++i) ts.push(1, i);
    for (int i = 0; i < 50; ++i) ts.push(2, i);
    try {
        ts.push(1, 100); // Should fail
        assert(false); // Shouldn't reach here
    } catch (const std::overflow_error&) {
        std::cout << "Test case 5 passed.\n";
    }
}

void testCase6() {
    TwoStack ts(100);
    try {
        ts.pop(1); // Should fail
        assert(false); // Shouldn't reach here
    } catch (const std::underflow_error&) {
        std::cout << "Test case 6 passed (Stack 1 empty pop).\n";
    }

    try {
        ts.pop(2); // Should fail
        assert(false); // Shouldn't reach here
    } catch (const std::underflow_error&) {
        std::cout << "Test case 6 passed (Stack 2 empty pop).\n";
    }
}

void testCase7() {
    TwoStack ts(100);
    try {
        ts.peek(1); // Should fail
        assert(false); // Shouldn't reach here
    } catch (const std::underflow_error&) {
        std::cout << "Test case 7 passed (Stack 1 empty peek).\n";
    }

    try {
        ts.peek(2); // Should fail
        assert(false); // Shouldn't reach here
    } catch (const std::underflow_error&) {
        std::cout << "Test case 7 passed (Stack 2 empty peek).\n";
    }
}

void testCase8() {
    TwoStack ts(100);
    for (int i = 0; i < 50; ++i) ts.push(1, i);
    for (int i = 0; i < 50; ++i) ts.push(2, i);
    assert(ts.isFull());
    std::cout << "Test case 8 passed.\n";
}

int main() {
    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();
    testCase6();
    testCase7();
    testCase8();
    std::cout << "All test cases passed successfully.\n";
    return 0;
}
