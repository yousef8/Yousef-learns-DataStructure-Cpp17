#include "../include/min_heap.hpp"
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <vector>

class MaxHeap {
  public:
	MaxHeap(int capacity = 1000) : heap(capacity) {}

	MaxHeap(std::initializer_list<int> vals) : heap(vals.size() + 1000) {
		for (int x : vals) {
			push(x);
		}
	}

	void push(int val) { heap.push(base - val); };

	int top() const { return base - heap.top(); };

	void pop() { heap.pop(); }

	bool empty() const { return heap.empty(); }

	void printTree() { heap.printTree(); }

  private:
	MinHeap heap;
	int base{1000};
};

int main() {
	MaxHeap heap{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

	heap.printTree();

	std::vector<int> v{};

	std::cout << "Popping all elements from the heap:\n";
	while (!heap.empty()) {
		std::cout << heap.top() << " ";
		v.push_back(heap.top());
		heap.pop();
	}
	std::cout << std::endl;

	bool isDesc = std::is_sorted(v.begin(), v.end(), std::greater<int>());

	std::cout << "Is Heap Sorted Desc: " << (isDesc ? "true" : "false")
			  << std::endl;

	return 0;
}