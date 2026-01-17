#include "../../include/test_suite.hpp"
#include "../include/bst.hpp"

class KthSmallestBST : public BST<KthSmallestBST> {
  public:
	using BST<KthSmallestBST>::BST;

	int kth_smallest(int &k) const {
		int idx = 0;
		return kth_smallest_helper(k, idx);
	}

  private:
	int kth_smallest_helper(int &k, int &idx) const {
		if (left) {
			int res = left->kth_smallest_helper(k, idx);
			if (res != -1234)
				return res;
		}

		++idx;

		if (idx == k)
			return data;

		if (right)
			return right->kth_smallest_helper(k, idx);

		return -1234;
	};
};

int main() {
	TestSuite<int> suite;

	suite.addTest(
		"Single node, k=1",
		[]() {
			KthSmallestBST tree(50);
			int k = 1;
			return tree.kth_smallest(k);
		},
		50);

	suite.addTest(
		"Single node, k=2 (out of bounds)",
		[]() {
			KthSmallestBST tree(50);
			int k = 2;
			return tree.kth_smallest(k);
		},
		-1234);

	suite.addTest(
		"Single node, k=0 (invalid)",
		[]() {
			KthSmallestBST tree(50);
			int k = 0;
			return tree.kth_smallest(k);
		},
		-1234);

	suite.addTest(
		"Single node, k=-1 (invalid)",
		[]() {
			KthSmallestBST tree(50);
			int k = -1;
			return tree.kth_smallest(k);
		},
		-1234);

	suite.addTest(
		"Balanced tree, k=1 (smallest)",
		[]() {
			KthSmallestBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(20);
			tree.insert(40);
			tree.insert(60);
			tree.insert(80);
			int k = 1;
			return tree.kth_smallest(k);
		},
		20);

	suite.addTest(
		"Balanced tree, k=4 (middle)",
		[]() {
			KthSmallestBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(20);
			tree.insert(40);
			tree.insert(60);
			tree.insert(80);
			int k = 4;
			return tree.kth_smallest(k);
		},
		50);

	suite.addTest(
		"Balanced tree, k=7 (largest)",
		[]() {
			KthSmallestBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(20);
			tree.insert(40);
			tree.insert(60);
			tree.insert(80);
			int k = 7;
			return tree.kth_smallest(k);
		},
		80);

	suite.addTest(
		"Balanced tree, k=8 (out of bounds)",
		[]() {
			KthSmallestBST tree(50);
			tree.insert(30);
			tree.insert(70);
			tree.insert(20);
			tree.insert(40);
			tree.insert(60);
			tree.insert(80);
			int k = 8;
			return tree.kth_smallest(k);
		},
		-1234);

	suite.addTest(
		"Left-skewed tree, k=3",
		[]() {
			KthSmallestBST tree(50);
			tree.insert(40);
			tree.insert(30);
			tree.insert(20);
			tree.insert(10);
			int k = 3;
			return tree.kth_smallest(k);
		},
		30);

	suite.addTest(
		"Right-skewed tree, k=2",
		[]() {
			KthSmallestBST tree(10);
			tree.insert(20);
			tree.insert(30);
			tree.insert(40);
			tree.insert(50);
			int k = 2;
			return tree.kth_smallest(k);
		},
		20);

	// Test 11: Right-skewed tree - k=1 (smallest)
	suite.addTest(
		"Right-skewed tree, k=1 (smallest)",
		[]() {
			KthSmallestBST tree(10);
			tree.insert(20);
			tree.insert(30);
			tree.insert(40);
			tree.insert(50);
			int k = 1;
			return tree.kth_smallest(k);
		},
		10);

	// Test 12: Right-skewed tree - k=last (largest)
	suite.addTest(
		"Right-skewed tree, k=5 (largest)",
		[]() {
			KthSmallestBST tree(10);
			tree.insert(20);
			tree.insert(30);
			tree.insert(40);
			tree.insert(50);
			int k = 5;
			return tree.kth_smallest(k);
		},
		50);

	// Test 13: Three nodes - k=2 (middle)
	suite.addTest(
		"Three nodes, k=2 (root)",
		[]() {
			KthSmallestBST tree(50);
			tree.insert(30);
			tree.insert(70);
			int k = 2;
			return tree.kth_smallest(k);
		},
		50);

	// Test 14: Larger tree - k at various positions
	suite.addTest(
		"Larger tree, k=5",
		[]() {
			KthSmallestBST tree(50);
			tree.insert(25);
			tree.insert(75);
			tree.insert(10);
			tree.insert(30);
			tree.insert(60);
			tree.insert(80);
			tree.insert(5);
			tree.insert(15);
			tree.insert(27);
			int k = 5;
			return tree.kth_smallest(k);
		},
		27);

	// Test 15: Verify k parameter remains unchanged
	suite.addTest(
		"Verify k remains unchanged",
		[]() {
			KthSmallestBST tree(50);
			tree.insert(30);
			tree.insert(70);
			int k = 2;
			tree.kth_smallest(k);
			return k; // Should still be 2
		},
		2);

	// Test 16: k way larger than tree size
	suite.addTest(
		"k=1000 on small tree",
		[]() {
			KthSmallestBST tree(50);
			tree.insert(30);
			tree.insert(70);
			int k = 1000;
			return tree.kth_smallest(k);
		},
		-1234);

	suite.run();

	return 0;
}
