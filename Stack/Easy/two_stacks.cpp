#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

class TwoStack
{
  private:
	int size{};
	int offset{2};
	int added_elements{0};
	int top[2]{-1, -2};
	int *array{};

  public:
	TwoStack(int size) : size{size}
	{
		array = new int[size * 2];
	}

	~TwoStack()
	{
		delete[] array;
	}

	void push(int idx, int x)
	{
		assert(idx > 0 && idx < 3);
		if (isFull())
		{
			throw std::overflow_error("Stack overflow!");
		}
		top[idx - 1] += offset;
		array[top[idx - 1]] = x;
		++added_elements;
	}

	int pop(int idx)
	{
		assert(idx > 0 && idx < 3);
		if (isEmpty())
		{
			throw std::underflow_error("Stack underflow!");
		}
		int old_top = array[top[idx - 1]];
		top[idx - 1] -= offset;
		--added_elements;
		return old_top;
	}

	int peek(int idx)
	{
		if (isEmpty())
		{
			throw std::underflow_error("Stack Underflow!");
		}
		return array[top[idx - 1]];
	}

	int isFull()
	{
		return added_elements == size;
	}

	int isEmpty()
	{
		return added_elements == 0;
	}

	void display(int idx)
	{
		for (int i = top[idx - 1]; i >= 0; i -= offset)
			std::cout << array[i] << " ";
		std::cout << "\n";
	}
};

// Test functions for each case
void testCase1()
{
	TwoStack ts(100);
	ts.push(1, 10);
	ts.push(1, 20);
	ts.push(1, 30);
	assert(ts.pop(1) == 30);
	assert(ts.peek(1) == 20);
	std::cout << "Test case 1 passed.\n";
}

void testCase2()
{
	TwoStack ts(100);
	ts.push(2, 100);
	ts.push(2, 200);
	ts.push(2, 300);
	assert(ts.pop(2) == 300);
	assert(ts.peek(2) == 200);
	std::cout << "Test case 2 passed.\n";
}

void testCase3()
{
	TwoStack ts(100);
	ts.push(1, 10);
	ts.push(2, 100);
	ts.push(1, 20);
	ts.push(2, 200);
	assert(ts.pop(1) == 20);
	assert(ts.pop(2) == 200);
	std::cout << "Test case 3 passed.\n";
}

void testCase4()
{
	TwoStack ts(100);
	for (int i = 0; i < 50; ++i)
		ts.push(1, i);
	for (int i = 0; i < 50; ++i)
		ts.push(2, i);
	assert(ts.isFull());
	std::cout << "Test case 4 passed.\n";
}

void testCase5()
{
	TwoStack ts(100);
	for (int i = 0; i < 50; ++i)
		ts.push(1, i);
	for (int i = 0; i < 50; ++i)
		ts.push(2, i);
	try
	{
		ts.push(1, 100); // Should fail
		assert(false);	 // Shouldn't reach here
	}
	catch (const std::overflow_error &)
	{
		std::cout << "Test case 5 passed.\n";
	}
}

void testCase6()
{
	TwoStack ts(100);
	try
	{
		ts.pop(1);	   // Should fail
		assert(false); // Shouldn't reach here
	}
	catch (const std::underflow_error &)
	{
		std::cout << "Test case 6 passed (Stack 1 empty pop).\n";
	}

	try
	{
		ts.pop(2);	   // Should fail
		assert(false); // Shouldn't reach here
	}
	catch (const std::underflow_error &)
	{
		std::cout << "Test case 6 passed (Stack 2 empty pop).\n";
	}
}

void testCase7()
{
	TwoStack ts(100);
	try
	{
		ts.peek(1);	   // Should fail
		assert(false); // Shouldn't reach here
	}
	catch (const std::underflow_error &)
	{
		std::cout << "Test case 7 passed (Stack 1 empty peek).\n";
	}

	try
	{
		ts.peek(2);	   // Should fail
		assert(false); // Shouldn't reach here
	}
	catch (const std::underflow_error &)
	{
		std::cout << "Test case 7 passed (Stack 2 empty peek).\n";
	}
}

void testCase8()
{
	TwoStack ts(100);
	for (int i = 0; i < 50; ++i)
		ts.push(1, i);
	for (int i = 0; i < 50; ++i)
		ts.push(2, i);
	assert(ts.isFull());
	std::cout << "Test case 8 passed.\n";
}

int main()
{
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
