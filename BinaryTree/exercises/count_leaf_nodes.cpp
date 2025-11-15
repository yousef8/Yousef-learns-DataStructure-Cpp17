#include "../include/binary_tree.hpp"
#include <cassert>
#include <iostream>

class CountLeafNodes : public BinaryTree<CountLeafNodes> {

  public:
	using BinaryTree<CountLeafNodes>::BinaryTree;

	int countLeafNodes() {
		int count{0};

		if (left)
			count += left->countLeafNodes();

		if (right)
			count += right->countLeafNodes();

		if (!left && !right)
			return 1;

		return count;
	}
};

void test_count_leaf_nodes() {
	// Test 1: Single node tree (root is a leaf)
	{
		CountLeafNodes root(1);
		assert(root.countLeafNodes() == 1);
		std::cout << "Test 1 passed: Single node\n";
	}

	// Test 2: Two nodes (left child is leaf)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		assert(root.countLeafNodes() == 1);
		std::cout << "Test 2 passed: Two nodes left\n";
	}

	// Test 3: Two nodes (right child is leaf)
	{
		CountLeafNodes root(1);
		root.add({2}, {'R'});
		assert(root.countLeafNodes() == 1);
		std::cout << "Test 3 passed: Two nodes right\n";
	}

	// Test 4: Three nodes (two leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		assert(root.countLeafNodes() == 2);
		std::cout << "Test 4 passed: Three nodes - two leaves\n";
	}

	// Test 5: Left-skewed tree (one leaf at bottom)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'L'});
		root.add({2, 3, 4}, {'L', 'L', 'L'});
		assert(root.countLeafNodes() == 1);
		std::cout << "Test 5 passed: Left-skewed tree\n";
	}

	// Test 6: Right-skewed tree (one leaf at bottom)
	{
		CountLeafNodes root(1);
		root.add({2}, {'R'});
		root.add({2, 3}, {'R', 'R'});
		root.add({2, 3, 4}, {'R', 'R', 'R'});
		root.add({2, 3, 4, 5}, {'R', 'R', 'R', 'R'});
		assert(root.countLeafNodes() == 1);
		std::cout << "Test 6 passed: Right-skewed tree\n";
	}

	// Test 7: Complete binary tree (4 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.countLeafNodes() == 4);
		std::cout << "Test 7 passed: Complete binary tree\n";
	}

	// Test 8: Large balanced tree (8 leaves)
	{
		CountLeafNodes root(1);
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
		assert(root.countLeafNodes() == 8);
		std::cout << "Test 8 passed: Large balanced tree\n";
	}

	// Test 9: Unbalanced tree (left-heavy, 4 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({2, 4, 6}, {'L', 'L', 'L'});
		root.add({2, 4, 7}, {'L', 'L', 'R'});
		assert(root.countLeafNodes() == 4);
		std::cout << "Test 9 passed: Unbalanced left-heavy\n";
	}

	// Test 10: Unbalanced tree (right-heavy, 4 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		root.add({3, 7, 8}, {'R', 'R', 'L'});
		root.add({3, 7, 9}, {'R', 'R', 'R'});
		assert(root.countLeafNodes() == 4);
		std::cout << "Test 10 passed: Unbalanced right-heavy\n";
	}

	// Test 11: Sparse tree with gaps (2 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.countLeafNodes() == 2);
		std::cout << "Test 11 passed: Sparse tree with gaps\n";
	}

	// Test 12: Only left subtree (2 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		assert(root.countLeafNodes() == 2);
		std::cout << "Test 12 passed: Only left subtree\n";
	}

	// Test 13: Only right subtree (2 leaves)
	{
		CountLeafNodes root(1);
		root.add({3}, {'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 7}, {'R', 'R'});
		assert(root.countLeafNodes() == 2);
		std::cout << "Test 13 passed: Only right subtree\n";
	}

	// Test 14: Zigzag pattern (1 leaf at bottom)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'R'});
		root.add({2, 3, 4}, {'L', 'R', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
		assert(root.countLeafNodes() == 1);
		std::cout << "Test 14 passed: Zigzag pattern\n";
	}

	// Test 15: Tree with one internal node having only left child
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		// Node 3 is a leaf, node 4 is a leaf
		assert(root.countLeafNodes() == 2);
		std::cout << "Test 15 passed: Partial children\n";
	}

	// Test 16: Tree with one internal node having only right child
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({3, 7}, {'R', 'R'});
		// Node 2 is a leaf, node 7 is a leaf
		assert(root.countLeafNodes() == 2);
		std::cout << "Test 16 passed: Partial children right\n";
	}

	// Test 17: Asymmetric tree (3 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({3, 6}, {'R', 'L'});
		root.add({3, 6, 8}, {'R', 'L', 'L'});
		root.add({3, 6, 8, 9}, {'R', 'L', 'L', 'R'});
		// Leaves: 4, 9
		assert(root.countLeafNodes() == 2);
		std::cout << "Test 17 passed: Asymmetric tree\n";
	}

	// Test 18: Deep chain (1 leaf)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'L'});
		root.add({2, 3, 4}, {'L', 'L', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6, 7}, {'L', 'L', 'L', 'L', 'L', 'L'});
		assert(root.countLeafNodes() == 1);
		std::cout << "Test 18 passed: Deep chain\n";
	}

	// Test 19: Partial complete tree (3 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		// Leaves: 4, 5, 6
		assert(root.countLeafNodes() == 3);
		std::cout << "Test 19 passed: Partial complete tree\n";
	}

	// Test 20: Tree with mixed depths (4 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({2, 4, 8}, {'L', 'L', 'L'});
		root.add({2, 4, 9}, {'L', 'L', 'R'});
		// Leaves: 8, 9, 5, 3
		assert(root.countLeafNodes() == 4);
		std::cout << "Test 20 passed: Mixed depths\n";
	}

	// Test 21: All nodes on one side at different levels (3 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({2, 5, 10}, {'L', 'R', 'L'});
		root.add({2, 5, 11}, {'L', 'R', 'R'});
		// Leaves: 4, 10, 11
		assert(root.countLeafNodes() == 3);
		std::cout << "Test 21 passed: One-sided with branches\n";
	}

	// Test 22: Complex structure with many internal nodes (5 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({3}, {'R'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		root.add({3, 6}, {'R', 'L'});
		root.add({2, 4, 8}, {'L', 'L', 'L'});
		root.add({2, 4, 9}, {'L', 'L', 'R'});
		root.add({3, 6, 12}, {'R', 'L', 'L'});
		root.add({3, 6, 12, 13}, {'R', 'L', 'L', 'R'});
		// Leaves: 8, 9, 5, 13
		assert(root.countLeafNodes() == 4);
		std::cout << "Test 22 passed: Complex structure\n";
	}

	// Test 23: Tree where root has one child which has two children
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({2, 4}, {'L', 'L'});
		root.add({2, 5}, {'L', 'R'});
		// Leaves: 4, 5
		assert(root.countLeafNodes() == 2);
		std::cout
			<< "Test 23 passed: Root with one child having two children\n";
	}

	// Test 24: Maximum asymmetry (2 leaves)
	{
		CountLeafNodes root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'R'});
		root.add({2, 3, 4}, {'L', 'R', 'R'});
		root.add({2, 3, 4, 5}, {'L', 'R', 'R', 'L'});
		// Leaves: 5
		assert(root.countLeafNodes() == 1);
		std::cout << "Test 24 passed: Maximum asymmetry\n";
	}

	// Test 25: Course Example (3 leaves)
	{
		CountLeafNodes root(2);
		root.add({3}, {'L'});
		root.add({13}, {'R'});
		root.add({13, 7}, {'R', 'L'});
		root.add({13, 8}, {'R', 'R'});
		// Leaves: 3, 8, 13
		assert(root.countLeafNodes() == 3);
		std::cout << "Test 25 passed: Course Example\n";
	}

	std::cout << "\nAll tests passed!\n";
}

int main() {
	test_count_leaf_nodes();
	return 0;
}
