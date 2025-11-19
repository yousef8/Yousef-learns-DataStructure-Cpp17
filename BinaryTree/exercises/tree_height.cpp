#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"
#include <algorithm>
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

int main() {
	TestSuite<int> suite;

	suite.addTest(
		"Single node",
		[]() {
			TreeHeightBT root(1);
			return root.height();
		},
		0);

	suite.addTest(
		"Left-skewed tree",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			return root.height();
		},
		3);

	suite.addTest(
		"Right-skewed tree",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'R'});
			root.add({2, 3, 4}, {'R', 'R', 'R'});
			root.add({2, 3, 4, 5}, {'R', 'R', 'R', 'R'});
			return root.height();
		},
		4);

	suite.addTest(
		"Balanced tree",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.height();
		},
		2);

	suite.addTest(
		"Unbalanced left-heavy",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({2, 4, 6}, {'L', 'L', 'L'});
			root.add({2, 4, 7}, {'L', 'L', 'R'});
			return root.height();
		},
		3);

	suite.addTest(
		"Unbalanced right-heavy",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			root.add({3, 7, 8}, {'R', 'R', 'L'});
			root.add({3, 7, 9}, {'R', 'R', 'R'});
			root.add({3, 7, 9, 10}, {'R', 'R', 'R', 'L'});
			return root.height();
		},
		4);

	suite.addTest(
		"Two nodes left",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			return root.height();
		},
		1);

	suite.addTest(
		"Two nodes right",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'R'});
			return root.height();
		},
		1);

	suite.addTest(
		"Three-level with gaps",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.height();
		},
		2);

	suite.addTest(
		"Deep left chain",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6, 7}, {'L', 'L', 'L', 'L', 'L', 'L'});
			return root.height();
		},
		6);

	suite.addTest(
		"Zigzag pattern",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
			return root.height();
		},
		4);

	suite.addTest(
		"Complete binary tree",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.height();
		},
		2);

	suite.addTest(
		"Large balanced tree",
		[]() {
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
			return root.height();
		},
		3);

	suite.addTest(
		"Asymmetric tree",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 6, 8}, {'R', 'L', 'L'});
			root.add({3, 6, 8, 9}, {'R', 'L', 'L', 'R'});
			return root.height();
		},
		4);

	suite.addTest(
		"Only right subtree",
		[]() {
			TreeHeightBT root(1);
			root.add({3}, {'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.height();
		},
		2);

	suite.addTest(
		"Only left subtree",
		[]() {
			TreeHeightBT root(1);
			root.add({2}, {'L'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			return root.height();
		},
		2);

	suite.run();
	return 0;
}