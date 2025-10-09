#include <cassert>
#include <iostream>

class CircularQueue {
  public:
	CircularQueue(int size) : size(size + 1) { array = new int[size + 1]; }

	~CircularQueue() { delete[] array; }

	void enqueue(int value) {
		assert(!isFull());
		array[rear] = value;
		rear = next(rear);
	}

	int dequeue() {
		assert(!isEmpty());
		int value = array[front];
		front = next(front);
		return value;
	}

	int front_val() const {
		assert(!isEmpty());
		return array[front];
	}

	void display() const {
		std::cout << "Front " << front << " - rear " << rear << "\t";
		if (isFull()) {
			std::cout << "full";
		} else if (isEmpty()) {
			std::cout << "empty\n\n";
			return;
		}
		std::cout << "\n";
		for (int cur = front; cur != rear; cur = next(cur))
			std::cout << array[cur] << " ";
		std::cout << "\n\n";
	}

	bool isEmpty() const { return rear == front; }

	bool isFull() const { return front == next(rear); }

  private:
	int size{};
	int front{0};
	int rear{0};
	int *array{};

	int next(int pos) const { return (pos + 1) % size; }
};

int main() {
	CircularQueue qu(6);
	assert(qu.isEmpty());
	qu.display();

	for (int i = 1; i <= 6; ++i) {
		assert(!qu.isFull());
		qu.enqueue(i);
		qu.display();
	}

	assert(qu.isFull());

	for (int i = 1; i <= 6; ++i) {
		assert(!qu.isEmpty());
		qu.dequeue();
		// qu.display();
	}

	qu.display();

	for (int i = 1; i <= 6; ++i) {
		assert(!qu.isFull());
		qu.enqueue(i);
		qu.display();
	}

	qu.dequeue();
	assert(!qu.isFull());
	qu.enqueue(7);
	assert(qu.isFull());
	qu.display();

	qu.dequeue();
	qu.dequeue();
	assert(!qu.isFull());
	qu.enqueue(8);
	assert(!qu.isFull());
	qu.display();
	qu.enqueue(9);
	assert(qu.isFull());
	qu.display();

	for (int i = 1; i <= 6; ++i) {
		assert(!qu.isEmpty());
		qu.dequeue();
		qu.display();
	}

	return 0;
}

/*
Front 0 - rear 0	empty

Front 0 - rear 1
1

Front 0 - rear 2
1 2

Front 0 - rear 3
1 2 3

Front 0 - rear 4
1 2 3 4

Front 0 - rear 5
1 2 3 4 5

Front 0 - rear 0	full
1 2 3 4 5 6

Front 0 - rear 1
1

Front 0 - rear 2
1 2

Front 0 - rear 3
1 2 3

Front 0 - rear 4
1 2 3 4

Front 0 - rear 5
1 2 3 4 5

Front 0 - rear 0	full
1 2 3 4 5 6

Front 1 - rear 1	full
2 3 4 5 6 7

Front 3 - rear 2
4 5 6 7 8

Front 3 - rear 3	full
4 5 6 7 8 9

Front 4 - rear 3
5 6 7 8 9

Front 5 - rear 3
6 7 8 9

Front 0 - rear 3
7 8 9

Front 1 - rear 3
8 9

Front 2 - rear 3
9

Front 3 - rear 3	empty


Observe for empty case: we always have rear = front
Observe for full case: always next(rear) = front
as we left one empty element between them

With current design choices, we can detect isEmpty and isFull
*/
