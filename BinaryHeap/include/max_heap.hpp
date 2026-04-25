#ifndef MAX_HEAP_20260418_HPP
#define MAX_HEAP_20260418_HPP

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>

class MaxHeap {
  public:
	MaxHeap(int capacity = 1000)
		: size(0), capacity(capacity), arr(new int[capacity]) {}

	MaxHeap(std::initializer_list<int> values) : MaxHeap(values.size() + 1000) {
		size = values.size();
		std::copy(values.begin(), values.end(), arr);
		heapify();
	}

	void push(int val) {
		if (full())
			throw std::overflow_error("Heap is full");
		arr[size++] = val;
		heapify_up(size - 1);
	}

	void pop() {
		if (empty())
			throw std::underflow_error("Heap is empty");
		arr[0] = arr[--size];
		heapify_down(0);
	}

	int top() const {
		if (empty())
			throw std::underflow_error("Heap is empty");
		return arr[0];
	}

	bool empty() const { return size == 0; }

	bool full() const { return size == capacity; }

	bool isValidMaxHeap() const {
		for (int i = 0; i <= (size - 2) / 2; i++) {
			if (arr[2 * i + 1] > arr[i])
				return false;

			if (2 * i + 2 < size && arr[2 * i + 2] > arr[i])
				return false;
		}
		return true;
	}

	std::string to_string() const {
		if (empty()) {
			return "(empty heap)";
		}

		std::string result{};
		for (int i = 0; i < size; ++i) {
			result += std::to_string(arr[i]) + " ";
		}

		result.pop_back();

		return result;
	}

	void printTree(std::ostream &out = std::cout) const {
		if (empty()) {
			out << "(empty heap)\n";
			return;
		}

		out << "MaxHeap (size=" << size << ")\n";
		out << arr[0] << "\n";

		int l = left(0);
		int r = right(0);

		if (l != -1)
			print_subtree(l, "", r == -1, out);
		if (r != -1)
			print_subtree(r, "", true, out);
	}

	~MaxHeap() { delete[] arr; }

  protected:
	int *arr{};
	int capacity{};
	int size{};

	int left(int idx) const {
		int i = 2 * idx + 1;
		return i >= size ? -1 : i;
	}

	int right(int idx) const {
		int i = 2 * idx + 2;
		return i >= size ? -1 : i;
	}

	int parent(int idx) const { return idx == 0 ? -1 : (idx - 1) / 2; }

	void heapify_up(int idx) { // O(logn)
		int p = parent(idx);
		if (p != -1 && arr[p] < arr[idx]) {
			std::swap(arr[p], arr[idx]);
			heapify_up(p);
		}
	}

	void heapify_down(int idx) { // O(logn)
		int l = left(idx);
		int r = right(idx);

		if (l == -1)
			return;

		int largest = l;

		if (r != -1 && arr[r] > arr[largest])
			largest = r;

		if (arr[idx] < arr[largest]) {
			std::swap(arr[largest], arr[idx]);
			heapify_down(largest);
		}
	}

	void heapify() { // O(n)
		for (int i = size / 2 - 1; i >= 0; --i) {
			heapify_down(i);
		}
	}

	void print_subtree(int idx, const std::string &prefix, bool is_last,
					   std::ostream &out) const {
		out << prefix << (is_last ? "`-- " : "|-- ") << arr[idx] << "\n";

		int l = left(idx);
		int r = right(idx);

		if (l == -1)
			return;

		std::string next_prefix = prefix + (is_last ? "    " : "|   ");

		if (l != -1)
			print_subtree(l, next_prefix, r == -1, out);
		if (r != -1)
			print_subtree(r, next_prefix, true, out);
	}
};

#endif // MIN_HEAP_20260418_HPP
