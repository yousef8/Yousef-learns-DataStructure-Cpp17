#include "../include/min_heap.hpp"
#include <cassert>
#include <iostream>
#include <vector>

class Solution : public MinHeap {
  public:
	using MinHeap::MinHeap;

	std::vector<int> findSmallerValues(int val) {
		std::vector<int> smallerValues{};
		findSmallerValuesHelper(val, 0, smallerValues);
		return smallerValues;
	}

  private:
	void findSmallerValuesHelper(int val, int idx,
								 std::vector<int> &smallerValues) {
		if (idx == -1 || idx == size || arr[idx] >= val)
			return;

		smallerValues.push_back(arr[idx]);
		findSmallerValuesHelper(val, left(idx), smallerValues);
		findSmallerValuesHelper(val, right(idx), smallerValues);
	}
};

int main() {
	Solution heap{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

	heap.printTree();

	auto smallerValues = heap.findSmallerValues(10);

	assert(smallerValues.size() == 5);
	assert(smallerValues[0] == 2);
	assert(smallerValues[1] == 5);
	assert(smallerValues[2] == 7);
	assert(smallerValues[3] == 6);
	assert(smallerValues[4] == 8);

	std::cout << "Smaller values than 10: ";
	std::cout << "[ ";
	for (auto val : smallerValues) {
		std::cout << val << " ";
	}
	std::cout << "]\n";
	std::cout << "All tests passed!\n";

	return 0;
}
