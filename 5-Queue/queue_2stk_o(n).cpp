#include "../4-Stack/Easy/stack_array.hpp"
#include <iostream>

class Queue {
  public:
	Queue(int size) : stk1(size), stk2(size) {}

	void enqueue(int value) {
		assert(!stk1.isFull());
		move(stk1, stk2);

		stk1.push(value);

		move(stk2, stk1);
		++added_elements;
	}

	int dequeue() {
		assert(!stk1.isEmpty());
		int value = stk1.pop();
		--added_elements;
		return value;
	}

	bool isEmpty() { return stk1.isEmpty(); }

	bool isFull() { return stk1.isFull(); }

  private:
	Stack stk1;
	Stack stk2;
	int added_elements{0};

	void move(Stack &from, Stack &to) {
		while (!from.isEmpty()) {
			to.push(from.pop());
		}
	}
};

int main() {
	Queue q(6);

	for (int i = 1; i <= 3; ++i) {
		q.enqueue(i);
	}

	std::cout << q.dequeue() << " ";

	for (int i = 4; i <= 5; ++i) {
		q.enqueue(i);
	}

	while (!q.isEmpty()) {
		std::cout << q.dequeue() << " ";
	}

	// 1 2 3 4 5

	return 0;
}
