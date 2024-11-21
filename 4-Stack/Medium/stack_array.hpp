#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

class Stack {
  private:
	int size{};
	int top{};
	int *array{};

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

	int peek() {
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
    if(isEmpty()){
      return;
    }

    int last_top = pop();
    reverse();
    push_back(last_top);
  }

	int isFull() { return top == size - 1; }

	int isEmpty() { return top == -1; }

	int capacity() { return top + 1; }

	void display() {
		for (int i = top; i >= 0; i--)
			cout << array[i] << " ";
		cout << "\n";
	}
};

