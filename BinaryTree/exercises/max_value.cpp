#include "../include/binary_tree.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

class MaxValueBT : public BinaryTree<MaxValueBT> {
  public:
	using BinaryTree<MaxValueBT>::BinaryTree;

	int max_value() const {
		int max_val{data};

		if (left) {
			max_val = std::max(max_val, left->max_value());
		}
		if (right) {
			max_val = std::max(max_val, right->max_value());
		}

		return max_val;
	}
};

void test_max_value() {
	// Test 1: Single node tree
	{
		MaxValueBT tree(10);
		assert(tree.max_value() == 10);
		std::cout << "Test 1 passed: Single node\n";
	}

	// Test 2: Tree with left children only
	{
		MaxValueBT tree(5);
		tree.add({10}, {'L'});
		tree.add({10, 15}, {'L', 'L'});
		assert(tree.max_value() == 15);
		std::cout << "Test 2 passed: Left children only\n";
	}

	// Test 3: Tree with right children only
	{
		MaxValueBT tree(20);
		tree.add({25}, {'R'});
		tree.add({25, 30}, {'R', 'R'});
		assert(tree.max_value() == 30);
		std::cout << "Test 3 passed: Right children only\n";
	}

	// Test 4: Balanced tree, max at root
	{
		MaxValueBT tree(100);
		tree.add({50}, {'L'});
		tree.add({75}, {'R'});
		tree.add({50, 25}, {'L', 'L'});
		tree.add({50, 60}, {'L', 'R'});
		assert(tree.max_value() == 100);
		std::cout << "Test 4 passed: Max at root\n";
	}

	// Test 5: Max in left subtree
	{
		MaxValueBT tree(10);
		tree.add({15}, {'L'});
		tree.add({15, 99}, {'L', 'R'});
		tree.add({5}, {'R'});
		assert(tree.max_value() == 99);
		std::cout << "Test 5 passed: Max in left subtree\n";
	}

	// Test 6: Max in right subtree
	{
		MaxValueBT tree(10);
		tree.add({5}, {'L'});
		tree.add({20}, {'R'});
		tree.add({20, 150}, {'R', 'R'});
		assert(tree.max_value() == 150);
		std::cout << "Test 6 passed: Max in right subtree\n";
	}

	// Test 7: Complex tree structure
	{
		MaxValueBT tree(1);
		tree.add({2, 4, 7}, {'L', 'L', 'L'});
		tree.add({2, 4, 8}, {'L', 'L', 'R'});
		tree.add({2, 5, 9}, {'L', 'R', 'R'});
		tree.add({3, 6, 10}, {'R', 'R', 'L'});
		assert(tree.max_value() == 10);
		std::cout << "Test 7 passed: Complex tree\n";
	}

	// Test 8: Negative values
	{
		MaxValueBT tree(-5);
		tree.add({-10}, {'L'});
		tree.add({-2}, {'R'});
		tree.add({-10, -15}, {'L', 'L'});
		assert(tree.max_value() == -2);
		std::cout << "Test 8 passed: Negative values\n";
	}

	// Test 9: Mix of positive and negative
	{
		MaxValueBT tree(-10);
		tree.add({-20}, {'L'});
		tree.add({5}, {'R'});
		tree.add({5, 3}, {'R', 'L'});
		assert(tree.max_value() == 5);
		std::cout << "Test 9 passed: Mixed positive/negative\n";
	}

	// Test 10: Course case
	{
		MaxValueBT tree(2);
		tree.add({3, 13, 7, 8}, {'L', 'R', 'L', 'R'});
		assert(tree.max_value() == 13);
		std::cout << "Test 10 passed: Course Example\n";
	}

	std::cout << "\nAll tests passed!\n";
}

int main() {
	test_max_value();
	return 0;
}
