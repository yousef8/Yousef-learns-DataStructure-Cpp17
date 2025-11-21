#include "../../include/test_suite.hpp"
#include "../include/binary_tree.hpp"

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

int main() {
	TestSuite<int> suite;

	suite.addTest(
		"Single node tree",
		[]() {
			CountLeafNodes root(1);
			return root.countLeafNodes();
		},
		1);

	suite.addTest(
		"Two nodes - left child",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			return root.countLeafNodes();
		},
		1);

	suite.addTest(
		"Two nodes - right child",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'R'});
			return root.countLeafNodes();
		},
		1);

	suite.addTest(
		"Three nodes - two leaves",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			return root.countLeafNodes();
		},
		2);

	suite.addTest(
		"Left-skewed tree",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			return root.countLeafNodes();
		},
		1);

	suite.addTest(
		"Right-skewed tree",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'R'});
			root.add({2, 3}, {'R', 'R'});
			root.add({2, 3, 4}, {'R', 'R', 'R'});
			root.add({2, 3, 4, 5}, {'R', 'R', 'R', 'R'});
			return root.countLeafNodes();
		},
		1);

	suite.addTest(
		"Complete binary tree (7 nodes)",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.countLeafNodes();
		},
		4);

	suite.addTest(
		"Large balanced tree (15 nodes)",
		[]() {
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
			return root.countLeafNodes();
		},
		8);

	suite.addTest(
		"Unbalanced tree - left heavy",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({2, 4, 6}, {'L', 'L', 'L'});
			root.add({2, 4, 7}, {'L', 'L', 'R'});
			return root.countLeafNodes();
		},
		4);

	suite.addTest(
		"Unbalanced tree - right heavy",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			root.add({3, 7, 8}, {'R', 'R', 'L'});
			root.add({3, 7, 9}, {'R', 'R', 'R'});
			return root.countLeafNodes();
		},
		4);

	suite.addTest(
		"Sparse tree with gaps",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.countLeafNodes();
		},
		2);

	suite.addTest(
		"Only left subtree",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			return root.countLeafNodes();
		},
		2);

	suite.addTest(
		"Only right subtree",
		[]() {
			CountLeafNodes root(1);
			root.add({3}, {'R'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 7}, {'R', 'R'});
			return root.countLeafNodes();
		},
		2);

	suite.addTest(
		"Zigzag pattern",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'R', 'L', 'R'});
			return root.countLeafNodes();
		},
		1);

	suite.addTest(
		"Partial children - left",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			return root.countLeafNodes();
		},
		2);

	suite.addTest(
		"Partial children - right",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({3, 7}, {'R', 'R'});
			return root.countLeafNodes();
		},
		2);

	suite.addTest(
		"Asymmetric tree",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({3, 6}, {'R', 'L'});
			root.add({3, 6, 8}, {'R', 'L', 'L'});
			root.add({3, 6, 8, 9}, {'R', 'L', 'L', 'R'});
			return root.countLeafNodes();
		},
		2);

	suite.addTest(
		"Deep chain",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'L'});
			root.add({2, 3, 4}, {'L', 'L', 'L'});
			root.add({2, 3, 4, 5}, {'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6}, {'L', 'L', 'L', 'L', 'L'});
			root.add({2, 3, 4, 5, 6, 7}, {'L', 'L', 'L', 'L', 'L', 'L'});
			return root.countLeafNodes();
		},
		1);

	suite.addTest(
		"Partial complete tree",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({3, 6}, {'R', 'L'});
			return root.countLeafNodes();
		},
		3);

	suite.addTest(
		"Tree with mixed depths",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({3}, {'R'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({2, 4, 8}, {'L', 'L', 'L'});
			root.add({2, 4, 9}, {'L', 'L', 'R'});
			return root.countLeafNodes();
		},
		4);

	suite.addTest(
		"One-sided with branches",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			root.add({2, 5, 10}, {'L', 'R', 'L'});
			root.add({2, 5, 11}, {'L', 'R', 'R'});
			return root.countLeafNodes();
		},
		3);

	suite.addTest(
		"Complex structure",
		[]() {
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
			return root.countLeafNodes();
		},
		4);

	suite.addTest(
		"Root with one child having two children",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({2, 4}, {'L', 'L'});
			root.add({2, 5}, {'L', 'R'});
			return root.countLeafNodes();
		},
		2);

	suite.addTest(
		"Maximum asymmetry",
		[]() {
			CountLeafNodes root(1);
			root.add({2}, {'L'});
			root.add({2, 3}, {'L', 'R'});
			root.add({2, 3, 4}, {'L', 'R', 'R'});
			root.add({2, 3, 4, 5}, {'L', 'R', 'R', 'L'});
			return root.countLeafNodes();
		},
		1);

	suite.addTest(
		"Course example",
		[]() {
			CountLeafNodes root(2);
			root.add({3}, {'L'});
			root.add({13}, {'R'});
			root.add({13, 7}, {'R', 'L'});
			root.add({13, 8}, {'R', 'R'});
			return root.countLeafNodes();
		},
		3);

	suite.run();
	return 0;
}
