#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

class BuildBalancedBST : public BST<BuildBalancedBST> {
  public:
	using BST<BuildBalancedBST>::BST;

	BuildBalancedBST(int data, BuildBalancedBST *left = nullptr,
					 BuildBalancedBST *right = nullptr)
		: BST<BuildBalancedBST>(data) {
		this->left = left;
		this->right = right;
	}

	int height() const {
		int left_height = left ? left->height() : 0;
		int right_height = right ? right->height() : 0;
		return 1 + std::max(left_height, right_height);
	}

	bool is_balanced(int &height) const {
		int left_height = 0, right_height = 0;

		bool left_balanced = !left || left->is_balanced(left_height);
		bool right_balanced = !right || right->is_balanced(right_height);

		height = 1 + std::max(left_height, right_height);

		return left_balanced && right_balanced &&
			   std::abs(left_height - right_height) <= 1;
	}

	int count_nodes() const {
		int count = 1;
		if (left)
			count += left->count_nodes();
		if (right)
			count += right->count_nodes();
		return count;
	}

	// Helper to verify BST property
	bool is_valid_bst(int min_val, int max_val) const {
		if (data <= min_val || data >= max_val)
			return false;

		bool left_valid = !left || left->is_valid_bst(min_val, data);
		bool right_valid = !right || right->is_valid_bst(data, max_val);

		return left_valid && right_valid;
	}
};

BuildBalancedBST *build_balanced_bst(const std::vector<int> &values,
									 int st = -1, int end = -1) {
	if (values.empty())
		return nullptr;

	if (st == -1 && end == -1) {
		st = 0;
		end = values.size() - 1;
	}
	if (st > end)
		return nullptr;

	if (st == end)
		return new BuildBalancedBST(values[st]);

	const int middle_idx = st + (end - st) / 2;

	auto left = build_balanced_bst(values, st, middle_idx - 1);
	auto right = build_balanced_bst(values, middle_idx + 1, end);

	return new BuildBalancedBST(values[middle_idx], left, right);
}

struct TestResult {
	bool passed;
	std::string message;

	bool operator==(const TestResult &other) const {
		return passed == other.passed;
	}
};

