#include "./include/max_heap.hpp"
#include <cassert>
#include <iostream>
#include <vector>

void create_heap_nlogn() {
	MaxHeap heap;

	std::vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

	for (int i = 0; i < v.size(); ++i)
		heap.push(v[i]);

	assert(heap.isValidMaxHeap() == true);

	std::cout
		<< "Heap successfully created using O(n log n) method and asserted:\n";
	heap.printTree();
}

void create_heap_n() {
	MaxHeap heap{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

	assert(heap.isValidMaxHeap() == true);

	std::cout << "Heap successfully created using O(n) method and asserted:\n";
	heap.printTree();
}

int main() {
	create_heap_nlogn();
	create_heap_n();

	return 0;
}