#include "./include/array_queue.hpp"
#include <iostream>

class Last_K_numbers_sum_stream {
  public:
	Last_K_numbers_sum_stream(int k) : q(k), size(k) {
		for (int i = 0; i < k; ++i) {
			q.enqueue(0);
		}
	}

	int next(int value) {
		int removed = q.dequeue();
		q.enqueue(value);
		current_sum += value - removed;
		return current_sum;
	}

  private:
	Queue q;
	int size;
	int current_sum{0};
};

int main() {
	Last_K_numbers_sum_stream lks(4);

	int num;
	while (std::cin >> num)
		std::cout << lks.next(num) << "\n";

	return 0;
}