int main() {
	TestSuite<TestResult> ts;

	ts.setFormatter([](const TestResult &result) {
		return result.message + " (" + (result.passed ? "PASS" : "FAIL") + ")";
	});

	ts.addTest(
		"Empty vector returns nullptr",
		[]() {
			auto tree = build_balanced_bst({});
			bool is_null = (tree == nullptr);
			delete tree;
			return TestResult{is_null,
							  is_null ? "Correct nullptr" : "Expected nullptr"};
		},
		TestResult{true, "Correct nullptr"});

	ts.addTest(
		"Single element [5]",
		[]() {
			auto tree = build_balanced_bst({5});
			bool valid = tree != nullptr && tree->print_inorder() == "5 " &&
						 tree->count_nodes() == 1;
			delete tree;
			return TestResult{valid, valid ? "Single node tree created"
										   : "Failed single node"};
		},
		TestResult{true, "Single node tree created"});

	ts.addTest(
		"Two elements [1, 2]",
		[]() {
			auto tree = build_balanced_bst({1, 2});
			bool valid = tree != nullptr && tree->print_inorder() == "1 2 " &&
						 tree->count_nodes() == 2 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max());
			delete tree;
			return TestResult{valid, valid ? "Binary tree with 2 nodes"
										   : "Failed 2-node tree"};
		},
		TestResult{true, "Binary tree with 2 nodes"});

	ts.addTest(
		"Three elements [1, 2, 3]",
		[]() {
			auto tree = build_balanced_bst({1, 2, 3});
			int h = 0;
			bool valid = tree != nullptr && tree->print_inorder() == "1 2 3 " &&
						 tree->count_nodes() == 3 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max()) &&
						 tree->is_balanced(h) && tree->height() == 2;
			delete tree;
			return TestResult{valid, valid ? "Balanced 3-node tree"
										   : "Failed 3-node balance"};
		},
		TestResult{true, "Balanced 3-node tree"});

	ts.addTest(
		"Seven elements [1, 2, 3, 4, 5, 6, 7]",
		[]() {
			auto tree = build_balanced_bst({1, 2, 3, 4, 5, 6, 7});
			int h = 0;
			bool valid = tree != nullptr &&
						 tree->print_inorder() == "1 2 3 4 5 6 7 " &&
						 tree->count_nodes() == 7 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max()) &&
						 tree->is_balanced(h) && tree->height() == 3;
			delete tree;
			return TestResult{valid, valid ? "Balanced 7-node tree"
										   : "Failed 7-node balance"};
		},
		TestResult{true, "Balanced 7-node tree"});

	ts.addTest(
		"Fifteen elements [1-15]",
		[]() {
			std::vector<int> values;
			for (int i = 1; i <= 15; i++)
				values.push_back(i);
			auto tree = build_balanced_bst(values);
			int h = 0;
			bool valid = tree != nullptr && tree->count_nodes() == 15 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max()) &&
						 tree->is_balanced(h) && tree->height() == 4;
			delete tree;
			return TestResult{valid, valid ? "Balanced 15-node tree"
										   : "Failed 15-node balance"};
		},
		TestResult{true, "Balanced 15-node tree"});

	ts.addTest(
		"Five elements [10, 20, 30, 40, 50]",
		[]() {
			auto tree = build_balanced_bst({10, 20, 30, 40, 50});
			int h = 0;
			bool valid = tree != nullptr &&
						 tree->print_inorder() == "10 20 30 40 50 " &&
						 tree->count_nodes() == 5 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max()) &&
						 tree->is_balanced(h) && tree->height() <= 3;
			delete tree;
			return TestResult{valid, valid ? "Balanced 5-node tree"
										   : "Failed 5-node balance"};
		},
		TestResult{true, "Balanced 5-node tree"});

	ts.addTest(
		"Six elements [5, 10, 15, 20, 25, 30]",
		[]() {
			auto tree = build_balanced_bst({5, 10, 15, 20, 25, 30});
			int h = 0;
			bool valid = tree != nullptr &&
						 tree->print_inorder() == "5 10 15 20 25 30 " &&
						 tree->count_nodes() == 6 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max()) &&
						 tree->is_balanced(h) && tree->height() <= 3;
			delete tree;
			return TestResult{valid, valid ? "Balanced 6-node tree"
										   : "Failed 6-node balance"};
		},
		TestResult{true, "Balanced 6-node tree"});

	ts.addTest(
		"Negative numbers [-10, -5, 0, 5, 10]",
		[]() {
			auto tree = build_balanced_bst({-10, -5, 0, 5, 10});
			int h = 0;
			bool valid = tree != nullptr &&
						 tree->print_inorder() == "-10 -5 0 5 10 " &&
						 tree->count_nodes() == 5 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max()) &&
						 tree->is_balanced(h);
			delete tree;
			return TestResult{valid, valid ? "Handles negative numbers"
										   : "Failed negative numbers"};
		},
		TestResult{true, "Handles negative numbers"});

	ts.addTest(
		"Large gaps [1, 100, 200, 300, 400]",
		[]() {
			auto tree = build_balanced_bst({1, 100, 200, 300, 400});
			int h = 0;
			bool valid = tree != nullptr &&
						 tree->print_inorder() == "1 100 200 300 400 " &&
						 tree->count_nodes() == 5 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max()) &&
						 tree->is_balanced(h);
			delete tree;
			return TestResult{valid, valid ? "Handles large gaps"
										   : "Failed large gaps"};
		},
		TestResult{true, "Handles large gaps"});

	ts.addTest(
		"31 elements (perfect tree size)",
		[]() {
			std::vector<int> values;
			for (int i = 1; i <= 31; i++)
				values.push_back(i);
			auto tree = build_balanced_bst(values);
			int h = 0;
			bool valid = tree != nullptr && tree->count_nodes() == 31 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max()) &&
						 tree->is_balanced(h) && tree->height() == 5;
			delete tree;
			return TestResult{valid, valid ? "Perfect 31-node tree"
										   : "Failed 31-node tree"};
		},
		TestResult{true, "Perfect 31-node tree"});

	ts.addTest(
		"Ten elements [1-10]",
		[]() {
			std::vector<int> values;
			for (int i = 1; i <= 10; i++)
				values.push_back(i);
			auto tree = build_balanced_bst(values);
			int h = 0;
			bool valid = tree != nullptr && tree->count_nodes() == 10 &&
						 tree->is_valid_bst(std::numeric_limits<int>::min(),
											std::numeric_limits<int>::max()) &&
						 tree->is_balanced(h) && tree->height() <= 4;
			delete tree;
			return TestResult{valid, valid ? "Balanced 10-node tree"
										   : "Failed 10-node tree"};
		},
		TestResult{true, "Balanced 10-node tree"});

	ts.run();

	return 0;
}
