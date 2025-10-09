#include "./include/array_queue.hpp"

class PriorityQueue {
  public:
	PriorityQueue(int size)
		: capacity{size}, queues{Queue(size), Queue(size), Queue(size)} {}

	PriorityQueue(const PriorityQueue &) = delete;
	PriorityQueue &operator=(const PriorityQueue &other) = delete;

	void enqueue(int value, int priority) {
		assert(priority >= 1 && priority <= 3);
		assert(!isFull());

		queues[priority - 1].enqueue(value);

		++added_elements;
	}

	int dequeue() {
		assert(!isEmpty());

		for (int i = 2; i >= 0; --i) {
			if (!queues[i].isEmpty()) {
				--added_elements;
				return queues[i].dequeue();
			}
		}
		assert(false &&
			   "No elements to dequeue"); // This line should never be reached
		return -1;
	}

	bool isFull() const { return added_elements == capacity; }

	bool isEmpty() const { return added_elements == 0; }

	void display() const {
		for (int i = 2; i >= 0; --i) {
			std::cout << "Priority #" << (i + 1) << " tasks: ";
			queues[i].display();
		}
	}

  private:
	Queue queues[3];
	int capacity{};
	int added_elements{0};
};

int main() {
	PriorityQueue tasks(8);

	tasks.enqueue(1131, 1);
	tasks.enqueue(3111, 3);
	tasks.enqueue(2211, 2);
	tasks.enqueue(3161, 3);

	tasks.display();
	// Priority #3 tasks: 3111 3161
	// Priority #2 tasks: 2211
	// Priority #1 tasks: 1131

	std::cout << tasks.dequeue() << "\n";
	// 3111

	std::cout << tasks.dequeue() << "\n";
	// 3161

	tasks.enqueue(1535, 1);
	tasks.enqueue(2815, 2);
	tasks.enqueue(3845, 3);
	tasks.enqueue(3145, 3);
	tasks.display();
	// Priority #3 tasks: 3845 3145
	// Priority #2 tasks: 2211 2815
	// Priority #1 tasks: 1131 1535

	while (!tasks.isEmpty()) {
		std::cout << tasks.dequeue() << " "; // 3845 3145 2211 2815 1131 1535
	}
}
