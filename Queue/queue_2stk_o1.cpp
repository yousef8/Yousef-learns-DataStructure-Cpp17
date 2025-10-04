#include "../Stack/include/stack_array.hpp"
#include <iostream>

class Queue {
  public:
	Queue(int s) : stk1(s), stk2(s), size(s) {}

	void enqueue(int value) { // O(1)
		assert(!isFull());
		stk1.push(value);
		++added_elements;
	}

	int dequeue() { // O(1) amortized OR O(n) worst case
		assert(!isEmpty());

		if (stk2.isEmpty()) {
			move(stk1, stk2);
		}

		int value = stk2.pop();
		--added_elements;
		return value;
	}

	bool isEmpty() { return added_elements == 0; }

	bool isFull() { return added_elements == size; }

  private:
	Stack stk1;
	Stack stk2;
	int size{};
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

	std::cout << std::endl;

	// 1 2 3 4 5

	return 0;
}
