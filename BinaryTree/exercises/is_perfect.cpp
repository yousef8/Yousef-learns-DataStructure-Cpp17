#include "../include/binary_tree.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

class PerfectBT : public BinaryTree<PerfectBT> {
  public:
	using BinaryTree<PerfectBT>::BinaryTree;

	int height() const {
		int h{0};

		if (left)
			h = 1 + left->height();

		if (right)
			h = std::max(h, 1 + right->height());

		return h;
	}

	bool isPerfect(int h = -1) const {
		if (h == -1) {
			h = height();
		}

		if (h == 0) {
			return true;
		}

		if (!left || !right) {
			return false;
		}

		return left->isPerfect(h - 1) && right->isPerfect(h - 1);
	}
};

void test_is_perfect() {
	// Test 1: Single node tree (perfect by definition)
	{
		PerfectBT root(1);
		assert(root.isPerfect() == true);
		std::cout << "Test 1 passed: Single node is perfect\n";
	}

	// Test 2: Two nodes - left child only (not perfect)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		assert(root.isPerfect() == false);
		std::cout << "Test 2 passed: Only left child not perfect\n";
	}

	// Test 3: Two nodes - right child only (not perfect)
	{
		PerfectBT root(1);
		root.add({2}, {'R'});
		assert(root.isPerfect() == false);
		std::cout << "Test 3 passed: Only right child not perfect\n";
	}

	// Test 4: Three nodes - perfect tree (height 1)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		assert(root.isPerfect() == true);
		std::cout << "Test 4 passed: Three nodes perfect\n";
	}

	// Test 5: Four nodes - missing one child (not perfect)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		assert(root.isPerfect() == false);
		std::cout << "Test 5 passed: Four nodes not perfect\n";
	}

	// Test 6: Perfect binary tree with 7 nodes (height 2)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.isPerfect() == true);
		std::cout << "Test 6 passed: Perfect tree 7 nodes\n";
	}

	// Test 7: Complete but not perfect (missing one leaf)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		assert(root.isPerfect() == false);
		std::cout << "Test 7 passed: Complete not perfect\n";
	}

	// Test 8: Perfect binary tree with 15 nodes (height 3)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		root.add({2, 4, 8}, {'L', 'L', 'L'});
		root.add({2, 4, 9}, {'L', 'L', 'R'});
		root.add({2, 5, 10}, {'L', 'R', 'L'});
		root.add({2, 5, 11}, {'L', 'R', 'R'});
		root.add({3, 6, 12}, {'R', 'L', 'L'});
		root.add({3, 6, 13}, {'R', 'L', 'R'});
		root.add({3, 7, 14}, {'R', 'R', 'L'});
		root.add({3, 7, 15}, {'R', 'R', 'R'});
		assert(root.isPerfect() == true);
		std::cout << "Test 8 passed: Perfect tree 15 nodes\n";
	}

	// Test 9: Almost perfect - missing one node at deepest level
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		root.add({2, 4, 8}, {'L', 'L', 'L'});
		root.add({2, 4, 9}, {'L', 'L', 'R'});
		root.add({2, 5, 10}, {'L', 'R', 'L'});
		root.add({2, 5, 11}, {'L', 'R', 'R'});
		root.add({3, 6, 12}, {'R', 'L', 'L'});
		root.add({3, 6, 13}, {'R', 'L', 'R'});
		root.add({3, 7, 14}, {'R', 'R', 'L'});
		// Missing node 15
		assert(root.isPerfect() == false);
		std::cout << "Test 9 passed: Almost perfect not perfect\n";
	}

	// Test 10: Left-skewed tree (not perfect)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'L'});
		root.add({2, 3, 4}, {'L', 'L', 'L'});
		assert(root.isPerfect() == false);
		std::cout << "Test 10 passed: Left-skewed not perfect\n";
	}

	// Test 11: Right-skewed tree (not perfect)
	{
		PerfectBT root(1);
		root.add({2}, {'R'});
		root.add({2, 3}, {'R', 'R'});
		root.add({2, 3, 4}, {'R', 'R', 'R'});
		assert(root.isPerfect() == false);
		std::cout << "Test 11 passed: Right-skewed not perfect\n";
	}

	// Test 12: Unbalanced tree (left heavier)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({2, 4, 6}, {'L', 'L', 'L'});
		root.add({2, 4, 7}, {'L', 'L', 'R'});
		assert(root.isPerfect() == false);
		std::cout << "Test 12 passed: Unbalanced left-heavy not perfect\n";
	}

	// Test 13: Unbalanced tree (right heavier)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		root.add({3, 7, 8}, {'R', 'R', 'L'});
		root.add({3, 7, 9}, {'R', 'R', 'R'});
		assert(root.isPerfect() == false);
		std::cout << "Test 13 passed: Unbalanced right-heavy not perfect\n";
	}

	// Test 14: Tree with only left subtree complete
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		assert(root.isPerfect() == false);
		std::cout << "Test 14 passed: Left subtree complete not perfect\n";
	}

	// Test 15: Tree with only right subtree complete
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.isPerfect() == false);
		std::cout << "Test 15 passed: Right subtree complete not perfect\n";
	}

	// Test 16: Sparse tree with gaps
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.isPerfect() == false);
		std::cout << "Test 16 passed: Sparse tree not perfect\n";
	}

	// Test 17: Zigzag pattern (not perfect)
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'R'});
		root.add({2, 3, 4}, {'L', 'R', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
		assert(root.isPerfect() == false);
		std::cout << "Test 17 passed: Zigzag not perfect\n";
	}

	// Test 18: Five nodes - one subtree deeper
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		assert(root.isPerfect() == false);
		std::cout << "Test 18 passed: Five nodes not perfect\n";
	}

	// Test 19: Six nodes - missing two at same level
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		assert(root.isPerfect() == false);
		std::cout << "Test 19 passed: Six nodes not perfect\n";
	}

	// Test 20: Asymmetric depths
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 6, 8}, {'R', 'L', 'L'});
		assert(root.isPerfect() == false);
		std::cout << "Test 20 passed: Asymmetric depths not perfect\n";
	}

	// Test 21: Perfect tree with 31 nodes (height 4)
	{
		PerfectBT root(1);
		// Level 1
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		// Level 2
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		// Level 3
		root.add({2, 4, 8}, {'L', 'L', 'L'});
		root.add({2, 4, 9}, {'L', 'L', 'R'});
		root.add({2, 5, 10}, {'L', 'R', 'L'});
		root.add({2, 5, 11}, {'L', 'R', 'R'});
		root.add({3, 6, 12}, {'R', 'L', 'L'});
		root.add({3, 6, 13}, {'R', 'L', 'R'});
		root.add({3, 7, 14}, {'R', 'R', 'L'});
		root.add({3, 7, 15}, {'R', 'R', 'R'});
		// Level 4
		root.add({2, 4, 8, 16}, {'L', 'L', 'L', 'L'});
		root.add({2, 4, 8, 17}, {'L', 'L', 'L', 'R'});
		root.add({2, 4, 9, 18}, {'L', 'L', 'R', 'L'});
		root.add({2, 4, 9, 19}, {'L', 'L', 'R', 'R'});
		root.add({2, 5, 10, 20}, {'L', 'R', 'L', 'L'});
		root.add({2, 5, 10, 21}, {'L', 'R', 'L', 'R'});
		root.add({2, 5, 11, 22}, {'L', 'R', 'R', 'L'});
		root.add({2, 5, 11, 23}, {'L', 'R', 'R', 'R'});
		root.add({3, 6, 12, 24}, {'R', 'L', 'L', 'L'});
		root.add({3, 6, 12, 25}, {'R', 'L', 'L', 'R'});
		root.add({3, 6, 13, 26}, {'R', 'L', 'R', 'L'});
		root.add({3, 6, 13, 27}, {'R', 'L', 'R', 'R'});
		root.add({3, 7, 14, 28}, {'R', 'R', 'L', 'L'});
		root.add({3, 7, 14, 29}, {'R', 'R', 'L', 'R'});
		root.add({3, 7, 15, 30}, {'R', 'R', 'R', 'L'});
		root.add({3, 7, 15, 31}, {'R', 'R', 'R', 'R'});
		assert(root.isPerfect() == true);
		std::cout << "Test 21 passed: Perfect tree 31 nodes\n";
	}

	// Test 22: One node missing from perfect tree of 31 nodes
	{
		PerfectBT root(1);
		// Level 1
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		// Level 2
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		// Level 3
		root.add({2, 4, 8}, {'L', 'L', 'L'});
		root.add({2, 4, 9}, {'L', 'L', 'R'});
		root.add({2, 5, 10}, {'L', 'R', 'L'});
		root.add({2, 5, 11}, {'L', 'R', 'R'});
		root.add({3, 6, 12}, {'R', 'L', 'L'});
		root.add({3, 6, 13}, {'R', 'L', 'R'});
		root.add({3, 7, 14}, {'R', 'R', 'L'});
		root.add({3, 7, 15}, {'R', 'R', 'R'});
		// Level 4 - missing one node
		root.add({2, 4, 8, 16}, {'L', 'L', 'L', 'L'});
		root.add({2, 4, 8, 17}, {'L', 'L', 'L', 'R'});
		root.add({2, 4, 9, 18}, {'L', 'L', 'R', 'L'});
		root.add({2, 4, 9, 19}, {'L', 'L', 'R', 'R'});
		root.add({2, 5, 10, 20}, {'L', 'R', 'L', 'L'});
		root.add({2, 5, 10, 21}, {'L', 'R', 'L', 'R'});
		root.add({2, 5, 11, 22}, {'L', 'R', 'R', 'L'});
		root.add({2, 5, 11, 23}, {'L', 'R', 'R', 'R'});
		root.add({3, 6, 12, 24}, {'R', 'L', 'L', 'L'});
		root.add({3, 6, 12, 25}, {'R', 'L', 'L', 'R'});
		root.add({3, 6, 13, 26}, {'R', 'L', 'R', 'L'});
		root.add({3, 6, 13, 27}, {'R', 'L', 'R', 'R'});
		root.add({3, 7, 14, 28}, {'R', 'R', 'L', 'L'});
		root.add({3, 7, 14, 29}, {'R', 'R', 'L', 'R'});
		root.add({3, 7, 15, 30}, {'R', 'R', 'R', 'L'});
		// Missing node 31
		assert(root.isPerfect() == false);
		std::cout << "Test 22 passed: 31 nodes minus one not perfect\n";
	}

	// Test 23: Original test case from code
	{
		PerfectBT tree(2);
		tree.add({3}, {'L'});
		tree.add({13, 7}, {'R', 'L'});
		tree.add({13, 8}, {'R', 'R'});
		assert(tree.isPerfect() == false);
		std::cout << "Test 23 passed: Original test case\n";
	}

	// Test 24: Deep perfect tree (height 5, 63 nodes) - partial test
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		root.add({2, 4, 8}, {'L', 'L', 'L'});
		root.add({2, 4, 9}, {'L', 'L', 'R'});
		root.add({2, 5, 10}, {'L', 'R', 'L'});
		root.add({2, 5, 11}, {'L', 'R', 'R'});
		root.add({3, 6, 12}, {'R', 'L', 'L'});
		root.add({3, 6, 13}, {'R', 'L', 'R'});
		root.add({3, 7, 14}, {'R', 'R', 'L'});
		root.add({3, 7, 15}, {'R', 'R', 'R'});
		assert(root.isPerfect() == true);
		std::cout << "Test 24 passed: Tree up to height 3 is perfect\n";
	}

	// Test 25: Node with one grandchild
	{
		PerfectBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 4, 8}, {'L', 'L', 'L'});
		assert(root.isPerfect() == false);
		std::cout << "Test 25 passed: One grandchild not perfect\n";
	}

	std::cout << "\nAll tests passed!\n";
}

int main() {
	test_is_perfect();
	return 0;
}