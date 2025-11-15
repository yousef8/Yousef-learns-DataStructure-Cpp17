#include "../include/binary_tree.hpp"
#include <cassert>
#include <iostream>

class NodesCountBT : public BinaryTree<NodesCountBT> {
  public:
	using BinaryTree<NodesCountBT>::BinaryTree;

	int countNodes() const {
		int count{1};

		if (left)
			count += left->countNodes();

		if (right)
			count += right->countNodes();

		return count;
	}
};

void test_count_nodes() {
	// Test 1: Single node tree
	{
		NodesCountBT root(1);
		assert(root.countNodes() == 1);
		std::cout << "Test 1 passed: Single node\n";
	}

	// Test 2: Two nodes (left child)
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		assert(root.countNodes() == 2);
		std::cout << "Test 2 passed: Two nodes left\n";
	}

	// Test 3: Two nodes (right child)
	{
		NodesCountBT root(1);
		root.add({2}, {'R'});
		assert(root.countNodes() == 2);
		std::cout << "Test 3 passed: Two nodes right\n";
	}

	// Test 4: Three nodes (both children)
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		assert(root.countNodes() == 3);
		std::cout << "Test 4 passed: Three nodes\n";
	}

	// Test 5: Left-skewed tree
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'L'});
		root.add({2, 3, 4}, {'L', 'L', 'L'});
		assert(root.countNodes() == 4);
		std::cout << "Test 5 passed: Left-skewed tree\n";
	}

	// Test 6: Right-skewed tree
	{
		NodesCountBT root(1);
		root.add({2}, {'R'});
		root.add({2, 3}, {'R', 'R'});
		root.add({2, 3, 4}, {'R', 'R', 'R'});
		root.add({2, 3, 4, 5}, {'R', 'R', 'R', 'R'});
		assert(root.countNodes() == 5);
		std::cout << "Test 6 passed: Right-skewed tree\n";
	}

	// Test 7: Complete binary tree (7 nodes)
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.countNodes() == 7);
		std::cout << "Test 7 passed: Complete binary tree\n";
	}

	// Test 8: Large balanced tree (15 nodes)
	{
		NodesCountBT root(1);
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
		assert(root.countNodes() == 15);
		std::cout << "Test 8 passed: Large balanced tree\n";
	}

	// Test 9: Unbalanced tree (left-heavy)
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({2, 4, 6}, {'L', 'L', 'L'});
		root.add({2, 4, 7}, {'L', 'L', 'R'});
		assert(root.countNodes() == 7);
		std::cout << "Test 9 passed: Unbalanced left-heavy\n";
	}

	// Test 10: Unbalanced tree (right-heavy)
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		root.add({3, 7, 8}, {'R', 'R', 'L'});
		root.add({3, 7, 9}, {'R', 'R', 'R'});
		assert(root.countNodes() == 7);
		std::cout << "Test 10 passed: Unbalanced right-heavy\n";
	}

	// Test 11: Sparse tree with gaps
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.countNodes() == 5);
		std::cout << "Test 11 passed: Sparse tree with gaps\n";
	}

	// Test 12: Only left subtree
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({2, 5, 10}, {'L', 'R', 'L'});
		assert(root.countNodes() == 5);
		std::cout << "Test 12 passed: Only left subtree\n";
	}

	// Test 13: Only right subtree
	{
		NodesCountBT root(1);
		root.add({3}, {'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		root.add({3, 7, 14}, {'R', 'R', 'L'});
		assert(root.countNodes() == 5);
		std::cout << "Test 13 passed: Only right subtree\n";
	}

	// Test 14: Zigzag pattern
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'R'});
		root.add({2, 3, 4}, {'L', 'R', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
		root.add({2, 3, 4, 5, 6}, {'L', 'R', 'L', 'R', 'L'});
		assert(root.countNodes() == 6);
		std::cout << "Test 14 passed: Zigzag pattern\n";
	}

	// Test 15: Deep chain (10 nodes)
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'L'});
		root.add({2, 3, 4}, {'L', 'L', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6, 7}, {'L', 'L', 'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6, 7, 8}, {'L', 'L', 'L', 'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6, 7, 8, 9},
				 {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6, 7, 8, 9, 10},
				 {'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L'});
		assert(root.countNodes() == 10);
		std::cout << "Test 15 passed: Deep chain\n";
	}

	// Test 16: Asymmetric tree
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 6, 8}, {'R', 'L', 'L'});
		root.add({3, 6, 8, 9}, {'R', 'L', 'L', 'R'});
		root.add({2, 4, 5}, {'L', 'L', 'R'});
		assert(root.countNodes() == 8);
		std::cout << "Test 16 passed: Asymmetric tree\n";
	}

	// Test 17: Partial complete tree (6 nodes)
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		assert(root.countNodes() == 6);
		std::cout << "Test 17 passed: Partial complete tree\n";
	}

	// Test 18: Complex structure (11 nodes)
	{
		NodesCountBT root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({2, 4, 8}, {'L', 'L', 'L'});
		root.add({2, 4, 9}, {'L', 'L', 'R'});
		root.add({2, 5, 10}, {'L', 'R', 'L'});
		root.add({3, 6, 12}, {'R', 'L', 'L'});
		root.add({3, 6, 12, 13}, {'R', 'L', 'L', 'R'});
		assert(root.countNodes() == 11);
		std::cout << "Test 18 passed: Complex structure\n";
	}

	std::cout << "\nAll tests passed!\n";
}

int main() {
	test_count_nodes();
	return 0;
}
