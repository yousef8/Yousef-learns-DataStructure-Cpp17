#include "../include/binary_tree.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

class TreeHeightBT : public BinaryTree<TreeHeightBT> {
  public:
	using BinaryTree<TreeHeightBT>::BinaryTree;

	int height() const {
		int h{0};

		if (left)
			h = 1 + left->height();

		if (right)
			h = std::max(h, 1 + right->height());

		return h;
	}
};

void test_tree_height() {
	// Test 1: Single node tree
	{
		TreeHeightBT root(1);
		assert(root.height() == 0);
		std::cout << "Test 1 passed: Single node\n";
	}

	// Test 2: Left-skewed tree
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'L'});
		root.add({2, 3, 4}, {'L', 'L', 'L'});
		assert(root.height() == 3);
		std::cout << "Test 2 passed: Left-skewed tree\n";
	}

	// Test 3: Right-skewed tree
	{
		TreeHeightBT root(1);
		root.add({2}, {'R'});
		root.add({2, 3}, {'R', 'R'});
		root.add({2, 3, 4}, {'R', 'R', 'R'});
		root.add({2, 3, 4, 5}, {'R', 'R', 'R', 'R'});
		assert(root.height() == 4);
		std::cout << "Test 3 passed: Right-skewed tree\n";
	}

	// Test 4: Balanced tree
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.height() == 2);
		std::cout << "Test 4 passed: Balanced tree\n";
	}

	// Test 5: Unbalanced tree (left-heavy)
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({2, 4, 6}, {'L', 'L', 'L'});
		root.add({2, 4, 7}, {'L', 'L', 'R'});
		assert(root.height() == 3);
		std::cout << "Test 5 passed: Unbalanced left-heavy\n";
	}

	// Test 6: Unbalanced tree (right-heavy)
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		root.add({3, 7, 8}, {'R', 'R', 'L'});
		root.add({3, 7, 9}, {'R', 'R', 'R'});
		root.add({3, 7, 9, 10}, {'R', 'R', 'R', 'L'});
		assert(root.height() == 4);
		std::cout << "Test 6 passed: Unbalanced right-heavy\n";
	}

	// Test 7: Two nodes (left child only)
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		assert(root.height() == 1);
		std::cout << "Test 7 passed: Two nodes left\n";
	}

	// Test 8: Two nodes (right child only)
	{
		TreeHeightBT root(1);
		root.add({2}, {'R'});
		assert(root.height() == 1);
		std::cout << "Test 8 passed: Two nodes right\n";
	}

	// Test 9: Three-level tree with missing nodes
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.height() == 2);
		std::cout << "Test 9 passed: Three-level with gaps\n";
	}

	// Test 10: Deep left chain
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'L'});
		root.add({2, 3, 4}, {'L', 'L', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6, 7}, {'L', 'L', 'L', 'L', 'L', 'L'});
		assert(root.height() == 6);
		std::cout << "Test 10 passed: Deep left chain\n";
	}

	// Test 11: Zigzag tree pattern
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'R'});
		root.add({2, 3, 4}, {'L', 'R', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
		assert(root.height() == 4);
		std::cout << "Test 11 passed: Zigzag pattern\n";
	}

	// Test 12: Complete binary tree (7 nodes)
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.height() == 2);
		std::cout << "Test 12 passed: Complete binary tree\n";
	}

	// Test 13: Large balanced tree (15 nodes)
	{
		TreeHeightBT root(1);
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
		assert(root.height() == 3);
		std::cout << "Test 13 passed: Large balanced tree\n";
	}

	// Test 14: Asymmetric tree structure
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 6, 8}, {'R', 'L', 'L'});
		root.add({3, 6, 8, 9}, {'R', 'L', 'L', 'R'});
		assert(root.height() == 4);
		std::cout << "Test 14 passed: Asymmetric tree\n";
	}

	// Test 15: Root with only right subtree
	{
		TreeHeightBT root(1);
		root.add({3}, {'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.height() == 2);
		std::cout << "Test 15 passed: Only right subtree\n";
	}

	// Test 16: Root with only left subtree
	{
		TreeHeightBT root(1);
		root.add({2}, {'L'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		assert(root.height() == 2);
		std::cout << "Test 16 passed: Only left subtree\n";
	}

	std::cout << "\nAll tests passed!\n";
}

int main() {
	test_tree_height();
	return 0;
}