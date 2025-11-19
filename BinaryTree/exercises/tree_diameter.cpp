#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <algorithm>
#include <utility>

class BinaryTreeDiameter : public BinaryTree<BinaryTreeDiameter> {
  public:
	using BinaryTree<BinaryTreeDiameter>::BinaryTree;

	std::pair<int, int> heightAndDiameter() const {
		auto left_pair = std::make_pair(0, 0); // height, diameter
		auto right_pair = std::make_pair(0, 0);

		if (left) {
			left_pair = left->heightAndDiameter();
		}

		if (right) {
			right_pair = right->heightAndDiameter();
		}

		int diameter = left_pair.first + right_pair.first;

		return {
			1 + std::max(left_pair.first, right_pair.first),
			std::max(diameter, std::max(left_pair.second, right_pair.second))};
	}

	int diameter() const { return heightAndDiameter().second; }
};

int main() {
	TestSuite<int> suite;

	// Test 1: Single node tree (diameter = 0)
	suite.addTest(
		"Single node tree",
		[]() {
			BinaryTreeDiameter tree(1);
			return tree.diameter();
		},
		0);

	// Test 2: Two nodes - left child only (diameter = 1)
	suite.addTest(
		"Two nodes - left child",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			return tree.diameter();
		},
		1);

	// Test 3: Two nodes - right child only (diameter = 1)
	suite.addTest(
		"Two nodes - right child",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'R'});
			return tree.diameter();
		},
		1);

	// Test 4: Three nodes - complete tree (diameter = 2, passes through root)
	suite.addTest(
		"Complete tree with 3 nodes",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			return tree.diameter();
		},
		2);

	// Test 5: Left skewed tree (diameter = 3)
	suite.addTest(
		"Left skewed tree (4 nodes)",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({2, 3}, {'L', 'L'});
			tree.add({2, 3, 4}, {'L', 'L', 'L'});
			return tree.diameter();
		},
		3);

	// Test 6: Right skewed tree (diameter = 3)
	suite.addTest(
		"Right skewed tree (4 nodes)",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'R'});
			tree.add({2, 3}, {'R', 'R'});
			tree.add({2, 3, 4}, {'R', 'R', 'R'});
			return tree.diameter();
		},
		3);

	// Test 7: Balanced tree where diameter passes through root
	suite.addTest(
		"Balanced tree - diameter through root",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			return tree.diameter();
		},
		4);

	// Test 8: Diameter NOT passing through root (in left subtree)
	suite.addTest(
		"Diameter in left subtree only",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({2, 4, 6}, {'L', 'L', 'L'});
			tree.add({2, 4, 7}, {'L', 'L', 'R'});
			tree.add({2, 5, 8}, {'L', 'R', 'L'});
			tree.add({2, 5, 9}, {'L', 'R', 'R'});
			return tree.diameter();
		},
		4);

	// Test 9: Diameter NOT passing through root (in right subtree)
	suite.addTest(
		"Diameter in right subtree only",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({3, 4}, {'R', 'L'});
			tree.add({3, 5}, {'R', 'R'});
			tree.add({3, 4, 6}, {'R', 'L', 'L'});
			tree.add({3, 4, 7}, {'R', 'L', 'R'});
			tree.add({3, 5, 8}, {'R', 'R', 'L'});
			tree.add({3, 5, 9}, {'R', 'R', 'R'});
			return tree.diameter();
		},
		4);

	// Test 10: Unbalanced tree - long left path, short right path
	suite.addTest(
		"Unbalanced - long left, short right",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 4, 5}, {'L', 'L', 'L'});
			tree.add({2, 4, 5, 6}, {'L', 'L', 'L', 'L'});
			return tree.diameter();
		},
		5);

	// Test 11: Complex tree with diameter = 7
	suite.addTest(
		"Complex tree with diameter 7",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({2, 4, 6}, {'L', 'L', 'L'});
			tree.add({2, 5, 7}, {'L', 'R', 'R'});
			tree.add({2, 5, 7, 8}, {'L', 'R', 'R', 'R'});
			tree.add({3, 9}, {'R', 'R'});
			tree.add({3, 9, 10}, {'R', 'R', 'R'});
			return tree.diameter();
		},
		7);

	// Test 12: Tree with only left children at each level
	suite.addTest(
		"Only left children chain",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({2, 3}, {'L', 'L'});
			tree.add({2, 3, 4}, {'L', 'L', 'L'});
			tree.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
			tree.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
			return tree.diameter();
		},
		5);

	// Test 13: Perfect binary tree of height 3
	suite.addTest(
		"Perfect binary tree height 3",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 5}, {'L', 'R'});
			tree.add({3, 6}, {'R', 'L'});
			tree.add({3, 7}, {'R', 'R'});
			tree.add({2, 4, 8}, {'L', 'L', 'L'});
			tree.add({2, 4, 9}, {'L', 'L', 'R'});
			tree.add({2, 5, 10}, {'L', 'R', 'L'});
			tree.add({2, 5, 11}, {'L', 'R', 'R'});
			tree.add({3, 6, 12}, {'R', 'L', 'L'});
			tree.add({3, 6, 13}, {'R', 'L', 'R'});
			tree.add({3, 7, 14}, {'R', 'R', 'L'});
			tree.add({3, 7, 15}, {'R', 'R', 'R'});
			return tree.diameter();
		},
		6);

	// Test 14: Diameter path between two leaf nodes in different subtrees
	suite.addTest(
		"Diameter between deep leaves",
		[]() {
			BinaryTreeDiameter tree(1);
			tree.add({2}, {'L'});
			tree.add({3}, {'R'});
			tree.add({2, 4}, {'L', 'L'});
			tree.add({2, 4, 5}, {'L', 'L', 'R'});
			tree.add({3, 6}, {'R', 'R'});
			tree.add({3, 6, 7}, {'R', 'R', 'L'});
			return tree.diameter();
		},
		6);

	suite.run();
	return 0;
}