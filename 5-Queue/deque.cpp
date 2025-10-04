#include <cassert>
#include <iostream>
using namespace std;

class Deque {
	int size{};
	int front{0};
	int rear{0};
	int added_elements{};
	int *array{};

  public:
	Deque(int size) : size(size) { array = new int[size]; }

	~Deque() { delete[] array; }

	int next(int pos) {
		return (pos + 1) % size; //  Or shorter way
	}

	int prev(int pos) { return (pos - 1 + size) % size; }

	void enqueue_rear(int value) {
		assert(!isFull());
		array[rear] = value;
		rear = next(rear);
		added_elements++;
	}

	void enqueue_front(int value) {
		assert(!isFull());
		front = prev(front);
		array[front] = value;
		++added_elements;
	}

	int dequeue_front() {
		assert(!isEmpty());
		int value = array[front];
		front = next(front);
		--added_elements;
		return value;
	}

	int dequeue_rear() {
		assert(!isEmpty());
		rear = prev(rear);
		int value = array[rear];
		--added_elements;
		return value;
	}

	void display() {
		cout << "Front " << front << " - rear " << rear << "\t";
		if (isFull())
			cout << "full";
		else if (isEmpty()) {
			cout << "empty\n\n";
			return;
		}
		cout << "\n";

		for (int cur = front, step = 0; step < added_elements;
			 ++step, cur = next(cur))
			cout << array[cur] << " ";
		cout << "\n\n";
	}

	int isEmpty() { return added_elements == 0; }

	bool isFull() { return added_elements == size; }
};

int main() {

	Deque dq(6);

	dq.enqueue_front(3);
	dq.display();
	dq.enqueue_front(2);
	dq.enqueue_rear(4);
	dq.enqueue_front(1);
	dq.enqueue_front(5);
	dq.enqueue_front(6);
	dq.display();						// 1 2 3 4
	cout << dq.dequeue_rear() << "\n";	// 4
	dq.display();						// 1 2 3
	cout << dq.dequeue_front() << "\n"; // 1
	dq.display();						// 2 3
	cout << dq.dequeue_rear() << "\n";	// 3
	cout << dq.dequeue_front() << "\n"; // 2

	while (!dq.isEmpty())
		dq.dequeue_rear();
	dq.display(); //
	for (int i = 0; i < 6; ++i)
		dq.enqueue_rear(i + 10);
	dq.display(); //

	return 0;
}

/*
Front 5 - rear 0
3

Front 1 - rear 1	full
6 5 1 2 3 4

4
Front 1 - rear 0
6 5 1 2 3

6
Front 2 - rear 0
5 1 2 3

3
5
Front 3 - rear 3	empty

Front 3 - rear 3	full
10 11 12 13 14 15


 */
