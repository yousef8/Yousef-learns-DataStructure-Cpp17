#include "../../include/test_suite.hpp"
#include "../include/max_heap.hpp"
#include <sstream>
#include <vector>

class KthNumberProcessor {
  public:
	KthNumberProcessor(int k) : k(k), h(k) {}

	int next(int new_num) {
		if (!h.full()) {
			h.push(new_num);
			return h.top();
		}

		if (new_num < h.top()) {
			h.pop();
			h.push(new_num);
			return h.top();
		}

		return h.top();
	}

  private:
	MaxHeap h;
	int k;
};

int main() {

	TestSuite<std::vector<int>> ts;

	ts.setFormatter([](const std::vector<int> &v) {
		std::ostringstream oss;
		oss << "[";
		for (size_t i = 0; i < v.size(); ++i) {
			if (i)
				oss << ", ";
			oss << v[i];
		}
		oss << "]";
		return oss.str();
	});

	ts.addTest("kth_smallest_sequence",
			   [&]() -> std::vector<int> {
				   KthNumberProcessor processor(4);
				   std::vector<int> outputs;
				   for (int n : {9, 8, 7, 6, 5, 4, 10, 8, 3, 5, 15}) {
					   outputs.push_back(processor.next(n));
				   }
				   return outputs;
			   },
			   {9, 9, 9, 9, 8, 7, 7, 7, 6, 5, 5});

	ts.run();

	return 0;
}