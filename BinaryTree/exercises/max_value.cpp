#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <algorithm>

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

int main() {
	TestSuite<int> suite;

	suite.addTest(
		"Single node tree",
		[]() {
			MaxValueBT tree(10);
			return tree.max_value();
		},
		10);

	suite.addTest(
		"Tree with left children only",
		[]() {
			MaxValueBT tree(5);
			tree.add({10}, {'L'});
			tree.add({10, 15}, {'L', 'L'});
			return tree.max_value();
		},
		15);

	suite.addTest(
		"Tree with right children only",
		[]() {
			MaxValueBT tree(20);
			tree.add({25}, {'R'});
			tree.add({25, 30}, {'R', 'R'});
			return tree.max_value();
		},
		30);

	suite.addTest(
		"Balanced tree - max at root",
		[]() {
			MaxValueBT tree(100);
			tree.add({50}, {'L'});
			tree.add({75}, {'R'});
			tree.add({50, 25}, {'L', 'L'});
			tree.add({50, 60}, {'L', 'R'});
			return tree.max_value();
		},
		100);

	suite.addTest(
		"Max in left subtree",
		[]() {
			MaxValueBT tree(10);
			tree.add({15}, {'L'});
			tree.add({15, 99}, {'L', 'R'});
			tree.add({5}, {'R'});
			return tree.max_value();
		},
		99);

	suite.addTest(
		"Max in right subtree",
		[]() {
			MaxValueBT tree(10);
			tree.add({5}, {'L'});
			tree.add({20}, {'R'});
			tree.add({20, 150}, {'R', 'R'});
			return tree.max_value();
		},
		150);

	suite.addTest(
		"Complex tree structure",
		[]() {
			MaxValueBT tree(1);
			tree.add({2, 4, 7}, {'L', 'L', 'L'});
			tree.add({2, 4, 8}, {'L', 'L', 'R'});
			tree.add({2, 5, 9}, {'L', 'R', 'R'});
			tree.add({3, 6, 10}, {'R', 'R', 'L'});
			return tree.max_value();
		},
		10);

	suite.addTest(
		"Negative values only",
		[]() {
			MaxValueBT tree(-5);
			tree.add({-10}, {'L'});
			tree.add({-2}, {'R'});
			tree.add({-10, -15}, {'L', 'L'});
			return tree.max_value();
		},
		-2);

	suite.addTest(
		"Mix of positive and negative",
		[]() {
			MaxValueBT tree(-10);
			tree.add({-20}, {'L'});
			tree.add({5}, {'R'});
			tree.add({5, 3}, {'R', 'L'});
			return tree.max_value();
		},
		5);

	suite.addTest(
		"Course example",
		[]() {
			MaxValueBT tree(2);
			tree.add({3, 13, 7, 8}, {'L', 'R', 'L', 'R'});
			return tree.max_value();
		},
		13);

	suite.run();
	return 0;
}
