#include "../include/min_heap.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

class Solution : public MinHeap {
  public:
	using MinHeap::MinHeap;

	// ==========> My Solution with (n^2) time complexity <==========
	// static void heap_sort(int *arr, int sz) {
	// 	for (int i{0}; i < sz - 1; ++i) {
	// 		heapify(arr + i, sz - i);
	// 	}
	// }

	// ==========> Optimal Solution with (nlogn) time complexity <==========
	static void heap_sort(int *arr, int sz) {
		heapify(arr, sz);
		for (int i = sz - 1; i > 0; --i) {
			std::swap(arr[0], arr[i]);
			heapify_down(arr, i, 0);
		}
		reverse(arr, sz);
	}

	static void reverse(int *arr, int sz) {
		for (int i{0}; i < sz / 2; ++i) {
			std::swap(arr[i], arr[sz - 1 - i]);
		}
	}

  private:
	static void heapify(int *arr, int sz) {
		for (int i = sz / 2 - 1; i >= 0; --i) {
			heapify_down(arr, sz, i);
		}
	}

	static int left(int sz, int idx) {
		int i = 2 * idx + 1;
		return i >= sz ? -1 : i;
	}

	static int right(int sz, int idx) {
		int i = 2 * idx + 2;
		return i >= sz ? -1 : i;
	}

	static void heapify_down(int *arr, int sz, int idx) {
		int l = left(sz, idx);
		int r = right(sz, idx);

		if (l == -1)
			return;

		int smallest = l;

		if (r != -1 && arr[r] < arr[smallest])
			smallest = r;

		if (arr[idx] > arr[smallest]) {
			std::swap(arr[smallest], arr[idx]);
			heapify_down(arr, sz, smallest);
		}
	}
};

int main() {
	const int SZ = 14;
	int arr[SZ]{17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30, 2};

	Solution heap;
	heap.heap_sort(arr, SZ);

	assert(std::is_sorted(arr, arr + SZ));

	std::cout << "Array successfully sorted using heap sort:\n";
	for (int i{0}; i < SZ; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
