#ifndef QUEUE_04102025_H
#define QUEUE_04102025_H

#include <cassert>
#include <iostream>

class Queue {
	int size{};
	int front{0};
	int rear{0};
	int added_elements{};
	int *array{};

  public:
	Queue(int size) : size(size) { array = new int[size]; }

	~Queue() { delete[] array; }

	int next(int pos) {
		return (pos + 1) % size; //  Or shorter way
	}

	void enqueue(int value) {
		assert(!isFull());
		array[rear] = value;
		rear = next(rear);
		added_elements++;
	}

	int dequeue() {
		assert(!isEmpty());
		int value = array[front];
		front = next(front);
		--added_elements;
		return value;
	}

	int front_val() {
		assert(!isEmpty());
		return array[front];
	}

	void display() {
		std::cout << "Front " << front << " - rear " << rear << "\t";
		if (isFull())
			std::cout << "full";
		else if (isEmpty()) {
			std::cout << "empty\n\n";
			return;
		}
		std::cout << "\n";

		for (int cur = front, step = 0; step < added_elements;
			 ++step, cur = next(cur))
			std::cout << array[cur] << " ";
		std::cout << "\n\n";
	}

	int isEmpty() { return added_elements == 0; }

	bool isFull() { return added_elements == size; }

	int length() { return added_elements; }
};
#endif
