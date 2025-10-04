#include "./include/array_queue.hpp"

class Stack {
  public:
	Stack(int size) : q(size) {}

	void push(int value) {
		int prev_queue_size = q.length();
		q.enqueue(value);
		while (prev_queue_size--) {
			q.enqueue(q.dequeue());
		}
	}

	void pop() { q.dequeue(); }

	bool isEmpty() { return q.isEmpty(); }

	int peek() { return q.front_val(); }

  private:
	Queue q;
};

int main() {
	Stack stk(3);
	stk.push(10);
	stk.push(20);
	stk.push(30);

	while (!stk.isEmpty()) {
		std::cout << stk.peek() << " ";
		stk.pop();
	} // 30 20 10

	return 0;
}
