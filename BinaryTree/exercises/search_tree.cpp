#include "../include/binary_tree.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

class SearchTreeBT : public BinaryTree<SearchTreeBT> {
  public:
	using BinaryTree<SearchTreeBT>::BinaryTree;

	bool isExists(int value) const {
		if (data == value)
			return true;

		if (left && left->isExists(value))
			return true;

		if (right && right->isExists(value))
			return true;

		return false;
	}
};

void test_is_exists() {
	// Test 1: Single node - value exists (root)
	{
		SearchTreeBT root(10);
		assert(root.isExists(10) == true);
		std::cout << "Test 1 passed: Single node exists\n";
	}

	// Test 2: Single node - value does not exist
	{
		SearchTreeBT root(10);
		assert(root.isExists(5) == false);
		std::cout << "Test 2 passed: Single node not exists\n";
	}

	// Test 3: Two nodes - value in root
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		assert(root.isExists(10) == true);
		std::cout << "Test 3 passed: Value in root\n";
	}

	// Test 4: Two nodes - value in left child
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		assert(root.isExists(5) == true);
		std::cout << "Test 4 passed: Value in left child\n";
	}

	// Test 5: Two nodes - value in right child
	{
		SearchTreeBT root(10);
		root.add({15}, {'R'});
		assert(root.isExists(15) == true);
		std::cout << "Test 5 passed: Value in right child\n";
	}

	// Test 6: Two nodes - value does not exist
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		assert(root.isExists(20) == false);
		std::cout << "Test 6 passed: Two nodes not exists\n";
	}

	// Test 7: Three nodes - all values exist
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		root.add({15}, {'R'});
		assert(root.isExists(10) == true);
		assert(root.isExists(5) == true);
		assert(root.isExists(15) == true);
		std::cout << "Test 7 passed: Three nodes all exist\n";
	}

	// Test 8: Three nodes - value does not exist
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		root.add({15}, {'R'});
		assert(root.isExists(20) == false);
		assert(root.isExists(1) == false);
		std::cout << "Test 8 passed: Three nodes not exists\n";
	}

	// Test 9: Left-skewed tree - value at bottom
	{
		SearchTreeBT root(10);
		root.add({8}, {'L'});
		root.add({8, 6}, {'L', 'L'});
		root.add({8, 6, 4}, {'L', 'L', 'L'});
		assert(root.isExists(4) == true);
		std::cout << "Test 9 passed: Left-skewed value at bottom\n";
	}

	// Test 10: Left-skewed tree - value in middle
	{
		SearchTreeBT root(10);
		root.add({8}, {'L'});
		root.add({8, 6}, {'L', 'L'});
		root.add({8, 6, 4}, {'L', 'L', 'L'});
		assert(root.isExists(6) == true);
		std::cout << "Test 10 passed: Left-skewed value in middle\n";
	}

	// Test 11: Left-skewed tree - value does not exist
	{
		SearchTreeBT root(10);
		root.add({8}, {'L'});
		root.add({8, 6}, {'L', 'L'});
		root.add({8, 6, 4}, {'L', 'L', 'L'});
		assert(root.isExists(5) == false);
		std::cout << "Test 11 passed: Left-skewed not exists\n";
	}

	// Test 12: Right-skewed tree - value at bottom
	{
		SearchTreeBT root(10);
		root.add({12}, {'R'});
		root.add({12, 14}, {'R', 'R'});
		root.add({12, 14, 16}, {'R', 'R', 'R'});
		assert(root.isExists(16) == true);
		std::cout << "Test 12 passed: Right-skewed value at bottom\n";
	}

	// Test 13: Right-skewed tree - value does not exist
	{
		SearchTreeBT root(10);
		root.add({12}, {'R'});
		root.add({12, 14}, {'R', 'R'});
		root.add({12, 14, 16}, {'R', 'R', 'R'});
		assert(root.isExists(15) == false);
		std::cout << "Test 13 passed: Right-skewed not exists\n";
	}

	// Test 14: Complete binary tree - all values exist
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		root.add({15}, {'R'});
		root.add({5, 3}, {'L', 'L'});
		root.add({5, 7}, {'L', 'R'});
		root.add({15, 12}, {'R', 'L'});
		root.add({15, 20}, {'R', 'R'});
		assert(root.isExists(10) == true);
		assert(root.isExists(3) == true);
		assert(root.isExists(7) == true);
		assert(root.isExists(12) == true);
		assert(root.isExists(20) == true);
		std::cout << "Test 14 passed: Complete tree all exist\n";
	}

	// Test 15: Complete binary tree - value does not exist
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		root.add({15}, {'R'});
		root.add({5, 3}, {'L', 'L'});
		root.add({5, 7}, {'L', 'R'});
		root.add({15, 12}, {'R', 'L'});
		root.add({15, 20}, {'R', 'R'});
		assert(root.isExists(1) == false);
		assert(root.isExists(25) == false);
		assert(root.isExists(11) == false);
		std::cout << "Test 15 passed: Complete tree not exists\n";
	}

	// Test 16: Search for negative values
	{
		SearchTreeBT root(0);
		root.add({-5}, {'L'});
		root.add({5}, {'R'});
		root.add({-5, -10}, {'L', 'L'});
		assert(root.isExists(-5) == true);
		assert(root.isExists(-10) == true);
		assert(root.isExists(-3) == false);
		std::cout << "Test 16 passed: Negative values\n";
	}

	// Test 17: Search for zero
	{
		SearchTreeBT root(10);
		root.add({0}, {'L'});
		root.add({15}, {'R'});
		assert(root.isExists(0) == true);
		std::cout << "Test 17 passed: Zero value\n";
	}

	// Test 18: Large values
	{
		SearchTreeBT root(1000);
		root.add({500}, {'L'});
		root.add({2000}, {'R'});
		root.add({2000, 5000}, {'R', 'R'});
		assert(root.isExists(5000) == true);
		assert(root.isExists(3000) == false);
		std::cout << "Test 18 passed: Large values\n";
	}

	// Test 19: Deep tree - value at deepest level
	{
		SearchTreeBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'L'});
		root.add({2, 3, 4}, {'L', 'L', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
		assert(root.isExists(6) == true);
		std::cout << "Test 19 passed: Deep tree value at bottom\n";
	}

	// Test 20: Deep tree - value does not exist
	{
		SearchTreeBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'L'});
		root.add({2, 3, 4}, {'L', 'L', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
		root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
		assert(root.isExists(7) == false);
		std::cout << "Test 20 passed: Deep tree not exists\n";
	}

	// Test 21: Zigzag pattern - value exists
	{
		SearchTreeBT root(1);
		root.add({2}, {'L'});
		root.add({2, 3}, {'L', 'R'});
		root.add({2, 3, 4}, {'L', 'R', 'L'});
		root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
		assert(root.isExists(5) == true);
		assert(root.isExists(3) == true);
		std::cout << "Test 21 passed: Zigzag pattern exists\n";
	}

	// Test 22: Sparse tree with gaps - existing values
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		root.add({15}, {'R'});
		root.add({5, 2}, {'L', 'L'});
		root.add({15, 20}, {'R', 'R'});
		assert(root.isExists(2) == true);
		assert(root.isExists(20) == true);
		std::cout << "Test 22 passed: Sparse tree exists\n";
	}

	// Test 23: Sparse tree - non-existing in gaps
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		root.add({15}, {'R'});
		root.add({5, 2}, {'L', 'L'});
		root.add({15, 20}, {'R', 'R'});
		assert(root.isExists(7) == false);
		assert(root.isExists(12) == false);
		std::cout << "Test 23 passed: Sparse tree gaps not exists\n";
	}

	// Test 24: Duplicate values in tree
	{
		SearchTreeBT root(10);
		root.add({10}, {'L'});
		root.add({10}, {'R'});
		assert(root.isExists(10) == true);
		std::cout << "Test 24 passed: Duplicate values\n";
	}

	// Test 25: Only left subtree - existing values
	{
		SearchTreeBT root(20);
		root.add({10}, {'L'});
		root.add({10, 5}, {'L', 'L'});
		root.add({10, 15}, {'L', 'R'});
		assert(root.isExists(5) == true);
		assert(root.isExists(15) == true);
		std::cout << "Test 25 passed: Only left subtree exists\n";
	}

	// Test 26: Only left subtree - non-existing
	{
		SearchTreeBT root(20);
		root.add({10}, {'L'});
		root.add({10, 5}, {'L', 'L'});
		root.add({10, 15}, {'L', 'R'});
		assert(root.isExists(25) == false);
		assert(root.isExists(3) == false);
		std::cout << "Test 26 passed: Only left subtree not exists\n";
	}

	// Test 27: Only right subtree - existing values
	{
		SearchTreeBT root(10);
		root.add({20}, {'R'});
		root.add({20, 15}, {'R', 'L'});
		root.add({20, 25}, {'R', 'R'});
		assert(root.isExists(15) == true);
		assert(root.isExists(25) == true);
		std::cout << "Test 27 passed: Only right subtree exists\n";
	}

	// Test 28: Only right subtree - non-existing
	{
		SearchTreeBT root(10);
		root.add({20}, {'R'});
		root.add({20, 15}, {'R', 'L'});
		root.add({20, 25}, {'R', 'R'});
		assert(root.isExists(5) == false);
		assert(root.isExists(30) == false);
		std::cout << "Test 28 passed: Only right subtree not exists\n";
	}

	// Test 29: Asymmetric tree - search in deeper branch
	{
		SearchTreeBT root(10);
		root.add({5}, {'L'});
		root.add({15}, {'R'});
		root.add({5, 3}, {'L', 'L'});
		root.add({15, 12}, {'R', 'L'});
		root.add({15, 12, 11}, {'R', 'L', 'L'});
		root.add({15, 12, 11, 11}, {'R', 'L', 'L', 'R'});
		assert(root.isExists(11) == true);
		std::cout << "Test 29 passed: Asymmetric deeper branch\n";
	}

	// Test 30: Multiple searches on same tree
	{
		SearchTreeBT root(50);
		root.add({25}, {'L'});
		root.add({75}, {'R'});
		root.add({25, 10}, {'L', 'L'});
		root.add({25, 35}, {'L', 'R'});
		root.add({75, 60}, {'R', 'L'});
		root.add({75, 90}, {'R', 'R'});

		assert(root.isExists(50) == true);
		assert(root.isExists(25) == true);
		assert(root.isExists(75) == true);
		assert(root.isExists(10) == true);
		assert(root.isExists(35) == true);
		assert(root.isExists(60) == true);
		assert(root.isExists(90) == true);
		assert(root.isExists(100) == false);
		assert(root.isExists(5) == false);
		assert(root.isExists(40) == false);
		std::cout << "Test 30 passed: Multiple searches\n";
	}

	{
		SearchTreeBT root(2);
		root.add({3}, {'L'});
		root.add({13}, {'R'});
		root.add({13, 7}, {'R', 'L'});
		root.add({13, 8}, {'R', 'R'});

		assert(root.isExists(13) == true);
		assert(root.isExists(70) == false);
		std::cout << "Test 31 passed: Course Example\n";
	}

	std::cout << "\nAll tests passed!\n";
}

int main() {
	test_is_exists();
	return 0;
}
