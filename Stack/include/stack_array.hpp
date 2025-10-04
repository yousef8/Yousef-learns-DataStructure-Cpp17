#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

class Stack {
  public:
	Stack(int size) : size(size), top(-1) { array = new int[size]; }

	~Stack() { delete[] array; }

	void push(int x) {
		if (isFull()) {
			throw std::overflow_error("Stack is full");
		}
		array[++top] = x;
	}

	int pop() {
		if (isEmpty()) {
			throw std::underflow_error("Stack is empty");
		}
		return array[top--];
	}

	int peek() const {
		assert(!isEmpty());
		return array[top];
	}

	void push_back(int x) {
		if (isFull()) {
			throw std::overflow_error("Stack is full");
		}

		if (isEmpty()) {
			push(x);
			return;
		}

		int last_top = pop();
		push_back(x);
		push(last_top);
	}

	void reverse() {
		if (isEmpty()) {
			return;
		}

		int last_top = pop();
		reverse();
		push_back(last_top);
	}

	int isFull() const { return top == size - 1; }

	int isEmpty() const { return top == -1; }

	int capacity() const { return top + 1; }

	void display() const {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}

  private:
	int size{};
	int top{};
	int *array{};
};
